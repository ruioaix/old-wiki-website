# Geant4.9.2.p02在ubuntu10.04下的安装

Geant4是我之前工作用到的工具，以后也许不会再用到了。趁我现在还记得，就将之前的一些经验都记录下来，希望可以帮到一些人。

linux的发行版应该都是支持Geant4的安装的，主要问题是Geant4需要的库要找到并安装好，我试过可以的有RHEL6&Fedora，Gentoo，ub
untu。

这里安装的是Geant4.9.2.p02，大概是2010年的东西了（因为ubuntu用的是10.04吗），记得当时从师兄那里学习的版本是Geant4.7，觉
得太老，自己就看手册看官网看斯坦福的论坛，最终竟然也倒腾出来了。

现在的Geant4的安装过程貌似已经改变了，这里的内容能量很有限了。

这一篇本身也是很久之前写的了。

## 使用的光盘

我使用的是从官网上下的ubuntu 10.04 desktop i386 dvd iso，好久之前下的，估计现在应该是10.04.1了。

注意：我使用的dvd版本，4G，虽然下的费时，但给人安全感……

## 系统安装过程

略过，图形化界面，傻瓜式操作；要注意的是分区，如果是新人，直接选择使用空闲空间或者整个磁盘吧。

安装的时候使用中文的环境，下面的都是基于中文环境的ubuntu来操作的。安装英文版本的时候会出现在新立得里面找不到函数库的问题。最终导致不能开启opengl
。

## 更新源

如果是学校的用户，可以去瀚海的linux版的置顶贴里面，能找到ubuntu10.04的源，直接下载下来：source.list.ubuntu，就这名字。
然后copy到/etc/apt下面，备份原来的：

  1. `mv source.list source.list.bak`
  2. `mv source.list.ubuntu source.list`
  3. `apt-get update`
  4. `apt-get upgrade`

等……学校的源很快，1MB/s的速度还是有的。

注意：下面上述命令可能会因为权限问题不能执行，这种时候在语句前加上`sudo`即可。

## 一些环境设置和安装一些库

### 环境设置

打开终端，输入：

  * `sudo passwd root`

这句话是用来设置你机器的root密码的，还是设置一个比较NB的密码比较好。 注意：我这有个挺好的测试密码安全程度的网站，可以试下:[[http://hows
ecureismypassword.net/](http://howsecureismypassword.net/) 穿越].

接着，装vim，ubuntu里面默认没有安装，这个必须装啦。_要是你用emacs，当我什么都没说_

  * `sudo apt-get install vim`

即可。

接着，装c++的工作环境，也是一句：

  * `sudo apt-get install build-essential`

就好。

### 安装一些库

这些库如果不装的话，会导致N多古怪的问题，但大多都是由于opengl这个与图形相关的部分引起的。

你可以使用新立得，也可以使用命令行，这些库包括：

  * libgl1-mesa-dev 
  * libgl1-mesa-glx 
  * mesa-common-dev 如果发现已经安装就不要管了
  * libglu1-mesa-glx 如果没找到这个，也不要管了
  * libglu1-mesa-dev 
  * libxi6 
  * libxi-dev 
  * libxmu 这个会搜到7/8个包，全部安装

安装好之后，准备工作就完成了，就可以开始正式的安装Geant4了。

## Geant4安装

安装主要基于这个文档[Installing Geant4 Release 4.9.2.p02 on
Linux](../files/Geant4/installhtml/InstallingGeant4.html)，这个文档是在Geant4官网上下的。

版本如上所示，使用的是4.9.4.p02；从上面的网页中，可以看到下面安装中需要的程序包，都可以直接的下载。

依据这个文档，给出如下解释。

安装分成3个部分：

  1. 安装[clhep](http://wiki.rrrui.com/files/Geant4/sources/clhep-2.0.4.2.tgz)
  2. 安装[G4EMLOW](http://wiki,rrrui.com/files/Geant4/sources/G4EMLOW.6.2.tar.gz)
  3. 安装[geant4](http://wiki.rrrui.com/files/Geant4/sources/geant4.9.2.p02.tar.gz)

## 在依据上述网页安装之前

在依据上述网页安装之前，需要规划好你的安装目录，虽然在安装的时候也可以一步一步做，但有个整体的意识总是好的。

我的规划如下：

  * 在我个人的目录下 _/home/xrfind_ 建立一个 _Geant4_ 目录：`mkdir ~/Geant4`。 
  * 在Geant4中建立两个目录 _InstallGeant4_ 和 _WorkDirForGeant4_ ，分别作为安装目录和工作目录。 
  * 在 _InstallGeant4_ 下，建立两个目录 _CLHEP_ 和 _geant4_ 。 
  * 将网页中的 _clhep-2.0.4.2.tgz_ 和 _geant4.9.2.p02.tar.gz_ 下载下来，然后分别copy到上述的两个目录中。 

## 安装CLHEP

  1. `cd ~/Geant4/InstallGeant4/CLHEP` 进入目录
  2. `tar -zxvf clhep-2.0.4.2.tgz` 在上节中已经将该文件放入 _CLHEP_ 中了，这里解压
  3. `cd 2.0.4.2/CLHEP` 进入目录
  4. `./configure --prefix /home/xrfind/Geant4/InstallGeant4/CLHEP` 配置
  5. `make` 编译
  6. `make install` 安装

**注意：的就是第四步，注意目录路径；且configure开头字母小写。**

## 安装G4EMLOW.6.2.tar.gz

  1. `cd ~/Geant4/InstallGeant4/geant4`
  2. `tar -zxvf geant4.9.2.p02.tar.gz`
  3. `cd geant4.9.2.p02`
  4. `mkdir data` 建立一个data文件夹
  5. `cp xxx/G4EMLOW.6.2.tar.gz data` 将G4EMLOW的文件copy到刚刚建立的data文件夹中，这里的xxx是你放置G4EMLOW的位置
  6. `cd data`
  7. `tar -zxvf G4EMLOW.6.2.tar.gz`

这一步相对简单。

## 安装geant4

官方文档中说的，在做这一步之前去喝杯咖啡，休息下。

我双手赞成，因为在这里我不止载了一回，最好有充裕的时间和安静的环境，不然宁可等下次。

  1. `cd ~/Geant4/InstallGeant4/gent4/geant4.9.2.p02`
  2. `./Configure -build` 这里的一步下面详细讲述
  3. `./Configure`

### 执行./Configure -build

当你执行`./Configure -build`这个命令之后，就进入了交互的环境。

在这里你需要回答很多的问题，大部分都保留默认，直接回车，下面列出需要特别关注的地方：

  * 当被询问 **Could not find CLHEP installed on this system!Please, specify where CLHEP is installed:** 的时候,你需要回答CLHEP安装在那个位置,就我的设置来说是: _/home/xrfind/Geant4/InstallGeant4/CLHEP_ 。 
  * 当被询问 **G4VIS_BUILD_OPENGLX_DRIVER G4VIS_USE_OPENGLX** 的时候，键入 **y** ，回车。 
  * 当被询问 **G4VIS_BUILD_RAYTRACERX_DRIVER G4VIS_USE_RAYTRACERX** 的时候，键入 **y** ，回车。 

当输入最后一个回车的时候，就会开始编译安装了，需要蛮久的，等待吧。

## 在使用之前的最后一步

有三条指令是需要你在每次运行Geant4程序之前必须执行的：

  1. `export G4WORKDIR=~/Geant4/WorkDirForGeant4` 这里定义工作目录
  2. `export LD_LIBRARY_PATH=~/Geant4/InstallGeant4/CLHEP/lib/:$LD_LIBRARY_PATH` 这里定义工作时用到的库
  3. `source ~/Geant4/InstallGeant4/geant4/geant4.9.2.p02/env.sh`
  4. `cd $G4WORKDIR` 这里是进入工作目录，方便点，不是必须的

但每次都输入那是很烦的，这里有两种方案来解决这个问题：

  * 执行`vim ~/.bashrc`，打开这个文件，在这个文件的最后将这三条指令加到最后，保存退出。 
  * 执行`vim ~/.g4`,建立一个新文件 _.g4_ ，将这三条指令加入其中，保存退出。 

第一种方案会在你每次打开shell的时候都执行这三条指令，这样你就可以直接编译修改你的Geant4程序了，但同时，即使你使用终端做别的事情，这三句还是会执行
，输出一堆东西。

第二种方案是在你需要做Geant4相关的事情的时候，使用`source .g4`这个指令，就相当于那三句指令，但简单的多，我使用的是这种方案。

好了到这里，你就可以使用Geant4了，但注意工作时要在工作目录哦。

