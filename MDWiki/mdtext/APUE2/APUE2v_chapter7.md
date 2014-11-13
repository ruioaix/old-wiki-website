# Chapter 7. Process Environment

12 sections.

## Section 7.1. Introduction

process之前的准备工作。

## Section 7.2. main Function

从这节知道的就是C program是被kernel使用exec函数来执行的，所有的C program都是如此。

## Section 7.3. Process Termination

这节讲的是process的终止。所有的程序大概都是有main函数的吧，不，所有的需要编译成为可执行格式文件的程序大概都是有main函数的吧，也不一定吗？准确
的讲应该是入口函数，不同的编译环境下有不同的入口函数，在UNIX的环境下，程序的入口函数就是main函数。所以，这里讲的是AP in the UNIX
Environment.

入口函数是main，出口就很多了，3个exit，3种last thread，1个return main，1个abort，1个signal。

不可以做太多假设，我可以做的是断言：在UNIX下所有的可执行文件都有main这个入口和9个出口。

UNIX下程序执行的顺序是这样的：

  1. kernel会通过exec来call一个二进制可执行格式文件。 
  2. exec会找到这个文件的入口，也就是main。 
  3. main以及main中调用的所有的函数，以及调用函数再调用的所有函数中，任意一个函数调用`_exit();`或`_Exit();`的时候，程序从这两个出口出来了，直接返回到kernel。 
  4. 在不存在`_exit();`和`_Exit();`的条件下，如果任意一个函数调用`exit();`，那么，程序从这个出口出去，到达一个临时区域，在这个区域中，会调用一些注册函数，最后清理下所有的I/O stream，然后从这个区域返回到kernel。 
  5. 如果也不存在`exit();`，那么就是`return`了，这个出口是回到上一级函数的出口，上一级再上一级。直到main，然后再`return`，就到了kernel调用exec产生的那个区域，在这个区域会自动的调用`exit`，执行一些注册函数，清理下，回到kernel。 

上面是正常的4个出口，另外的3个last thread，属于main return一样的处理；还有2个，abort和signal，再看。

  * `#include <stdlib.h>`
  * `void exit(int status);`
  * `void _Exit(int status);`
  * 这是ISO C定义的，难怪exit会处理I/O stream，stream也是ISO C定义的吗。 

总结下，UNIX下，process的开始总是exec导致的，process回归kernel总是_exit或_Exit导致的。无例外。（exit在做完所有事情
的时候，也会调用上面的两个。）

## Section 7.4. Command-Line Arguments

无啥

## Section 7.5. Environment List

  * `extern char **environ;`

这个使用的话是：`for(i=0; environ[i] != NULL; i++){}`。

不过类似于/etc/passwd等system data file，对于这个全局变量，UNIX也有相应的函数可以获取并设置。

## Section 7.6. Memory Layout of a C Program

这一节的内容很好，首先分清楚：C program在执行时内存中的布局和C program保存在硬盘上时硬盘文件的布局。

这里讲的是前者：5个部分。

  * text segment，Initialized data segment，Uninitialized data segment，stack和heap。 
  * stack和heap分别从上下向中间增加，前者是函数调用和动态变量，后者是动态分配的内存空间。 
  * 两个data segment都是指全局变量，一个初始化了，一个没有初始化。 
  * text segment是程序执行代码。 

这里是C program内存中的布局，很易理解，也不需死记。 至于C program文件本身的布局，看吧。

## Section 7.7. Shared Libraries

这一节只是说明了shared libraries是啥。

## Section 7.8. Memory Allocation

三个函数，`malloc`, `calloc`, `realloc`。不初始化，初始化为0，不初始化。

有句话让我在意：这3个函数通常是使用`sbrk`来实现的。这个函数会扩展process的heap。

  * 我好像对这3个函数有了错误的认识。 
  * sbrk是通过增加data segment来的，heap不是一个使用的空间，而是一个可以被使用的空间，增加了data segment，也就是减小了heap。 
  * 3个函数增加的空间从heap获取而来，但现在隶属于data segment，空间的地址会被返回给程序。程序不关心归属，而只关心地址。 
  * free了之前的空间，但data segment不会因此减小，这free的空间还在data segment里面，虽然没有被使用，但是记录在册。这就是说的malloc pool。 
  * 不，以上理解还是有疑问的，但也可以这样理解，另外还有一种理解。 

第二种理解：

  * heap就是指从data segment开始的，向上延伸的空间。暂且认为heap存在上地址和下地址，下地址就是data segment的顶端，上地址就是heap的另一端的地址。 
  * 程序刚开始的时候，heap是0，也就是无空间。上地址和下地址相等。 
  * 在使用这3个函数的时候，就开始扩展heap了，或者说这个时候heap就是从data segment开始到分配的空间的地址这段空间。下地址不变，上地址增加了。 
  * free的时候，heap并不随之减小，上地址保持不变，多余出来的可用空间，就称为malloc pool。 

第二种理解更为合适一些，我之所以有第一种理解是因为linux sbrk的说明说其被用于增长data segment的空间。但这两种理解其实是一样的，本质上。

`alloca`直接从stack里面获取空间。自成一系，但不理解stack frame的意思，但也不影响，再说。

## Section 7.9. Environment Variables

ISO C没有定义任何的环境变量。

使用`putenv`的时候，其参数不可以是存储在stack中的。可以理解。

  * 如果调用是putenv的不是main，那么，当这个函数返回的时候，stack中存储的内容就不再可用，main中如果使用这个环境变量，那么会导致操作非法地址。 
  * 但如果调用putenv的是main，那么，貌似就没有问题啊。是不是？ 

原本的environment list通常存储在stack之上。

当进行修改的时候，如果修改导致原本的stack之上的空间不足，那么通常会在heap中取出空间进行存储。

environment
list是一个数组，所以需要存储空间，数组元素指向的可以stack之上空间，可以是heap中的空间，但不可以是stack中的空间。这么理解应该没问题。

## Section 7.10. setjmp and longjmp Functions

对这两个函数还不熟：

  * `#include <setjmp.h>`
  * `int setjmp(jmp_buf env);`
  * `void longjmp(jmp_buf env, int val);`

他们的工作模式还是很奇怪的，但就是这么工作的。

这里面有一个问题，就是setjmp之前，定义了一些变量，在setjmp之后longjmp之前变化了，那么longjmp跳回到setjmp的时候，这些变量的值
是为何？

  * 变量有：automatic，register，volatile，global，static。 
  * 如果不加任何优化的编译，那么这些变量保持变化之后的值。 
  * 如果加了优化，那么automatic，register保持定义时候的值，其他三个保持变化之后的值。 
  * 这里注意，在setjmp之前定义的变量，在其之后的变量自然没有了。 
  * 没有优化的时候，这些变量都在内存中，longjmp跳回去，并不影响这些内存中的变量，因为这些变量都在setjmp之前定义。 
  * 优化了之后，automatic和register变量被放入了寄存器之中，longjmp跳回去的时候，寄存器被覆盖了，所以。 

这里也认识了一些其他的知识，比如各种变量，被优化编译时，register和automatic会被放到寄存器中；volatile就是不要被优化，ok。

加一条： **never be referenced after the function that declared it returns**
这是对automatic variable来的。

## Section 7.11. getrlimit and setrlimit Functions

这里说的是processd的resource
limit，什么是resource，就是这个process最多可以使用的cpu时间，最大可以使用memory等等。感觉貌似在linux上很多resource
limit都是无限制的。这也是可以理解的。

  * `#include <sys/resource.h>`
  * `int getrlimit(int resource, struct rlimit *rlptr);`
  * `int setrlimit(int resource, const struct rlimit *rlptr);`

hard limit和soft limit也好理解。规则也好理解。

所有这些limit都是定义的常量，在上面的头文件中吧。

这一节其实真的可以玩一下的。

## Section 7.12. Summary

**OVER**
