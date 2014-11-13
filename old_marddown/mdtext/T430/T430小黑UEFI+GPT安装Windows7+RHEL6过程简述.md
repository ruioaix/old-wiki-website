# T430小黑UEFI+GPT安装Windows7+RHEL6过程简述

凭记忆去描述。

## BIOS设置

首先在BIOS中设置UEFI only，CSM开启。我一直没有使用独显，在BIOS中设置只使用核芯显卡且独显不可被OS探测。

需要注意的一个事情是LENOVO UEFI BIOS在1.16和2.50版本的时候RHEL6.3是可以正常使用的，前些日子从1.16升级BIOS到2.20，
结果RHEL6.3出现了屏幕右移、颜色错误的情况，从2.20升级到2.50之后，这一bug被修复。问题应该是BIOS中的代码影响了RHEL6的显卡驱动。

## Windows 7安装

先安装Windows7，直接download的msdn的cn_windows_7_ultimate_with_sp1_x64_dvd_u_677408.is
o，然后使用ultroISO将镜像写入到U盘，结果不能正常启动安装。

对这个镜像进行修改，在efi目录中添加了 **boot\BOOTX64.efi**
。也就是说现在，efi目录下，有两个目录了，一个是microsoft，一个是boot。至于这个BOOTX64.efi文件，是从
**source\install.wim** 文件中提取的，提取路径是 **Windows\Boot\EFI\bootmgfw.efi** 文件要重命名为
**BOOTX64.efi** 。

修改镜像之后，刻录到U盘，U盘引导启动，然后进入windows安装程序，在分区的时候，使用 **shift+F10** 打开命令行，键入
**diskpart.exe** 回车，打开diskpart工具。

使用该工具将硬盘转化为GPT硬盘，这里要注意，如果硬盘上还有分区，那么 **convert GPT**
就会失败，所以，需要先用diskpart将所有分区都删除掉。然后再 **convert GPT** 。

转化为GPT硬盘之后，还是使用diskpart来创建分区，这里有个好处，之后会讲。

先创建ESP分区，也就是 **EFI system partition**
分区。这是每个GPT硬盘上都必须有的一个分区，我给了500M，这个分区不仅仅是用来放置windows的EFI
application（一般是efi后缀的文件，用于引导对应OS启动），之后还会放置所有其他OS的EFI
application。我大概会用到三到四个系统，所以分了500M，应该足够了。

ESP分区创建后，再创建一个MSR分区，这个不是mbr，这是windows的保留分区，我分200M给它。

上述两个分区是windows在UEFI+GPT系统上必须提前分配好的分区，之后就可以建立用来安装windows系统的分区，也就是C盘。我给了70G。

整个使用diskpart的过程是：

  * `list disk` 查看有哪些硬盘
  * `select disk 0` 选择主硬盘
  * `list partition` 查看有那些分区
  * `select partition n` 选择分区
  * `delete partition` 删除分区，只有删除所有分区，才可以convert gpt
  * `convert GPT` 硬盘转换为GPT格式的
  * `create partition esp size=500` 建立esp，size默认是M
  * `create partition msr size=200`
  * `create partition primary size=71000`

diskpart的使用说明：[http://support.microsoft.com/kb/300415/zh-
cn](http://support.microsoft.com/kb/300415/zh-cn)

上面的使用diskpart来分区的方式相比较于之间使用图形界面来分区要复杂的多，但有一个好处。当你使用windows安装程序的图形界面来建立分区的时候，你只
能建立数据分区，也就是C盘，D盘这种分区，ESP和MSR分区的建立都是windows安装程序自动建立的，导致的一个结果就是ESP只有一两百兆，这个大小对wi
ndows来说足够了，但对于多系统的用户就不适合了。

之后windows的安装过程就傻瓜式的，一步到底。

## RHEL6.3 安装

安装好windows之后，需要安装RHEL6。

RHEL6的光盘使用的是 **rhel-server-6.3-x86_64.iso** ，这个iso直接支持U盘UEFI安装。但你需要一个大U盘。先使用ul
traISO刻录iso到U盘，然后，将iso文件直接copy到U盘根目录，这需要大概8G的空间。

U盘引导启动，next，next……到了选择image的那一步，先选 **hard disk** ，再选 **/dev/sdb4** （这是U盘），然后ne
xt就到了图形化的安装界面，然后常规的next，next，到了分区这一步，需要注意，首先要选择已经存在的，在安装windows时候建立的ESP分区，在其上挂
载 **/boot/efi** ，然后再建立`/boot`,`/`等分区，之后一路到底。

这里还要注意的事情是，如果你为 **/boot/efi** 建立了一个新的分区，RHEL6还是可以启动的，只不过这个分区是一个奇怪的ESP，LENOVO
UEFI BIOS可以识别RHEL6的存在，但 **/boot/efi** 的GUID类型并不是ESP。应该说是不符合规范的吧。

两者安装好了之后，在UEFI BIOS的boot manager里面就可以看见windows boot manager和Redhat Enterprise
linux两个选项了，由于现在电脑上只有一个windows，所以，选择windows boot
manager会直接开启windows7，否则会出现windows的选择界面。而Redhat Enterprise linux会打开Grub
0.99，RHEL修改之后的grub，这里面有两个选项，一个是RHEL，一个是other，但这个other是没办法启动的。

两个系统的切换。在T430上，如果想切换两个系统，就需要按F12打开boot manager选择，这是很麻烦的，所以，我默认是启动Redhat
Enterprise linux，然后修改 **/boot/efi/EFI/redhat/grub.conf** ，最后三行修改为：

  * `title Windows 7 sp1 (x86_64)`
  * ` rootnoverify (hd0,0)` 这是ESP，我的磁盘的第一个分区就是ESP，所以是0.0
  * ` chainloader /EFI/Microsoft/Boot/bootmgfw.efi`

如果想在linux下进行硬盘操作，可以使用gdisk，还是蛮好用的。

# over

