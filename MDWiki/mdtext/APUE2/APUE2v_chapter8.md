# Chapter 8. Process Control

17 sections.

## Section 8.1. Introduction

introduction.

## Section 8.2. Process Identifiers

process ID 0调度进程，swapper，不对应disk上的任何文件，是kernel的一部份，system process。process ID
1通常是init process，user process。

system process和user process是如何划分的？

6个函数，分别是pid，ppid，uid，euid，gid，egid。

## Section 8.3. fork Function

fork之后，两个进程有自己独立的data segment，heap和stack；完全一样的。但两个进程共用text segment。

上面这样做很容易理解，但是现在的实现已经不这么做了，原因应该是复制操作和内存空间所带来的开销。

standard I/O stream中的stdout，本来就存在于一个process中，但存在于哪呢？stack中，如果新建一个stream，FILE，那
么这个算是automatic，应该在stack中。标准的3个？

process有自己的file descriptor table，子process会复制这部分，因此，父子process会指向同一个内核维护的file ta
ble。父子进程同时操作一个文件的时候，还是比较好处理的，因为共享文件和文件的offset，write和read文件以及相应的offset的改变是原子的。

## Section 8.4. vfork Function

这个函数和fork类似，但其产生的子进程并不复制父进程的data text
segment，heap和stack。其运行于父进程的这些空间中，如果有修改，那么修改的就是父进程的空间，这和fork是不同的。

同时，在以上这些内存空间都不复制的时候，file
descriptor还是会复制一份。这个东西到底存储在进程的什么地方？或者是内核维护的，并不放在进程的空间中？

在子进程exit或者exec之前，父进程会sleep。

## Section 8.5. exit Function

很好，从这一章，我可以知道的信息是process的file descriptor的确被kernel维护着。

不管一个process如何终止，kernel都执行相同的code，包括关闭process的file descriptor，释放memory等。

入口函数是main，出口就很多了，3个exit，3种last thread，1个return main，1个abort，1个signal。

exit涉及的几件事情：flush stream，close stream，run exit handler。现在的大多数exit实现并不close
stream，而只是flush stream和run exit handler。

_Exit不会运行run exit handler，flush stream与否取决于实现。UNIX上是不flush的。

3个exit，1个return main，2个last thread都是exit类型的，余下1个abort，1个last
thread，1个signal是非exit类型的。

  * 前者，exit类型，process terminate status，就是给予exit函数的参数。 
  * 后者，非exit类型，process terminate status，是kernel产生的。 

parent process总是通过使用`wait`或`waitpid`函数来获取这个process terminate
status。而不管是上面的前者还是后者，两者所做的都只是设置了一个status而已。

termination status是kernel转化exit status而来的，两者之间还是有差异的。

使用`wait`,`waitpid`得到的都是termination status，而UNIX提供了检测这些status意义的宏。

当一个process终止的时候，kernel会轮寻所有的process来产看是否有process为当前process的孩子。轮寻，kernel也使用这种。

关于zombie process，就是子process死后，没有及时被parent process回收，信息被保存在了kernel中，难道child
process可以在死后立即被parent process回收吗？不经过kernel这一步？应该是可以的，死后立即回收。

## Section 8.6. wait and waitpid Function

process的终止总是要kernel介入的。一个process调用exit或以其他方式终止的时候，最终kernel都会接收，负责将file
descriptor和memory释放掉。kernel在完成了这些之后才会发信号到该进程的父进程去，告诉其child process已死。是这样的吧？

即使调用wait或者waitpid，也是在kernel将进程处理完成之后，wait才会返回的吧。 这么理解是合理的

  * `#include <sys/wait.h>`
  * `pid_t wait(int *statloc);`
  * `pid_t waitpid(pid_t pid, int *statloc, int options);`

wait函数每次返回一个，如果有多个child process都已终止，那么wait也是返回一个，不知道wait是按照何种顺序来返回的，但一次只返回一个是可
以断言的。wait还是很简单的，要么block，要么返回，要么error。

waitpid就复杂的多了，可以不block，可以job control。

## Section 8.7. waitid Function

貌似更详细，和waitpid类似的多，貌似和信号的相关比较大，理解起来不复杂，复杂的是第三个参数的意义所在。 再说。

## Section 8.8. wait3 and wait4 Functions

这两个函数提过了获取process所使用的resource信息，比如cpu time，signals
num等等。某些程序会用到……这是废话，总有程序用到的。

## Section 8.9. Race Conditions

中文是竞争条件。多进程操作某一共享数据时会发生；解决的途径，从本节来看，signal，IPC。

## Section 8.10. exec Functions

exec会使用disk上的new program来替换当前process的data segment，text
segment，heap，stack。也就是内存中的都替换为新的了，可以知道这个时候heap大小为0.

这本书里介绍的都是比较基础的函数，但只有这里用了primitive这个词，足见process的基础就是已知的这些函数：fork，exit，wait，exec
。primitive，万变不离其宗。

execve是这6个的基础，patchname，argv，envp。

对于ARG_MAX的疑问，这是参数的长度，这个长度是如何算的？括号内的所有字符数目之和？再说。

另一个疑问也被解答了，file descriptor在exec时候的继承问题，很早就讲过，没注意，现在这里知道了。

新process的ID也属于好理解的范畴。

关于另外一个就是，`argv[0]`就不理解了，我们在编写c program的时候，当我们在main中输出`argv[0]`的时候，我们得到的是什么？在RH
EL6上，是我在shell中调用可执行文件的方式，可以是`./a.out`，可以是`/home/ray/apue2v/workingDIR/a.out`，可
以是`../workingDIR/a.out`。就是这样。

而要知道的是，我在shell中执行一个可执行文件，深入理解是shell本身fork并exec了一下，那么这个时候我可以清楚的知道传递给exec的argv[0
]就是我在shell中输入的可执行文件路径。

而当我直接调用exec这些函数的时候，我可以指定argv[0]，我怎么指定都可以，这对于实际的功能是不影响的，这个意思就是说，如果我写一个shell，那么我
可以在这个shell中执行可执行文件，这些可执行文件是c program，如果在这些可执行文件中的某一个上有输出argv[0]的语句，你会发现你得到的输出是
“nihaoworld”，这就是我编写这个shell时设置的。

一般的c program也不会使用argv[0]来进行实际有意义的操作，我想不出意义所在，c
program应该实现的是有意义的功能，而不应该纠结于本身可执行文件的名字。

## Section 8.11. Changing User IDs and Group IDs

