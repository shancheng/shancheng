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

## Battery-Backed Write Cache (BBWC) & Flash-Based Write Cache (FBWC)

[DBA应该知道的RAID卡知识](https://blog.csdn.net/eurasiaxz/article/details/11355149)

BBWC即Battery Backed Write Cache（电池备份写高速缓存）用来提高服务器I/O性能。服务器合并，大量的多媒体程序，实时响应程序，以及大量的存储空间请求，这些东西使得磁盘I/O性能成为服务器系统中的一道瓶颈。减轻负担的一个办法是增加一个BBWC（电池备份写高速缓存）模块。


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

https://en.wikipedia.org/wiki/Data_deduplication

In computing, data deduplication is a specialized data compression technique for eliminating duplicate copies of repeating data. Related and somewhat synonymous terms are intelligent (data) compression and single-instance (data) storage. This technique is used to improve storage utilization and can also be applied to network data transfers to reduce the number of bytes that must be sent. In the deduplication process, unique chunks of data, or byte patterns, are identified and stored during a process of analysis. As the analysis continues, other chunks are compared to the stored copy and whenever a match occurs, the redundant chunk is replaced with a small reference that points to the stored chunk. Given that the same byte pattern may occur dozens, hundreds, or even thousands of times (the match frequency is dependent on the chunk size), the amount of data that must be stored or transferred can be greatly reduced.

## The applications that can benefit from data deduplicataion

Data backup

Email

NetDisk

## Implementation considerations

When to dedupe
- Post-process deduplication
- In-line Deduplication

Where to dedupe
- Source deduplication
- Target deduplication

Data format
- Content-agnostic data deduplication
- Content-aware data deduplication

Commercial deduplication implementations differ by their chunking methods and architectures.
- Chunking. In some systems, chunks are defined by physical layer constraints (e.g. 4KB block size in WAFL). In some systems only complete files are compared, which is called single-instance storage or SIS. The most intelligent (but CPU intensive) method to chunking is generally considered to be sliding-block. In sliding block, a window is passed along the file stream to seek out more naturally occurring internal file boundaries.
- Client backup deduplication. This is the process where the deduplication hash calculations are initially created on the source (client) machines. Files that have identical hashes to files already in the target device are not sent, the target device just creates appropriate internal links to reference the duplicated data. The benefit of this is that it avoids data being unnecessarily sent across the network thereby reducing traffic load.
- Primary storage and secondary storage. By definition, primary storage systems are designed for optimal performance, rather than lowest possible cost. The design criteria for these systems is to increase performance, at the expense of other considerations. Moreover, primary storage systems are much less tolerant of any operation that can negatively impact performance. Also by definition, secondary storage systems contain primarily duplicate, or secondary copies of data. These copies of data are typically not used for actual production operations and as a result are more tolerant of some performance degradation, in exchange for increased efficiency.

## Rolling hash

https://en.wikipedia.org/wiki/Rolling_hash

http://gsoc.cat-v.org/people/mjl/blog/2007/08/06/1_Rabin_fingerprints/

https://software.intel.com/en-us/articles/accelerate-data-deduplication-using-chunking-and-hashing-functions

## Convergent encryption

https://en.wikipedia.org/wiki/Convergent_encryption

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


# Hierarchical storage management

https://en.wikipedia.org/wiki/Hierarchical_storage_management

Hierarchical storage management (HSM) is a data storage technique that automatically moves data between high-cost and low-cost storage media. HSM systems exist because high-speed storage devices, such as solid state drive arrays, are more expensive (per byte stored) than slower devices, such as hard disk drives, optical discs and magnetic tape drives. While it would be ideal to have all data available on high-speed devices all the time, this is prohibitively expensive for many organizations. Instead, HSM systems store the bulk of the enterprise's data on slower devices, and then copy data to faster disk drives when needed. In effect, HSM turns the fast disk drives into caches for the slower mass storage devices. The HSM system monitors the way data is used and makes best guesses as to which data can safely be moved to slower devices and which data should stay on the fast devices.
