# Preparing a New Partition

最少2.8G的空间要求。10G认为是合适的。

swap分区可以就认为是用来存放内存中不常使用的数据的地方，以把内存流给更加活跃的数据。

`gdisk`分了100M给/boot，30G给/，40G给/home。gdisk需要重启才可以生效。

`mkfs.ext4 /dev/sda8 /dev/sda9 /dev/sda10`

  * `cd /mnt/`
  * `mkdir lfs`
  * `mount -v -t ext4 /dev/sda9 lfs`
  * `cd lfs`
  * `mkdir boot home`
  * `mount -v -t ext4 /dev/sda8 boot`
  * `mount -v -t ext4 /dev/sda10 home`

