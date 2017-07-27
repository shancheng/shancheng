# SQLite busy handler

SQLite doesn't support high concurrency. In case of a lot of concurrent access from multi-process or multi-thread, calling a SQLite r/w function is prone to hit the case that the database is locked by another process or thread. The default behavior is that the SQLite r/w function return SQLITE_BUSY immediately, and the caller should retry the call later.

Below is an example function. When the SQLite function returns SQLITE_BUSY, the caller sleep one second then retry. The sleep is required to optimize the CPU utilization, without the sleep, the CPU will be occupied by a lot of retries.

<pre>
bool Execute(const string& sql) {
  char* errmsg = NULL;
  while (true) {
    int status = sqlite3_exec(db_, sql.c_str(), NULL, NULL, &errmsg);
    if (status == SQLITE_OK) {
      return true;
    } else if (status == SQLITE_BUSY) {
      ++total_busycount;
      cerr << "Thread " << threadindex_ << ": failed to execute " << sql << " (" << errmsg << ")\n";
      sqlite3_free(errmsg);
      sleep(1);
    } else {
      cerr << "Thread " << threadindex_ << ": failed to execute " << sql << " (" << errmsg << ")\n";
      sqlite3_free(errmsg);
      return false;
    }
  }
  return false;
}
</pre>

In fact, the caller doesn't need to sleep explicitly, calling [sqlite3_busy_timeout](https://sqlite.org/c3ref/busy_timeout.html) before SQLite r/w functions will make SQLite automaticlly insert sleep between two sequential calls of a r/w function. It's safe to set a big timeout value. SQLite splits the big timeout value into many small timeout values. With the optimization, if the lock is available while the caller is waiting, the caller won't need to wait to timeout. See below code,

<pre>
1452  static int sqliteDefaultBusyCallback(
1453   void *ptr,               /* Database connection */
1454   int count                /* Number of times table has been busy */
1455  ){
1456  #if SQLITE_OS_WIN || HAVE_USLEEP
1457    static const u8 delays[] =
1458       { 1, 2, 5, 10, 15, 20, 25, 25,  25,  50,  50, 100 };
1459    static const u8 totals[] =
1460       { 0, 1, 3,  8, 18, 33, 53, 78, 103, 128, 178, 228 };
1461  # define NDELAY ArraySize(delays)
1462    sqlite3 *db = (sqlite3 *)ptr;
1463    int timeout = db->busyTimeout;
1464    int delay, prior;
1465
1466    assert( count>=0 );
1467    if( count < NDELAY ){
1468      delay = delays[count];
1469      prior = totals[count];
1470    }else{
1471      delay = delays[NDELAY-1];
1472      prior = totals[NDELAY-1] + delay*(count-(NDELAY-1));
1473    }
1474    if( prior + delay > timeout ){
1475      delay = timeout - prior;
1476      if( delay<=0 ) return 0;
1477    }
1478    sqlite3OsSleep(db->pVfs, delay*1000);
1479    return 1;
1480  #else
1481    sqlite3 *db = (sqlite3 *)ptr;
1482    int timeout = ((sqlite3 *)ptr)->busyTimeout;
1483    if( (count+1)*1000 > timeout ){
1484      return 0;
1485    }
1486    sqlite3OsSleep(db->pVfs, 1000000);
1487    return 1;
1488  #endif
1489  }
</pre>

Another alternative is set a busy hander by calling [sqlite3_busy_handler](https://sqlite.org/c3ref/busy_handler.html). If the busy callback returns 0, then no additional attempts are made to access the database and SQLITE_BUSY is returned to the application. If the callback returns non-zero, then another attempt is made to access the database and the cycle repeats.

