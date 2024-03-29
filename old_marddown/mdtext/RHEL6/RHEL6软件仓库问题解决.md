# RHEL6的软件仓库问题解决

RHEL自带的软件仓库是要钱的，买的是服务吗。 之前也曾经使用centos6的仓库，但是当`yum
update`之后，RHEL左上角applications旁边的小红帽不见了，开机画面变成了centos6的，这样实在不伦不类。
现在我是通过建立本地仓库，同时使用第三方仓库的方案来解决软件仓库的问题。

## 本地仓库

  * RHEL的光盘镜像iso文件中存在着仓库，可以将iso的文件拷贝到本地，并建立本地仓库。 
  * 切换到root账户`su -`，建立`/yum/`目录，将iso中所有文件都拷贝到该目录下。 
  * RHEL所有的仓库配置文件都放在`/etc/yum.repos.d/`目录中，建立一个本地仓库配置文件`yumlocal.repo`。 
  * `su -`
  * `cd /etc/yum.repos.d/`
  * `vim yumlocal.repo`
    
    
        [local]
        name=local
        baseurl=file:///yum/Server
        enable=1
        gpgcheck=0
    

  * `yum clean all`
  * `yum update`
  * `yum list` 可以查看本地仓库中有哪些文件。 

## 第三方仓库

第三方仓库我一般使用两个： **EPEL** 和 **rpmfusion** 。 同时，还有一个 **remi**
，这个虽然我有安装，但是保持了它本身的`enable=0`，只在某些库找不到的时候在这里查看一下。

  * EPEL的安装很简单，去官网：[http://fedoraproject.org/wiki/EPEL](http://fedoraproject.org/wiki/EPEL) ，下载对应的rpm，双击安装即可。 
  * rpmfusion同上，官网: [http://rpmfusion.org/Configuration](http://rpmfusion.org/Configuration) 。 
  * remi同上，官网：[http://rpms.famillecollet.com](http://rpms.famillecollet.com) 。 
  * 值得注意的是，EPEL和rpmfusion安装后，默认就是enable的，remi默认是unenabled。 
  * enable与否的设置在`/etc/yum.repos.d/`目录中对应的配置文件中。 
  * 当前，我的`/etc/yum.repos.d/`目录中有的配置文件： 
    1. adobe-linux-x86_64.repo 
    2. epel.repo 
    3. epel-testing.repo 
    4. google-chrome.repo 
    5. remi.repo 
    6. rpmfusion-free-updates.repo 
    7. rpmfusion-free-updates-testing.repo 
    8. rpmfusion-nonfree-updates.repo 
    9. rpmfusion-nonfree-updates-testing.repo 
    10. yumlocal.repo 

补充：还有一个仓库，rpmforge。可以在[http://pkgs.repoforge.org/rpmforge-
release/](http://pkgs.repoforge.org/rpmforge-release/) 这里找到rpmforge-release-0.
5.2-2.el6.rf.x86_64.rpm，安装即可。里面有smplayer。安装smplayer的时候，可能会出现在菜单Applications里的条
目没有图片，这时使用`ln -s /usr/share/icons/hicolor/64x64/apps/smplayer.png
/usr/share/icons/smplayer.png`。

## 删除RHEL收费仓库相关的软体

  * 不删除的话，系统会经常性的提醒你注册，我是无法忍受这种烦恼的。 
  * 和RHEL收费仓库相关的软体主要是两类 
    * rhn（redhat network） 
    * subscription-manager 
  * 使用`rpm -qa|grep subscription-manager`，检查与`subscription-manager`相关的软体。 
    * 一共有3个。 
    * `rpm -e subscription-manager-firstboot subscription-manager-gnome subscription-manager`
  * 使用`rpm -qa|grep rhn`，检查与`redhat network`相关的软体。 
    * 一共有7个。 
    * `rpm -e rhn-check rhn-setup rhnlib rhnsd yum-rhn-plugin rhn-setup-gnome rhn-client-tools`

## other tips

# OVER

