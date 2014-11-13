# MySQL Server and Server-Startup Programs

讲述几个启动MySQL server的programs，包括：mysqld，mysql_safe.

## mysqld - The MySQL Server

mysqld就是MySQL主要的程序，也被认为就是MySQL server本身。

  * MySQL server管理对放置有数据库和表的MySQL data directory的访问。 
  * 当MySQL server启动后，它就开始监听来自于client programs的连接，并控制这些clients对数据库的访问。 
  * mysqld在启动的时候有很多的选项可以指定。 
  * 在mysqld运行的时候，也有很多的系统变量可以设置从而影响其操作。 
  * MySQL server也有很多的状态变量用来显示当前操作的信息。可以监测这些状态变量来查看server的运行表现。 

## others

  * mysqld_safe，在unix系统上被推荐使用的启动mysqld的方式。 
  * mysql.server，与system v-style相关的启动方式。 
  * mysqld_multi，多个mysqld进程相关。 

# OVER

