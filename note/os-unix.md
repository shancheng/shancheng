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
