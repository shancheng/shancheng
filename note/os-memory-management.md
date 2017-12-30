###### Buddy memory allocation

https://en.wikipedia.org/wiki/Buddy_memory_allocation

###### Slab allocation

https://en.wikipedia.org/wiki/Slab_allocation

http://www.ibm.com/developerworks/cn/linux/l-linux-slab-allocator/index.html

###### STL allocator

http://zhanyonhu.blog.163.com/blog/static/16186044201461461751705/ stl的allocator替换为boost内存池后的问题

###### Buffer cache

http://www.tldp.org/LDP/sag/html/buffer-cache.html

http://stackoverflow.com/questions/6345020/linux-memory-buffer-vs-cache

###### How to adjust kernel maximum share memory size

/etc/sysctl.conf
```
kernel.shmmax=134217728
```

sysctl -w kernel.shmmax=134217728

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
