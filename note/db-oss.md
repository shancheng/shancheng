# SQLite

https://www.sqlite.org/pragma.html#pragma_integrity_check

https://stackoverflow.com/questions/784173/what-are-the-performance-characteristics-of-sqlite-with-very-large-database-file

https://www.sqlite.org/formatchng.html


# MySQL

## Maintenance

###### Ubuntu

```
GRANT SHUTDOWN ON *.* TO debian-sys-maint@localhost IDENTIFIED BY '4KhQl4mxzAONT7ny';
GRANT SELECT ON mysql.user TO debian-sys-maint@localhost IDENTIFIED BY '4KhQl4mxzAONT7ny';
```

###### How to Reset the Root Password

http://dev.mysql.com/doc/refman/5.0/en/resetting-permissions.htm
```
UPDATE mysql.user SET Password=PASSWORD('MyNewPass') WHERE User='root';
FLUSH PRIVILEGES;
```

###### Force MySQL Encoding to UTF-8

Find and edit the file my.cnf on your database server. Add the following lines to the mysqld section:

```
[mysqld]
default-character-set=utf8
skip-character-set-client-handshake

Now if you restart MySQL, the encoding should default to UTF8.
```

## Integrity

[Verifying backup integrity with CHECK TABLES](http://www.mysqlperformanceblog.com/2012/02/01/verifying-backup-integrity-with-check-tables/)

mysqlbinlog --stop-date

## performance

淘宝内部分享：怎么跳出MySQL的10个大坑

淘宝内部分享：MySQL & MariaDB性能优化


# PostgreSQL

Don't use oid as key
- oid is generated automatically
- Could not recover the database from a dump file
- Could not replication the database


pg_clog < Oracle control file

pg_xlog = Oracle redo log


###### Windows

pg_ctl.exe runservice -N <service name> -D <data> -w

sc delete "postgresql-8.3" >nul 2>&1
