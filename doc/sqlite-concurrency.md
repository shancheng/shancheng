This document describes the technologies to concurrent access to a SQLite database. There are also some code analysis to reveal the low level implementations.

# Multi-process

See the official FAQ [Can multiple applications or multiple instances of the same application access a single database file at the same time?](http://www.sqlite.org/faq.html#q5)

Multiple processes can have the same database open at the same time. Multiple processes can be doing a SELECT at the same time. But only one process can be making changes to the database at any moment in time, however.

SQLite uses reader/writer locks to control access to the database. (Under Win95/98/ME which lacks support for reader/writer locks, a probabilistic simulation is used instead.) But use caution: this locking mechanism might not work correctly if the database file is kept on an NFS filesystem. This is because fcntl() file locking is broken on many NFS implementations. You should avoid putting SQLite database files on NFS if multiple processes might try to access the file at the same time. On Windows, Microsoft's documentation says that locking may not work under FAT filesystems if you are not running the Share.exe daemon. People who have a lot of experience with Windows tell me that file locking of network files is very buggy and is not dependable. If what they say is true, sharing an SQLite database between two or more Windows machines might cause unexpected problems.

We are aware of no other embedded SQL database engine that supports as much concurrency as SQLite. SQLite allows multiple processes to have the database file open at once, and for multiple processes to read the database at once. When any process wants to write, it must lock the entire database file for the duration of its update. But that normally only takes a few milliseconds. Other processes just wait on the writer to finish then continue about their business. Other embedded SQL database engines typically only allow a single process to connect to the database at once.

However, client/server database engines (such as PostgreSQL, MySQL, or Oracle) usually support a higher level of concurrency and allow multiple processes to be writing to the same database at the same time. This is possible in a client/server database because there is always a single well-controlled server process available to coordinate access. If your application has a need for a lot of concurrency, then you should consider using a client/server database. But experience suggests that most applications need much less concurrency than their designers imagine.

When SQLite tries to access a file that is locked by another process, the default behavior is to return SQLITE_BUSY. You can adjust this behavior from C code using the sqlite3_busy_handler() or sqlite3_busy_timeout() API functions.

## Code analysis

Multi-process concurrent control is implemented using **fcntl** on Linux/Unix, **LockFileEx/UnlockFileEx** on Windows, and [probabilistic locking](https://github.com/shancheng/shancheng/blob/master/doc/sqlite-concurrency.md) on Win95/98/ME.

See https://sqlite.org/lockingv3.html for more details

* UNLOCKED	No locks are held on the database. The database may be neither read nor written. Any internally cached data is considered suspect and subject to verification against the database file before being used. Other processes can read or write the database as their own locking states permit. This is the default state.
* SHARED	The database may be read but not written. Any number of processes can hold SHARED locks at the same time, hence there can be many simultaneous readers. But no other thread or process is allowed to write to the database file while one or more SHARED locks are active.
* RESERVED	A RESERVED lock means that the process is planning on writing to the database file at some point in the future but that it is currently just reading from the file. Only a single RESERVED lock may be active at one time, though multiple SHARED locks can coexist with a single RESERVED lock. RESERVED differs from PENDING in that new SHARED locks can be acquired while there is a RESERVED lock.
* PENDING	A PENDING lock means that the process holding the lock wants to write to the database as soon as possible and is just waiting on all current SHARED locks to clear so that it can get an * * EXCLUSIVE lock. No new SHARED locks are permitted against the database if a PENDING lock is active, though existing SHARED locks are allowed to continue.
* EXCLUSIVE	An EXCLUSIVE lock is needed in order to write to the database file. Only one EXCLUSIVE lock is allowed on the file and no other locks of any kind are allowed to coexist with an EXCLUSIVE lock. In order to maximize concurrency, SQLite works to minimize the amount of time that EXCLUSIVE locks are held.

# Multi-thread

See [Using SQLite In Multi-Threaded Applications](https://sqlite.org/threadsafe.html)

1 Overview

SQLite supports three different threading modes:

Single-thread. In this mode, all mutexes are disabled and SQLite is unsafe to use in more than a single thread at once.

Multi-thread. In this mode, SQLite can be safely used by multiple threads provided that no single database connection is used simultaneously in two or more threads.

Serialized. In serialized mode, SQLite can be safely used by multiple threads with no restriction.

The threading mode can be selected at compile-time (when the SQLite library is being compiled from source code) or at start-time (when the application that intends to use SQLite is initializing) or at run-time (when a new SQLite database connection is being created). Generally speaking, run-time overrides start-time and start-time overrides compile-time. Except, single-thread mode cannot be overridden once selected.

The default mode is serialized.

2 Compile-time selection of threading mode

Use the SQLITE_THREADSAFE compile-time parameter to selected the threading mode. If no SQLITE_THREADSAFE compile-time parameter is present, then serialized mode is used. This can be made explicit with -DSQLITE_THREADSAFE=1. With -DSQLITE_THREADSAFE=0 the threading mode is single-thread. With -DSQLITE_THREADSAFE=2 the threading mode is multi-thread.

The return value of the sqlite3_threadsafe() interface is determined by the compile-time threading mode selection. If single-thread mode is selected at compile-time, then sqlite3_threadsafe() returns false. If either the multi-thread or serialized modes are selected, then sqlite3_threadsafe() returns true. The sqlite3_threadsafe() interface predates the multi-thread mode and start-time and run-time mode selection and so is unable to distinguish between multi-thread and serialized mode nor is it able to report start-time or run-time mode changes.

If single-thread mode is selected at compile-time, then critical mutexing logic is omitted from the build and it is impossible to enable either multi-thread or serialized modes at start-time or run-time.

3 Start-time selection of threading mode

Assuming that the compile-time threading mode is not single-thread, then the threading mode can be changed during initialization using the sqlite3_config() interface. The SQLITE_CONFIG_SINGLETHREAD verb puts SQLite into single-thread mode, the SQLITE_CONFIG_MULTITHREAD verb sets multi-thread mode, and the SQLITE_CONFIG_SERIALIZED verb sets serialized mode.

4 Run-time selection of threading mode

If single-thread mode has not been selected at compile-time or start-time, then individual database connections can be created as either multi-thread or serialized. It is not possible to downgrade an individual database connection to single-thread mode. Nor is it possible to escalate an individual database connection if the compile-time or start-time mode is single-thread.

The threading mode for an individual database connection is determined by flags given as the third argument to sqlite3_open_v2(). The SQLITE_OPEN_NOMUTEX flag causes the database connection to be in the multi-thread mode and the SQLITE_OPEN_FULLMUTEX flag causes the connection to be in serialized mode. If neither flag is specified or if sqlite3_open() or sqlite3_open16() are used instead of sqlite3_open_v2(), then the default mode determined by the compile-time and start-time settings is used.

## Code analysis

### SQLITE_THREADSAFE=0

See below code, once SQLITE_THREADSAFE=0, the mutex operations are omitted. That's why if single-thread mode is selected at compile-time, it is impossible to enable either multi-thread or serialized modes at start-time or run-time.

```c++
#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex;
#endif
```

```c++
#if SQLITE_THREADSAFE
# include <pthread.h>
# define SQLITE_UNIX_THREADS 1
#endif
```

### SQLITE_THREADSAFE=1 and SQLITE_THREADSAFE=2 

SQLITE_THREADSAFE=1 means serialized mode, and -DSQLITE_THREADSAFE=2 means multi-thread mode.

In both modes, mutexes are used to protect critical resource. So what's the difference? See below code,

global.c
```c++
SQLITE_WSD struct Sqlite3Config sqlite3Config = {
   SQLITE_DEFAULT_MEMSTATUS,  /* bMemstat */
   1,                         /* bCoreMutex */
   SQLITE_THREADSAFE==1,      /* bFullMutex */
```

main.c
```c++
isThreadsafe = sqlite3GlobalConfig.bFullMutex;
...
if( isThreadsafe ){
  db->mutex = sqlite3MutexAlloc(SQLITE_MUTEX_RECURSIVE);
```

vdbeblob.c
```c++
148 sqlite3_mutex_enter(db->mutex); in sqlite3_blob_open() 
361 sqlite3_mutex_enter(db->mutex); in sqlite3_blob_close() 
388 sqlite3_mutex_enter(db->mutex); in blobReadWrite() 
486 sqlite3_mutex_enter(db->mutex); in sqlite3_blob_reopen()
```

If SQLITE_THREADSAFE=1, SQLite allocates a mutex for each connection and use the mutex to serialize the operations on the connection.

In fact, for SQLITE_THREADSAFE, there is no difference between 2 and any value other than 0 and 1, in which case, only access to the global resources are proteced by mutex, no per connection serialization, concurrently access a connection from multiple threads can cause errors.
