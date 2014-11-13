# DOM Scripting: web Design with JavaScript and the Document Object Model

this is a book, you can find pdf from internet. I am reading the this book
with 2005 version.

## A Brief History of JavaScript

web design就是三个部分：html，css，javascript。

  * html负责将web page的内容表述成为一个一个的element。 
  * css复杂在web page上有型的放置这些element。 
  * javascript负责这些element的交互。 

world object model和document object model的解释太精辟了。

DOM是API，这种解释也是很好的。

## JavaScript Syntax

  * statement，每行一个statement，同一行多个statement需要`;`分开，单行一个statement不需要`;`，但为了更好的编程风格，每行加上`;`是推荐的。 
  * 注释是`//`，`/**/`都是可以的，同c；`<!-`和`//`是相同的。同c的两个注释符号足够，避免使用html风格的那个注释符号。 
  * `var my_mood="happy", age=10;`
  * `var age="xxx"; age=3;`

这一章介绍的还是极好的，总的来说，javascript集合了php和c的语法，就是怎么舒服怎么用。

值得注意的有两点：

  1. 变量的作用域，使用`var`的变量才是local的，这点很不一样。 
  2. object中的两种已经存在的，一个是native object，比如date等，一个是host object，比如doc等，前者是javascript提供的，后者是浏览器提供的。 

array也是一种已经存在的native object。

## The Document Object Model

javascript中的三种对象：

  * user-defined的对象 
  * native object，比如array，math，date等，js提供的。 
  * host object，browser提供的。 

在DOM中有3种node：element node，text node，attribute node；attribute node必定包含在element
node中，纯文本就是text node。

在DOM中每一个element node都是一个object，有两个函数可以获取：`getElementById`,`getElementsByTagNam
e`。使用这两个函数的是`document`对象。

`getAttribute`是element object使用的，不同于上面的两个函数。

js中`if(xxx != null)`和`if(xxx)`是一样的。

## A JavaScript Image Gallery

很不错的一章

## Best Practices

最佳实践，就是编写js应该符合的最好的规则或者原则。

BOM：bowser object model。

没有js使能的bowser也可以正常访问的网站。

很不错，说明了window.onload的问题。

## Image Gallery Revisited

@TODO

