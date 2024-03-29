# Using MySQL Programs

  * 调用这些程序，直接在shell中输入程序名称，并添加你希望添加的选项、变量等。 
  * 虽然每个程序都有自己的options，但有一些options是大部分程序都公有的，比如`--host(-h)`，`--user(-u)`，`--password(-p)`。 

## Connecting to the MySQL Server

  * `mysql -h localhost -u myname -pmypass mydb`
  * `mysql --host=localhost --user=myname --password=mypass mydb`
  * 密码不应该放置在command line里面，因为有安全风险。 
  * 对于host option是`localhost`，MySQL programs使用a Unix socket file连接local server。 
  * 如果想确保使用TCP/IP来连接一个local server，那么host option设置为127.0.0.1；或者localserver的IP地址。 
    * `mysql -h 127.0.0.1`
    * `mysql --protocol=TCP`
  * 连接远程server一直使用TCP/IP。 
  * 对于`localhost`，如果不强制使用TCP/IP，那么，指定`--port`也是没有用的。 
  * 以上的参数都可一放入options file中。 

## Specifying Program Options

  * [Specifying_Program_Options](Specifying_Program_Options.html)

