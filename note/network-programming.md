# Socket

TCP socket

UDP socket

Raw socket

[Can two applications listen to the same port?](
http://stackoverflow.com/questions/14388706/socket-options-so-reuseaddr-and-so-reuseport-how-do-they-differ-do-they-mean-t)

http://www.cnblogs.com/skynet/archive/2010/12/12/1903949.html

###### Close

[Graceful Shutdown, Linger Options, and Socket Closure](https://docs.microsoft.com/en-us/windows/desktop/WinSock/graceful-shutdown-linger-options-and-socket-closure-2)

[Linux-socket的close和shutdown区别及应用场景](https://www.cnblogs.com/JohnABC/p/7238241.html)

http://stackoverflow.com/questions/4160347/close-vs-shutdown-socket
How to judge if the peer has closed?
- recv returns 0
- epoll_wait receives EPOLLRDHUP

https://stackoverflow.com/questions/3757289/tcp-option-so-linger-zero-when-its-required

http://www.cnblogs.com/zhenjing/archive/2011/04/20/2021791.html

[TCP的三次握手与四次挥手过程，各个状态名称与含义，TIMEWAIT的作用](https://blog.csdn.net/sinat_32487221/article/details/55272305)

[TCP状态转换图](https://www.cnblogs.com/qlee/archive/2011/07/12/2104089.html)

###### Out of band (OOB)

URGENT flag is set in TCP header

MSG_OOB is used in send/recv

select receives event in exceptfds

epoll_wait receives EPOLLPRI

SIGURG (MUSE call fcntl(sock, SETOWN, getpid())

###### SIGPIPE

Generated during write if reader has closed

Solution 1: catch the signal and handle it

Solution 2: set MSG_NOSIGNAL in send

###### 深入理解TCP网络编程中的send和recv

TCP协议本身是为了保证可靠传输,并不等于应用程序用tcp发送数据就一定是可靠的，必须要容错

send（）和recv（）没有固定的对应关系，不定数目的send()可以触发不定数目的recv（），这话不专业，但是还是必须说一下，初学者容易疑惑

关键点，send（）只负责拷贝，拷贝到内核就返回，我通篇在说拷贝完返回，很多文章中说send（）在成功发送数据后返回，成功发送是说发出去的东西被ACK确认过。send（）只拷贝，不会等ACK

此次send（）调用所触发的程序错误，可能会在本次返回，也可能在下次调用网络IO函数的时候被返回

###### 系统调用被信号中断和自动重启动 某些信号可以不重启

http://blog.csdn.net/dianhuiren/article/details/7291540

###### 进程间传递文件描述符

http://danier.iteye.com/blog/575158

http://blog.csdn.net/sparkliang/article/details/5486069


# I/O multiplexing

###### select

###### poll

###### epoll

http://linux.die.net/man/7/epoll

###### IOCP

http://blog.csdn.net/markman101/article/details/6235516

http://blog.sina.com.cn/s/blog_492b29580100vswq.html

http://www.cprogramdevelop.com/1059279/

http://www.cnblogs.com/showna/articles/1026566.html

http://dev.gameres.com/Program/Control/IOCP.htm

###### Asynchronous I/O

http://www.ibm.com/developerworks/cn/linux/l-async/#N10056


# C10k tuning

```
/etc/sysctl.conf
fs.file-max = 9839574
fs.nr_open = 2000000
net.ipv4.ip_local_port_range = 1024 65535

/etc/security/limits.conf
* - nofile 2000000
```

所有进程打开的文件描述符数不能超过/proc/sys/fs/file-max

单个进程打开的文件描述符数不能超过ulimit中nofile的soft limit

nofile的soft limit不能超过其hard limit

nofile的hard limit不能超过/proc/sys/fs/nr_open


# Framework

ACE

Boost.Asio

libevent

libuv


# libcurl

https://curl.haxx.se/libcurl/c/libcurl-multi.html  CURL multi interface

https://curl.haxx.se/libcurl/c/curl_multi_socket_action.html  reads/writes available data given an action

```
curl_global_init
loop
|
|-> curl_easy_init
|
|-> *curl_easy_setopt
|
|-> curl_easy_setopt CURLOPT_VERBOSE
|
|-> curl_easy_setopt CURLOPT_STDERR
|
|-> curl_easy_perform
|
|-> curl_easy_cleanup
```
