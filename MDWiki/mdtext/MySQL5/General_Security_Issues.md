# General Security Issues

## Security Guidelines

当运行MySQL的时候，要遵循以下规则：

  * 不可以将 `mysql` database中的`user`table的访问权交给除了 **root** 之外的任何人。 
  * 理解MySQL access Privilege system的工作方式，使用 **grant** 和 **revoke** 语句来控制MySQL的访问。 
    * 不要授予超过需求的权限。 
    * 不要所有权限给all hosts。 
    * `show grants;`查看账户和对应权限。 
  * 不要明文存储密码，应该使用`sha2(),sha1(),md5(0`等单向加密算法。 
  * 不要使用字典中的密码。 
  * 建立防火墙。MySQL的默认端口是3306。 
  * 使用MySQL的应用不应该相信用户的输入，用户的输入应该经过一些处理。 
  * 不要在internet使用明文传递信息，应该使用ssh这种加密通道。 
  * 学习使用 **tcpdump** 和 **strings** 工具来查看你的MySQL数据流是否加密过。 
    * `tcpdump -l -i wlan0 -w - src or dst port 3306|strings`

## Keeping Passwords Secure

MySQL用户应该使用以下方针来保证密码安全：

  * 不要该直接在command line中使用密码，即直接在`-p`options之后写入密码。 
  * 在command line的`-p`后不接密码，而在之后的交互中输入；这种很安全，但是在运行script的时候，可能不方便，或者出现因为没有密码中断script的情况。 
  * 使用options file。安全。 
  * 将密码存入 **MYSQL_PWD** 环境变量。极度不安全。 
  * **.my.cnf** 和 **.mysql_history** 和 **.bash_history** 这种可能记录有你密码的文件应该设置成严格的权限。比如600，400。 

有一些SQL语句会记录密码明文，比如 **create user** ， **grant** ， **set password**
。这些语句会被记录进入MySQL的日志文件，所以这些日志文件的访问权限应该被严格控制。

MySQL 在mysql database中的user表中记录用户账户，包括用户的密码，这些密码是被加密过的。

  * MySQL通过两步来使用密码 
    * client programs首先提供一个hash加密的值，这个值必须和user table中对应账户的一个密码加密值所匹配（相等）。 
    * 当连接好之后，clients可以设置或者改变密码，clients可以使用password()这种函数来产生一个加密密码值。 
    * 换句话说，server在验证用户的时候，使用hash值来验证；当client使用password()或者其他密码语句时，server会产生一个hash值。 

MySQL中密码加密的方法是在不断变化的。

  * 具体描述暂且不管。 

## Making MySQL Secure Against Attackers

为了使MySQL更安全，你应该很慎重的考虑一下建议：

  * 每个MySQL账户都应该有密码。 
  * 不要该使用 **root** 用户来启动MySQL，这样的话，任何拥有`FILE`权限的人都可以像root一样的建立文件，比如`/root/.bashrc`。 
    * `mysqld`除非使用`--user=root`选项，否则不会以root身份运行。 
    * `mysqld`有其自己的身份， **mysql** 用户。在`/etc/my.cnf`文件中就有： 
    
    
        [mysqld]
        user=mysql
    

    * 这就是mysqld的启动身份。 
    * **User names for MySQL accounts have nothing to do with user names for Unix accounts.**
    * 上面的话是说，运行mysqld的是Unix账户，而mysqld里面存储的账户和Unix账户是没有关系的。 
    * 比如`mysql -uroot -p`，说的是使用mysqld里面的root用户来登录mysqld，这个root和Unix系统里面的root没有任何关系。 
  * 等等 

# OVER

