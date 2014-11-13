# Chapter 5. Standard I/O Library

15 sections.

## Section 5.1. Introduction

相比较于system I/O，Standard I/O处理了buffer。或者说，多了个buffer。

## Section 5.2. Streams and FILE Objects

FILE包含的东西还是很多的：实际文件的描述符，buffer，buffer point，buffer
size，当前buffer的字符数目等等，主要集中在两个方面，一个是文件，一个buffer。

## Section 5.3. Standard Input，Standard Output， and Standard Error

一个process总有三个stream可用：`stdin`, `stdout`, `stderr`。三个指针，在stdio.h中定义了。

## Section 5.4. Buffering

buffer存在的理由是减少`read`和`write`的使用。

三种buffer，fully buffered，line buffered，unbuffered。实际学习函数的时候，应该可以理解的更深刻一些。

在之前的章节中，说到了三个file descriptor：0，1，2，这三个描述符对应的文件现在本包含在了FILE结构中，分别是三个stream：stdin
，stdout，stderr。对于system call，前面三个fd总是存在于process中的，对于standard
I/O后面三个总是存在于process中的。

绝大部分的系统：stderr是unbuffered，终端使用的stream是line buffered的，所有其他的stream都是fully
buffered的。

可以设置stream的buffer类型，stream是FILE，buffer是buffer。

还有个重要的概念：

  * buffer是对I/O来说的。 
  * 对于O，也就是output，具有flush这一操作，操作的内容是将未output的buffer里面的内容output，这一操作还是很有意思的，未output的内容要output最终需要调用的是write函数，也就是数据先要发送的kernel，然后kernel调用write函数将内容写到硬盘或者终端，或者其他。 
  * flush只是对O来说的，对I没有意义。 

## Section 5.5. Opening a Stream

fopen,freopen,fdopen，三个函数，返回的都是FILE指针。

作用都是将一个文件和一个stream联系起来，在这三个函数之后，可以修改stream里面的buffer，设为fully，line，或者un，都是可以的。

本质上，FILE就是file descriptor上面的一层包装。

## Section 5.6. Reading and Writing a Stream

打卡一个stream，可以对stream进行操作了。

unformatted I/O，formatted I/O。

  * `#include <stdio.h>`
  * `int getc(FILE *fp);`
  * `int fgetc(FILE *fp);`
  * `int getchar(void);`
  * `int ferror(FILE *fp);`
  * `int feof(FILE *fp);`
  * `void clearerr(FILE *fp);`
  * `int ungetc(int c, FILE *fp);`
  * `int putc(int c, FILE *fp);`
  * `int fputc(int c, FILE *fp);`
  * `int putchar(int c);`

当到达FILE所包含的文件尾部，fgetc返回EOF，这是一种机制吧。EOF本不存在于文件中。ungetc不能push back EOF，这很好理解了。

ungetc和putc操作的FILE必须可写吧，getc操作的FILE必须可读吧。

## Section 5.7. Line-at-a-Time I/O

  * `#include <stdio.h>`
  * `char *fgets(char *restrict buf, int n, FILE *restrict fp);`
  * `char *gets(char *buf);`
  * `int fputs(const char *restrict str, FILE *restrict fp);`
  * `int puts(const char *str);`

fgets一次最多读取n-1个char，最有一个char放null。一行多余n-1个char，就分两次读。一行不到n-1个char，应该是直接读取这一行吧。

fputs严格来书不算line output，因为，他输出一段c字符串到FILE，这段字符串不必以newline结尾。

## Section 5.8. Standard I/O Efficiency

这里，有个概念：

  * 如前面所述，stream可以是没有buffer的，当然也可以有，fully，line。 
  * getc这种每次操作一个字符的函数，操作的对象是stream。 
  * getc给人一种单个字符怎么缓冲的错觉，但实际情况是，getc虽然一次一个字符的操作，但其操作的stream可以有缓冲的，所以getc调用的虽然多，但read调用的可以很少。 
  * 如果getc操作的无buffer的stream，那么我想比read(1)还慢很多吧。 

本节的重点是分清楚这些函数和stream。

## Section 5.9. Binary I/O

这两个函数还是蛮好理解的。

  * `#include <stdio.h>`
  * `size_t fread(void *restrict prt, size_t siez, size_t nobj, FILE *restrict fp);`
  * `size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);`

关于这个函数的致命缺点，现在还理解不到，之后应该会理解。

## Section 5.10. Positioning a Stream

  * `#include <stdio.h>`
  * `long ftell(FILE *fp);`
  * `int fseek(FILE *fp, long offset, int whence);`
  * `void rewind(FILE *fp);`
  * `off_t ftello(FILE *fp);`
  * `int fseeko(FILE *fp, off_t offset, int whence);`
  * `int fgetpos(FILE *restrict fp, fpos_t *restrict pos);`
  * `int fsetpos(FILE *fp, const fpos_t *pos);`

上面的3对都是配合的，前者给出一个位置，后者使用这个位置。这是肯定可以的使用方法，其他的不能肯定一定可以。

## Section 5.11. Formatted I/O

  * `#include <stdio.h>`
  * `int printf(const char *restrict format, ...);`
  * `int fprintf(FILE *restrict fp, const char *restrict format, ...);`
  * `int sprintf(char *restrict buf, const char *restrict format, ...);`
  * `int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);`

这几个都还比较好理解。

  * `#include <stdarg.h>`
  * `#include <stdio.h>`
  * `int vprintf(const char *restrict format, va_list arg);`
  * `int vfprintf(FILE *restrict fp, const char *restrict format, va_list arg);`
  * `int vsprintf(char *restrict buf, const char *restrict format, va_list arg);`
  * `int vsnprintf(char *restrict buf, size_t n, const char *restrict format, va_list arg);`

和上面完全对应的，都加了一个v。

  * `#include <stdio.h>`
  * `int scanf(const char *restrict format, ...);`
  * `int fscanf(FILE *restrict fp, const char *restrict format, ...);`
  * `int sscanf(const char *restrict buf, const char *restrict format, ...);`

同上，还有3个，加v的对应上面的函数。

总结下，是这样的，终端一个，一个stream，一个char *buf。每样一个。再加上参数的变化，每样一个，输出输入，每样一个。

## Section 5.12. Implementation Details

这里说的是stream的细节，其实也没什么太多的细节，让你自己看。就自己看吧。

细节都在FILE struct中。

## Section 5.13. Temporary Files

这种东西存在的意义是用来临时的保存内容到文件中？

  * `#include <stdio.h>`
  * `char *tmpnam(char *ptr);`
  * `FILE *tmpfile(void);`
  * `char *tempnam(const char *dir, const char *prefix);`
  * `#include <stdlib.h>`
  * `int mkstemp(char *template);`

## Section 5.14. Alternatives to Standard I/O

各种替代standard I/O的库。接口相同吗？

## Section 5.15. Summary

**OVER** tmpfile的实现经常使用tmpnam来搞。 
