# Chapter 4. Files and Directories

25 sections.

## Section 4.1. Introduction

nothing to say.

## Section 4.2. stat, fstat, and lstat Functions

  * `#include <sys/stat.h>`
  * `int stat(const char *restrict pathname, struct stat *restrict buf);`
  * `int fstat(int filedes, struct stat *buf);`
  * `int lstat(const char *restrict pathname, struct stat *restrict buf);`
  * 成功返回0，失败返回-1。 

struct stat { mode_t st_mode; ino_t st_ino; dev_t st_dev; dev_t st_rdev;
nlink_t st_nlink; uid_t st_uid; gid_t st_gid; off_t st_size; time_t st_atime;
time_t st_mtime; time_t st_ctime; blksize_t st_blksize; blkcnt_t st_blocks; }

这几个函数就是获取一个文件的属性，这些属性本来存储在i-node中吧。

## Section 4.3. File Types

7种file type。不用一一说明了，判断一个文件的type的方法是使用`sys/stat.h`中的macro。参数是struct
stat中的st_mode。

还存在另外3种文件，分别是message queue，semaphore，shared memory
object，这三种文件类型的判断也是使用`sys/stat.h`中的macro，但参数是struct stat指针。

也就是说，UNIX中也就这10种文件了。是这样吗？

## Section 4.4. Set-User-ID and Set-Group-ID

先分辨两个不同的事物：文件和进程，file and process。

file有两个ID，st_uid和st_gid。这两个记录了文件的所有者ID和所在组ID。

process有6个，甚至更多的ID。

人，用户，也有2个，uid和gid。这两个ID就是process中的两个。real uid和real gid。

由用户我执行的程序，首先一条，这个程序的process的两个ID确定了，real uid和real gid确定了。

当我执行一个程序，也就是一个可执行的文件，的时候，这个程序的process的effective uid和effective
gid一般就是我的uid和gid，也就是real uid和real gid。

file里面有st_mode，前面说了是用于辨别file type的，但除此之外，其还包含了另外两个信息位，set-user-ID和set-group-
ID。

当我执行一个程序，也就是一个可执行的文件，的时候，如果这个文件的st_mode里面有设置上述的两个bit，那么，这个程序的process的effective
uid是这个文件的st_uid，effective gid是这个文件st_gid。

set-user-ID和set-group-ID的检测也是通过`sys/stat.h`里面的macro。

这一节很容易混乱，关键是ID太多了，不过仔细看也是很好区分的，三个对象：人，文件，进程，各有ID。

一个进程的effective uid/gid决定了这个进程的权限，但这个权限能做到什么程度还是挺让人困惑的，如果root建了一个程序，给了set-user-
ID，程序的作用是`rm -rf /`，那么任何人都可以让系统崩溃。这很危险，而passwd是一个root建立的具有set-user-
ID的程序，为什么不用担心其会造成安全问题呢？passwd不能加参数，这里有一个判断，passwd的real uid还是我的，所以从real
uid判断下，如果不是root，那么就不允许带参数，恩，权限还是要和程序本身的功能联系在一起才有意义。

## Section 4.5. File Access Permissions

这一节回答了我上一节最后的问题。

file被操作，只能被process操作，在PC上没有其他东西了，就只有process。file只会被process操作。

process上面说了有7个，甚至更多的ID。其中与file操作相关的是3个，effective uid/gid和supplementary
gid。file本身的ID就两个st_uid和st_gid。

  1. 如果process的effective uid是root，那么这个进程可以做任何事，无视file本身的9项，file access总是被允许的，也就是说，没有process不能进入的目录，没有process不能删除的文件，没有process不能读的文件，没有process不能写的文件…… 
  2. 如果process的effective uid不是root，那么瞬间process的能力打上大折扣： **file的9项开始起作用** 。对于st_uid等于effective uid的文件，process具有最大的自由度 **file的9项的前三项起作用** ，只要文件能读，那么process就可以读，如果文件能写，那么process就可以写，如果文件可以执行，那么process就可以执行，如果file不能读不能写不能执行，那么process什么都做不了，过程依赖于file的9项中的前面3项。 
  3. 如果process的effective uid既不是root，也不等于file的st_uid，那么就要看effective gid或者supplementary gid是不是等于file的st_gid了，是的话，process对这个file具有第二等的自由度， **file的9项的中三项起作用** ，process根据file的9项中的中间三项来进行操作。 
  4. 如果process的effective uid不是root，不是file的st_uid，且，process的effective gid或supplementary gid不是file的st_gid，那么，process根据 **file的9项的最后三项** 来进行操作。 

非常清楚。但还是有没注意到的地方：

  1. 上面的第一条，root，还是root，没有任何改变。 
  2. 第二、三、四条中，有个要注意的地方，上面的file包含了目录，目录也是file的一种吗，而process处理的file必然是一个包含file名字的路径名，在路径名中可能有一层一层的目录，我相信，上面的后3条，会先对第一个目录进行一次，如果结果是能进入，然后再对第二层目录来一次，如果能进入，再向下，一直到最后的file，如果某一层目录进不去，那么也就是process对file没有权限，file access会被禁止掉。 
  3. 当然，如果文件就在process的当前目录，默认的包含了本目录的进入权限，然后就真的是按照上面的步骤进行了。 

目录本身的rwx权限理解还是小古怪的，r是获取目录文件列表，w是修改目录文件列表，x是进入目录。

  * 修改目录中文件的内容，只需要x。 
  * 修改目录中文件的名字，需要wx。（目录文件列表改变了） 
  * 在目录中建立文件，需要wx。 
  * 在目录中删除文件，需要wx。 

最后，上述的检测过程都是kernel进行的，process只要进行file access相关的活动，都会导致kernel进行这个检测。

## Section 4.6. Ownership of New Files and Directories

只有process会建立一个file，首先file的st_uid肯定是process的effective uid。

在RHEL6中，我使用`touch`的时候，`touch`并没有set-user-ID，所以，其effective uid是real
uid，而其建立的文件的st_uid自然就是real uid，也就是我了。同时effective gid也是real
uid，也就是file的st_gid，所以建立的file是我的。如果在设置了set-group-
ID的目录里面使用`touch`，首先，st_uid还是不变的，但是，st_gid就是目录的st_gid了。
在RHEL6中，建立目录和建立文件是一样的，使用`mkdir`的时候，st_uid是real uid。如果在设置了set-group-
ID的目录里面使用`mkdir`，那么建立的目录的st_gid就是上一层目录的st_gid，同时为了保持传递性，`mkdir`必须使新建立的目录的set-
group-ID位也被设置。

## Section 4.7. access Function

  * `#include <unistd.h>`
  * `int access(const char *pathname, int mode);`
  * 成功返回0，失败返回-1。 

process的real uid/gid总是登录的那个人的，这里检测的就是那个人对pathname的访问权限。

看不出这个函数的意义，安全性？

突然想到，我的process如果想执行root的一个可执行文件，那么，除非我和root一个组且这个文件的中间3项有个x，或者，这个文件最后3项有个x。

我草，RHEL6里面 **/sbin/reboot** 是rwxr-xr-x，刚才用非root的我的帐号试了下，真的重启了……（幸好，先 **:w**
了一下）， **/sbin/halt** 也是可以使用的，但 **/sbin/init** 同样是rwxr-
xr-x，但会提示只有root可以启动。看来，程序的内部逻辑和程序文件的9项是合作的。

## Section 4.8. umask Function

process建立一个文件的时候，根据两个事物来确定一个文件的9项。建立文件只能使用`open`和`create`，两个都有mode参数，这就是其一，其二就
是umask。如果process中没有使用`umask`，那么，process使用其父进程的umask。使用了`umask`函数，就使用新的。

  * `#include <sys/stat.h>`
  * `mode_t umask(mode_t cmask);`
  * 返回之前的mask值。无错误返回。 

一个函数没有错误返回是啥意思？意味着什么？一个函数又为什么会出错？致命性的错误对任何函数都是不可抵御的，这里是断电之类的错误；除了这一类的错误，函数所有的出
错返回意味着这个函数结束返回了，这个函数成功的执行完毕了，从 **成功执行完毕** 这一点上来说，函数是没有发生问题的，所谓的函数出错返回是指函数没有完成我
们希望它完成的任务。和程序的复杂性有关，如果一个程序非常的复杂，那么，其不能完成指定任务的可能性就大的多，如果程序简单，那么不能完成指定任务的可能性就小很多
，没有错误返回，只能说，这个函数的任务非常之简单，不可能完不成任务。

同时，如果一个函数在执行过程中被中断了，比如信号什么的，这个时候，函数没有出错返回，也没有正确的返回，它只是被中断了，就像断电一样，那么这个时候会发生什么？
后面会说的，再谈。

## Section 4.9. chmod and fchmod Functions

  * `#include <sys/stat.h>`
  * `int chmod(const char *pathname, mode_t mode);`
  * `int fchmod(int filedes, mode_t mode);`
  * 成功返回0，失败返回-1。 

process像使用这两个函数，那么process的effective uid要么是root，要么是file的st_uid。否则可以遇见返回-1。

这两个函数影响的都是file的st_mode，这个里面包含的真是不少东西：file type，9项，set-user-ID，set-group-
ID，sticky bit。蛮多的内容。

这一节最后的两个部分让我有些混乱，讲述的是sticky bit和set-group-ID。使用touch命令和mkdir命令在RHEL6上进行测试的时候，得
出的与最后部分不符合，或许是我对这段话理解不到位，或许是touch命令和mkdir命令与在process执行chmod是很不同的。再谈。

## Section 4.10. Sticky Bit

这里有一个地方我有疑问，前面说过了要想删除一个目录的文件，必须至少拥有对目录wx的权限，而这里只说w的权限，这应该是省略，应该是wx的权限，同时，除了wx的
权限要求外，还需要额外的条件才能删除加了sticky bit的目录里面的文件。

这么理解我比较理解。

## Section 4.11. chown, fchown, and lchown Functions

  * `#include <unistd.h>`
  * `int chown(const char *pathname, uid_t owner, gid_t group);`
  * `int fchown(int filedes, uid_t owner, gid_t group);`
  * `int lchown(const char *pathname, uid_t owner, gid_t group);`
  * 成功返回0，失败返回-1。 

这三个函数都是针对一个特定的文件，我想，如果这个文件被设置了_POSIX_CHOWN_RESTRICTED，那么，执行这3个函数的process要么是roo
t，要么只能修改file的gid到可到的gid。这还是蛮严格的限制的。

中间也说过，linux总是enforce the chown restriction的，我在RHEL6做了测试，可以看到对于`/`目录，limit
**_PC_CHOWN_RESTRICTED=1** ，所以，linux总是启用限制的，也就是上面的限制。

## Section 4.12. File Size

在这一节之前，讲的竟然主要都是file的 **st_mode** ，可见，这个属性是多么NB。

这一节说的是st_size，只适用三到四种文件，regular，dir，symbolic，和不确定的pipe。

dir在RHEL6的ext4上，总是4096。

st_size就是`ls -l`显示的，对于有hole和没hole的文件是不区别的，要区别这种文件，可以使用`ls
-ls`看第一行。那是使用的block数目。

有hole的文件，cp之后，block数目就变成和没hole一样了，mv的话，block数目是不变的，虽然如果使用vim看文件还是一个一个的占位符。

## Section 4.13. File Truncation

  * `#include <unistd.h>`
  * `int truncate(const char *pathname, off_t length);`
  * `int ftruncate(int filedes, off_t length);`
  * 成功返回0，失败返回-1。 

文件的size如果大于length，那么这是正常的截断；如果size比length还小，那么函数执行的结果就随implementation决定了，我想大部分
应该是加大吧，有个hole罢了。

## Section 4.14. File Systems

经常说一个partition分出来之后要给其一个filesystem，这张讲的也就是一种filesystem，具有代表意义的filesystem：UFS。

需要记住的概念之一是 **i-node**
，这是一个文件的核心，不，应该说这是一个文件的本体，我们在gnome里面看到的，在终端里面ls看到的，都是文件的外在表现形式，一个文件的灵魂在i-
node上面，i-node记录了文件的绝大部分信息。其中一个重要的信息就是link_count，它记录了有多少个directory entry指向该i-
node。这里是第二个需要记住的概念： **directory entry** 。

**directory entry** 是directory block的一个条目，directory block和data block都是block，是实际存储数据的地方，不，准确的说只有data block是真正存储数据的地方，而directory block就是存储重要概念directory entry的地方。 **directory entry** 的作用是对应inode和文件的外在表现filename。 

有个问题：directory entry对应一个i-node和一个filename，这个i-node会指向一个block，可以是data
block，也可以是directory block，如果是data，那么到此为止，如果directory呢？那么，这个i-
node指向了一坨directory entry，如果本行出现的第一个directory entry是这一陀中的一个，这是可以的，每个目录中的 **.**
就是这么一个情况。

还有个问题：关于根目录的 **/** ，哦，知道了，根目录下的 **.** 会指向根目录。

directory entry和i-node之间的关系叫做hard link；而symbokic link指的仅仅是data block里面存储了一个路径。

本质区别啊。

这一节里面说一个filesystem里面的directory entry不可能指向另一个filesystem里面的i-
node，这是对的，在RHEL6上的确如此，会`ln: creating hard link xxxx: Invalid cross-device
link`。不过symbolic link是可以跨越filesystem的。

## Section 4.15. link, unlink, remove, and rename Functions

本节的link函数建立的link都是hard link。

在RHEL6 ext4上，即不允许跨filesystem，也不允许建立目录的hard
link，这可能是RHEL6的`ln`命令的原因，但也可能就是不允许。但在RHEL6上是存在目录的hard link的，这些在初始安装之后就存在了。

对于symbolic link，unlink只会unlink sysbolic link本身。这也是很好理解的，因为unlink作用的是directroy
entry和i-node，而不去关系data block。

4个函数用时再找，重要的是上面的概念。

## Section 4.16. Symbolic Links

这节需要注意的问题不是symbolic link，而是函数，有一坨函数会跟踪symbolic link，而另外的函数不会。

跟踪symbolic link就是指函数操作的是link指向的file或dir，而不是symbolic link本身。

## Section 4.17. symlink and readlink Functions

创造symbolic link和读取symbolic link文件内容的函数。

## Section 4.18. File Times

与file相关的，i-node，directory entry，block。

block的最后一次读取时间，block的最后一次修改时间。都会记录，一个是a，一个是m。 i-node最后一次修改的时间。这三个时间。

这里对文件的修改导致父辈目录3个时间的修改还是很奇怪的。父辈目录包含的是一个一个的i-node&directory entry对，这些是父辈目录的内容，当这
些对中任意一条变化时，父辈目录的内容变化了，m时间肯定变化了，同时，如果这些对的变化会导致这些对大小的变化，那么父辈目录的内容大小就变化了，那么c时间就变化
了。任意改变这些对所对应的block的行为都不会改变父辈目录的内容。

重点在于是是inode&directoryentry变了，还是inode&directoryentry指向的block的内容变了。

## Section 4.19. utime Function

修改m时间和a时间，c时间是没有办法的。

## Section 4.20. mkdir and rmdir Functions

始终容易搞混linux的shell 命令和这本书里的这些函数，两者之间是完全不等价的，必然的命令会使用函数，但是命令中必然也有额外的处理。

## Section 4.21. Reading Directories

又忘记了set-user-id和set-group-id的作用了。回忆下：

  * 首先的一个概念，上面的两个id是file所有的。 
  * 对于非directory的file，并且可执行的，上面两者的作用就是将由该文件产生的进程的effective uid/gid设置为文件的所有者uid/gid，而不是当前登录用户的id。 
  * 对于directory的file来说，设置set-user-id的作用看不出来，或许是无意义的。 
  * 对于directory的file来说，设置set-group-id的作用是根据实现而不同的，但本质上的作用就是：这种目录下建立的文件是否具有这个目录的group id。 

以上，是对set-user-id和set-group-id的回忆。

对于sticky bit，这也是file的一个bit。回忆下：

  * 这个bit只对目录有用。 
  * 目录有了这个bit，那么，你要删除目录下的东西，不仅需要拥有目录的wx，还需要拥有文件，或者拥有目录。的确sticky了一点。 

这一章说的读目录很奇特，读的是directory entry，而不是说directory entry指向的文件。而directory
entry的格式根据实现的不同而不同，所以才有了这节的函数。直接操作directory entry。

  * `#include <dirent.h>`
  * `DIR *opendir(const char *pathname);`
  * `struct dirent *readdir(DIR *dp);`
  * `void rewinddir(DIR *dp);`
  * `int closedir(DIR *dp);`
  * `long telldir(DIR *dp);`

## Section 4.22. chdir, fchdir, and getcwd Functions

每个process都有一个current working directory，这是process的一个属性。

虽然是属性，但也是目录，有目录的path，打开这个path可以得到一个文件的描述符，这些都是一样的。某个进程中调用这个函数，改变到了一个新的dir，然后，可
以以这个dir为起点进行其他的操作，主要的还是搜索文件吧。

这个dir是搜索相对路径的起点，理解这一点很重要。

其实这个函数调用的必要不是那么多，但存在即合理，可能有必须用到这种函数才能解决的问题吧。

## Section 4.23. Device Special Files

一个file的st_dev存储的是放置这个file的filesystem的device number。

st_dev和st_rdev是平等的，两个都分别包含了major和minor。

只有character和block file才有st_rdev值。

## Section 4.24. Summary of File Access Permission Bits

这一节很好，非常好。

  * set-user-id果然对dir没有意义。 

## Section 4.25. Summary

stat中的数据都是从i-node获得的，不可以给stat.xxx直接复制，所有修改stat的行为都有一个单独额system call来完成
，可以说本章存在的意义就是将修改文件i-
node的函数描述出来。如果可以直接修改stat当然简单，但是内核和应用就直接关联了，interface的出现的原因就是隔离吗。

**OVER**

