# Automating System Tasks

RHEL使用automationg system tasks来保证系统的更新。

RHEL使用的automated task utilities有 **cron** ， **anacron** ， **at** ， **batch** 。

前两者是循环执行，后两者是单次执行。这里感兴趣的只有前两者。

## Cron and Anacron

  * cron和anacron都是daemon。 
  * cron可以到每分钟执行task的速度，但是，它假设电脑一直运行着，如果在要执行task的时候电脑关闭着，那么cron就忽略这个task。 
  * anacron则不是，即使当时电脑关闭着，anacron也不会忽略task，而是在电脑启动时进行执行。不过，anacron一天只能运行一个task。 
  * cron是由cronie软件包提供的，anacron是由cronie-anacron软件包提供的。后者是前者的一部分，所以当安装cron的时候，anacron必定也安装了。 
  * `/etc/init.d/crond`控制cron和anacron。 

## Anacron的配置文件

  * `/etc/anacrontab` 当前我的电脑上的内容： 
    
    
    # /etc/anacrontab: configuration file for anacron
    
    # See anacron(8) and anacrontab(5) for details.
    
    SHELL=/bin/sh
    PATH=/sbin:/bin:/usr/sbin:/usr/bin
    MAILTO=root
    # the maximal random delay added to the base delay of the jobs
    RANDOM_DELAY=45
    # the jobs will be started during the following hours only
    START_HOURS_RA=3-22
    
    #period in days   delay in minutes   job-identifier   command
    1       5       cron.daily              nice run-parts /etc/cron.daily
    7       25      cron.weekly             nice run-parts /etc/cron.weekly
    @monthly 45     cron.monthly            nice run-parts /etc/cron.monthly
    

  * **MAILTO=root** 表示anacron执行task的输出寄给root。 
  * 第一个task是执行`/etc/cron.daily`中的脚本，每天一次，在3:11到22:50会被触发。 
  * 第二个task是执行`/etc/cron.weekly`中的脚本，每周一次，大概也是在上面的时间吧。 
  * 第三个task是执行`/etc/cron.monthly`中的脚本，每月一次。 

## cron配置文件

  * `/etc/crontab` 当前我的电脑上的内容： 
    
    
    SHELL=/bin/bash
    PATH=/sbin:/bin:/usr/sbin:/usr/bin
    MAILTO=root
    HOME=/
    
    # For details see man 4 crontabs
    
    # Example of job definition:
    # .---------------- minute (0 - 59)
    # |  .------------- hour (0 - 23)
    # |  |  .---------- day of month (1 - 31)
    # |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
    # |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
    # |  |  |  |  |
    # *  *  *  *  * user-name command to be executed
    

  * 具体的内容就不关心了。 
  * crond daemon会每分钟检查一次`/etc/anacrontab`,`/etc/crontab`,`/etc/cron.d/`,`/var/spool/cron/`。如果有变化，就将变化加载入内存中。 

# OVER

RHEL6的task主要是由anacron执行的，包括dailyjob，weeklyjob，monthlyjob。

只有hourjob是通过cron来执行的，通过`/etc/cron.d/0hourly`来执行。

总的来说：

  * anacron：dailyjob，weeklyjob，monthlyjob。 
  * cron：hourlyjob，cron.d目录下的其他，/var/spool/cron/目录下的其他。 

