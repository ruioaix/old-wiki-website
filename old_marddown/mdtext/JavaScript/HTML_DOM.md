# HTML DOM

通过JavaScript，可以重构整个HTML文档。可以添加、移除、改变和重排页面上的项目。

要改变页面的某个东西，JavaScript就需要获得对HTML文档中所有元素进行访问的入口。这个入口，连同对HTML元素进行添加、移动、改变或移除的方法和属
性，都是通过文档对象模型来获得的。

DOM可被JavaScript用来读取、改变HTML、XHTML以及XML文档。

HTML DOM节点

  * 整个文档是一个文档节点 
  * 每个HTML标签是一个元素节点 
  * 包含在HTML元素中的文本是文本节点 
  * 每一个HTML属性是一个属性节点 
  * 注释属于注释节点 

查找并访问节点：

  * 通过使用getElementByld()和getElementsByTagName()方法 
  * 通过使用一个元素节点的parentNode，firstChild以及lastChild属性 
  * document.documentElement 
  * document.body 

