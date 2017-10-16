# Common

[Latency Numbers Every Programmer Should Know](http://www.eecs.berkeley.edu/~rcs/research/interactive_latency.html)

[高并发性能调试经验分享](http://makaidong.com/chenpingzhao/356_14088.html)

# Tools

## Common tools

[iostat来对linux硬盘IO性能进行了解](http://www.php-oa.com/2009/02/03/iostat.html)

top

gstack

## oprofile

operf --pid PID

opreport -l -c

## valgrind

http://www.ibm.com/developerworks/cn/linux/l-cn-valgrind/index.html

## gprof

http://sourceware.org/binutils/docs/gprof/

http://www.cs.utah.edu/dept/old/texinfo/as/gprof_toc.html

-pg

gprof -b <exe> gmon.out

## Visual Studio Performance Tools

## IBM Quantify

## Intel VTune

# Network

[10G(82599EB) 网卡测试优化(ethtool)](http://www.tuicool.com/articles/EVRjQb)

## Network tuning steps

Find NUMA Nodes of NICs and show results

Only bond NICs in the same NUMA Node

Choose a better bonding mode - 2 or 4 with xmit_hash_policy=layer3+4

Increase ring buffer to max

Decrease number of NIC queues to 10

Confine workload to same NUMA Node as NICs using numactl/numad

Tune NIC coalescense to increase usecs before hard interrupt

Disable C-states C1E and below in BIOS and kernel

# Web

[A curated list of Web Performance Optimization](https://github.com/davidsonfellipe/awesome-wpo#)
