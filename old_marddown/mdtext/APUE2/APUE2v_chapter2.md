# chapter 2. UNIX Standardization and Implementations

10 Sections.

## Section 2.1. Introduction

An important part of all the standardization efforts is the specification of
various limits that each implementation must define.

unix是第一个发展起来的OS，存在即合理。UNIX标准指明的东西有两个部分：interface和limit。

  * interface指在UNIX系统之上编写程序时可以在添加对应的系统上已经存在的头文件之后，直接可以使用的函数，这些函数一些是系统调用，其他的是库函数。头文件只记录了function prototype，这些function prototype就是interface。至于这些函数原型的具体实现，就是每个UNIX或类UNIX操作系统各自去编写了，各不相同。所以，interface其实就是和头文件对应起来的。 
  * limit是限制，思想是无限的，但只要落到实处，无限总会变成有限，有限就是限制，每个UNIX或类UNIX OS都是一个具体的实现，必定存在着这样或者那样的限制，在一个OS上，int类型是31bit来表示数值，1bit来表示正负，在另一个OS上，int类型是63bit数值1bit正负，在另另一个OS上，int类型是15bit数值1bit正负，这些对每一个OS来说都是合理的，存在即合理。这三个OS上int类型的最大公约数是16bit表示，而再看看其他的OS会发现，大多OS的int都至少是16bit表示的，所以，就决定了一个limit：int最少15bit数值1bit正负。然后在各种OS上发现各种限制的最大公约数，一个一个的limit，合在一起就是UNIX标准的第二个部分：限制。限制通常表现为定义在头文件中的常量，constant，通常而已，限制还有不通常的情况。 

## Section 2.2. UNIX Standardization

4个standardization：ISO C，POSIX.1，SUS，FIPS。ISO
C被POSIX.1包含，POSIX.1被SUS包含，而FIPS作用已渐小。

  * 符合SUS标准的系统，结果检验授权之后才可以挂以UNIX系统商标。 

还不理解的地方，上面说过了，标准在我看来在于两个地方，一个是interface，一个limit，那么，POSIX.1包含ISO C，准确的说应该是包含ISO
C library的header，也就是ISO C定义的interface，而不包括ISO
C定义的C语法语义什么的，这中认识不见得正确，但蛮合理，且不用去深究。

还疑惑的地方，除了interface和limit，标准还有一个option没有充分理解。后面继续思考。

宣称自己POSIX complain的系统应该很多，但通过SUS认证的恐怕就不多了。

## Section 2.3. UNIX System Implementation

solaris是经过SUS认证的，是UNIX操作系统。freeBSD是在老的UNIX系统的延续，并且开源。linux是本身就是本身的起点，从上节来看，lin
ux还是很符合POSIX.1的。传说中AIX和HP-UX都是UNIX系统，私有的，带有UNIX商标的系统。

其实，OS这种东西，私有的比开源的要多的多啊，linux太过响亮，搞得大家都认为UNIX或类UNIX系统都是开源的感觉。私有的或许在很多方面都要优于开源的，
之前以为开源的总会一通河山，但现在想来，不一定，或者，需要很长时间。

## Section 2.4. Relationship of Standards and Implementations

Implementatio总是兼容之前版本的特性的，如果一个Implementation是POSIX
complain的，那说明它提供了POSIX指定的接口，但同时，它可能也保留了它之前版本中的一些不符合POSIX的接口，为了兼容性。

## Section 2.5. Limits

limit是在各种standardization中定义的，在standardization中有其standardization中的名字，一个standard
ization中一个limit只有一个名字，但多个standardization中可能对同一个limit进行的设定，那么这个limit就有了两个standa
rdization中的名字；一个limit在implementation中则可能有三种名字，这三个名字可能存在一种，也可能存在两种，三种都存在是不可能的，因
为有两种是存在互斥的关系的。三种名字对应三种limit，一种是compile-time limit，一种是runtime limit about
file/directory，一种是runtime limit not about
file/directory。后两种显然互斥，但后两者和第一个是可能同时存在的，因为，runtime limit在一个确定的OS中可能是确定的
，那么就可以设置为compile-time limit；一个limit在implementation中的三个名字也是比较好记忆的
，只要记忆第一种compile-time名字就好，第二中是在compile-time名字上加 **_PC_** 前缀，第三种是加 **_SC_** 前缀。

compile-time limit在implementation中往往就是一个存在于某个头文件中的constant。runtime
limit则是存在于某个头文件中的 `define` 了的标志符（其实也是constant，这么说以加以区分）。

确定一个limit的值的方式是非常简单明了的，首先确定有没有定义这个limit对应的constant，有的话，ok，这个limit就确定了；如果没有定义，那
么就使用函数和这个limit的标志符来获取这个limit的值。

三种standardization中存在的limit：

  1. ISO C中的limit都是compile-time limit，也就是都是在头文件中定义的constant。limits.h中包含的最多，其他的头文件也包含了一些。 
  2. POSIX.1定义了数不清的limit……，其中有些作为constant定义在limits.h中，其他的在各种地方吧。 
  3. XSI包含POSIX.1，额外的还有。 

需要注意的是，通过测试程序发现，即使ISO
C中的limit都存在对应的constant，但使用sysconf函数来获取这些limit的值也是成功的，也就是说ISO
C中的limit在RHEL6中都有两个名字。通过这个测试，也就知道了，不同太过注意区分一个limit到底是compile-time
limit还是runtime limit，在真的需要确定一个limit的时候，总是经历上面说的那两个步骤，先看看是不是constant（compile-
time），是就不继续，不是就再看看函数是否可以获取值（runtime time）。

三个获取limit的函数：

  * `#include <unistd.h>`
  * `long sysconf(int name);`
  * `long pathconf(const char *pathname, int name);`
  * `long fpathconf(int filedes, int name);`
  * 三个函数中的name就是limit在implementation中的name，前面说过name有三种，这里因为是runtime的，所以就两种，第一个函数的name必定是 **_SC_** 前缀，后两个函数的前缀必定是 **_PC_** 前缀。 
  * 如果limit没有`define`过，那么返回-1，并设置 **errno** 为 **EINVAL** 。 
  * 如果limit是indeterminate，那么返回-1，但不设置 **errno** 。 
  * 否则，返回limit的值。 

对于indeterminate的limit通常就是猜个值了。

注：本节的awk程序使用的pathconf.sym和sysconf.sym中的每一行的两个元素之间要使用tab分开，空格是不行的。

注：如果你的pathconf.sym和sysconf.sym中有足够的limit，本节的awk输出的c程序的运行结果则是根据你包含的头文件的多少而定的，因为
那些limit都是定义在各种头文件中的，你漏掉了那一个，结果就显示no symbol，这是值得注意的地方。

## Section 2.6. Options

standardization有很多的可选的接口，那么如何看任意一个implementation是否支持其中一个接口呢？就通过option。使用option
的手法和limit非常像，先constant，然后函数上。

使用option和limit的总是运行在OS之上的应用程序，为了保证程序的可移植性，应用程序会获取limit，获取的方法上一节已经介绍过了，同样的，也是为了
保证程序的可移植性，应用程序会获取option，从而知道OS是否支持某个可选的interface，获取option的方法盒limit很类似。

每个option在standardization里有一个自己的名字，在implementation里面则可能有一到两个名字，一个是头文件中的constant
，另一个就是用于作为函数参数的已`define`的标志符。

但这中间的判定看起来要比limit复杂一些，constant的值就代表了不同意思，不过归根结底，结果就是implementation要么支持option，要
么不支持。

## Section 2.7. Feature Test Macros

这个功能的实现依赖于编译器吧，limit和option都不依赖于编译器，这两个都是使用constant和函数来确定功能，但本功能怎么看都依赖于编译器。

这个功能简单来说就是：通过定义一个constant来屏蔽掉所有不是standardization中的interface。如果应用程序中有一个接口不是stan
dardization中的，那么编译出错。

这种功能只能是编译器提供的。

相关的constant是： `_POSIX_C_SOURCE` , `_XOPEN_SOURCE` , `__STDC__` 。

## Section 2.8. Primitive System Data Types

一些implementation-dependent data type。使用c语言的`typedef`功能建立。

这里没有说这些类型到底是几个bit，可以预见在各个implementation上这些数据类型可能有不同bit数目，但不要紧，因为，可以不用去管这些数据的bi
t数目，而安心的使用这些数据类型，因为是安全的。

暂时，我不知道为什么是安全的。

## Section 2.9. Confilcts Between Standards

ISO C: 定义了一个clock函数，返回一个`clock_t`值，这个值除以在`time.h`头文件中定义的 **CLOCKS_PER_SEC**
得到一个以秒为单位的cpu使用时间。

POSIX.1：定义了一个times函数，也返回一个`clock_t`值，这个值除以使用sysconf获得的另一个每秒clock数目，得到一个以秒为单位的c
pu使用时间。

两者得出的最后的已秒为单位的cpu时间是相同的，但是 **CLOCKS_PER_SEC**
是1000000；而sysconf得到的是100；同时前者的clock函数返回值也大后者的times函数返回值10000倍。

ISO C和POSIX.1还是有差别的，不是说POSIX.1保护ISO C吗？看来不是。可以知道的是POSIX.1包含列ISO
C的标准库函数，可能是这样的，POSIX.1除了ISO C之外，还有其他的部分，这其他的部分盒ISO
C那一部份就产生列差异。只能这么理解了。在这么理解的基础上，那么POSIX.1会定义一些与ISO
C中的函数接近但更加健壮的函数，这种函数通常是用来取代ISO C中对应函数的，但是为了保持兼容性，所以ISO
C中的对于函数还是会保留，这就产生了两个接近的函数。

POSIX.1可以比ISO C建立更强健的函数是可以理解的，因为ISO C与系统相关的很少，POSIX.1就是为系统而生的。

## Section 2.10. Summary

over.

