# Managing Projects with GNU Make, 3.Xth Edition

target紧靠行首。command使用hard tab开头，hard tab不可以使用space替代。

使用vim编写Makefile的时候，会发现即使在~/.vimrc中使用了expandtab，在键入tab的时候，tab的确还是tab，而不是几个space
。这是因为Vim识别出了Makefile，所以启动了“makefile mode”。

A rule consists of three parts: target, prerequisites, command.

The default goal is always the first target listed in the makefile.

`default: all`中的`default`和`all`都只是习惯而已。

make的过程就是target-prerequisites-target-prerequisites这样的递归循环。

`make xxx`的时候，如果xxx没有prerequisites，那么只有在xxx不存在的情况下，xxx下面的command才会执行。xxx有prere
quisites的话，自然是按照target-prerequisites-target-prerequisites的递归来判断。

Building and processing this dependency graph to update the requested target
is what make is all about.

rule分几种：explicit rules，patterns rules，implicit rules。

