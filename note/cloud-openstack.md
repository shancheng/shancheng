# Insall OpenStack using devstack

[centos 7 devstack 安装 openstack Mitaka](http://blog.csdn.net/scucscheng/article/details/51884613)

[Installing Openstack errors](https://stackoverflow.com/questions/20390267/installing-openstack-errors)

```
Make change in stackrc :
-GIT_BASE=${GIT_BASE:-git://git.openstack.org}
+GIT_BASE=${GIT_BASE:-https://www.github.com}
```

# Network

###### [Understanding FlatNetworking](https://wiki.openstack.org/wiki/UnderstandingFlatNetworking)

#!wiki caution
If you're using a single interface, then that interface (often eth0) needs to be set into promiscuous mode for the forwarding to happen correctly. This _does not_ appear to be needed if you're running with physical hosts that have and use two interfaces.

###### [Promiscuous mode](https://en.wikipedia.org/wiki/Promiscuous_mode)

In computer networking, promiscuous mode (often shortened to "promisc mode" or "promisc. mode") is a mode for a wired network interface controller (NIC) or wireless network interface controller (WNIC) that causes the controller to pass all traffic it receives to the central processing unit (CPU) rather than passing only the frames that the controller is specifically programmed to receive. This mode is normally used for packet sniffing that takes place on a router or on a computer connected to a hub (instead of a switch) or one being part of a WLAN. Interfaces are placed into promiscuous mode by software bridges often used with hardware virtualization.

