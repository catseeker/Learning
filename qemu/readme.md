# Qemu Learning Notes

## 1.典型网络设置
1.1 采用tap/bridge桥接模式创建  
1.2 新建网桥br和虚拟网卡tap,br网桥连接实体网卡和虚拟网卡tap
1.3 命令如下：
```
ifconfig eth0 down
brctl addbr br0
brctl addif br0 eth0
btctl stp  br0 off
brctl setfd br0 1
brctl sethello br0 1
ifconfig br0 0.0.0.0 promisc up
ifconfig eth0 0.0.0.0 promisc up
dhclient br0
tunctl -t tap0 -u root
brctl addif br0 tap0
ifconfig tap0 0.0.0.0 promisc up
```
## 2.根文件系统生成镜像文件
2.1 采用dd或者qemu-img均可
```
#qemu-img形式
qemu-img create -f raw rootfs.img 128M
mkfsext4 -F rootfs.img
mkdir tmpfs
mount -t ext4 rootfs.img tmpfs/
cp -r rootfs/* tmpfs/
unmount tmpfs/
```


