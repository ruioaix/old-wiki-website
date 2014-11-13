# Redis(2.6.10)'s Makefile

## make学习

  * [http://www.gnu.org/software/make/manual/make.html](http://www.gnu.org/software/make/manual/make.html)
  * [make_3_3之前](make_3_3之前.html)
  * make_3_3到 

`include foo *.mk
$(bar)`是可以的，make处理include的方法是暂停当前，执行include里面的makefile之后，返回当前。还是头文件的意思。

`-include filenames`，找不到filename也没事。`sinclude filenames`一个意思。

## 主目录的Makefile

    
    
    default: all
    .DEFAULT:
        cd src && $(MAKE) $@
    install:
        cd src && $(MAKE) $@
    .PHONY: install
    

  * 当我`make`的时候，默认第一个target，相当于`make default`，也就相当于`make all`。 
  * 没有target叫`all`，所以`make all`就会执行 **.DEFAULT** 下面的recipe。也就是`cd src && make all`。 
  * 当我`make xxx`的时候，如果`xxx`也会执行，相当于`cd src && make xxx`。 
  * 当我`make install`的时候，`install`这个target有recipe，也就是`cd src && make install`。 
  * 所以，有意义的是这几个命令，这几个命令包含了所有的情况： 
    * `cd src && make xxx`
    * `cd src && make all`
    * `cd src && make install`

进入src。

## src目录下的Makefile
