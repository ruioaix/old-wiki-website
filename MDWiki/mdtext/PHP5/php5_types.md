# PHP5 types

php 有8种类型。

4种标量类型：boolean，integer，float（double），string。

2种复合类型：array，object。

2种特殊类型：resource，NULL。

可以使用`var_dump()`来查看一个表达式结果的类型和值。

`gettype($xx)`返回变量的类型。

`is_type($xx)`来检查变量是否为某一类型。

## Boolean

  * **TRUE** 和 **FALSE** 是大小写不敏感的， **true** ， **TRue** ， **FAlSe** 都是相同的。 
  * 以下都是在转换为boolean时会变成 **false** 的值： 
    * **false** 本身。 
    * integer 0 
    * float 0.0 
    * empty string 
    * string “0” 
    * 没有element的array 
    * 特殊类型NULL 
    * 从empty tags创建的SimpleXML object 
  * 此外的所有都是 **true** 。 

## Integer

  * 整数 
  * 前面加0，表示八进制。 
  * 前面加0x，表示十六进制。 
  * 前面加0b，表示二进制。 
  * integer的取值范围是平台决定的， 
  * php不支持无符号整数，只支持signed integer。 
  * 从 **PHP_INI_SIZE** 和 **PHP_INI_MAX** 可以知道整数可以取到的最大最小值。 
  * 从boolean到integer，false就是0，true就是1。 
  * 从float到integer，原则是向零逼近。 
    * 如果float超出了integer的范围，转换结果不确定。我的机器上，变成了负数。有点c语言截断高位的感觉。 
  * 从string到integer，在string节介绍。 
  * 从上面3个之外的类型到integer类型的转换是未定义的。 

## Floating point numbers

  * 1.234，1.2e3，1E-11。 
  * float的取值范围也是平台决定的。 
  * float也是有精度限制的。 
    * 不要相信float的最后一位，并且不要直接比较float是否相等。 
  * string到float的转换，string节讲。 
  * 其他类型到float，先是到int，然后再到float。 
  * float的比较，可以使用两者之差小于某个很小的数的方式。 
  * **NAN** 表示不可呈现的结果，使用任何value和这个值进行比较，结果都是 **NAN** 。 
    * `is_nan()`

## String

  * string只支持256个字符，也就是8bit可以表示的所有。因此并不支持Unicode。 
  * string可以到2G大小。 
  * string literal（字符串字面值） 
    * Single quoted单引号 
      * 如果字面值里面有单引号，那么使用backslash。 
      * 如果字面值里面有backslash，那么使用两个backslash。 
      * 其他情况下，backslash就是backslash本身。也就是说 **\r** 之类的特殊字符是没有效果的，会原样输出。 
    * Double quoted双引号 
      * 双引号就会解释很多特殊字符。 
    * Heredoc 
      * **<<<** 后面跟着一个标志符，然后同一个标志符用于结束。 
      * 结束用的标志符必须从newline开头开始，后面只能接一个分号，分号和标志符之间不允许任何的字符，分号之后不允许任何的字符。 
      * heredoc里面的内容表现和双引号的一致。 
      * 同时，heredoc里面的双引号不需要backslash。 
      * **<<<** 后面的标志副可以使用双引号，也可以不使用。 
    * Nowdoc 
      * 如果说Heredoc对应双引号，那么Nowdoc对应单引号。 
      * **<<<** 后面的标志符需要使用单引号来包含。 
      * nowdoc里面即使两个backslash和一个backslash加上一个单引号也不会解释，这是nowdoc和单引号的不同。也就是说nowdoc不解释任何东西。 
  * Variable parsing（在双引号和heredoc之中） 
    * simple syntax，提供一个简单的方法从而嵌入一个variable，一个数组值，一个对象属性到一个string。 
      * **$** 标志符 
      * 对数组来说， **]** 就是结束标志。 
    * complex syntax 
      * 这里的complex指复杂的表达式。 
      * 使用 *\({* 和 *{\)* 来搞定。就是使用 **$** 和 **{** 的不断组合。 
  * String access and modification by character 
    * string可以被任务是array，从而操作其内部的字符。 
    * 可以使用 *\(str[1]* ， 也可以使用 *\)str{'1'}* 。 
  * 可以使用 **.** （dot）进行string的串联。 
  * Converting to string 
    * boolean **TRUE** 变为string **“1”** 。 
    * boolean **False** 变为 string **“”** 。 
    * integer和float 就是 变成字面字符串。 
    * array总是变为 **“Array”** 。 
    * object总是变为 **“Object”** 。 
    * **NULL** 变为 **“”** 。 
    * 如上所述，直接将array，object，resource转为string不会得到任何有用的信息。 
  * string conversion to number 
    * 当string中不含有e，E和小数点的时候，就会被转换为integer，其他情况就是float。 
    * 只取string前面的数字部分，如果后面有字母，就不care了。如果第一个就不是数字，那么就为0. 
  * Details of the String Type 
    * string在php中就是通过an array of bytes and an length integer实现的。 
    * 至于这些byte如何表示character，就不是php关心的事情了。 
    * 那么php如何编码呢？结果：当你在使用什么编码编写php文件的时候，string就是按照那种编码编码的。 
    * 上面一行的功能只有Zend Multibyte enabled的时候才有用。 
    * 各种处理string的函数有各种对string编码的假定。 
      * 一些就认为string就是byte。 
      * 一些将编码作为参数，传递给函数 
      * 结合当前locale来选择byte编码（只能使用single byte） 
      * 一些假设string就是某种编码 

## Arrays

  * 使用 `array()` 来建立一个array。 
  * `key => value`，逗号分开，最后一组的逗号留不留都可以。 
  * 从php5.4开始，可以使用 **[]** 来代替 `array()`。 
  * `key`可以是integer和string。 
  * 当`key`中出现某些类型时，会出现下面的强制转换。 
    * 整数类型string会被转换为integer 
    * float类型直接截断为integer 
    * boolean类型要么是integer 1，要么是integer 0. 
    * **NULL** 会变成 **""** ，这个只能出现一次。因为每个 **NULL** 都会变成 **""** ，就会报错。 
    * array和object不能成为key。 
  * 多个同样的key，只使用最后一个key的value。除了上面的 **NULL** 。 
  * array的元素可以使用 `array[key]` 的方式读取。 
  * `$arr[]=value` ，如果arr不存在，那么这是一种建立array的方式。 
    * 如果arr存在，那么value的key就根据arr中曾经存在的key变化。 
    * 注意是曾经的key。 
  * `unset(\(arr);` `unset(\)arr[key]);`
    * 上面的函数可以删除某一项key和value，但是并没有re-index数组。 
  * 使用`array_values()`来re-index数组。 
  * `foreach()`就是特别为array存在的。 
  * `\(foo['bar']`是正确的，`\)foo[bar]`是错误的。 
    * 但是后者可以使用，在某些情况下。 
    * 这是因为，如果php找不到bar对应的标志符，那么就自动的将bar转化为`'bar'`这个string。 
    * 如果bar是常量，并且其代表的值是一个key，那么上面的后者是正确的。 
    * key放入variable也是没错的。 
  * 4种标量类型和resource类型到array的转化： 
    * `(array)\(scalarValue`和`array(\)scalarValue)`是相同的。 

## Objects

  * to create a new object，use the new statement to instantiate a class. 

## Resources

  * a resource is a special variable, holding a reference to an external resource. 

## NULL

  * null类型中唯一一个可能的值就是NULL。 
  * NULL表示一个没有值的变量。 
  * 在下面的情况下，一个变量会被认为是null 
    * 被赋予NULL的变量 
    * 还没被赋予任何变量 
    * 被`unset()`
  * NULL大小写不敏感，null，Null，NuLL都一样。 

## Pseudo-types

  * mixed指可能接受多种类型，`gettype()`
  * number要么是integer，要么是float。 
  * callback 
  * void表示返回值是无用的。 

