# The MySQL Server

mysqld 就是 MySQL server，启动mysql的时候使用的命令`/etc/init.d/mysqld start`与此有一定的对应关系。

## Server Option and Variable Reference

  * MySQL server的配置选项和变量有以下几种： 
    * command-line options 
    * options in configuration files 
    * server system variables 
    * status variables（global，session或者both） 
  * MySQL server有很多的操作参数，你可以在启动时候用command-line options设置，也可以在configuration files中进行options设置。 
  * 在server运行时，也可以改变非常多的参数。 
  * MySQL server提供了很多配置好的配置文件，你可以直接拿来作为你自己配置的基础。 

## Server Command Options

  * mysqld 读取[mysqld]和[server]节的options。 
  * mysqld_safe 读取[mysqld]，[server]，[mysqld_safe]，[safe_mysqld]节的options。 
  * mysql.server读取[mysqld]，[mysql.server]节的options。 

# OVER

这节的东西太过于细节了，不再细看。

