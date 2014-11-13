# Tips for Vim

  * `set compatible?` 这一句不是设置，是确定，注意后面有一个问号，所有的vim设置都可以这么查看。 
  * `%` 会在`（）[] {}`这三种括号的两个标号之间来回跳。 
  * `33G`和`:33`都到33行。 
  * `50% 60% 70%`分别到文件中间，60%处，70%处。 
  * `c-e`和`c-y`，前者是上滚，一行一行的，后者是下滚，一行一行的。 
  * `*`和`#`，当前光标在xxx，按*则光标移动到下一个xxx，#移动到上一个。 
  * `/^xxx`查找一行开头的xxx，`/xxx$`查找一行结尾的xxx。 
  * `/x.x`查找3个字符，左右x，中间是一个任意字符。 
  * `''`两个单引号，回到使用G命令跳走的那个行。`c-o`跳到更老的地方。`c-i`跳到新的地方。 
  * `ma`标记当前行为a，`'a`跳到标记为a的行。 
  * `v`是行选择，`c-v`是列选择。 
  * `~/.vim/plugin/`是全局插件的目录，所有这个目录下的插件，在打开vim时就启用。 
  * `filetype plugin on`是使用针对不同文件类型的插件所必须的。 
  * `~/.vim/ftplugin`是文件类型插件的放置目录。 
  * `:options`显示选项，set xxx中的xxx。 
  * `set list`将tab显示为^I，$显示在每行的结尾。 
  * `z+.`将当前行移动到终端中间。 
  * `z+ENTER`将当前行移动至终端顶部。 

## vim的比较好的学习资料

  * [vim中文help](http://vimcdoc.sourceforge.net/doc/help.html). 
  * [a byte of vim 语言风格很体贴](http://wiki.rrrui.com/files/Vim/byte_of_vim_v051.pdf)
  * [Hacking VIM 2010 版（希望合法）](http://wiki.rrrui.com/files/Vim/Packtpub.Hacking.Vim.7.2.Apr.2010.pdf)
  * [台湾某位的著作](http://wiki.rrrui.com/files/Vim/vim-hacks.pdf)
  * [国人翻译的HackingVIM，不全，但翻译的很好](http://wiki.rrrui.com/files/Vim/vim_advanced_usage.pdf)
  * [vim的键位图片](http://wiki.rrrui.com/files/Vim/programmers_print.png)
