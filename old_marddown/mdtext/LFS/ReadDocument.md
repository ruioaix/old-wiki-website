# Read Document

32位的linux发行版可以安装在64位intel cpu上，也可以作为一个host system。

从LFS直接建立的64位系统是一个纯64位系统，纯，表示其只支持64位可执行文件。

建立一个multi-lib系统，需要编译很多应用两次，一次为32位，一次为64位。

很多包不支持纯64位系统，因为，这些包里可能嵌入了特殊的32位依赖。

也许，第一次实验性质的，我该先选择安装一个32位的系统。

## 一陀要使用的包

  1. Autoconf 
    * 这个包里的程序是用来产生shell script的，这些产生的shell script会自动根据开发者的模板来配置source code。 
  2. Automake 
    * 这个包里的程序是用来根据一个模板来产生make file的。 
  3. Bash 
    * 这个包提供了一个bourne shell给系统；LSB要求有一个shell接口。 
  4. Binutils 
    * 这个包包括了一个连接器linker，一个汇编器assembler以及其他一些用来处理object file的工具。对象文件，其实就是具有特殊格式的二进制文件。大部分LFS包的编译都需要这个工具。 
  5. Bison 
    * 不清楚这个是什么意思，yacc是什么？ 
  6. Bzip2 
    * 这个包用来解压和压缩文件。 
  7. Check 
    * 作用不清楚 
  8. Coreutils 
    * 这个包提供了很多查看操作文件和目录的必须程序；大多数包的安装过程都需要这个包。 
  9. DejaGNU 
    * 这个包提供了一种检查测试其他程序的框架，貌似是安装时候的临时工具。 
  10. Diffutils 
    * 这个包提供了用来显示文件之间的不同或者目录之间的不同的程序。 
  11. Expect 
    * 这个包提供了一个程序，可以和其他的交互式程序进行脚本形式的对话。 
  12. E2fsprogs 
    * 这个包包含了处理ext2，ext3，ext4的工具。 
  13. File 
    * 这个包包含可以确定文件类型的工具。 
  14. Findutils 
    * 这个包包含需找文件系统中的文件的工具。 
  15. Flex 
    * 不清楚，貌似是文本编辑？ 
  16. Gawk 
    * 这个包包含了操纵文本文件的程序，就是awk的GNU版。 
  17. Gcc 
    * GNU的编译器合集，包含了c编译器和c++编译器。 
  18. GDBM 
    * 这个包包含Database Manager library，是数据库管理库。Man-DB会用到这个library吧。 
  19. Gettext 
    * 这个包包含了国际化和本地化的工具、library。 
  20. Glibc 
    * 这个包包含了the main C library。 
  21. GMP 
    * 这个包包含了可以进行任意精度计算的数学library。 
  22. Grep 
    * 包含可以搜寻文件内容的工具，就是grep吧 
  23. Groff 
    * 这个包包含处理和格式化文本文件的程序，主要功能是格式化man page。 
  24. GRUB 
    * the Grand Unified Boot Loader 
  25. Gzip 
    * 包含压缩和解压缩文件的程序 
  26. Iana-etc 
    * 这个包提供data给network services和protocol。 
  27. Inetutils 
    * 包含了基本网络管理的程序。 
  28. IProute2 
    * 这个包提供了程序用于基本的和高级的IPv4、IPv6网络 
  29. Kbd 
    * 这个包包含了键盘按键表，键盘工具等。 
  30. Kmod 
    * 包里包含了管理kernel modules的程序 
  31. Less 
    * 包含很好的阅读文本文件的工具，就是less吗，manpage也用它看。 
  32. Libtool 
    * 提供了GNU generic library support script，不知道准确的工作定义 
  33. Linux Kernel 
    * 字面意思吧 
  34. M4 
    * 文本宏处理器，不明白准确的意思 
  35. Make 
    * 这个包包含了指导编译的工具，每个lfs的包都会用到。 
  36. Man-DB 
    * 这个包包含了寻找和浏览man page的程序，其中less就是其用来浏览man page的程序。 
  37. Man-pages 
    * 这个包包含man page的实际内容。 
  38. MPC 
    * 貌似包含复数运算的函数。 
  39. MPFR 
    * 貌似包含多精度运算的函数。 
  40. Ncurses 
    * 包含library，字符屏幕终端的什么处理 
  41. Patch 
    * 这个包包含一个程序，程序根据使用diff程序得到的patch文件来修改和创建文件。 
  42. Perl 
    * 实时编程语言PERL的解释器。 
  43. Pkg-config 
    * 这个包包含用于返回已安装的library或者包的元数据meta-data的程序。 
  44. Popt 
    * 包含一个library，用于分析命令行的输入。 
  45. Procps 
    * 这个包包含了监视进程的程序。 
  46. Psmisc 
    * 这个包包含了显示正在运行进程的信息的程序。 
  47. Readline 
    * 包含一组library，提供命令行编辑和历史记录功能。 
  48. Sed 
    * 这个包允许在没有一个编辑器的情况下编辑一个文本文件；大多数包的configure scripts都需要它。 
  49. Shadow 
    * 这个包提供了可以安全处理password的程序。 
  50. Sysklogd 
    * 这个包包含了记录系统信息的程序，比如kernel和daemon在事情发生时给出的信息。 
  51. Tar 
    * 这个包提供了打包和解包的能力，几乎所有的lfs的包都使用。 
  52. Tcl 
    * 用于测试的吧，不清楚。 
  53. Texinfo 
    * 这个包包含了读，写，转换info page的程序；大多数程序的安装过程都会用到。 
  54. Udev 
    * 这个包包含了动态创建device node的功能，用来替代在/dev下建立成千上万的静态节点。 
  55. Util-linux 
    * 这个包提供了各种工具程序，处理文件系统、控制台、分区等各种工具。 
  56. Vim 
    * vim吗 
  57. XZ Utils 
    * 这个包包含压缩和解压文件的程序，提供了最高的压缩率。 
  58. Zlib 
    * 包含了压缩和解压routines，不明白。 

## Host System Requirements

  * Bash-3.2: **Bash-4.1.2**
  * Binutils-2.17: **binutils-2.20.51.0.2**
  * Bison-2.3: **bison-2.4.1**
  * Bzip2-1.0.4: **bzip2-1.0.5**
  * Coreutils-6.9: **coreutils-8.4**
  * Diffutils-2.8.1: **diffutils-2.8.1**
  * Findutils-4.2.31: **findutils-4.4.2**
  * Gawk-3.1.5: **gawk-3.1.7**
  * Gcc-4.1.2: **gcc-4.4.6**
  * Glibc-2.5.1: **glibc-i686-2.12, glibc-x86_64-2.12**
  * Grep-2.5.1a: **grep-2.6.3**
  * Gzip-1.3.12: **gzip-1.3.12**
  * Linux Kernel-2.6.25: **kernel-2.6.32**
  * M4-1.4.10: **m4-1.4.13**
  * Make-3.81: **make-3.81**
  * Patch-2.5.4: **patch-2.6**
  * Perl-5.8.8: **perl-5.10.1**
  * Sed-4.1.5: **sed-4.2.1**
  * Tar-1.18: **tar-1.23**
  * Texinfo-4.9: **texinfo-4.13a**
  * Xz-5.0.0: _xz-4.999.9_

想知道编译kernel的gcc版本，看 **/proc/version** ，里面的gcc就是指编译kernel的gcc。

