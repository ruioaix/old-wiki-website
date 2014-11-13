# Order Directive

这个命令和`Deny`和`Allow`组成了一个访问限制。

虽然只有三个，但我混乱了很久。

这是基本的，核心的思想是：

  * `Order`产生了一个域，之后的每一条作用于这个域，这个域要么是deny all，要么是allow all。 
  * `Order`后面的`Allow`和`Deny`的执行顺序安装`Order`中指定的顺序执行。 
  * 不断修改域，直到结束。 

## 看例子，例子才是王道。

  * Order deny,allow 
  * allow from all 
  * deny from 219.204.253.8 
  * 先是Order指定了allow all的域，然后先执行Deny，后执行Allow，结果：allow all。 
  * Order deny,allow 
  * deny from 219.204.253.8 
  * allow from all 
  * 同上。先是Order指定了allow all的域，然后先执行Deny，后执行Allow，结果：allow all。 
  * Order allow,deny 
  * deny from 219.204.253.8 
  * allow from all 
  * 先是Order指定了deny all的域，然后Allow将域改变为allow all，最后Deny对allow all进行修改，结果：allow all except 219.204.253.8 
  * Order allow,deny 
  * allow from all 
  * deny from 219.204.253.8 
  * 同上。先是Order指定了deny all的域，然后Allow将域改变为allow all，最后Deny对allow all进行修改，结果：allow all except 219.204.253.8 
  * Order allow,deny 
  * deny from all 
  * allow from 219.204.253.8 
  * 先是Order指定了deny all的域，然后Allow将域改变为deny all except 219.204.253.8，最后Deny又deny all，结果：deny all 
  * Order allow,deny 
  * allow from 219.204.253.8 
  * deny from all 
  * 同上。先是Order指定了deny all的域，然后Allow将域改变为deny all except 219.204.253.8，最后Deny又deny all，结果：deny all 
  * Order deny,allow 
  * allow from 219.204.253.8 
  * deny from all 
  * 先是Order指定了allow all的域，然后先执行Deny，将域改变为deny all，后执行Allow，结果：deny all except 219.204.253.8 
  * Order deny,allow 
  * deny from all 
  * allow from 219.204.253.8 
  * 同上。先是Order指定了allow all的域，然后先执行Deny，将域改变为deny all，后执行Allow，结果：deny all except 219.204.253.8 
  * Order deny,allow 
  * 直接一个allow all的域，结果：allow all 
  * Order allow,deny 
  * 直接一个deny all的域，结果：deny all 
  * Order allow,deny 
  * deny from all 
  * 先是Order指定deny all的域，然后又deny all一次，结果：deny all。 
  * Order deny,allow 
  * deny from all 
  * 先是Order知道allow all的域，然后deny修改为deny all，结果：deny all。 
  * 對於上面兩種情況，如果将deny from all換成allow from all，則全部都可以通行！ 
  * Order deny,allow 
  * deny from 219.204.253.8 
  * 先是Order指定allow all的域，然后deny修改，结果：allow all except 219.204.253.8 
  * Order allow,deny 
  * deny from 219.204.253.8 
  * 先是Order指定deny all的域，然后deny某一个（这是没有意义的），结果：deny all 
  * Order allow,deny 
  * allow from 219.204.253.8 
  * 先是Order指定deny all的域，然后allow某一个，结果：deny all except 219.204.253.8 
  * Order deny,allow 
  * allow from 219.204.253.8 
  * 先是Order指定allow all的域，然后再allow某一个（这是没有意义的），结果：allow all 
  * order deny,allow 
  * allow from 218.20.253.2 
  * deny from 218.20 
  * 先使用Order指定allow all的域，然后deny 218.20.*.*，这时候是allow all except 218.20，最后Allow修改了，结果：代表拒絕218.20開頭的IP，但允許218.20.253.2通過；而其它非218.20開頭的IP也都允許通過。 
  * order allow,deny 
  * allow from 218.20.253.2 
  * deny from 218.20 
  * 先使用Order指定deny all的域，然后Allow，这时候是deny all except 218.20.253.2，最后Deny 218.20.*.*（这个也同时deny掉了刚刚allow的218.20.253.2），所以结果是：deny all。 

# OVER
