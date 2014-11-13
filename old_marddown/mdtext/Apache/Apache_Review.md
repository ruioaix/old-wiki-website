# Review Apache

回顾应该有个主线，沿着主线思考，应该想出自己困惑的地方，然后解决，使自己有个完整的正确的认识。

主线就是Apache整个服务的流程。

从client端开始，user、浏览器、DNS&hosts，这三个是client端。

  * user负责在浏览器地址栏写入hostname或者IP。 
  * hostname的话，会从user PC的hosts中或者DNS中取得对应的IP，这种情况下，对于不是太老的所有浏览器来说，http request header里面包含的不只是IP，还包括了hostname。 
  * IP的话，http request header里就只有IP。 
  * 浏览器发出request。 

从server端来看，最前端（离client最近的部分）是网卡，或者说network
interface。一个网卡，一个IP，server可以有很多网卡，很多个IP。

client的request到达server的方式只是依靠于IP和port的。hostname对于request在网络上的传输是没有意义的。

apache可以监听所有网卡的所有端口，也可以只监听某一网卡的某一端口，随意，通过`Listen`来实现。

server端所有网卡总会源源不断的将收到各种各样的request，被监听的网卡的对应端口的request都将被汇总到apache那里。apache如果忙呢
，就放在queue里，如果不忙呢就直接生个进程或线程处理了这个request。

apache可以支持纯进程的、也支持多线程的处理request的方式，但不管方式，对于每个request的处理的流程都是一样的。

我对这个流程的理解：

  1. 从request剥离出IP，port，hostname（如果有的话），通过这三者，唯一的对应到apache的一个`DocumentRoot`下面去。 
  2. 从这个`DocumentRoot`获得对应的数据返回给client。 

就这两步，两步是两个对应关系：

  * 第一步——apache是如何使用IP，port，hostname(如果有的话)唯一的对应到某个`DocumentRoot`的？ 
  * 第二步——apache是如何对应url（IP，port，hostname之后的部分）和filesystem上的数据的？ 

## 第一次对应

对应左方：IP，port，hostname（如果有的话）。 对应右方：某个`DocumentRoot`。

对应的方式有两种：main server和VirtualHost。前者可以有一个，或者没有；后者可以有N个。

在所有VirtualHost外面的那个`DocumentRoot`就是main
server；VirtualHost外面没有`DocumentRoot`的话，那么就没有main server。

当`NameVirtualHost`后面接了确切的IP+port，比如： _1.2.3.4：5_
，那么所有从这个网卡的这个port进入的request都必须由这个`NameVirtualHost`对应的`VirtualHost`来处理。

当没有`NameVirtualHost`或者，`NameVirtualHost`后面的IP或port含有通配符的话，那么apache来进行匹配选出最合适的，
如果有多个同等合适的匹配项，那么选择在httpd.conf中位置最靠前的。

main server是在VirtualHost之外的，而其他各种配置也都散落在VirtualHost之外，main
server在httpd.conf的位置也不重要，VirtualHost总是会继承main server的配置的。

hostname的价值体现，只发生在 **name-based VirtualHost** 中，对于IBVH和main
server来说，IP和port是有意义的，hostname无意义。

如果在NBVH中没有`ServerName`，那么这个NBVH就是符合对应的`NameVirtualHost`的default。

任何使用 `_default_`的vhost的`ServerName`都使用main server的值。

Apache有一个hash table，这个里面记录了VirtualHost的信息，即某个IP下有那些VirtualHost。通过IP下是否有Virtual
Host来判断是IBVH还是NBVH。main server是不记录在这个hash table的。

  * 在`NameVirtualHost`中存在确切IP（非通配符）的话，那么这个IP被记录在hash table中，所有与此`NameVirtualHost`对应的VirtualHost也都记录在这个IP之下。 
  * 在IBVH中，IP也会记录在hash table中，但此IP下没有额外的记录。 

client发过来的request总是有确切IP的。

Apache对应过程：

  1. IBVH，最先判断。 
  2. NBVH，第二 
  3. request的header里面没有hostname，或者有hostname但匹配不上，那么第一个匹配的VirtualHost处理。 
  4. request的header里面的hostname匹配上了，交给第一个匹配的VirtualHost处理。 
  5. `_default_` VirtualHost，第三。 
  6. main server, 第四。 

按照上面的4点，那么可以得出以下结论：

  * 如果request的IP匹配了IBVH或者NBVH，那么就轮不到`_default_` VirtualHost和main server来处理了。 
  * main server处理的是连`_default_` VirtualHost都不能处理的，一般`_default_`使用的是`_default_:*`，这种情况下，main server什么也干不了。 

基于以上理解，看下[这些例子](http://httpd.apache.org/docs/2.2/vhosts/examples.html)，基本上没啥不能
理解的了。

## 第二次对应

第二次对应，是在第一次对应完成的前提下，进行的url和server端文件之间的对应关系。

对应方式有几种：

  1. 直接将url加在`DocumentRoot`后面。最常见，最多应用，最简单。 
  2. `Alias Url /path/to/somewhere`
  3. UserDir module这个功能其实完全可以由Alias替代的。 
  4. `Redirect permanent /DIRURLunderDocumentRoot/ http://newwebsit.me/xx/`
  5. `ProxyPass /DIRURLunderDocumentRoot/ http://origin.me/xx/`
  6. Rewriting Engine，这是最强大的，上面4个其实就3种，这3种都可以使用rewrite来实现。 
    * drupal的clean url就是使用rewrite实现的。 
  7. 404，`ErrorDocument`。 

所有的第二次对应的方式都在上面，也就这几种。最常用的第一种。

# OVER

