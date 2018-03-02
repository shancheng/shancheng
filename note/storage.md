# Hardware

http://en.wikipedia.org/wiki/Hard_disk_drive

http://en.wikipedia.org/wiki/Disk_drive_performance_characteristics

http://en.wikipedia.org/wiki/Solid-state_drive#Comparison_of_SSD_with_hard_disk_drives

http://en.wikipedia.org/wiki/IOPS

http://www.linuxvox.com/2009/10/how-fast-is-your-disk/

## Flash, Fusion and SSD

https://en.wikipedia.org/wiki/Flash_memory

https://en.wikipedia.org/wiki/Fusion-io

[Fusion-io软件定义存储：全闪存阵列DIY时代？](http://storage.chinabyte.com/18/12398018.shtml)

[浅析Fusion-IO和Intel SSD](http://www.cnblogs.com/jhj117/p/5780597.html)

https://serverfault.com/questions/523278/do-i-need-to-raid-fusion-io-cards


# Storage protocols

## iSCSI

https://en.wikipedia.org/wiki/ISCSI

https://en.wikipedia.org/wiki/LIO_(SCSI_target)

[在RHEL / CentOS 7上使用iSCSI目标/启动器创建集中安全存储](https://www.howtoing.com/create-centralized-secure-storage-using-iscsi-target-initiator/)

[Comparing Performance Between iSCSI, FCoE, and FC](http://en.community.dell.com/techcenter/storage/w/wiki/2722.comparing-performance-between-iscsi-fcoe-and-fc)

## Object storage

https://www.storagecraft.com/blog/storage-wars-file-block-object-storage/

http://www.enterprisestorageforum.com/storage-management/object-storage-vs.-file-storage.html


# Ceph

http://docs.ceph.com/docs/master/

http://docs.ceph.com/docs/master/architecture/#

https://www.supportsages.com/infinite-storage-scaling-using-ceph-part-1-introduction/

https://www.supportsages.com/ceph-part-2-philosophy-and-design/

https://www.supportsages.com/ceph-part-3-technical-architecture-and-components/

https://www.virtualtothecore.com/en/adventures-ceph-storage-part-1-introduction/

https://www.virtualtothecore.com/en/adventures-ceph-storage-part-2-architecture-dummies/

https://www.virtualtothecore.com/en/adventures-ceph-storage-part-3-design-nodes/


# Deduplication

## Rolling hash

https://en.wikipedia.org/wiki/Rolling_hash

http://gsoc.cat-v.org/people/mjl/blog/2007/08/06/1_Rabin_fingerprints/

https://software.intel.com/en-us/articles/accelerate-data-deduplication-using-chunking-and-hashing-functions

## Integrity check

https://www.emc.com/collateral/software/white-papers/h7219-data-domain-data-invul-arch-wp.pdf

## OpenDedup

http://opendedup.org/odd/

[OpenDedup documentation](http://opendedup.org/odd/documentation/)

[OpenDedup source code](https://github.com/opendedup/sdfs)

http://www.datishsystems.com/

### Third-party software

###### Guava

https://github.com/google/guava

Guava is a set of core libraries that includes new collection types (such as multimap and multiset), immutable collections, a graph library, functional types, an in-memory cache, and APIs/utilities for concurrency, I/O, hashing, primitives, reflection, string processing, and much more!

###### RocksDB

http://rocksdb.org/

A persistent key-value store for fast storage environments

RocksDB is an embeddable persistent key-value store for fast storage.

###### rabinfingerprint

https://github.com/themadcreator/rabinfingerprint

A Java implementation of the rabin fingerprinting method. (http://en.wikipedia.org/wiki/Rabin_fingerprint)

Optimized for use on a stream including a sliding window fingerprint.

Includes arbitrary-precision-polynomial hashing as well as very fast long-based hashing implementations, which are best for most hashing uses.

###### minio

https://minio.io

Minio is a distributed object storage server, written in Go and open sourced under Apache License Version 2.0

###### LIO

https://en.wikipedia.org/wiki/LIO_(SCSI_target)
