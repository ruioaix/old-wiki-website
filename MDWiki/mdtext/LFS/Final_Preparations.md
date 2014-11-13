# Final Preparations

  * `export LFS=/mnt/lfs`
  * `mkdir -v $LFS/tools`
  * `ln -sv $LFS/tools /`
    * 在/下建立了tools，软链接。 
  * `useradd -m -k /dev/null lfs`
  * `passwd lfs`
  * `chown -v lfs $LFS/tools`
  * `chown -v lfs $LFS/sources`
    * 这两步只分配了owner，而不包括group。也就是说tools和sources的group还是root。 
  * `su - lfs`

分配一个user是正确的选择。

在`su - lfs`之后，就进入了lfs的用户，修改或着说是添加两个文件 **.bash_profile** 和 **.bashrc** 。

在.bash_profile中，一句话`exec env -i HOME=\(HOME TERM=\)TERM PS1='\u:\w\$ ' /bin/ba
sh`，先是exec，执行后面的命令用来取代当前的shell；接着env，设置一个全新的环境来执行后面的/bin/bash命令；结合在一起就是建立一个非常干
净的环境变量空间，然后在这个环境中运行bash，以替代虚拟终端中的bash。

上面的打开的新的bash是一个non-login shell，其会读取.bashrc中的内容。

  * `set +h` 效果就是每次在bash中输入命令，都会从$PATH中进行完全查找，而不去记忆曾经运行过的命令
  * `umask 022`
  * `LFS=/mnt/lfs`
  * `LC_ALL=POSIX` 地区化的变量，设置为POSIX是一种保险的选择
  * `LFS_TGT=$(uname -m)-lfs-linux-gnu`
  * `PATH=/tools/bin:/bin:/usr/bin`
  * `export LFS LC_ALL LFS_TGT PATH`

最后，`source .bash_profile`，重新产生一个读取.bashrc的bash。

到这一步，就要开始编译东西了。如果我现在关闭电脑，然后明天开始，没有任何问题，我所要做的：

  * `su -`
  * `mount -v -t ext4 /dev/sda9 /mnt/lfs`
  * `mount -v -t ext4 /dev/sda8 /mnt/lfs/boot` 这一行和下一行在目前可要可不要
  * `mount -v -t ext4 /dev/sda10 /mnt/lfs/home`
  * `su - lfs`

`su - lfs`这一步意味着什么，我在执行这一步的时候，我的角色是root还是其他的用户没有任何关系，这只是切换用户的命令，进入lfs之后，我就是lfs
了，我所有的能力都是bash给予的，新的bash给予的，我所能操作的文件也只有那些我能操作的文件。我被限制在了很小的范围内部，/home/lfs是我的地盘，
/tools是我的地盘，/mnt/lfs/sources是我的地盘，/mnt/lfs/tools就是/tools。这3个地方，加上一个bash，以及PATH
中的/bin，/usr/bin目录下的我可以执行的命令，这就是我的所有。
