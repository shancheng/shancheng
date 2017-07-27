# Probabilistic locking in SQLite

In SQLite, a [reader/writer](https://en.wikipedia.org/wiki/Readers-writer_lock) lock mechanism is required to control the multi-process concurrent access to a database. It is implemented using **fcntl** on Linux/Unix, and **LockFileEx/UnlockFileEx** on most Windows. But on Win95/98/ME the functions are not available. So on Win95/98/ME, SQLite uses probabilistic locking to simulate the reader/writer lock.

The idea is that **using a exclusive locking pool to simulate a reader/writer lock**.

* Acquire writer lock means locking all locks in the pool
* Acquire reader lock means locking a random lock in the pool

Writer lock is exclusive with both writer lock and reader lock. But multiple readers can access the lock at the same time, though there is some probability to conflict.

A conflict does not cause error, just makes the concurrent capacity a bit lower. The conflict probabilty depends on pool size and the concurrent process count.

In the latest SQLite, the pool size (SHARED_SIZE) is 510, according to the [birthday attack](https://en.wikipedia.org/wiki/Birthday_attack) formula, the 26th has more than 50% probabilistic to conflict.
