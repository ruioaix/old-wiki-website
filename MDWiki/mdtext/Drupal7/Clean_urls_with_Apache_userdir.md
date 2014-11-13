# Clean urls with Apache userdir in RHEL6

之前按照[../RHEL6/在RHEL6配置LAMP_fordevelopment](../RHEL6/在RHEL6配置LAMP_fordevelopmen
t.html)里面的内容设置了userdir，从而可以使用我本身的vim配置（如果将需要开发的内容放在/var/www/html/内部的话，我就需要使用ro
ot账户了，很不舒服）。

但由于使用了apache的userdir导致了我今天在配置drupal718的clean urls的时候总是出问题，好在最终找到原因了。

## 配置步骤

  1. 确认mod_rewrite的存在 
    * `apachectl -M |grep rewrite`得到了 **rewrite_module (shared)** 的输出，ok。 
    * 或者，查看 `/etc/httpd/conf/httpd.conf`，在RHEL6.3中的apache2.2.15的环境下，在上面文件的190行左右可以看到 **LoadModule rewrite_module modules/mod_rewrite.so** 这一行，ok。 
  2. 修改httpd.conf，就是上面的文件，因为我的drupal放在userdir（/home/*/webDevelopDir）下，找到这个Directory，确保其下的 **AllowOverride All** 。 
    
    
    	<Directory /home/*/webDevelopDir>
    		AllowOverride All
    		Options MultiViews Indexes SymLinksIfOwnerMatch IncludesNoExec
    		Allow from all
    		Order allow,deny
    	</Directory>
    

  3. 修改httpd.conf，确保其中存在 **AccessFileName .htaccess** 的存在。这在httpd.conf中本来也是存在的，在416行左右。所以不用修改。 
  4. 修改drupal目录下的.htaccess文件，在drupal718下的.htaccess文件中，98行是`RewriteBase /home/ray/webDevelopDir/drupal718`，这一行的内容根据你的userdir和drupal目录的名字不同而不同，但格式如上，将此行comment掉，然后加入新行`RewriteBase /~ray/drupal718`即可。 
  5. 到你的drupal页面，configuration，search节下的clean urls，这个时候应该就可以enable了。 
  6. OVER 

中间记得`/etc/init.d/httpd restart`。

