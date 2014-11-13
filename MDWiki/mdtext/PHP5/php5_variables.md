# Variables

变量是用 **$** 加上变量名来表示的。变量名大小写敏感。

  * `$this`是不能赋值的特殊变量。 

变量也支持引用和赋值，与c蛮像。

不赋值的话，各类型有default value。

  * boolean：false 
  * integer&floats：0 
  * strings：empty string 
  * aray：empty array 

php提供了大量的预定义变量。

## Variable scope 变量作用域

  * 与c有点不同，在函数里面，如果想使用全局变量，必须使用 **global** 。 
  * global关键字和`$GLOBALS['a']`是相同的。 
  * `$GLOBALS`是superglobal。 
  * 大部分的predefined variable并不是superglobal。 
  * 在函数外使用global关键字是错误。 
  * static和c很像。 

## Variable variables

## Variable From External Sources

