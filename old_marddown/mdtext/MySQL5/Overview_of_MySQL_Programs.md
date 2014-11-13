# Overview of MySQL Programs

在MySQL中有很多不同的程序。大部分的MySQL发行版本中都包含了将要介绍的这些程序。每个程序都有自己特殊的options，可以使用`--help`命令来
查看。 这些程序的配置都是可以改写的，通过制定在command line指定options或者是通过option files。

  * **mysqld** 是MySQL中完成大多数工作的主要程序，the SQL daemon，这个程序是通过几个相关的scripts结合起来实现的。要使用client programs， **mysqld** 必须运行。 
  * **mysqld_safe** 是一个server启动脚本。 
  * **mysqld.server** 也是一个server启动脚本，会调用 **mysqld_safe** 。 
  * **mysqld_multi** server启动脚本，多servers on a system。 
  * **comp_err** 在MySQL编译安装的时候使用。 
  * **mysql_install_db** 建立MySQL database，只在安装MySQL的时候运行一次。 
  * **mysql_plugin** 用于配置MySQL server plugins。 
  * **mysql_secure_installation** 加强MySQL安装时候的安全性。 
  * **mysql_tzinfo_to_sql** 使用host system zoneinfo database来load the time zone tables in the mysql database。 
  * **mysql_upgrade** 在MySQL更新之后使用，用于验证数据完整性，并在必要时修复他们。 
  * **mysql** 用于输入SQL语句的的command-line工具。 
  * ...... 

