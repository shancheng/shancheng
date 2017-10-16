# Shell commands

## Find

find
- -exec
- -print0

xargs
- -0
- -i

[find + xargs 删除文件名中含有空格的文](http://blog.sina.com.cn/s/blog_53df94780100072w.html)

问题：查找某个目录下更改时间超过7天的文件并删除它们。

方法一：
$ find . -type f -mtime +7 -print -exec rm {} \;
问题来了，在使用find命令的-exec选项处理匹配到的文件时，find命令将所有匹配到的文件一起传递给exec执行。不幸的是，有些系统对能够传递给exec的命令长度有限制，这样在find命令运行几分钟之后，就会出现溢出错误。错误信息通常是"参数列太长"或"参数列溢出"。这就是xargs命令的用处所在，特别是与find命令一起使用。find命令把匹配到的文件传递给xargs命令，而xargs命令每次只获取一部分文件而不是全部，不像-exec选项那样。这样它可以先处理最先获取的一部分文件，然后是下一批，并如此继续下去。在有些系统中，使用-exec选项会为处理每一个匹配到的文件而发起一个相应的进程，并非将匹配到的文件全部作为参数一次执行；这样在有些情况下就会出现进程过多，系统性能下降的问题，因而效率不高；而使用xargs命令则只有一个进程。另外，在使用xargs命令时，究竟是一次获取所有的参数，还是分批取得参数，以及每一次获取参数的数目都会根据该命令的选项及系统内核中相应的可调参数来确定。

方法二：
$ find . -type f -mtime +7 -print | xargs rm
还是有问题：当有许多包含空格、圆括号和其他“禁用”字符的文件时， xargs处理起来会比较困难。幸运的是，在Linux下find命令有一个选项-print0，它以null字符分隔输出的文件名而不是用新行字符。tar 和 xargs 等命令有 -0（或 --null）选项，这使它们能够理解这种形式的参数。

方法三：
$ find . -type f -mtime +7 -print0 | xargs -0 rm
但是遗憾的是这种方法在Solaris下不支持！不过不用担心，也有解决的方法：

方法四：
$ find . -type f -mtime +7 -print | while read l; do rm "$l";done

方法五：
$ find . -type f -mtime +7 -print | xargs -i echo '"{}"' | xargs rm

## Library utility

ranlib

http://www.linuxsir.org/main/doc/gnumake/GNUmake_v3.80-zh_CN_html/make-11.html

http://hi.baidu.com/doyee/blog/item/ad4c4a341089ed47251f1484.html

更新静态库的符号索引表

本小节的内容相对简单。前边提到过，静态库文件需要使用“ar”来创建和维护。当给静态库增建一个成员时（加入一个.o文件到静态库中），“ar”可直接将需要增加的.o文件简单的追加到静态库的末尾。之后当我们使用这个库进行连接生成可执行文件时，链接程序“ld”却提示错误，这可能是：主程序使用了之前加入到库中的.o文件中定义的一个函数或者全局变量，但连接程序无法找到这个函数或者变量。

这个问题的原因是：之前我们将编译完成的.o文件直接加入到了库的末尾，却并没有更新库的有效符号表。连接程序进行连接时，在静态库的符号索引表中无法定位刚才加入的.o文件中定义的函数或者变量。这就需要在完成库成员追加以后让加入的所有.o文件中定义的函数（变量）有效，完成这个工作需要使用另外一个工具“ranlib”来对静态库的符号索引表进行更新。

我们所使用到的静态库（文档文件）中，存在这样一个特殊的成员，它的名字是“__.SYMDEF”。它包含了静态库中所有成员所定义的有效符号（函数名、变量名）。因此，当为库增加了一个成员时，相应的就需要更新成员“__.SYMDEF”，否则所增加的成员中定义的所有的符号将无法被连接程序定位。完成更新的命令是：
ranlib ARCHIVEFILE
通常在Makefile中我们可以这样来实现：
libfoo.a: libfoo.a(x.o) libfoo.a(y.o) ...
ranlib libfoo.a

它所实现的是在更新静态库成员“x.o”和“y.o”之后，对静态库的成员“__.SYMDEF”进行更新（更新库的符号索引表）。

如果我们使用GNU ar工具来维护、管理静态库，我们就不需要考虑这一步。GNU ar本身已经提供了在更新库的同时更新符号索引表的功能（这是默认行为，也可以通过命令行选项控制ar的具体行为。可参考 GNU ar工具的man手册）。

## I/O utility

cpio

- find DIR -depth | cpio -pdmv .
- (cd DIR; tar cvf - SUBDIR1 SUBDIR2) | tar xf -
- cpio -vdump ../content < /tmp/f

losetup

# AIX

System Management Interface Tool (SMIT)

[Logical Volume Manager (LVM) Commands for AIX](http://wxs.ro/mirrors/aixlvm/tips-aix-lvm.html)

## Lib

[AIX Toolbox for Linux Applications](http://www-03.ibm.com/systems/power/software/aix/linux/toolbox/alpha.html)

[Aix上使用库文件和编写库文件]http://www.cppblog.com/prayer/archive/2008/12/31/70847.html

## AIX switching between 32-bit and 64-bit mode

Query

bootinfo -y tells you if your Hardware can do 64 bit when it stats "64"
bootinfo -K tells you if your Kernel is currently running in 64 bit mode.

Switching from 32-bit to 64-bit mode

ln -sf /usr/lib/boot/unix_64 /unix
ln -sf /usr/lib/boot/unix_64 /usr/lib/boot/unix
bosboot -ad /dev/ipldevice
shutdown -Fr
bootinfo -K (should now show 64)

Switching from 64-bit to 32-bit mode

ln -sf /usr/lib/boot/unix_mp /unix
ln -sf /usr/lib/boot/unix_mp /usr/lib/boot/unix
bosboot -ad /dev/ipldevice
shutdown -Fr
bootinfo -K (should now show 32)

## AIX nargs

In AIX 5L Version 5.1, the option has been added to allow the super user or any user belonging to the system group to dynamically change the value of the NCARGS parameters. In previous releases of AIX, these values were permanently defined as 24576, which resulted in a problem similar to that shown below when a large number of arguments are parsed to a command:

```
rm FILE*
ksh: /usr/bin/rm: 0403-027 The parameter list is too long.
```

The value of NCARGS can be increased to overcome this problem. The value can be tuned anywhere within the range of 24576 to 524288 in 4 KB page size increments. To display the value, use the following command.

ncargs

```
Purpose: Specifies the maximum allowable size of the ARG/ENV list (in 4KB blocks) when running exec() subroutines.
Values: Default: 6; Range: 6 to 128
Display: lsattr -E -l sys0 -a ncargs
Change: chdev -l sys0 -a ncargs=NewValue
Change takes effect immediately and is preserved over boot.
```

Diagnosis: Users cannot execute any additional processes because the argument list passed to the exec() system call is too long.

Tuning: This is a mechanism to prevent the exec() subroutines from failing if the argument list is too long. Please note that tuning to a higher ncargs value puts additional constraints on system memory resources.

# HP-UX

[Open source tools](http://hpux.connect.org.uk/hppd/cgi-bin/)

System Administration Manager (SAM)

X-networking

http://h30499.www3.hp.com/t5/Networking/HP-UX-X-Open-Socket-and-BSD-Socket-Issue/td-p/5346471#.U-sNtfmSyAQ

HP-UX provides two styles of Sockets API:

- default BSD Sockets
- X/Open Sockets

These two styles of Sockets API have the same function names but they have differences in semantics and argument types. For example, the optlen field in X/Open getsockopt() is size_t type, while BSDX
getsockopt() is int type. In 64 bit mode, size_t is 64 bit and int is still 32 bit.

Linking objects compiled to X/Open Sockets specification and objects compiled to BSD Sockets specification in the same program using the linkage method in method A would erroneously resolve BSD Sockets calls to X/Open Sockets functions in the Xnet library.  As a result, the program may result in application core dumps or unexpected Socket errors when it is run. These symptoms commonly occur when BSD Sockets accept(), getpeername(), getsockname(), getsockopt(), recvfrom(), sendmsg(), and recvmsg() are called.

So you need to compile any of the application/library  using xopen socket with also -D_HPUX_ALT_XOPEN_SOCKET_API option, like that xopen socket don't need the application to be linked with libxnet, and will avoid the mismatch between the 2 APIs.
