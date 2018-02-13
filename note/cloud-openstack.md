# Installation

https://wiki.openstack.org/wiki/Documentation/training-labs

https://docs.openstack.org/devstack/latest/

https://docs.openstack.org/devstack/latest/guides.html

## Speed up the install in china

###### http://kiwik.github.io/openstack/2013/12/21/DevStack-install-in-China/

/etc/apt/sources.list, copied from https://mirror.tuna.tsinghua.edu.cn/help/ubuntu/

```
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted universe multiverse
```

~/.config/pip/pip.conf and ~/.pip/pip.conf

```
[global]
timeout = 6000
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
[install]
use-mirrors = true
mirrors = https://pypi.tuna.tsinghua.edu.cn
```

###### [Installing Openstack errors](https://stackoverflow.com/questions/20390267/installing-openstack-errors)

```
Make change in stackrc :
-GIT_BASE=${GIT_BASE:-git://git.openstack.org}
+GIT_BASE=${GIT_BASE:-https://www.github.com}
```


# Networking

https://www.rdoproject.org/networking/difference-between-floating-ip-and-private-ip/

https://www.mirantis.com/blog/configuring-floating-ip-addresses-networking-openstack-public-private-clouds/

###### [Understanding FlatNetworking](https://wiki.openstack.org/wiki/UnderstandingFlatNetworking)

#!wiki caution
If you're using a single interface, then that interface (often eth0) needs to be set into promiscuous mode for the forwarding to happen correctly. This _does not_ appear to be needed if you're running with physical hosts that have and use two interfaces.

###### [Promiscuous mode](https://en.wikipedia.org/wiki/Promiscuous_mode)

In computer networking, promiscuous mode (often shortened to "promisc mode" or "promisc. mode") is a mode for a wired network interface controller (NIC) or wireless network interface controller (WNIC) that causes the controller to pass all traffic it receives to the central processing unit (CPU) rather than passing only the frames that the controller is specifically programmed to receive. This mode is normally used for packet sniffing that takes place on a router or on a computer connected to a hub (instead of a switch) or one being part of a WLAN. Interfaces are placed into promiscuous mode by software bridges often used with hardware virtualization.
