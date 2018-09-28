# Concepts

Database cluster:	A set of databases managed by an instance of DB server

Schema: Namespace in database

Tablespace: A logical storage unit

Segment: Sub unit of tablespace

Extent: A sequence of blocks

Block: The basic unit

###### Data type

Difference between BLOB and text
- BLOB is octet sequence
- Text has a property: character set

Character set

Collation: Determine how to compare two chars

###### GUID

Use GUID as key

http://www.sql-server-performance.com/2005/guid-performance/

http://stackoverflow.com/questions/45399/advantages-and-disadvantages-of-guid-uuid-database-keys

http://stackoverflow.com/questions/5949/whats-your-opinion-on-using-uuids-as-database-row-identifiers-particularly-in-w

http://stackoverflow.com/questions/412341/how-should-i-store-guid-in-mysql-tables

http://www.mysqlperformanceblog.com/2007/03/13/to-uuid-or-not-to-uuid/

SQLServer: NEWID()

Oracle: SYS_GUID()

MySQL: UUID()


# Transaction and concurrency control

https://en.wikipedia.org/wiki/Two-phase_commit_protocol

https://en.wikipedia.org/wiki/Three-phase_commit_protocol

Isolation and lock

Optimistic concurrency control

Isolation Level


# Index

https://en.wikipedia.org/wiki/B-tree

https://en.wikipedia.org/wiki/R-tree

http://postgis.net/docs/using_postgis_dbmanagement.html#gist_indexes


# Normalization

http://www.tonymarston.net/php-mysql/database-design.html
