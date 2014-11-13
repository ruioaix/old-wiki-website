# MySQl 5.5 Reference Manual

用于MySQL5.5到MySQL5.5.30之间的版本，我当前使用的是5.5.28，从remi中获得。 [http://dev.mysql.com/doc/
refman/5.5/en/index.html](http://dev.mysql.com/doc/refman/5.5/en/index.html)

## Tutorial

  * linux中在终端使用的mysql命令，是一个客户端程序，可以使用这个程序同MySQL servr进行交互。 
  * mysql命令可以交互着来，也可以使用batch mode（读取已经放入命令的文件，顺序执行）。 
  * 也就是说，安装LAMP组合的时候，M其实包含两部分：mysql命令和MySQL server。 
  * 使用mysql命令来交互MySQL server的时候，通常第一件事是建立连接： 
    * `mysql -h host -u username -p`
    * 然后输入用户密码，本机登录的话，`-h host`可以省略。 
  * mysql命令做的事情就是将命令发给MySQL server，后者执行并反馈结果，mysql再显示结果。 
  * mysql命令显示结果的方式是表格，并会给出有多少行结果，执行所耗费的时间（这是粗略的时间）。 
  * mysql中数据库和表的名字都是大小写敏感的。 
  * `create database test_database_name;`
  * `use test_database_name` 这个命令不需要分号结尾 
  * 在连接MySQL server之后，每次都需要选择自己所要操作的数据库，但是也可以在连接的时候设置。 
    * `mysql -h host -u user -p test_database_name` ，就是在其他所有命令选项之后，加入自己要选择的database即可。 
    * 上面的`-p`之后如果直接输入密码，那么p和密码之间不要有空格。 
  * 使用`select database();`查看当前选择的数据库。 
    * `create table test_table_name(name varchar(20), other1 varchar(20), other2 varchar(20), sex char(1), birth date, death date);`
    * `describe test_table_name;` 给出详细的表内容。 
    * `load data local infile '/root/pet001' into table pet;`
    * `insert into pet values('puffball','dianna','hamster','f','1999-02-20',null);`
  * `select`命令用来查看table中的内容。 
    
    
        select what_to_select
        from which_table
        where conditions_to_satisfy;
    

    * `select * from pet;` 查看pet table中的所有内容。 
    * `delete from pet;` 删除pet table中的所有。 
    * `update pet set birth='1999-03-24' where name='bowser';`
    * `select * from pet where name='whitler';` 输出一行，string的比较通常是大小写不敏感的。 
    * `select * from pet where species='dog' and sex='f';`
    * `select * from pet where species='dog' or sex='f';`
    * `select name,birth from pet;`
    * `select distinct owner from pet;` 多个条目中都有一个owner的时候，可以让这个owner只出现一次。 
    * `select name,species,birth from pet where species='dog' or species='cat';` 结合行和列的选择。 
    * `select name,birth from pet order by birth;`
    * `select name,birth from pet order by birth desc;`
    * `select name,species,birth from pet order by species,birth desc;` 先按照种类排序，然后在一种种类内部按照生日降序显示。 
    * `select name,birth,curdate(),(year(curdate())-year(birth))-(right(curdate(),5)<right(birth,5)) as age from pet order by age;`
    * `select name,birth,month(birth) from pet where month(birth)=5;`
    * **null** 表示 一个不知道的值。不能被直接用于比较。可以用的 **is not null** 。这种方式不错。 
    * 0不是null，使用`select 0 is null;`会出现0，也就是说0不是null。 
    * sql的模式匹配和linux终端的表示方法很像，`_`表示一个未知字母，`%`表示任意未知字母的组合。在where中用 **like** 和 **not like** 来比较。 
    * 匹配的方式还有一种 **regexp** 。 
    * `select count(*) from pet;` 计算总共有几只宠物。 
    * `select owner,count(*) from pet group by owner`
    * `select species,count(*) from pet group by species`
    * `select species,sex,count(*) from pet group by species,sex;`
    * `mysql -h host -u user -p < batch-file`
  * Examples of Common Queries 
    * `select max(article) as article from shop;`
    * `select article,dealer,price from shop where price=(select max(price) from shop);`

## MySQL Server Administration

  * [The_MySQL_Server](The_MySQL_Server.html)
  * [MySQL_Server_Logs](MySQL_Server_Logs.html)

## MySQL Programs

介绍MySQL command-line programs。

  * [Overview_of_MySQL_Programs](Overview_of_MySQL_Programs.html)
  * [Using_MySQL_Programs](Using_MySQL_Programs.html)
  * [MySQL_Server_and_Server_Startup_Programs](MySQL_Server_and_Server_Startup_Programs.html)

## Security in MySQL

  * [General_Security_Issues](General_Security_Issues.html)
  * [Postinstallation_Setup_and_Testing](Postinstallation_Setup_and_Testing.html)
