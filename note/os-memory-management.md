# Kernel parameters

###### How to adjust kernel maximum share memory size

/etc/sysctl.conf
```
kernel.shmmax=134217728
```

sysctl -w kernel.shmmax=134217728

###### min_free_bytes

https://stackoverflow.com/questions/21374491/vm-min-free-kbytes-why-keep-minimum-reserved-memory

###### numa_balancing

https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/virtualization_tuning_and_optimization_guide/sect-virtualization_tuning_optimization_guide-numa-auto_numa_balancing


# Memory allocation

###### Buddy memory allocation

https://en.wikipedia.org/wiki/Buddy_memory_allocation

###### Slab allocation

https://en.wikipedia.org/wiki/Slab_allocation

http://www.ibm.com/developerworks/cn/linux/l-linux-slab-allocator/index.html

###### STL allocator

http://zhanyonhu.blog.163.com/blog/static/16186044201461461751705/ stl的allocator替换为boost内存池后的问题


# Cache

###### Buffer cache

http://www.tldp.org/LDP/sag/html/buffer-cache.html

http://stackoverflow.com/questions/6345020/linux-memory-buffer-vs-cache

###### How to clear or drop the cache buffer pages from Linux memory

Introduction

Cache in Linux memory is where the Kernel stores the information it may need later, as memory is incredible faster than disk, it is great that the Linux Kernel takes care about that.

Anyway you can also manipulate how the cache behaves, there usually no need to do that, as Linux Operating system is very efficient in managing your computer memory, and will automatically free the RAM and drop the cache if some application needs memory.

Let’s see how to force Linux to drop the cache from memory.

drop_caches

Since Kernel 2.6.16, you can control how cache behaves, there are four possible “positions” for the switch.

0 -> Will give the Kernel full control to the cache memory 1 -> Will free the page cache 2 -> Will free dentries and inodes 3 -> Will free dentries and inodes as well as page cache
So, just enter those values to the file /proc/sys/vm/drop_caches, with echo, and as root:
sync; echo 0 > /proc/sys/vm/drop_caches

or
```
sync; echo 1 > /proc/sys/vm/drop_caches
```

or
```
sync; echo 2 > /proc/sys/vm/drop_caches
```

or
```
sync; echo 3 > /proc/sys/vm/drop_caches
```


# Out of memory

[When Linux Runs Out of Memory](http://www.linuxdevcenter.com/pub/a/linux/2006/11/30/linux-out-of-memory.html)

## Overcommit

[What is Overcommit? And why is it bad?](https://www.etalabs.net/overcommit.html)

Overcommit refers to the practice of giving out virtual memory with no guarantee that physical storage for it exists.

The approach taken in reality when you want to avoid committing too much memory is to account for all the memory that’s allocated. In our credit card analogy, this corresponds to using a credit card, but keeping track of all the purchases on it, and never purchasing more than you have funds to pay off. This turns out to be the Right Thing when it comes to managing virtual memory, and in fact it’s what Linux does when you set the vm.overcommit_memory sysctl parameter to the value 2. In this mode, all virtual memory that could potentially be modified (i.e. has read-write permissions) or lacks backing (i.e. an original copy on disk or other device that it could be restored from if it needs to be discarded) is accounted for as “commit charge”, the amount of memory the kernel as committed/promised to applications. When a new virtual memory allocation would cause the commit charge to exceed a configurable limit (by default, the size of swap plus half the size of physical ram), the allocation fails.

[Overcommit Memory in SLES](https://www.suse.com/support/kb/doc/?id=7002775)

Mode 0 is the default mode for SLES servers. This allows for processes to overcommit "reasonable" amounts of memory. If a process attempts to allocate an "unreasonable" amount of memory (as determined by internal heuristics), the memory allocation attempt is denied. In this mode, if many applications perform small overcommit allocations, it is possible for the server to run out of memory. In this situation, the Out of Memory killer (oom-kill) will be used to kill processes until enough memory is available for the server to continue operating.

Mode 1 allows processes to commit as much memory as requested. These allocations will never result in an "out of memory" error. This mode is usually appropriate only in specific scientific applications.

Mode 2 prevents memory overcommit and limits the amount of memory that is available for a process to allocate. This model ensures that processes will not be randomly killed by the oom-killer, and that there will always be enough memory for the kernel to operate properly. The total amount of memory available for use by the system is determined through the following calculation:
Total Commit Memory = (swap size + (RAM size * overcommit_ratio))
By default, overcommit_ratio is set to 50. With this setting, the total commit memory size will be equal to the total amount of swap space in the server, plus 50% of the RAM. In other words, if a server has 1 GB of RAM, and 1GB of swap space, the system would have a total commit limit of 1.5GB.

[Virtual memory settings in Linux - The Problem with Overcommit](http://engineering.pivotal.io/post/virtual_memory_settings_in_linux_-_the_problem_with_overcommit/)

## max_map_count

https://stackoverflow.com/questions/38384759/vm-max-map-count-and-mmapfs
