# MySQL Server Logs

MySQL server有几个日志文件。

  * Error log，开始、运行、关闭mysqld时候遇到的问题。 
  * General query log，记录从clients发来的连接，语句等。 
  * Binary log，记录改变数据库内容的语句。 
  * Relay log，data changes received from a replication master server。 
  * slow query log，记录花费时间超过`long_query_time`的查询。 

默认情况下，这些日志都没有使能（linux下）。

## Selecting General Query and Slow Query Log Output Destinaions

  * 这两个日志文件的设置是很灵活的。 
  * 在server 开始的时候，可以使用`--log-output`来指定log的输出位置。 
  * 等等 

# OVER

如果需要到时再查吧

