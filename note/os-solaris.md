# commands

http://hi.baidu.com/dbaeyes/blog/item/9bf88bed306f204a78f05570.html
20%的SOLARIS知识解决80%的问题




# Advanced Lights Out Manager

http://docs.oracle.com/cd/E19076-01/t1k.srvr/819-3250-11/command_shell.html

poweroff

poweron

console -f

break




# Solaris Management Console (SMC)

fdisk/format
- Partition id tags: unassigned, boot, root, swap, usr, backup, stand, var, home, alternates
- Commands: newfs, mkfs
- Default file system: ufs

# /etc/

Filesystem
- /etc/vfstab
- /etc/mnttab




# Package management

pkg*




# Service management

svc*




# Device management

iostat -xnp

iostat -E

prtconf

prtdiag




# HBA

对emulex的卡,使用命令prtpicl -v|grep 10df

对qlogic的卡,使用命令prtpicl -v|grep 1077

prtconf -vp

prtpicl -v

luxadm -e port




# NFS

http://help.lockergnome.com/linux/Mounting-nfs-solaris-client-linux-server--ftopict487875.html

/etc/default/nfs
```
NFS_CLIENT_VERSMAX=3
```




# Network

```
[root@unknown]vncserver
vncserver: couldn't find "xauth" on your PATH.

[root@unknown]ln -s /usr/openwin/bin/xauth /usr/bin/

[root@unknown]vncserver
vncserver: couldn't find "Xvnc" on your PATH.

[root@unknown]ln -s /usr/X11/bin/Xvnc /usr/bin/

/usr/sbin/ndd -get /dev/tcp tcp_xmit_hiwat
```
