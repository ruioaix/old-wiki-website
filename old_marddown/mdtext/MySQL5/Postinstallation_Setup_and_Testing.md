# Postinstallation Setup and Testing

在安装MySQL之后，有一些问题要注意，比如初始化账户是没有密码的。

## Unix Postinstallation Procedures

在安装完MySQL之后，必须初始化the grant tables。 在Unix上，the grant tables是通过mysql_install_db
program来设置的。 如果使用RPM安装MySQL，那么RPM会自动运行这个program。

......

这一节里虽然介绍的是安装之后应该注意的东西，但是，这里的安装之后其实与我所经历的安装之后有很大差异，这里安装之后的一步一步其实在各个linux发行版中都包含
在安装过程之中了。

也就是说，现在很多时候，比如apt-get和rpm，yum安装方式，都已经替我们考虑了这一节所介绍的事情。

暂且就这样吧。

## Securing the Initial MySQL Accounts

......

