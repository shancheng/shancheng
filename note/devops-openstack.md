# Insall OpenStack using devstack

[centos 7 devstack 安装 openstack Mitaka](http://blog.csdn.net/scucscheng/article/details/51884613)

[Installing Openstack errors](https://stackoverflow.com/questions/20390267/installing-openstack-errors)

```
Make change in stackrc :
-GIT_BASE=${GIT_BASE:-git://git.openstack.org}
+GIT_BASE=${GIT_BASE:-https://www.github.com}
```
