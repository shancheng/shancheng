# File types

Normal file

Directory file

Link file

Device file


# Filesystem types

swap, proc

ext2, ext3, ext4<br>
从ext2转换到ext3有以下理由：可用性、数据完整性、速度以及易于转化。

reiser, xfs, vxfs, jfs

FAT, VFAT, NTFS

NFS, GFS


# Clustered filesystems

http://en.wikipedia.org/wiki/Clustered_file_system

http://www.yolinux.com/TUTORIALS/LinuxClustersAndFileSystems.html


# Encrypted filesystems

## Linux

http://en.wikipedia.org/wiki/Dm-crypt

dm-crypt is a transparent disk encryption subsystem in Linux kernel. It is part of the device mapper infrastructure, and uses cryptographic routines from the kernel's Crypto API.

dm-crypt is implemented as a device mapper target and may be stacked on top of other device mapper transformations. It can thus encrypt whole disks (including removable media), partitions, software RAID volumes, logical volumes, as well as files. It appears as a block device, which can be used to back file systems, swap or an LVM physical volume.

cryptsetup

Operation | Command
--- | ---
Format | cryptsetup luksFormat DEVICE
Open | cryptsetup luksOpen DEVICE NAME
Make filesystem | mkfs.ext3 /dev/mapper/NAME
Mount | mount /dev/mapper/NAME /mnt
Unmount | umount /dev/mapper/NAME
Close | cryptsetup luksClose DEVICE


# FUSE

http://en.wikipedia.org/wiki/Filesystem_in_Userspace

http://www.ibm.com/developerworks/library/l-fuse/index.html

https://lastlog.de/misc/fuse-doc/doc/html/

[Write a filesystem with FUSE](https://engineering.facile.it/blog/eng/write-filesystem-fuse/)

[Writing a FUSE Filesystem: a Tutorial](https://www.cs.nmsu.edu/~pfeiffer/fuse-tutorial/)


# Filesystem performance

## I/O

Raw I/O

Buffered I/O

Direct I/O

* [Use Direct I/O to improve performance of your AIX applications](http://www.ibm.com/developerworks/aix/library/au-DirectIO.html)

## MPIO

http://www.brentozar.com/archive/2009/05/san-multipathing-part-1-what-are-paths/

http://www.brentozar.com/archive/2009/05/san-multipathing-part-2-what-multipathing-does/

http://i.dell.com/sites/content/business/solutions/brochures/zh/Documents/cb107-multi-path-io_cn.pdf


# Transaction

```
            flush     fsync
Application -----> OS -----> Hardware
```

http://www.postgresql.org/docs/9.1/static/runtime-config-wal.html#GUC-WAL-SYNC-METHOD

http://www.postgresql.org/docs/9.1/static/wal-reliability.html

[小议同步IO ：fsync与fdatasync](http://www.cnblogs.com/promise6522/archive/2012/05/27/2520028.html)

[Does a sequence of close()/re-open()/fsync() provide the same durability guarantees as fsync()/close()?](https://stackoverflow.com/questions/37288453/calling-fsync2-after-close2)
- after closing an FD, you lose all ways to enforce durability
- after an fsync() fails, you cannot call fsync() again in the hope that now your data would be written
- you must re-do/confirm all writing work if that happens

[PostgreSQL's handling of fsync() errors is unsafe and risks data loss at least on XFS](https://www.postgresql.org/message-id/flat/CAMsr%2BYHh%2B5Oq4xziwwoEfhoTZgr07vdGG%2Bhu%3D1adXx59aTeaoQ%40mail.gmail.com#CAMsr+YHh+5Oq4xziwwoEfhoTZgr07vdGG+hu=1adXx59aTeaoQ@mail.gmail.com)

[Writing programs to cope with I/O errors causing lost writes on Linux](https://stackoverflow.com/questions/42434872/writing-programs-to-cope-with-i-o-errors-causing-lost-writes-on-linux)


# Logical Volume Manager

https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux)

## Snapshot

http://www.tuxfixer.com/backup-and-restore-logical-volume-using-lvm-snapshot/

```
lvcreate --snapshot --name storage_snapshot -L 10G /dev/fedora/storage
umount /mnt
lvconvert --merge /dev/fedora/storage_snapshot
mount /dev/fedora/storage /mnt
```


# Resource

http://en.wikipedia.org/wiki/Comparison_of_file_systems

http://linux-xfs.sgi.com/projects/xfs/papers/xfs_white/xfs_white_paper.html

http://buffalo.nas-central.org/index.php/Using_XFS_instead_of_ext3_(network_performance_boost)

http://www.humboldt.co.uk/2009/03/fsync-across-platforms.html
