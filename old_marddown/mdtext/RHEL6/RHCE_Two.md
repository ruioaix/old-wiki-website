# RHCE Part Two

Red Hat Certified Engineer.

## Unit 1 Installation

  * linux内核支持大部分的硬件，同时，现在linux有dynamically loadable kernel modules功能。 
  * 可以使用 **User Mode Access** 来存取内核。 
    * system calls and signals 
    * filesystem device nodes 
    * network interfaces 
  * 多重开机，必定存在boot loader。 
  * block device和character device的不同 
    * 一个以block为存取单位，可能是512/1024bytes；另一个以1byte来存取。 
  * dmesg 查看系统信息 
  * /var/log/dmesg 查看系统信息 
  * /var/log/messages 系统出现错误的时候，系统错误信息都会记录在这个文件中 
  * /root/install.log 安装过程会记录在这个文件中 
  * system-config-*命令可以做蛮多事情。 

## Unit 2 System Initialization and Services

  * bios->mbr->kernel->init 
    * mbr只能挂在 **/** 这个根目录所在的分区，所以一些目录必须在这个分区中，比如/etc等。 
    * init是第一个运行的程序。 
  * kernel开机时的工作 
    * device detection 
    * device driver 初始化 
    * 挂载root filesystem 
    * load inital process（init） 
  * **init** 程序，首先读取 `/etc/inittab`这个设定文件。 
  * `/etc/rc.d/rc.sysinit`是系统初始化脚本，这一点在upstart中也是如此。 
  * `/etc/rc.d/rc 5` 和 `/etc/rc.d/rc5.d/` 在runlevel在5的时候，也是会执行的。后者目录中的脚本也是`/etc/rc.d/init.d/`里面脚本的link。 
  * `/etc/rc.d/init.d/`中的d都是daemon的意思，rc.d里面也是。 
  * 在`/etc/rc.d/rc5.d/`中的服务要么是k开头，要么是s开头。k代表kill，s代表start。先执行k，后执行s，k和s之中则按照数字从小到大来。 
  * daemon分两种：standalone和transient。 
    * 在standalone中又分两种，一种是init直接启动的，一种是system V daemon类型。 
    * system V daemon都在`/etc/rc.d/init.d/`、 
    * `/etc/init.d/`和`/etc/rc.d/init.d/`其实是一个目录。两者是link。 
  * `rc.local`在几个`rcX.d`目录下都有。而是是S99打头。 
  * `chkconfig`的作用就是将/etc/init.d下面的script放到对应的rcX.d目录下。 
  * `service` run a system V init script. 这个还不如直接`/etc/init.d/xxx start`呢。 

## Unit 3 Kernel Services and Configuration

  * kernel Modules 
    * kernel modules是额外挂载在kernel上的。 
    * 存放在/lib/modules目录下 
    * lsmod显示当前载入的modules 
    * modprobe临时载入modules 
    * modinfo命令可以看module的信息。 
    * module的设定在/etc/modprobe.d/目录下 
    * insmod和modprobe类似，但modprobe可以自动载入依赖module 
    * rmmod移除module 
  * /proc是虚拟文件系统，不在硬盘里，在内存里。 
    * /proc/cpuinfo 
    * /proc/scsi 
    * `echo "1" > /proc/sys/net/ipv4/icmp_echo_ignore_all`
    * 使用sysctl修改/proc/sys 
      * sysctl：configure kernel parameters at runtiome. 
  * `/var/log/dmesg`
  * lspci查看目前有什么插在pci插槽中 
  * free和vmstat显示内存的使用情况 
  * `kill -l`和`kill -9 pid`

## Unit 4 Filesystem Management

  * `fdisk -l /dev/sda`查看disk 
  * `mke2fs`格式化分区为ext2/3/4。 
  * `df -h`硬盘使用情况。 
  * `fuser -v /home/xxx/`可以查看有那些程序在操作文件，当不能umount的时候可用。 
  * `fsck -V /dev/sda1`检查分区 
  * add a disk 
    * 插入硬盘 
    * 建立分区 
    * 使用partprobe重新读入disk table 
    * 建立filesystem 
    * 建立mount point。 
    * 将记录写入/etc/fstab中。 

## Unit 5 Network Configuration

  * 所有网卡的驱动都是以module的方式建立的。 
  * 如果设定在开机时网络enabled，那么network interface modules会在启动时加载。 
  * `ifconfig`通常用来查看，也可以设置。 
  * `ifup`,`ifdown`
  * 可以通过`/etc/sysconfig/network-scripts/ifcfg-xxx`来修改对应网卡的信息。 
  * `/etc/sysconfig/network`中的hostname如果修改了，需要reboot才可以完全生效。 
  * `route`已经过时了，现在使用`ip`代替;`ip route list`。 
  * 每台pc都有hostname（主机名称），主机名称和主机ip的对应关系叫做name resolution。 
    * 从hostname到ip的解析叫做forward lookup 
    * 从ip到hostname的解析叫做reverse lookup 
    * pc和pc之间是使用ip通信的。 
    * hostname在`/etc/rc.sysinit`和`/etc/sysconfig/network`中设置和存储。 
    * `/etc/rc.sysinit`是`/etc/rc.d/rc.sysinit`的link。 
    * 每台pc中都已经储存了一些hostname和ip的对应关系，在`/etc/hosts`文件中。 
    * 当name resolution发生时，系统都会先查看`/etc/hosts`文件，这里面不存在的时候，才会找网络上的DNS。 
    * `/etc/nsswitch.conf`中定义了先找`/etc/hosts`再找网络，在这个文件中可以修改这一先后顺序。 
    * `/etc/resolv.conf`中定义了使用那一台机器作为name server。 
      * 其中的search和domain其实是相同的。作用都是使用没有小数点的短名时会自动的添加上search和domain后面的域名。 
      * 比如: `ping www` 就会导致 `ping www.xxx.com`。 
    * `host`用来测试dns。 

## Unit 6 RPM and Kickstart

  * RPM最早是redhat提出的，“red hat parkage manager“。 
  * rpm components 
    * `/var/lib/rpm/`
    * `rpm` command 
    * package files：name-version-release.architectures.rpm 
  * `rpm -i` 安装，新旧版本都留下 
  * `rpm -U` 安装，旧版本删除。 
  * `rpm -F` 没有旧版本就不安装，安装之后旧版本删除。 
  * `rpm -e` 删除 
  * `-v, -h` 详细信息和安装进度条。 
  * 更新内核，记得使用`rpm -i`
  * 已经安装的软件查询 
  * `rpm -qa`
    * `rpm -qf /bin/gzip` 查看这个命令从那个rpm中安装的。 
    * `rpm -qi gzip` 查看gzip rpm的信息。 
    * `rpm -ql gzip` 列出gzip rpm里面的文件列表。 
  * 未安装的软叫查询 
    * `rpm -qip package_file.i686.rpm`
    * `rpm -qlp package_file.i686.rpm`
  * `rpm -V initscripts`
  * `rpm -Vp package_file.i686.rpm`
  * red hat在发布rpm包时都会包含一个GPG key。 
    * `rpm --import /xxx/RPM-GPG-KEY`
    * `rpm -qa gpg-pubkey`
    * `rpm -checksig /dir/gzip-1.3.12-18.el6.x86_64`
  * `rpm2cpio` 和 `cpio -id < xx.cpio`
  * `up2date`是rhn的指令。 
  * `kickstart`成批安装redhat。配合network installation server。 

## Unit 7 User Administrator

  * User Policy Considerations 
    * the amount of access on system files and resources 
    * whether to limit logins at certain times and places 
    * whether to force periodic password changes 
    * whether to enforce CPU and memory limits 
    * whether to enable disk quotas 
  * `/etc/passwd`——user account db。 
    * 第二列的 **x** 表示使用密码，如果为空，则表示不需要密码。 
    * root的uid一定是0，1-499是系统使用的uid，用户从500开始。 
    * 最后一列，如果是`/bin/bash`，则用户登录启动的第一个程序是bash shell。如果是`/sbin/nologin`，那么代表这个帐号只能通过特殊的方式（ftp？）登录。如果是`/bin/false`，则表明这个账户只能收发email而不能登录。 
    * 该文件的权限应该是 **-rw-r--r--** 。 
  * `useradd username`
    * 上面的命令导致编辑：`/etc/passwd`,`/etc/shadow`,`/etc/group`。 
    * create home dir。 
    * set homedir的permission。 
    * 将`/etc/skel/`下的隐藏文件拷贝到user homedir。 
    * `passwd user`
    * `newusers`可以批量搞。 
  * 在redhat中，当user account开始时，一个对应的private group也会被create。 
    * 不同的系统，user homedir的权限是不相同的。 
    * redhat是 **rwx------** 。 
    * unix和suse是 **rwxr-xr-x** 。 
    * 不同的系统，user accout开始时所属群组也是不同的。 
  * `groupadd`，`groupmod`，`groupdel`，加，rename，删。 
  * `usermod`
  * remove user 
    * 手动`/etc/passwd`,`/etc/shadow`,`/etc/group`,`/var/spool/mail/username`。 
    * 或者，使用`userdel -r username`
  * user passwd 过期时间 
    * 默认不会过期。 
    * `chage`
    * **99999** 就说明不需要更换密码。 
    * 在`/etc/shadow`修改。 
  * user login shell scripts 
    * `/etc/profile`
      * `/etc/profile.d/xx.sh`
    * `~/.bash_profile`
      * `~/.bashrc`
        * `/etc/bashrc`
  * user non login shell scripts (使用su user，就是non login） 
    * `~/.bashrc`
      * `/etc/bashrc`
        * `/etc/profile.d/xx.sh`
  * profile类型的文件：设置variable。只有login才执行。 
  * bashrc类型的文件：配置bash。在login和subshell都执行。 
  * switching accounts 
    * `su [-] [user]`
    * `-`表示login shell，不带表示non login shell。 
  * `sudo`与`/etc/sudoers`
    * `visudo /etc/sudoers`
  * file ownership: `chown`
  * file permissions 
    * r:cat/ls -l 
    * w:vim/mv,rm 
    * x:script/cd 
  * suid只能用在文件上。 
  * sgid可以文件可以目录。 
  * sticky只能用在目录上。 
  * 对于可执行文件，suid和sgid分别表示run with the owner‘s uid or gid。 
  * 对于sticky的目录，在目录中的文件，只有文件的owner才能删除文件。 
  * 对于sgid的目录，目录中建立的文件的group是目录的group。 
  * 一般用户的umask是0002 
  * root的umask是0022 
  * Access Control Lists(ACLs)可以用来设置个别user对个别dir的访问权限。 
    * `setfacl -m u:user2:r-x /project1`

## Unit 8 Printing and Administration Tools

  * cups(common unix printing system) 
    * cupsd是`/etc/init.d/cups`。 
    * `/etc/cups/cupsd.conf`
    * `/etc/cups/printers.conf`
    * `http://localhost:631`
    * `lpadmin`
  * cron 
    * `/etc/cron.allow` 和 `/etc/cron.deny`
    * `/etc/crontab`
    * `/etc/cron.daily/tmpwatch`用于将长时间未使用的文件删除。 
      * 当然这些都是在各种tmp目录下的文件。 
    * `/etc/cron.daily/logrotate`压缩并mail系统的log文件。 
  * log 
    * `/var/log/`
    * `/etc/rsyslog.conf`
  * `tar cvf /var/home.tar /home`
  * `du -h /var/home.tar`
  * `tar tf /var/home.tar`
  * `tar xzf /var/home.tar.gz`
  * `dump`备份整个partion。 
  * `cpio`
  * `tar -czvf root@example1:/var/home.tar.gz /home`
  * `dump -0uf root@example1:/var/home.tar.gz /home`

## Unit 9 The X Window System

  * XOrg组织使用x protocol开发出叫做X11的应用程序。 
  * X11就是用来与硬件沟通。 
  * X Client必须安装gui工具。 
  * X server通过X11与邮件沟通。 

## Unit 10 Advanced Filesystem Management

略

## Unit 11 Troubleshooting

  * 收集信息 
  * check log 
  * 备份 
  * Things to Check：X 
    * 不要在level 5下检查。 
    * `system-config-display`
    * `X -probeonly`
    * 检查/home和/tmp是否没有空间了。 
    * 检查xfs有没有启动。 
  * Things to Check：Networking 
    * `dig hostname`
    * `ifconfig`
    * `ip route -n`
    * `cat /etc/modprobe.conf`

## over

