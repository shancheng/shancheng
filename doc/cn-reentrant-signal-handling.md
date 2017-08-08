# 信号处理中的死锁

应用程序访问无效地址时会发生Segment Fault，在UNIX上，OS会发一个SIGSEGV信号通知应用程序。我们可以通过sigaction设置自定义的信号处理函数，对捕获的信号进行一些操作。

需要注意的是在自定义的信号处理函数中不要调用malloc，也不要调用那些可能间接调用malloc的函数，这可能发生死锁。我们最近在一个死锁的程序中发现如下信息：

```
#0  0x00007fb80cfb612c in __lll_lock_wait_private () from /lib64/libc.so.6
#1  0x00007fb80cf33f93 in _L_lock_14932 () from /lib64/libc.so.6
#2  0x00007fb80cf31013 in malloc () from /lib64/libc.so.6
#3  0x00007fb80cee3778 in _nl_make_l10nflist () from /lib64/libc.so.6
#4  0x00007fb80cee152a in _nl_find_domain () from /lib64/libc.so.6
#5  0x00007fb80cee0d6e in __dcigettext () from /lib64/libc.so.6
#6  0x000000000045029c in sigsegv(int) ()
#7  <signal handler called>
#8  0x00007fb80cf2e4c2 in _int_malloc () from /lib64/libc.so.6
#9  0x00007fb80cf30fbc in malloc () from /lib64/libc.so.6
```

在这个例子中malloc导致SIGSEGV，SIGSEGV又调用了一个会间接调用malloc的函数。由于malloc需要上锁，而嵌套调用的函数所需的的锁已被之前的调用获取，所以这里会出现死锁。

最后推荐几篇相关文章
* [使用可重入函数进行更安全的信号处理](https://www.ibm.com/developerworks/cn/linux/l-reent.html)
* [linux: 可重入函数与不可重入函数](http://www.cnblogs.com/mylinux/p/4956771.html)
* [POSIX Safety Concepts](https://www.gnu.org/software/libc/manual/html_mono/libc.html#POSIX-Safety-Concepts)
