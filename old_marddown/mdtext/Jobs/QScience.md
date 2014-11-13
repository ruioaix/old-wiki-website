# QScience

## Patterns Central Server

### Features

  1. 容易实现 
  2. 可以分享不同用户建立的pattens 
  3. 跟踪pattern的进化过程（类似于版本控制） 
  4. need authentication 
  5. 收集跟踪user的行为 
  6. 进行统计分析 
  7. 容易使用 

### Implementation

实现起来：

  * 作为一个drupal的module 
  * 使用d2d 
  * should ping back a central server of global statistics 
  * 同git集成 

### Relevant modules

  * Unordered List ItemVersion Control API: [http://drupal.org/project/versioncontrol](http://drupal.org/project/versioncontrol)
  * Implementation of Version Control API for Git: [http://drupal.org/project/versioncontrol_git](http://drupal.org/project/versioncontrol_git)
  * Project (the module that generates the usage pages): [http://drupal.org/project/project](http://drupal.org/project/project)

### Ideas/discussion

  * pattern的父母链，就是其上一个版本，上上一个版本……是否需要存在在pattern内部？记录最近5代？ 
  * 同一个pattern的不同格式文件xml，yaml，php是否设置为同一个id。这里可能需要refactor the schema。 
  * “commit”是pattern获得新uuuid的方式。 
  * 发布一个pattern，看作初始commit。 
  * hash with sha512，16MB，0.1s。 
  * 发布的patterns，如果有问题，可以删除。但该pattern的后代该如何？标记为orphans（孤儿）。 

### more considerations
