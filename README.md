# FAS3.0
### Cloud ML
wget https://raw.githubusercontent.com/qccx110/fas/master/lyfas.sh;bash lyfas.sh

常见问题
无法运行脚本？提示 no common encryption algorithm(s)
解决：

CentOS请执行：yum -y install openssl nss

Debian请执行：apt-get -y install openssl nss

无法运行脚本？提示 bash:wget:command not found
解决：

CentOS请执行：yum -y install wget

Debian请执行：apt-get -y install wget

修改：fas.sh、lyfas.sh 的链接，注意是下载链接,软件教程才软件里
