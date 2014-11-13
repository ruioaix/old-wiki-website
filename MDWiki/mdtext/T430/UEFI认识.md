# UEFI

Unified Extensible Firmware Interface, 统一可扩展固件接口。

  * 这是字面翻译。 
  * 有时候缩写为 **UEFI**
  * 有时候缩写为 **Unified EFI**
  * UEFI是一个接口，更多的是规范，也就是标准性质的东西，是一个说明书。 
  * 各个厂商照着说明书作出统一的接口。 
  * 接口吗，就是供人使用的，或者供其他什么东西使用的。 
  * 统一，一致吗，统一的接口，就是大家都照着这个接口来，可能大家自己的实现各式各样，但是接口都是一致的。 

**UEFI Specification** ，UEFI规范，这就是那本书了，那本说明书了。 

书是谁写的？ **Unified EFI Forum** 写的。

  * 这个论坛，或者组织负责开发，管理，推进UEFI Specification。 
  * 这是一个非盈利non-profit的合作贸易collaborative trade组织。不知道这样的组织是什么样的组织。 
  * 组织的董事会成员都是NB的大公司：Apple inc，Lenovo，IBM，Intel等等。 
  * 董事会干嘛的，左右公司的，左右组织的。 

那么，UEFI到底是干嘛的？

  * 有一个词叫 **the pre-boot environment** ，这个就是你按下电脑电源键然后到windows或者linux或者mac开始启动的这段时间。 
  * 这段时间里面发生了什么？主板上电，然后主板上各式各样的芯片里面的固件开始运行，自检，初始化啊什么的，其中最重要的是BIOS了，它里面有固件，负责了大多数其他芯片和硬件的检测，并且会放入一些特定的数据在内存中，然后让cpu开始执行内存中的数据，这一步已经是这段时间的最后了，这段数据执行的结果就是windows或者linux或者mac开始他们的启动。 
  * 之前的BIOS，我们称为 **Legacy BIOS** ，它如何自检，如何读取硬盘第一扇区的数据等等太多资料可以看，我可以确定的是，它的工作过程太过死板，而且只能那么死板，没有改进的空间，或者说改进的空间太小，不能说智能，而且永远不能说智能。在Legacy BIOS上，就没有接口一说，因为过程死的，要什么接口？ 
  * 现在的很多比较高级的主板上都有了新型的BIOS，它的接口是按照UEFI Specification来的，我们称这种BIOS为 **UEFI BIOS** 。 
  * **UEFI BIOS** 里面也是有固件的，这种固件就比 **Legacy BIOS** 里面的固件负责的多，可以做的事情，可以实现的功能也都多得多，在启动windows、linux、mac之前，它可以做的事情也多的多，多了就复杂了，复杂了就需要统一，统一的结果就是一致的接口。 
  * **UEFI Specification** 就定义了这种接口，这个规范详细的说明了控制是如何从 **the pre-boot environment** 转移到windows、linux、mac的。也就是OS和平台固件之间的接口。 

EFI和UEFI

  * EFI Specification是intel写的，然后intel把它捐给了Unified EFI Forum，Unified EFI Forum就在EFI Specification的基础上写了一本新的书，就是UEFI Specification。 
  * EFI Specification已经被intel抛弃了，不再更新。 
  * UEFI Specification变成了王道。 

UEFI Specification就是一份说明书，任何人都可以根据说明书做出自己的实现。

上面说了 **the pre-boot environment** ，这是UEFI BIOS的天下。

  * OS还没有启动。 
  * UEFI BIOS因为其智能和强大，拥有所有硬件的控制权。 
  * 只要UEFI BIOS里面的固件足够NB，那么，其实这也是一个系统啊。 
  * 根据UEFI Specification，固件可以支持网络，USB，高分辨率图形，文件系统，对所有硬件的访问权限。 
  * 现在可以知道UEFI有多么强大了，完全可以称为一个小OS了。 

在Lenovo ThinkServer TS430（不是T430）上的UEFI firmware是符合UEFI Specification 2.1的。

  * 在该机器上的，UEFI在启动os的时候，会从物理或者逻辑上的设备找到特殊的文件。 
  * 在UEFI可以启动的硬盘上，一个特殊的分区会存在，该分区包含了 **the main UEFI boot loader** ，其路径是 **\efi\boot\bootx64.efi** 。如果这个文件存在，也就是这个boot loader存在，那么UEFI firmware会自动的根据这个文件进行启动。 
  * 在POST的时候， **the Boot Manager** 会自动确定和枚举所有的可以启动的设备以及UEFI boot target，并会自动为这些启动项创建启动入口选项。如果UEFI发现某个OS安装了，也会为之创建入口选项，指向OS boot loader file。 
  * 一个硬盘要么是MBR，要么是GPT。如果的多个bootable UEFI 分区存在于一个硬盘上，boot manager将列出所有的启动选项。 
  * Boot Manager我可以对应上我的T430了。 

## T430的UEFI机制思考

  * T430的UEFI BIOS会搜索所有分区寻找每一个UEFI boot target（也就是efi后缀的文件）吗？ 
    * UEFI BIOS可以识别的filesystem貌似只有fat16，fat32几个吧，所以应该不会去搜索ntfs和extn的分区，我所知道的是RHEL6的启动efi文件可以放在不是ESP的fat32分区，UEFI BIOS的boot manager里面会有RHEL的选项。我猜测，UEFI BIOS会搜索fat16/32的分区，同时，安装一个系统的时候，很可能有一种注册机制，向UEFI BIOS的boot manager注册的机制。 
  * CSM的概念（我的猜测） 
    * CSM的概念好像是必要的，对于一个硬盘的机器，可以只用纯的UEFI启动，但是如果你有一个dvd，而dvd的启动是x86 boot record，那么如果你使用的UEFI，你可能就会不能引导dvd的启动，对应的，如果你启用CSM，那么dvd是可以启动的。这才是CSM的意义所在。 
    * 更进一层，如果你有两个硬盘，那么，一个硬盘可以UEFI，一个可以x86 boot，由于CSM的存在后者中的系统应该是可以启动的。 
  * 一个硬盘要么是mbr格式的，要么是GPT格式的。 
  * gdisk是支持GPT的，不，就是为GPT硬盘而存在的；fdisk是不支持GPT硬盘的。 

UEFI理解分区表，也理解filesystems。 现在的UEFI固件支持MBR和GPT两种分区表。 大部分的UEFI
firmware都支持FAT12（软盘），FAT16和FAT32（硬盘），ISO9660（cd、dvd）。

UEFI不提取MBR的任何内容，不管其存不存在。 相对的，UEFI从分区表中找到ESP这个特殊分区，从中提取UEFI
firmware需要的数据。每个vendor都可以将他的文件存入到<EFI SYSTEM partition>/EFI/<VENDOR
NAME>/目录下，这个盒RHEL6还是很对应的，在RHEL6中，就是/boot/efi/xxx。每个vendor也能使用firmware或者UEFI
shell来开启这些boot program。

一般的ESP会使用FAT32.

在UEFI下，OS loader，memory testing apps等等，都是UEFI应用。

因为每个vendor都可以在ESP中放入自己的文件，这并不影响其他vendor的文件，所以，多引导在UEFI下就是选择的问题，很N啊。

Boot Process under UEFI 1，系统启动，自检 2，UEFI firmware加载 3，UEFI firmware读取Boot
Manager数据 4，UEFI firmware启动boot manager中的某一个应用，大多是ESP中的一个。 5，这个UEFI
application可能是GRUB（RHEL6就是这么干的），可能是其他的UEFI application。

## GPT磁盘

所有用于解释GPT磁盘分区方案所需的信息完全包含在物理媒体指定位置的结构中。

我觉得吧，windows的很多文档里都说到了ESP，但windows并没有把它当做一个各种系统共用的分区，而是将之看做是自己独有的分区，windows对其E
SP的使用也没有关心规范什么的，里面的内容恐怕都是按照windows自己的风格放置的。

一个硬盘要么是MBR，要么是GPT的。

很明显，我现在的硬盘是GPT的。

GPT是如何实现的：

  1. 第一个block是MBR，这里的block就是扇区，512字节。LBA0 
    * 因为这一点，所以，在一个BIOS+GPT的系统上，从GPT启动是可能的，实现的方法是MBR中指定boot loader的地址，但boot loader和OS都必须是识别GPT的，这才能保证OS的正常启动。 
  2. 第二个block是GPT header。LBA1 
    * GPT header中放置着指向partition entry array的指针。 
    * 一般，入口矩阵就在LBA2上。 
  3. UEFI Specification规定partition entry array至少要有16384字节，也就是512*32，也就是说，从LBA2开始，到LBA33为止的这32个block都必须是partition entry array的。 
    * 而如果一个partition entry是128字节，那么16384字节总共就可以放置128个partition entry。 
    * 这里还有可以说的地方，windows的实现支持128个分区，那么90%的可能性windows就是按照上面这么干的，windows安装的时候，会将磁盘格式化为GPT磁盘，在这一过程里面就将partition entry array固化为了16384字节，而同时使用128字节一个partition entry。从而导致了128个分区的限制。 
    * 如果windows将partition entry array扩大一倍，partition entry仍然是128字节，那么分区数目就可以达到256个了。 
  4. 我的T430是先安装的windows7，所以可以预见，我的磁盘是上述实现。而从LBA34开始，才是真实可用的空闲空间。 
  5. partition header和partition entry array有备份，在磁盘的最后33个block，1个header和32个array。 
    * partition header里面第一个可用的block的地址；disk guid；第一个partition entry的位置，有多少个partition entry，partition entry的size是多少；crc32 header，crc32 partition array。 
  6. LBA是一种计算方式，是按照扇区或者block来的，至于扇区里面有多少byte，其实不关心。多的byte，空着呗。 
  7. partition entry里面 
    * 第一个16byte，是分区类型GUID 
    * 第二个16byte，是分区GUID 
    * 第三个16byte，是起始和结束LBA 
    * 第四个8byte，是分区的属性标志。 
    * 剩下的72byte，是分区的名字。 
  8. 以上。 

# OVER

