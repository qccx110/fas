#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
//* 脚本来源于聚力工作室 *//
//* 文件源码已全部开源   *//
//* 2020.11.24  溜了溜了 *//
char* cmd_system(char* command);
char buff[1024];
int code = 0;
char Start_Check_Scripts[] = "./fast.bin";
char JuLi_APP_File[] = "dalo.juli.vpn";
//char Download_Host[] = "https://daloradius.coding.net/p/fast/git/raw/master/source";
char* shellcmd(char* cmd, char* buff, int size)
{
  char temp[256];
  FILE* fp = NULL;
  int offset = 0;
  int len;
  
  fp = popen(cmd, "r");
  if(fp == NULL)
  {
    return NULL;
  }
 
  while(fgets(temp, sizeof(temp), fp) != NULL)
  {
    len = strlen(temp);
    if(offset + len < size)
    {
      strcpy(buff+offset, temp);
      offset += len;
    }
    else
    {
      buff[offset] = 0;
      break;
    }
  }
  
  if(fp != NULL)
  {
    pclose(fp);
  }
 
  return buff;
}

int yum(char* pack)
{
	char co_install[100000];
	sprintf(co_install,"yum install -y %s > /dev/null 2>&1;echo -n $?",pack);
	if(strcat(cmd_system(co_install),"0")!="0"){
		return 1;
	}else{
		return 0;
	}
}

int runshell(int way,char* content)
{
	if(way==1){
		return yum(content);
	}else if(way==2){
		char com[100000];
		sprintf(com,"%s;echo -n $?",content);
		return atoi(cmd_system(com));
	}else{
		puts("程序逻辑错误！脚本终止...");
		exit(1);
	}
}

void checkcode(int code1)
{
	if(code1!=0){
	code=code+1;
	}
}

void Start_Check()
{
	if(code!=0){
		printf("\033[31m启动失败！\n\033[0m");
	}else{
		printf("\033[32m启动成功！\n\033[0m");
	}
	code=0;
}

void Home()
{
	char IP[500];
	strcpy(IP,cmd_system("echo `curl -s \"http://members.3322.org/dyndns/getip\"` | tr -d '\n'"));
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	printf("-----------------欢迎使用FAS网络用户管理系统--------------------\n");
	printf("----------------V3.0 (2020.09.17更新(No.045))-------------------\n");
	printf("本脚本支持国内外服务器搭建，梯子、免流、DNS拦截等等，免费搭建！\n");
	printf("FAS3.0流控  作者：筑梦科技(冬瓜) https://www.dingd.cn/product/fas.html  \n");
	printf("此版本为FAS3.0流控去授权版  所有源码和FAS3.0原版一毛一样  无任何后门  不放心的别用！  \n");
	printf("FAS流控【用户流量监控】已去除授权，可正常使用，由南瓜群(白菜大佬)提供的FAS【用户流量监控】去授权版\n");
	printf("脚本源码文件已全部开源(Coding)：https://daloradius.coding.net/public/fast/fast/git/files \n");
	printf("脚本源码文件已全部开源(Github)：https://github.com/heyixiao/FAS3.0-OpenVPN \n");
	printf("交流QQ群: 812968838 欢迎大佬！\n");
	printf("2021.6.7更新\n");
	printf("脚本修复：\n");
	printf("1、修复了IP无法获取的问题！\n");
	printf("2021.6.30更新\n");
	printf("脚本优化：\n");
	printf("1、更改安装源模式：可选、Coding、Github安装源\n");
	printf("-----------------------同意 请回车继续--------------------------\n");
	char hc[1];
	gets(hc);
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	printf("\n\033[33m正在检测您的IP是否正确加载...\033[0m\n");
	sleep(3);
	if (strcmp(IP,"")==0){
		printf("\n\033[34m无法检测您的服务器IP，可能会影响到您接下来的搭建工作，保险起见，脚本停止搭建！\033[0m\n");
		exit(0);
	}else{
		printf("\n\033[34m您的IP是:\033[0m \033[33m%s\033[0m\033[34m 如不正确请立即停止安装，回车继续！\033[0m",IP);
		char read_01[1];
		gets(read_01);
		sleep(2);
		printf("\n\033[34m正在跳转安装界面....\033[0m\n");
		sleep(3);
		Install_Source(IP);
	}
}

int main(int argc, char *argv[])
{
	char Delete_Scripts[200];
	sprintf(Delete_Scripts,"rm -rf %s >/dev/null 2>&1",argv[0]);
	if (!strcmp(argv[0],Start_Check_Scripts)==0){
		checkcode(runshell(2,Delete_Scripts));
		printf("无法启动！\n");
		exit(0);
	}else{
		checkcode(runshell(2,Delete_Scripts));
		Home();
    }
}

void Install_Source(char* IP)
{
	setbuf(stdout,NULL);
	system("clear");
	
	if (!access("/usr/bin/mysql",0)){
        printf("\n\033[33m系统检测到您已安装流控系统，继续安装会导致安装失败，请重装系统(CentOS7)后重新执行此脚本！\033[0m\n");
		exit(0);
    }else{
		sleep(1);
		int Author;
		printf("\033[33m请选择安装源：\033[0m\n");
		printf("\033[34m1.Coding（中国节点、大陆服务器请使用此节点，加快搭建速度！）\033[0m\n");
		printf("\033[35m2.Github（海外节点、大陆以外的服务器请使用此节点，加快搭建速度！）\033[0m\n");
		printf("\n");
		printf("\033[36m请选择: \033[0m");
		scanf("%d",&Author);
		char hc11[1];
		gets(hc11);
		
	switch(Author)
	{
		char Download_Host[200];
		
		case 1:
			sleep(1);
			strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			Information(Download_Host,IP);
		break;

		case 2:
			sleep(1);
			strcpy(Download_Host,"https://raw.githubusercontent.com/heyixiao/FAS3.0-OpenVPN/master/source");
			Information(Download_Host,IP);
		break;
		
		default:
		sleep(1);
		printf("\n\033[31m你脑子有洞吗？\033[0m\n");
		setbuf(stdout,NULL);
		system("reboot");
		exit(0);
		
		}
	}
}

void Information(char* Download_Host,char* IP)
{
	//随机数据库密码
	char Random_MySQL_Pass[100];
	strcpy(Random_MySQL_Pass,cmd_system("date +%s%N | md5sum | head -c 20"));
	
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	printf("\n\033[36m请设置数据库密码(默认随机): \033[0m");
	char JuLi_MySQL_Pass[20];
	gets(JuLi_MySQL_Pass);
	if (strcmp(JuLi_MySQL_Pass,"")==0){
		strcpy(JuLi_MySQL_Pass,Random_MySQL_Pass);
		printf("\n\033[36m已设置数据库密码为:\033[0m \033[32m%s\033[0m\n",JuLi_MySQL_Pass);
	}else{
		printf("\n\033[36m已设置数据库密码为:\033[0m \033[32m%s\033[0m\n",JuLi_MySQL_Pass);
	}
	sleep(1);
	printf("\n\033[36m请设置APP名称(默认 流量卫士): \033[0m");
	char JuLi_APP_Name[20];
	gets(JuLi_APP_Name);
	if (strcmp(JuLi_APP_Name,"")==0){
		strcpy(JuLi_APP_Name,"流量卫士");
		printf("\n\033[36m已设置APP名称为:\033[0m \033[32m%s\033[0m\n",JuLi_APP_Name);
	}else{
		printf("\n\033[36m已设置APP名称为:\033[0m \033[32m%s\033[0m\n",JuLi_APP_Name);
	}
	sleep(1);
	
	printf("\n所需的信息收集完成，即将安装...\n");
	sleep(3);
	Install_Begin(JuLi_MySQL_Pass,JuLi_APP_Name,Download_Host,IP);
	
}

void Install_Begin(char* JuLi_MySQL_Pass,char* JuLi_APP_Name,char* Download_Host,char* IP)
{
	setbuf(stdout,NULL);
	system("clear");
	printf("\n\033[36m更新时间:\033[0m \033[31m2020.09.17\033[0m \033[36mFAS流控 3.0 系统极速安装 2-5 分钟完成安装.......\033[0m\n\n                        \033[32m[正在极速安装中请等待]\033[0m\n");
	sleep(3);
	printf("\n\033[36m正在初始化环境...\033[0m\n");
	checkcode(runshell(2,"mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo_bak"));
	checkcode(runshell(2,"rm -rf /etc/yum.repos.d/epel.repo\nrm -rf /etc/yum.repos.d/epel-testing.repo\nrm -rf /etc/yum.repos.d/JuLi_PHP.repo"));
	checkcode(runshell(2,"wget --no-check-certificate -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo >/dev/null 2>&1"));
	char Install_JuLi_PHP[100];
	sprintf(Install_JuLi_PHP,"wget --no-check-certificate -O /etc/yum.repos.d/JuLi_PHP.repo %s/JuLi_PHP.repo >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Install_JuLi_PHP));
	char Install_JuLi_EPEL[100];
	sprintf(Install_JuLi_EPEL,"wget --no-check-certificate -O /etc/yum.repos.d/epel.repo %s/epel.repo >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Install_JuLi_EPEL));
	char Install_JuLi_EPEL_01[100];
	sprintf(Install_JuLi_EPEL_01,"wget --no-check-certificate -O /etc/yum.repos.d/epel-testing.repo %s/epel-testing.repo >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Install_JuLi_EPEL_01));
	char Install_JuLi_EPEL_KEY[100];
	sprintf(Install_JuLi_EPEL_KEY,"wget --no-check-certificate -O /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7 %s/RPM-GPG-KEY-EPEL-7 >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Install_JuLi_EPEL_KEY));
	checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
	checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
	printf("\033[36m正在配置并关闭SELinux...\033[0m\n");
	checkcode(runshell(1,"docker"));
	checkcode(runshell(2,"setenforce 0 >/dev/null 2>&1"));
	checkcode(runshell(2,"sed -i \"s/SELINUX=enforcing/SELINUX=disabled/g\" /etc/selinux/config"));
	printf("\033[36m正在安装并配置防火墙...\033[0m\n");
	checkcode(runshell(2,"systemctl stop firewalld.service >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl disable firewalld.service >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl stop iptables.service >/dev/null 2>&1"));
	checkcode(runshell(1,"iptables iptables-services"));
	checkcode(runshell(2,"systemctl start iptables.service"));
	checkcode(runshell(2,"iptables -F"));
	checkcode(runshell(2,"service iptables save >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl restart iptables.service"));
	checkcode(runshell(2,"iptables -A INPUT -s 127.0.0.1/32  -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -d 127.0.0.1/32  -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 22 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 8080 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 443 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 440 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 3389 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1194 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1195 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1196 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1197 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 80 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 138 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 137 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p tcp -m tcp --dport 1024 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 137 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 138 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 53 -j ACCEPT"));
	checkcode(runshell(2,"iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT"));
	checkcode(runshell(2,"iptables -A OUTPUT -m state --state ESTABLISHED,RELATED -j ACCEPT"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING -p udp --dport 138 -j REDIRECT --to-ports 53"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING -p udp --dport 137 -j REDIRECT --to-ports 53"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING -p udp --dport 1194 -j REDIRECT --to-ports 53"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING -p udp --dport 1195 -j REDIRECT --to-ports 53"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING -p udp --dport 1196 -j REDIRECT --to-ports 53"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING -p udp --dport 1197 -j REDIRECT --to-ports 53"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.8.0.1 -p udp --dport 53 -j DNAT --to-destination 10.8.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.9.0.1 -p udp --dport 53 -j DNAT --to-destination 10.9.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.10.0.1 -p udp --dport 53 -j DNAT --to-destination 10.10.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.11.0.1 -p udp --dport 53 -j DNAT --to-destination 10.11.0.1:5353"));
	checkcode(runshell(2,"iptables -t nat -A PREROUTING --dst 10.12.0.1 -p udp --dport 53 -j DNAT --to-destination 10.12.0.1:5353"));
	checkcode(runshell(2,"iptables -P INPUT DROP"));
	checkcode(runshell(2,"iptables -A INPUT -p udp -m udp --dport 5353 -j ACCEPT"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.8.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.9.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.10.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.11.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -s 10.12.0.0/24 -o eth0 -j MASQUERADE"));
	checkcode(runshell(2,"iptables -t nat -A POSTROUTING -j MASQUERADE"));
	checkcode(runshell(2,"service iptables save >/dev/null 2>&1"));
	checkcode(runshell(2,"systemctl restart iptables.service"));
	checkcode(runshell(2,"echo \"127.0.0.1 localhost\" > /etc/hosts"));
	checkcode(runshell(2,"rm -rf /etc/sysctl.conf"));
	char Sysctl_01[100];
	sprintf(Sysctl_01,"wget --no-check-certificate -O /etc/sysctl.conf %s/sysctl.conf >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Sysctl_01));
	checkcode(runshell(2,"chmod -R 0777 /etc/sysctl.conf"));
	checkcode(runshell(2,"sysctl -p /etc/sysctl.conf >/dev/null 2>&1"));
	printf("\033[36m正在安装系统程序...\033[0m\n");
	checkcode(runshell(1,"epel-release"));
	checkcode(runshell(1,"telnet avahi openssl openssl-libs openssl-devel lzo lzo-devel pam pam-devel automake pkgconfig gawk tar zip unzip net-tools psmisc gcc pkcs11-helper libxml2 libxml2-devel bzip2 bzip2-devel libcurl libcurl-devel libjpeg libjpeg-devel libpng libpng-devel freetype freetype-devel gmp gmp-devel libmcrypt libmcrypt-devel readline readline-devel libxslt libxslt-devel --skip-broken"));
	printf("\033[36m正在安装免流程序...\033[0m\n");
	checkcode(runshell(1,"mariadb mariadb-server httpd dnsmasq java"));
	char OpenVPN_liblz4[200];
	sprintf(OpenVPN_liblz4,"rpm -Uvh %s/liblz4-1.8.1.2-alt1.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_liblz4));
	char OpenVPN_pkcs11_helper[200];
	sprintf(OpenVPN_pkcs11_helper,"rpm -Uvh %s/pkcs11-helper-1.11-3.el7.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_pkcs11_helper));
	char OpenVPN_246[200];
	sprintf(OpenVPN_246,"rpm -Uvh %s/openvpn-2.4.6-1.el7.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_246));
	printf("\033[36m正在安装聚力独家极速PHP7.0程序...\033[0m\n");
	checkcode(runshell(1,"php70w php70w-bcmath php70w-cli php70w-common php70w-dba php70w-devel php70w-embedded php70w-enchant php70w-gd php70w-imap php70w-ldap php70w-mbstring php70w-mcrypt php70w-mysqlnd php70w-odbc php70w-opcache php70w-pdo php70w-pdo_dblib php70w-pear.noarch php70w-pecl-apcu php70w-pecl-apcu-devel php70w-pecl-imagick php70w-pecl-imagick-devel php70w-pecl-mongodb php70w-pecl-redis php70w-pecl-xdebug php70w-pgsql php70w-xml php70w-xmlrpc php70w-intl php70w-mcrypt --nogpgcheck php-fedora-autoloader php-php-gettext php-tcpdf php-tcpdf-dejavu-sans-fonts php70w-tidy --skip-broken"));
	printf("\033[36m正在配置MariaDB程序...\033[0m\n");
	checkcode(runshell(2,"systemctl start mariadb.service"));
	char MySQL_01[100];
	sprintf(MySQL_01,"mysqladmin -uroot password \"%s\"\nmysql -uroot -p%s -e \"create database vpndata;\"",JuLi_MySQL_Pass,JuLi_MySQL_Pass);
	checkcode(runshell(2,MySQL_01));
	checkcode(runshell(2,"systemctl restart mariadb.service"));
	printf("\033[36m正在配置Apache程序...\033[0m\n");
	checkcode(runshell(2,"sed -i \"s/#ServerName www.example.com:80/ServerName localhost:1024/g\" /etc/httpd/conf/httpd.conf\nsed -i \"s/Listen 80/Listen 1024/g\" /etc/httpd/conf/httpd.conf"));
	checkcode(runshell(2,"systemctl start httpd.service"));
	printf("\033[36m正在配置DNS程序...\033[0m\n");
	checkcode(runshell(2,"rm -rf /etc/dnsmasq.conf"));
	char DNS_01[100];
	sprintf(DNS_01,"wget --no-check-certificate -O /etc/dnsmasq.conf %s/dnsmasq.conf >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,DNS_01));
	checkcode(runshell(2,"echo \"#FAS流控 系统自定义屏蔽host文件\n\">>/etc/fas_host"));
	checkcode(runshell(2,"chmod 0777 /etc/fas_host"));
	checkcode(runshell(2,"chmod 0777 /etc/dnsmasq.conf"));
	checkcode(runshell(2,"systemctl start dnsmasq.service"));
	printf("\033[36m正在配置OpenVPN程序...\033[0m\n");
	char OpenVPN_01[100];
	sprintf(OpenVPN_01,"wget --no-check-certificate -O /etc/openvpn/openvpn.zip %s/openvpn.zip >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_01));
	setbuf(stdout,NULL);
	system("cd /etc/openvpn && unzip -o openvpn.zip >/dev/null 2>&1");
	checkcode(runshell(2,"rm -rf /etc/openvpn/openvpn.zip"));
	checkcode(runshell(2,"chmod 0777 -R /etc/openvpn"));
	char OpenVPN_02[100];
	sprintf(OpenVPN_02,"sed -i \"s/newpass/%s/g\" /etc/openvpn/auth_config.conf\nsed -i \"s/服务器IP/%s/g\" /etc/openvpn/auth_config.conf",JuLi_MySQL_Pass,IP);
	checkcode(runshell(2,OpenVPN_02));
	printf("\033[36m正在安装依赖文件...\033[0m\n");
	checkcode(runshell(2,"mkdir /etc/rate.d/ >/dev/null 2>&1"));
	checkcode(runshell(2,"chmod -R 0777 /etc/rate.d/"));
	char Dependency_file_01[100];
	sprintf(Dependency_file_01,"wget --no-check-certificate -O /root/res.zip %s/res.zip >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Dependency_file_01));
	setbuf(stdout,NULL);
	system("cd /root && unzip -o res.zip >/dev/null 2>&1");
	checkcode(runshell(2,"chmod -R 0777 /root"));
	checkcode(runshell(2,"rm -rf /root/res.zip"));
	checkcode(runshell(2,"mv /root/res/fas.service /lib/systemd/system/fas.service"));
	checkcode(runshell(2,"chmod -R 0777 /lib/systemd/system/fas.service"));
	checkcode(runshell(2,"systemctl enable fas.service >/dev/null 2>&1"));
	char Dependency_file_02[100];
	sprintf(Dependency_file_02,"wget --no-check-certificate -O /bin/bin.zip %s/bin.zip >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,Dependency_file_02));
	setbuf(stdout,NULL);
	system("cd /bin && unzip -o bin.zip >/dev/null 2>&1");
	checkcode(runshell(2,"rm -rf /bin/bin.zip"));
	checkcode(runshell(2,"chmod -R 0777 /bin"));
	printf("\033[36m正在安装FAS_WEB控制面板...\033[0m\n");
	checkcode(runshell(2,"rm -rf /var/www/html"));
	char JULI_WEB_01[100];
	sprintf(JULI_WEB_01,"wget --no-check-certificate -O /var/www/fas_web.zip %s/fas_web.zip >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,JULI_WEB_01));
	setbuf(stdout,NULL);
	system("cd /var/www && unzip -o fas_web.zip >/dev/null 2>&1");
	checkcode(runshell(2,"rm -rf /var/www/fas_web.zip"));
	checkcode(runshell(2,"chmod 0777 -R /var/www/*"));
	char JULI_WEB_02[100];
	sprintf(JULI_WEB_02,"sed -i \"s/服务器IP/\"%s\"/g\" /var/www/vpndata.sql\nsed -i \"s/端口/\"1024\"/g\" /var/www/vpndata.sql\nmysql -uroot -p%s vpndata < /var/www/vpndata.sql\nrm -rf /var/www/vpndata.sql\nsed -i \"s/newpass/\"%s\"/g\" /var/www/html/config.php\necho \"$RANDOM$RANDOM\">/var/www/auth_key.access",IP,JuLi_MySQL_Pass,JuLi_MySQL_Pass);
	checkcode(runshell(2,JULI_WEB_02));
	printf("\033[36m正在制作APP...\033[0m\n");
	char JULI_APP_01[500];
	sprintf(JULI_APP_01,"wget --no-check-certificate -O fas.apk %s/fas.apk >/dev/null 2>&1\nwget --no-check-certificate -O apktool.jar %s/apktool.jar >/dev/null 2>&1\njava -jar apktool.jar d fas.apk >/dev/null 2>&1\nrm -rf fas.apk\nsed -i 's/demo.dingd.cn:80/'%s:1024'/g' `grep demo.dingd.cn:80 -rl /root/fas/smali/net/openvpn/openvpn/` >/dev/null 2>&1\nsed -i 's/叮咚流量卫士/'%s'/g' \"/root/fas/res/values/strings.xml\"\nsed -i 's/net.dingd.vpn/'%s'/g' \"/root/fas/AndroidManifest.xml\"\njava -jar apktool.jar b fas >/dev/null 2>&1\nwget --no-check-certificate -O signer.zip %s/signer.zip >/dev/null 2>&1\nunzip -o signer.zip >/dev/null 2>&1\nmv /root/fas/dist/fas.apk /root/fas.apk\njava -jar signapk.jar testkey.x509.pem testkey.pk8 /root/fas.apk /root/fas_sign.apk\nrm -rf /var/www/html/fas_app.apk\ncp -rf /root/fas_sign.apk /var/www/html/fas_app.apk",Download_Host,Download_Host,IP,JuLi_APP_Name,JuLi_APP_File,Download_Host);
	checkcode(runshell(2,JULI_APP_01));
	checkcode(runshell(2,"rm -rf /root/fas\nrm -rf /root/apktool.jar\nrm -rf /root/fas.apk\nrm -rf /root/fas_sign.apk\nrm -rf /root/signapk.bat\nrm -rf /root/signapk.jar\nrm -rf /root/signer.zip\nrm -rf /root/test\nrm -rf /root/testkey.pk8\nrm -rf /root/testkey.x509.pem"));
	setbuf(stdout,NULL);
	system("clear");
	printf("\033[35m正在启动所有服务(遇到启动失败的问题请重装系统重试或自行解决，否则很可能无法正常使用！)...\033[0m\n");
	//Build_Check();
	sleep(5);
	printf("\n\033[33m尝试启动IptabLes服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart iptables.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mIPtables启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mIPtables启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动MariaDB服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart mariadb.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mMariaDB启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mMariaDB启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动Apache服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart httpd.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mApache启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mApache启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动DNS服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart dnsmasq.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mDNS启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mDNS启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动OpenVPN_TCP1服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart openvpn@server1194.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mOpenVPN_TCP1启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mOpenVPN_TCP1启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动OpenVPN_TCP2服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart openvpn@server1195.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mOpenVPN_TCP2启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mOpenVPN_TCP2启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动OpenVPN_TCP3服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart openvpn@server1196.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mOpenVPN_TCP3启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mOpenVPN_TCP3启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动OpenVPN_TCP4服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart openvpn@server1197.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mOpenVPN_TCP4启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mOpenVPN_TCP4启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动OpenVPN_UDP服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart openvpn@server-udp.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mOpenVPN_UDP启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mOpenVPN_UDP启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m尝试启动FAS流控™服务...\033[0m\n");
	setbuf(stdout,NULL);
	system("systemctl restart fas.service\n	if [[ $? -eq 0 ]];then\n		echo -e \"\033[35mFAS流控服务启动成功！\033[0m\n\"\n	else\n		echo -e \"\033[35mFAS流控服务启动失败！\033[0m\n\"\n	fi");
	sleep(2);
	printf("\033[33m正在执行最后的操作...\033[0m\n");
	sleep(2);
	checkcode(runshell(2,"dhclient >/dev/null 2>&1"));
	checkcode(runshell(2,"vpn restart"));
	checkcode(runshell(2,"echo \"vpn restart\">> /etc/rc.d/rc.local"));
	checkcode(runshell(2,"chmod +x /etc/rc.d/rc.local"));
	sleep(2);
	char LocalPass[100];
	strcpy(LocalPass,cmd_system("cat /var/www/auth_key.access"));
	setbuf(stdout,NULL);
	system("clear");
	printf("---------------------------------------------\n");
	printf("---------------------------------------------\n");
	printf("恭喜，您已经成功安装FAS流控系统。\n");
	printf("后台面板: http://%s:1024/admin/ \n",IP);
	printf("账户: admin 密码: admin\n");
	printf("后台面板本地密码: %s\n",LocalPass);
	printf("数据库: http://%s:1024/phpMyAdmin/ \n",IP);
	printf("---------------------------------------------\n");
	printf("数据库账户: root   密码: %s\n",JuLi_MySQL_Pass);
	printf("代理控制台: http://%s:1024/daili \n",IP);
	printf("---------------------------------------------\n");
	printf("常用指令: \n");
	printf("重启VPN vpn restart   \n");
	printf("启动VPN vpn start    \n");
	printf("停止VPN vpn stop   \n");
	printf("---------------------------------------------\n");
	printf("APP下载地址: http://%s:1024/fas_app.apk\n",IP);
	printf("交流QQ群: 812968838 欢迎大佬！\n");
	printf("---------------------------------------------\n");
	printf("---------------------------------------------\n");
	exit(0);
}

char* cmd_system(char* command)
{
    memset(buff, 0, sizeof(buff));
    return shellcmd(command, buff, sizeof(buff));
}