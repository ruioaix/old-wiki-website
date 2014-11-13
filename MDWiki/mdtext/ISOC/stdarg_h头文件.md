# stdarg.h

本头文件提供了使我们能够自己编写带有变长参数列表的函数。如同printf和scanf。

本头文件声明了一种类型（va_list）并定义了几个宏。

C89中有三个宏：va_start,va_arg,va_end。C99增加了va_copy。

vfprintf，vprintf，vsprintf函数都属于stdio.h。在C99中，增加了vsnprintf函数。这些函数总是和stdarg.h中的宏联
合使用。

    
    
    static void
    pr_sysconf(char *mesg, int name)
    {
    	long	val;
    
    	fputs(mesg, stdout);
    	errno = 0;
    	if ((val = sysconf(name)) < 0) {
    		if (errno != 0) {
    			if (errno == EINVAL)
    				fputs(" (not supported)\n", stdout);
    			else
    				err_sys("sysconf error");
    		} else {
    			fputs(" (no limit)\n", stdout);
    		}
    	} else {
    		printf(" %ld\n", val);
    	}
    }
    

  * 上面的函数中使用了err_sys函数。 
    
    
    void
    err_sys(const char *fmt, ...)
    {
    	va_list		ap;
    
    	va_start(ap, fmt);
    	err_doit(1, errno, fmt, ap);
    	va_end(ap);
    	exit(1);
    }
    

  * 上面的函数中首先定义了 **va_list ap;** 。 
  * 然后初始化 **va_start(ap, fmt);** 。 
  * 之后使用了err_doit函数。 
    
    
    static void
    err_doit(int errnoflag, int error, const char *fmt, va_list ap)
    {
    	char	buf[MAXLINE];
    
    	vsnprintf(buf, MAXLINE, fmt, ap);
    	if (errnoflag)
    		snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s",
    		  strerror(error));
    	strcat(buf, "\n");
    	fflush(stdout);		/* in case stdout and stderr are the same */
    	fputs(buf, stderr);
    	fflush(NULL);		/* flushes all stdio output streams */
    }
    

  * 上面使用了 **vsnprintf(buf, MAXLINE, fmt, ap)** 。 
  * 这个函数的意思是将ap的值嵌入到fmt中，就像printf（fmt，ap）的意思，然后，嵌入了的fmt放入buf中，但最多放入buf中MAXLINE个字符。 
  * 然后又使用了 **snprintf(buf, MAXLINE, ": %s", str)** 。这同上面的一样，只不过vsnprintf中的ap可以是多个参数，而snprintf只能是一个参数。同样放入buf中。 
  * 然后给buf添加一个换行符。 
  * 然后将buf输出。 
  * 对于err_sys，同样的输出错误信息，然后结束，返回1。 

