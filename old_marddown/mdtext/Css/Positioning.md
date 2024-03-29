# Positioning

## 一切皆为框

块级元素：div，h1，p；一块内容，“块框”，

行内元素：span，strong等，“行内框”。

`display: block`，可以使span表现得像块级元素一样。

`display: none`，使得元素没有框，不再显示，不再占用文档空间。

无名块框，块级元素开头的文本自动添加上的块框。

行框和行内框是不一样的。

## css定位机制

普通流，默认情况：

  * 块级框从上到下一个接一个地排列，框之间的垂直距离由框的垂直外边距计算出来。 
  * 行内框在一行中水平布置，可以使用水平内边距、边框、外边距来调整它们的间距。但是，垂直内边距、边框和外边距不影响行内框的高度。 
  * 由一行形成的水平框称为行框，行框的高度总是足以容纳它包含的所有行内框。不过设置行高可以增加这个框的高度。 

## css position属性

**static** : 默认，块级元素生成一个矩形框，作为文档流的一部分，行内元素则会创建一个或多个行框，置于其父元素中。 

**relative** ： 元素框偏移某个距离，元素仍保持其未定位前的形状，它原本所占的空间仍保留。 

**absolute** ： 元素框从文档流完全删除，并相对于其包含块定位。包含块可能是文档中的另一个元素或者是初始包含块。元素原本在正常文档流中所占的空间会关闭，就好像元素原来不存在一样。元素定位后生成一个块级框，而不论原来它在正常流中生成何种类型的框。 

**fixed** ： 元素框的表现类似于将position设置为absolute，不过其包含块是视窗本身。 

总的来说，static和relative是一波的，absolute和fixed是一波的。

static是正常流，relative是相对于正常流的小偏移。

absolute是脱离正常流，相对于父级块，fixed也是脱离正常流，相对于视窗。

absolute是相对于最近的已定位祖先元素，如果元素没有已定位的祖先元素，那么它的位置相对于最初的包含块。

## css 浮动

浮动的框，向左或者向右移动，直到它的外边缘碰到包含框或另一个浮动框的边框为止。

浮动框不再正常流中，所以正常流中的框不care浮动框，就好象浮动框不存在一样。

浮动框如果位置和某个正常流中的框有重叠，那么，浮动框在上，其覆盖正常流中的框。

浮动框旁边的航空被缩短，从而给浮动框流出空间，行框围绕浮动框。因此，创建浮动框可以使文本围绕图像。

# OVER

基本上，我理解了。

