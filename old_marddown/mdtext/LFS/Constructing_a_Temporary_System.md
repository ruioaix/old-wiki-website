# Constructing a Temporary System

## Introduction

临时系统，现在还不能体会为什么要存在一个临时系统，直接以host来建立新系统不行吗？不行在什么地方？

这一章过后，在/mnt/lfs/tools里面应该有各种工具：compiler，assember，linker等等各种。不过，在tools中也就应该是只有这
些可执行的文件，没有其他的什么，本章的工作就是一个一个的编译之前download下来的所有包。

编译第一个包的时候，显然，用的是RHEL6的编译器，第二个或许也是，大概第几个的时候，就不再需要RHEL6的编译器了，而开始使用刚刚编译出来的放在/mnt/
lfs/tools下的编译器了，这就是第一阶段；第二阶段就是使用tools下的编译器编译所有还没编译的包，编译完了，第二阶段也就结束了。本章就结束了。

之后，也就是在下一章，会进行`chroot`，还会经过设置吧，最终结果就是，只剩下tools下的工具可用了，使用这些工具，来建立一个lfs系统。

## Toolchain Technical Notes

本章的目标是创造一个和host分离的area，其中包含了足够的tool。

使用binutils中的 **./config.guess** 会输出 **x86_64-unknown-linux-gnu** 。

dynamic loader和standard load是两个不同的东西。使用`readelf -l <name of binary> |grep
interpreter`会输出 **/lib64/ld-linux-x86_64.so.2** 。前者是glibc提供的，后者是binutils提供的。

在我的机器上LFS_TGT是 **x86_64-lfs-linux-gnu** 。

  * cross-comipler是可以编译出并非本平台使用的二进制文件；通常的compiler都是将源文件编译成为可以在本机上运行的二进制文件。 
  * 使用LFS_TGT保证了，第一次编译binutils和gcc，可以得到一个cross-linker和cross-compiler。 
  * cross的作用就是在我的64位机上，可以编译出32位的程序，也可以编译出64位的程序。 

binutils安装assembler和linker。binutils先安装，gcc和glibc的configure文件执行很多对assembler和lin
ker的测试，然后决定那种特性会启用，那种特性会关闭。

**binutils** 之后，第二个安装的是 **GCC** 。再然后，第三个安装的是 **Linux API headers** 。再然后是 **Glibc**

build process

  1. 将需要编译的package和patch放在/mnt/lfs/sources/中。 
  2. 进入sources目录 
    * tar 
    * 进入tar产生的目录 
    * build 
    * 进入sources 
    * 清理已ok的源文件。 

编译之前的准备工作：

  * `mount -v -t ext4 /dev/sda9 /mnt/lfs`
  * `cd /mnt/lfs/sources`
  * `mkdir package_dir`
  * `mkdir patch_dir`
  * `mv *z *2 package_dir`
  * `mv *patch patch_dir`

## Binutils-2.22-Pass 1

一个linker，一个assembler，其他处理object files二机制文件？的工具。

  * `mv package_dir/binutils-2.22.tar.bz2 .`
  * `mv patch_dir/binutils-2.22-build_fix-1.patch .`
  * `tar -jxvf binutils-2.22.tar.bz2`
  * `cd binutils-2.22`
  * `patch -Np1 -i ../binutils-2.22-build_fix-1.patch`
  * `mkdir -v ../binutils-build`
  * `cd ../binutils-build`
  * `../binutils-2.22/configure --prefix=/tools --with-sysroot=\(LFS --with-lib-path=/tools/lib --target=\)LFS_TGT --disable-nls --disable-werror`
  * `make`
  * `mkdir -v /tools/lib && ln -sv lib /tools/lib64`
  * `make install`

在我的机器上，大概1分40秒。

## GCC-4.7.1-Pass 1

GCC，就是GNU compiler collection，包含了c和c++ compiler。

## Linux-3.5.2 API Headers

linux kernel's API，会被glibc用到。一坨头文件呗。

## Glibc-2.16.0

glibc包含了main c library，就是c的标准库吧。

  * `[Requesting program interpreter: /tools/lib64/ld-linux-x86-64.so.2]`

## Binutils-2.22-Pass 2

介绍内容完全同上。

## GCC-4.7.1-Pass 2

介绍内容完全同上。

  * `[Requesting program interpreter: /tools/lib64/ld-linux-x86-64.so.2]`

## Tcl-8.5.12

本package和之后的3个都是用来构筑一个test环境。

## Expect-5.5

## DejaGNU-1.5

## Check-0.9.8

unix testing framework for C

## Ncurses-5.9

## Bash-4.2

## Bzip2-1.0.6

## Coreutils-8.19

## Diffutils-3.2

## File-5.11

## Findutils-4.4.2

## Gawk-4.0.1

## Gettext-0.18.1.1

## Grep-2.14

## Gzip-1.5

## M4-1.4.16

## Make-3.82

## Patch-2.6.1

## Perl-5.16.1

## Sed-4.2.1

## Tar-1.26

## Texinfo-4.13a

## Xz-5.04

over

