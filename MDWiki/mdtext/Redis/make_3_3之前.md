# make_3_3之前

rule的三个部分：target，prerequisites，recipe。前两者一行，第三者下一行。没有prerequisites，之后target的ta
rget叫做phony target。

只输入`make`的时候，从第一条非`.`开头的target开始。其他rule的执行是因为他们的target出现在了第一条非`.`开头的target rul
e的prerequisites中。一层一层的先到最底部，然后检测看看是否需要执行最底部的那个rule，然后一层一层的检测着，返回着，直到本来的那个最高层的r
ule。

**variable** 的例子 

  * `objects = main.o kdb.o display.o`
  * `edit : $(objects)`
  * ` cc -o edit $(objects)`

**cc -c main.c -o main.o** 的缩写。 

  * `main.o : main.c defs.h`
  * ` cc -c main.c`
  * 上面两句可以写为下面一句。 
  * `main.o : defs.h`

target和prerequisites的组合，本来，是1对多的，但在.h的时候，也是可以多对1的，这是makefile的另一种style。

**.PHONY : clean** 的意思是说明clean并非一个文件，而是一个phony target。从而避免clean文件存在并且存在于某个prerequisites中所导致的问题。我的理解是这样的。 

makefile包含了五种：explicit rules，implicit rules，variable，directives，comments。

make先找`GNUmakefile`，再找`makefile`，再找`Makefile`。使用`-f`或`--file`的时候，上面的3个不会被make寻
找。

