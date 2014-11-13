# 在RHEL6上安装SKYPE

在RHEL6上安装skype，对于32位机和64位机有些许不同。 下面的安装过程按照32位机来，64位机不同的地方我会特别指出。

  * 安装一些总要装的库 
    * `yum install alsa-lib.i686 fontconfig.i686 freetype.i686 \`
    * `glib2.i686 libSM.i686 libXScrnSaver.i686 libXi.i686 \`
    * `libXrandr.i686 libXrender.i686 libXv.i686 libstdc++.i686 \`
    * `pulseaudio-libs.i686 qt.i686 qt-x11.i686 zlib.i686`
    * 注意，这里都带了后缀，指定是i686，也就是32位机。 
    * 如果不带后缀，那么yum会自动根据系统的情况来选择x86_64或者i686。 
    * **在64位机器上，上面这些包的64位版本一般都已经安装过了，但仍然需要安装32位版本（也就是上面的i686版本）**
  * 下载skype包，从[http://www.skype.com/intl/en/get-skype/on-your-computer/linux/](http://www.skype.com/intl/en/get-skype/on-your-computer/linux/) 这个网址，其中没有RHEL的，所以使用`Static`。当前的版本是4.0.0.8。 
    * 目前上面的网站已经没有`Static`了，取而代之的是`dynamic`，版本也变成了4.1.0.20。（2012.11.22） 
    * 这个版本目前再RHEL6上没有稳定的安装方法，Centos社区也建议仍然使用4.0.08的版本。地址：[http://download.skype.com/linux/skype_static-4.0.0.8.tar.bz2](http://download.skype.com/linux/skype_static-4.0.0.8.tar.bz2)
  * 解压 
  * `su -`
  * `mkdir /opt/skype`
  * `tar xvf skype_static-4.0.0.8.tar.bz2 -C /opt/skype`
  * `cd /usr/lib`
  * `ln -s libtiff.so.3 /usr/lib/libtiff.so.4` 这一步在32位机器上是可以的，但在64位机器上，会发现在 **/usr/lib/** 下没有libtiff.so.3，这是因为机器上没有安装i686版本的libtiff（也就是32位版本的），这个时候需要你使用`yum install libtiff.i686`来强制在64位机器上安装32位的包。 
  * `ln -s /opt/skype/skype.desktop /usr/share/applications/skype.desktop` 这几句话作用是将skype放入到RHEL左上角的applications菜单中。 
  * `ln -s /opt/skype/icons/SkypeBlue_48x48.png /usr/share/icons/skype.png`
  * `ln -s /opt/skype/icons/SkypeBlue_48x48.png /usr/share/pixmaps/skype.png`
  * `vim /usr/bin/skype`
    
    
        #!/bin/bash
        export SKYPE_HOME="/opt/skype"
        $SKYPE_HOME/skype --resources=$SKYPE_HOME $*
    

  * `chmod 755 /usr/bin/skype`

# OVER

