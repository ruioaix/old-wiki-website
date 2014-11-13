# RHEL6下面的一些小技巧

## 修改MAC地址

可能会遇到这样一种情况：如果想上网，必须将你的MAC地址告诉网管，网管给你注册之后你的机器才可以使用网口上网。

显然很烦，找一台公司里没人用的电脑，查看下MAC地址，然后在 **/etc/sysconfig/network-scripts/ifcfg-eth0**
中进行修改：将其中的 **HWADDR="xx:xx:xx:xx:xx:xx** 一行删除，加上
**MACADDR="xx:xx:xx:xx:xx:xx"** 这一行。就可以了。macaddr就是那台没人用的机器的mac。最好备份下ifcfg-
eth0文件。

