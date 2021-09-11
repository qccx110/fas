#FAS3.0流控一键安装脚本 (2021.09.11更新)
####FAS3.0流控一键安装脚本: wget --no-check-certificate -O fast.bin "https://daloradius.coding.net/p/fast/git/raw/master/fast-3.0.bin" && chmod +x fast.bin && ./fast.bin
####个人博客: blog.daloradius.cn
####编译指令(编译文件在当前目录即可进行编译，否则需要填写文件路径) gcc -o fast.bin newfast.c
####提示缺少gcc文件：yum -y install gcc gcc-c++ gdb
####交流群：812968838
####怕有后门的别用，所有文件已开源可以自己检查，实在不放心的请自己二开后编译使用，个别C语言文件 冬瓜(筑梦科技) 也没有开源，源文件我也没有，别找我要！！！谢谢 
####2021.09.11更新
####优化脚本逻辑问题，重新整理，修复APP编译问题，添加程序安装成功or失败检测，添加系统更新解决大部分搭建失败的问题，添加系统负载