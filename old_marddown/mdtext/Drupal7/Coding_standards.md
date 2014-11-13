# Coding standards

  * 所有新的代码都要遵循当下的coding standards。已存在的代码可以update，但update不是必须的。 
  * 缩进使用2个space，不使用tab。 
  * line的结尾不应该有trailing whitespace。 
  * all text files应该以single newline结尾。 
  * 所有的二元操作符，前后都应该留一个space。 
  * 所有的一元操作符和操作数之间不应该有space。 
  * 强制转换类型时，(type)和$var之间要有一个space。 
  * 不要使用 **else if** ，使用 **elseif** 代替。 
  * if，switch等和后面的条件判断之间使用space分开，从而与函数区别。 
  * if，switch等的执行语句，总是要使用花括号，即使执行语句只有一句，语法上可以不用花括号的情况下也应该使用花括号。 
  * 一般情况下，所有line应该不超过80个char。 
  * 函数名和括号和第一个参数之间都不应该有space。 
  * 参数和逗号之间应该有space。 
  * 最后一个参数和括号和分号之间不应该有space。 
  * 多个相关的赋值语句，他们的赋值符号应该保持一列，相应的添加一些space。 
  * array中的元素和逗号之间要有一个space。 
  * **=>** 是二元操作符，所以两边都要有space。 
  * 如果array的声明超过了80个char，那么每个元素分一行写。最后一行也要加上逗号，防止添加其他元素。 
  * 引号的使用，drupal并没有硬性规定。 
  * string连接符的使用，二元符，所以两边都要有space。 
  * 一直使用 **<?php ?>** ，而不要使用 **<? ?>** 。 
  * php允许在php block结束的最后有一行不使用分号，但drupal要求总是要分号。 
  * 函数名和变量都应该使用小写命名，可以使用下划线。 
  * constant使用大写命名，可以使用下划线。 

