#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
//流控版权为筑梦冬瓜所有！！
//此脚本为聚力编写！！
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


void Readme()
{
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	printf("-----------------欢迎使用FAS网络用户管理系统--------------------\n");
	printf("----------------V3.0 (2021.09.09聚力重新整理)-------------------\n");
	printf("本脚本支持国内外服务器搭建，梯子、免流、DNS拦截等等，免费搭建！\n");
	printf("FAS3.0流控  作者：筑梦科技(冬瓜) https://www.dingd.cn/product/fas.html  \n");
	printf("此版本为FAS3.0流控去授权版  所有源码和FAS3.0原版一毛一样  没有任何后门  不放心的别用！  \n");
	printf("FAS流控【用户流量监控】已去除授权，可正常使用，由南瓜群(白菜大佬)提供的FAS【用户流量监控】去授权版\n");
	printf("脚本源码文件已全部开源(Coding)：https://daloradius.coding.net/public/fast/fast/git/files \n");
	printf("脚本源码文件已全部开源(Github)：https://github.com/heyixiao/FAS3.0-OpenVPN \n");
	printf("----------------------------------------------------------------\n");
	printf("交流QQ群: 812968838  个人博客: blog.daloradius.cn\n");
	printf("----------------------------------------------------------------\n");
	printf("2021.09.11优化脚本逻辑问题，重新整理，修复APP编译问题，添加程序安装成功or失败检测，添加系统更新解决大部分搭建失败的问题 添加系统负载功能   如有逻辑错误请反馈！！\n");
	printf("2021.10.11修复搭建逻辑错误问题！\n");
	printf("-----------------------同意 请回车继续--------------------------\n");
	char hc11[1];
	gets(hc11);
	GET_IP();
}


void GET_IP()
{
	setbuf(stdout,NULL);
	system("clear");
	int Author;
		printf("\033[33m请选择IP获取方式：\033[0m\n");
		printf("\033[34m1.自动获取IP（接口来自 members.3322.org ）\033[0m\n");
		printf("\033[35m2.手动输入IP（自动获取IP失败时请使用此选项）\033[0m\n");
		printf("\n");
		printf("\033[36m请选择[1-2]: \033[0m");
		scanf("%d",&Author);
		char hc11[1];
		gets(hc11);
		
	switch(Author)
	{
		char IP[200];
		
		case 1:
			printf("\n\033[36m请稍等\033[0m\n");
			sleep(1);
			strcpy(IP,cmd_system("echo `curl -s \"http://members.3322.org/dyndns/getip\"` | tr -d '\n'"));
			if (strcmp(IP,"")==0){
				printf("\n\033[31m无法检测您的服务器IP，可能会影响到您接下来的搭建工作，保险起见，请手动输入IP进行确认！\033[0m\n");
				sleep(1);
				printf("\n\033[36m请输入服务器IP: \033[0m");
				gets(IP);
				if (strcmp(IP,"")==0){
					printf("\n\033[31m你脑子有洞吗？\033[0m\n");
					setbuf(stdout,NULL);
					system("reboot");
					exit(0);
				}else{
					printf("\n\033[33m您的IP是:\033[0m \033[32m%s\033[0m\033[33m 如不正确请立即停止安装，回车继续！\033[0m",IP);
					char read_01[1];
					gets(read_01);
					//sleep(2);
					printf("\n\033[35m正在跳转安装界面....\033[0m\n");
					sleep(3);
					Install_Option(IP);
				}
			}else{
				printf("\n\033[33m您的IP是:\033[0m \033[32m%s\033[0m\033[33m 如不正确请立即停止安装，回车继续！\033[0m",IP);
				char read_01[1];
				gets(read_01);
				//sleep(2);
				printf("\n\033[35m正在跳转安装界面....\033[0m\n");
				sleep(3);
				Install_Option(IP);
			}
		break;

		case 2:
			sleep(1);
			printf("\n\033[36m请输入服务器IP: \033[0m");
			gets(IP);
			if (strcmp(IP,"")==0){
				printf("\n\033[31m你脑子有洞吗？\033[0m\n");
				setbuf(stdout,NULL);
				system("reboot");
				exit(0);
			}else{
				printf("\n\033[33m您的IP是:\033[0m \033[32m%s\033[0m\033[33m 如不正确请立即停止安装，回车继续！\033[0m",IP);
				char read_01[1];
				gets(read_01);
				sleep(2);
				printf("\n\033[35m正在跳转安装界面....\033[0m\n");
				sleep(3);
				Install_Option(IP);
			}
			
			
		break;
		
		default:
		sleep(1);
		printf("\n\033[31m你脑子有洞吗？\033[0m\n");
		setbuf(stdout,NULL);
		system("reboot");
		exit(0);
		
	}
}





void FAS_On_MySQL(char* IP)
{
	
	
	
	//主机开启远程数据库访问权限
	
	
	printf("\n\033[36m请输入本机IP: \033[0m");
	char FAS_On_MySQL_IP[20];
	gets(FAS_On_MySQL_IP);
	if (strcmp(FAS_On_MySQL_IP,"")==0){
		strcpy(FAS_On_MySQL_IP,IP);
		printf("\n\033[36m已输入主机IP为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_IP);
	}else{
		printf("\n\033[36m已输入主机IP为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_IP);
	}
	sleep(1);
	
	printf("\n\033[36m请输入本机数据库端口: \033[0m");
	char FAS_On_MySQL_Port[20];
	gets(FAS_On_MySQL_Port);
	if (strcmp(FAS_On_MySQL_Port,"")==0){
		strcpy(FAS_On_MySQL_Port,"");
		printf("\n\033[36m已输入本机数据库端口为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_Port);
	}else{
		printf("\n\033[36m已输入本机数据库端口为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_Port);
	}
	sleep(1);
	
	
	printf("\n\033[36m请输入本机数据库账户: \033[0m");
	char FAS_On_MySQL_User[20];
	gets(FAS_On_MySQL_User);
	if (strcmp(FAS_On_MySQL_User,"")==0){
		strcpy(FAS_On_MySQL_User,"");
		printf("\n\033[36m已输入本机数据库账户为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_User);
	}else{
		printf("\n\033[36m已输入本机数据库账户为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_User);
	}
	sleep(1);
	
	printf("\n\033[36m请输入本机数据库密码: \033[0m");
	char FAS_On_MySQL_Pass[20];
	gets(FAS_On_MySQL_Pass);
	if (strcmp(FAS_On_MySQL_Pass,"")==0){
		strcpy(FAS_On_MySQL_Pass,"");
		printf("\n\033[36m已输入本机数据库密码为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_Pass);
	}else{
		printf("\n\033[36m已输入本机数据库密码为:\033[0m \033[32m%s\033[0m\n",FAS_On_MySQL_Pass);
	}
	sleep(1);
	
	
	printf("\n\033[32m操作中...\033[0m \n");
	sleep(3);
	
	char FAS_On_MySQL1[200];
	sprintf(FAS_On_MySQL1,"mysql -h%s -P%s -u%s -p%s -e \"grant all privileges on *.* to '%s'@'%' identified by '%s' with grant option;flush privileges;\"",FAS_On_MySQL_IP,FAS_On_MySQL_Port,FAS_On_MySQL_User,FAS_On_MySQL_Pass,FAS_On_MySQL_User,FAS_On_MySQL_Pass);
	checkcode(runshell(2,FAS_On_MySQL1));
	
	setbuf(stdout,NULL);
	system("systemctl restart mariadb.service");
	
	
	
	
	printf("\n\033[33m操作已完成。\033[0m \n");
	exit(0);
	
	
	
	
}





void FAS_Note_for_MySQL(char* IP)
{
	
	
	
	//节点机器对接主机数据库.  或者云库
	
	
	printf("\n\033[36m请输入主机IP/云库域名: \033[0m");
	char FAS_Note_for_MySQL_IP[20];
	gets(FAS_Note_for_MySQL_IP);
	if (strcmp(FAS_Note_for_MySQL_IP,"")==0){
		strcpy(FAS_Note_for_MySQL_IP,"");
		printf("\n\033[36m已输入主机IP为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_IP);
	}else{
		printf("\n\033[36m已输入主机IP为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_IP);
	}
	sleep(1);
	
	printf("\n\033[36m请输入主机数据库端口: \033[0m");
	char FAS_Note_for_MySQL_Port[20];
	gets(FAS_Note_for_MySQL_Port);
	if (strcmp(FAS_Note_for_MySQL_Port,"")==0){
		strcpy(FAS_Note_for_MySQL_Port,"");
		printf("\n\033[36m已输入主机数据库端口为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_Port);
	}else{
		printf("\n\033[36m已输入主机数据库端口为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_Port);
	}
	sleep(1);
	
	
	printf("\n\033[36m请输入主机数据库账户: \033[0m");
	char FAS_Note_for_MySQL_User[20];
	gets(FAS_Note_for_MySQL_User);
	if (strcmp(FAS_Note_for_MySQL_User,"")==0){
		strcpy(FAS_Note_for_MySQL_User,"");
		printf("\n\033[36m已输入主机数据库账户为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_User);
	}else{
		printf("\n\033[36m已输入主机数据库账户为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_User);
	}
	sleep(1);
	
	printf("\n\033[36m请输入主机数据库密码: \033[0m");
	char FAS_Note_for_MySQL_Pass[20];
	gets(FAS_Note_for_MySQL_Pass);
	if (strcmp(FAS_Note_for_MySQL_Pass,"")==0){
		strcpy(FAS_Note_for_MySQL_Pass,"");
		printf("\n\033[36m已输入主机数据库密码为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_Pass);
	}else{
		printf("\n\033[36m已输入主机数据库密码为:\033[0m \033[32m%s\033[0m\n",FAS_Note_for_MySQL_Pass);
	}
	sleep(1);
	
	
	printf("\n\033[32m操作中...\033[0m \n");
	sleep(3);
	
	
	//删除配置文件
	checkcode(runshell(2,"rm -rf /etc/openvpn/auth_config.conf"));
	checkcode(runshell(2,"rm -rf /var/www/html/config.php"));
	
	//创建新的配置文件auth_config
	char ADD_auth_config[200];
	sprintf(ADD_auth_config,"cat >> /etc/openvpn/auth_config.conf <<EOF\n#!/bin/bash\n#兼容配置文件 此文件格式既可以适应shell也可以适应聚力监控，但是这里不能使用变量，也不是真的SHELL文件，不要写任何shell在这个文件\n#聚力流控监控系统配置文件\n#请谨慎修改\n#数据库地址\nmysql_host=%s\n#数据库用户\nmysql_user=%s\n#数据库密码\nmysql_pass=%s\n#数据库端口\nmysql_port=%s\n#数据库端口\nmysql_data=vpndata\n#本机地址\naddress=%s\n#指定异常记录回收时间 单位s 600即为十分钟\nunset_time=600\n#删除僵尸记录地址\ndel=\"/root/res/del\"\n\n#进程1监控地址\nstatus_file_1=\"/var/www/html/openvpn_api/online_1194.txt 7075 1194 tcp-server\"\nstatus_file_2=\"/var/www/html/openvpn_api/online_1195.txt 7076 1195 tcp-server\"\nstatus_file_3=\"/var/www/html/openvpn_api/online_1196.txt 7077 1196 tcp-server\"\nstatus_file_4=\"/var/www/html/openvpn_api/online_1197.txt 7078 1197 tcp-server\"\nstatus_file_5=\"/var/www/html/openvpn_api/user-status-udp.txt 7079 53 udp\"\n#睡眠时间\nsleep=3\nEOF",FAS_Note_for_MySQL_IP,FAS_Note_for_MySQL_User,FAS_Note_for_MySQL_Pass,FAS_Note_for_MySQL_Port,IP);
	checkcode(runshell(2,ADD_auth_config));
	checkcode(runshell(2,"chmod -R 0777 /etc/openvpn/auth_config.conf"));
	
	
	//创建新的配置文件config
	char ADD_config[200];
	sprintf(ADD_config,"cat >> /var/www/html/config.php <<EOF\n<?php\ndefine(\"_host_\",\"%s\");\ndefine(\"_user_\",\"%s\");\ndefine(\"_pass_\",\"%s\");\ndefine(\"_port_\",\"%s\");\ndefine(\"_ov_\",\"vpndata\");\ndefine(\"_openvpn_\",\"openvpn\");\ndefine(\"_iuser_\",\"iuser\");\ndefine(\"_ipass_\",\"pass\");\ndefine(\"_isent_\",\"isent\");\ndefine(\"_irecv_\",\"irecv\");\ndefine(\"_starttime_\",\"starttime\");\ndefine(\"_endtime_\",\"endtime\");\ndefine(\"_maxll_\",\"maxll\");\ndefine(\_other_\",\"dlid,tian\");\ndefine(\"_i_\",\"i\");\nEOF",FAS_Note_for_MySQL_IP,FAS_Note_for_MySQL_User,FAS_Note_for_MySQL_Pass,FAS_Note_for_MySQL_Port);
	checkcode(runshell(2,ADD_config));
	checkcode(runshell(2,"chmod -R 0777 /var/www/html/config.php"));
	
	
	
	
	setbuf(stdout,NULL);
	system("vpn restart");
	
	
	
	checkcode(runshell(2,"chmod -R 0777 /var/www/html/config.php"));
	printf("\n\033[33m操作已完成。\033[0m \n");
	exit(0);
	
	
	
	
	
	
	
}

void FAS_Load(char* IP)
{
	
	//系统负载
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	int Author1;
		printf("\n\033[33m请选择安装类型：\033[0m\n");
		printf("\033[34m1.主机开启远程数据库访问权限(只需要开启一次)\033[0m\n");
		printf("\033[36m2.节点机器对接主机数据库(也可以直接对接云库)\033[0m\n");
		printf("\033[35m3.退出脚本\033[0m\n");
		printf("\n");
		printf("\033[36m请选择[1-3]: \033[0m");
		scanf("%d",&Author1);
		char hc111[1];
		gets(hc111);
			
	switch(Author1)
	{
		//char Download_Host[200];
		//char Option_Download_Host_1[200];
		case 1:
			sleep(1);
			//strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			//strcpy(Option_Download_Host_1,"Coding");
			printf("\033[32m请稍等\033[0m \n");
			sleep(3);
			FAS_On_MySQL(IP);
		break;

		case 2:
			sleep(1);
			//strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			//strcpy(Option_Download_Host_1,"Coding");
			printf("\033[32m请稍等\033[0m \n");
			sleep(3);
			FAS_Note_for_MySQL(IP);
		break;
		
		case 3:
			printf("\n\033[31m脚本结束。\033[0m\n");
			exit(0);
		break;
			
			
			
		default:
		sleep(1);
		printf("\n\033[31m你脑子有洞吗？\033[0m\n");
		setbuf(stdout,NULL);
		system("reboot");
		exit(0);
		
	}
	
	
}




void CentOS_Update(char* Download_Host)
{
	
	//系统更新  
	
	
	
	//更换YUM源
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
	
	
	
	//开始更新
	setbuf(stdout,NULL);
	system("yum clean all");
	setbuf(stdout,NULL);
	system("yum makecache");
	setbuf(stdout,NULL);
	system("yum -y install update");
	setbuf(stdout,NULL);
	system("yum -y install upgrade");
	setbuf(stdout,NULL);
	system("yum groupinstall -y Development tools");
	printf("\n\033[36m更新完成。\033[0m\n");
	
	
	
	exit(0);
	
	
	
	
	
}




void Install_Option(char* IP)
{
	
	
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	int Author1;
		printf("\n\033[33m请选择安装类型：\033[0m\n");
		printf("\033[34m1.全新安装[FAS3.0]\033[0m\n");
		printf("\033[36m2.系统负载[集群]\033[0m\n");
		printf("\033[32m3.系统更新[CentOS7.X系统更新至CentOS7.10最新]\033[0m\n");
		printf("\033[35m4.退出脚本\033[0m\n");
		printf("\n");
		printf("\033[36m请选择[1-4]: \033[0m");
		scanf("%d",&Author1);
		char hc111[1];
		gets(hc111);
			
	switch(Author1)
	{
		char Download_Host[200];
		//char Option_Download_Host_1[200];
		case 1:
			//sleep(1);
			//strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			//strcpy(Option_Download_Host_1,"Coding");
			printf("\n\033[32m请稍等\033[0m \n");
			sleep(3);
			Option_Download_Host(IP);
		break;

		case 2:
			//sleep(1);
			//strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			//strcpy(Option_Download_Host_1,"Coding");
			printf("\n\033[32m请稍等\033[0m \n");
			sleep(3);
			FAS_Load(IP);
		break;

		case 3:
			//sleep(1);
			//char Download_Host[200];
			strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			//strcpy(Option_Download_Host_1,"Coding");
			printf("\n\033[32m请稍等\033[0m \n");
			sleep(3);
			CentOS_Update(Download_Host);
		break;
		
		case 4:
			printf("\n\033[31m脚本结束。\033[0m\n");
			exit(0);
		break;
		
		
		
		default:
		sleep(1);
		printf("\n\033[31m你脑子有洞吗？\033[0m\n");
		setbuf(stdout,NULL);
		system("reboot");
		exit(0);
		
	}
}



void Option_Download_Host(char* IP)
{
	setbuf(stdout,NULL);
	system("clear");
	sleep(1);
	int Author1;
		printf("\n\033[33m开始安装FAS3.0\033[0m\n");
		printf("\n\033[33m请选择安装源：\033[0m\n");
		printf("\033[34m1.Coding（中国节点、大陆服务器请使用此节点，加快搭建速度！）\033[0m\n");
		printf("\033[35m2.Github（海外节点、大陆以外的服务器请使用此节点，加快搭建速度！）\033[0m\n");
		printf("\n");
		printf("\033[36m请选择[1-2]: \033[0m");
		scanf("%d",&Author1);
		char hc111[1];
		gets(hc111);
			
	switch(Author1)
	{
		char Download_Host[200];
		char Option_Download_Host_1[200];
		case 1:
			sleep(1);
			strcpy(Download_Host,"https://daloradius.coding.net/p/fast/git/raw/master/source");
			strcpy(Option_Download_Host_1,"Coding");
			printf("\n\033[32m已选择安装源为:\033[0m \033[32mCoding\033[0m\n");
			Install_information(Download_Host,IP,Option_Download_Host_1);
		break;

		case 2:
			sleep(1);
			strcpy(Download_Host,"https://raw.githubusercontent.com/heyixiao/FAS3.0-OpenVPN/master/source");
			strcpy(Option_Download_Host_1,"Github");
			printf("\n\033[32m已选择安装源为:\033[0m \033[32mGithub\033[0m\n");
			Install_information(Download_Host,IP,Option_Download_Host_1);
		break;
		
		
		
		default:
		sleep(1);
		printf("\n\033[31m你脑子有洞吗？\033[0m\n");
		setbuf(stdout,NULL);
		system("reboot");
		exit(0);
		
	}
}


void Install_information(char* Download_Host,char* IP,char* Option_Download_Host_1)
{
	if (!access("/usr/bin/mysql",0)){
        printf("\n\033[33m错误，检测到有MySQL残留或已安装流控系统，请先重装系统后重试！\033[0m\n");
		exit(0);
    }else{
		//printf("\n\033[33m未安装数据库！\033[0m\n");
	}
	
	//随机数据库密码
	char Random_MySQL_Pass[100];
	strcpy(Random_MySQL_Pass,cmd_system("date +%s%N | md5sum | head -c 20"));
	
	sleep(1);
	printf("\n\033[36m请设置数据库密码(默认: 随机密码): \033[0m");
	char JuLi_MySQL_Pass[20];
	gets(JuLi_MySQL_Pass);
	if (strcmp(JuLi_MySQL_Pass,"")==0){
		strcpy(JuLi_MySQL_Pass,Random_MySQL_Pass);
		printf("\n\033[36m已设置数据库密码为:\033[0m \033[32m%s\033[0m\n",JuLi_MySQL_Pass);
	}else{
		printf("\n\033[36m已设置数据库密码为:\033[0m \033[32m%s\033[0m\n",JuLi_MySQL_Pass);
	}
	sleep(1);
	printf("\n\033[36m请设置APP名称(默认: 流量卫士): \033[0m");
	char JuLi_APP_Name[20];
	gets(JuLi_APP_Name);
	if (strcmp(JuLi_APP_Name,"")==0){
		strcpy(JuLi_APP_Name,"流量卫士");
		printf("\n\033[36m已设置APP名称为:\033[0m \033[32m%s\033[0m\n",JuLi_APP_Name);
	}else{
		printf("\n\033[36m已设置APP名称为:\033[0m \033[32m%s\033[0m\n",JuLi_APP_Name);
	}
	sleep(1);
	
	printf("\n\033[36m请输入SSH端口(默认: 22): \033[0m");
	char JuLi_SSH_Port[20];
	gets(JuLi_SSH_Port);
	if (strcmp(JuLi_SSH_Port,"")==0){
		strcpy(JuLi_SSH_Port,"22");
		printf("\n\033[36m已输入SSH端口为:\033[0m \033[32m%s\033[0m\n",JuLi_SSH_Port);
	}else{
		printf("\n\033[36m已输入SSH端口为:\033[0m \033[32m%s\033[0m\n",JuLi_SSH_Port);
	}
	sleep(1);
	
	printf("\n\033[35mTip: 如果正常搭建失败，请尝试更新下系统在进行搭建，可以解决大部分因系统环境不全而搭建失败的问题!(更新系统很费时，请做好准备!)\033[0m");
	printf("\n\033[36m是否需要进行系统更新[Y/N]: \033[0m");
	char JuLi_System_Update[20];
	gets(JuLi_System_Update);
	if (strcmp(JuLi_System_Update,"Y")==0){
		//相同
		printf("\n\033[36m系统更新\033[0m \033[32m[已开启]\033[0m\n");
	}else{
		if (strcmp(JuLi_System_Update,"y")==0){
			//相同
			printf("\n\033[36m系统更新\033[0m \033[32m[已开启]\033[0m\n");
		}else{
			if (strcmp(JuLi_System_Update,"N")==0){
			//相同
				printf("\n\033[36m系统更新\033[0m \033[31m[未开启]\033[0m\n");
			}else{
				if (strcmp(JuLi_System_Update,"n")==0){
					//相同
					printf("\n\033[36m系统更新\033[0m \033[31m[未开启]\033[0m\n");
				}else{
					//不相同
					strcpy(JuLi_System_Update,"n");
					printf("\n\033[36m系统更新\033[0m \033[31m[未开启]\033[0m\n");
				}
			}
		}
	}
	sleep(1);
	
	printf("\n所需的信息收集完成，即将安装...\n");
	sleep(3);
	
	Install_Begin(Download_Host,IP,Option_Download_Host_1,JuLi_MySQL_Pass,JuLi_APP_Name,JuLi_System_Update,JuLi_SSH_Port);
	
}

void Install_Begin(char* Download_Host,char* IP,char* Option_Download_Host_1,char* JuLi_MySQL_Pass,char* JuLi_APP_Name,char* JuLi_System_Update,char* JuLi_SSH_Port)
{
	//printf("\n所需的信息收集完成，即将安装...\n");
	if (strcmp(JuLi_System_Update,"Y")==0){
		//相同
		printf("\n\033[36m正在准备系统更新(耗时较久耐心等待)...\033[0m\n");
		sleep(5);
		if (strcmp(Option_Download_Host_1,"Coding")==0){
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
			//checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
			//checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
		}else{
			if (strcmp(Option_Download_Host_1,"Github")==0){
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
				//checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
				//checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
			}else{
				printf("\n\033[31m错误，没有选择安装源!!!\033[0m\n");
				exit(0);
				//checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
				//checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
			}
		}
		setbuf(stdout,NULL);
		system("yum clean all");
		setbuf(stdout,NULL);
		system("yum makecache");
		setbuf(stdout,NULL);
		system("yum -y install update");
		setbuf(stdout,NULL);
		system("yum -y install upgrade");
		setbuf(stdout,NULL);
		system("yum groupinstall -y Development tools");
		printf("\n\033[36m更新完成，即将开始安装流控...\033[0m\n");
		sleep(5);
		setbuf(stdout,NULL);
		system("clear");
	}else{
		if (strcmp(JuLi_System_Update,"y")==0){
			//相同
			printf("\n\033[36m正在准备系统更新(耗时较久耐心等待)...\033[0m\n");
			sleep(5);
			if (strcmp(Option_Download_Host_1,"Coding")==0){
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
				//checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
				//checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
			}else{
				if (strcmp(Option_Download_Host_1,"Github")==0){
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
					//checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
					//checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
				}else{
					printf("\n\033[31m错误，没有选择安装源!!!\033[0m\n");
					exit(0);
					//checkcode(runshell(2,"yum clean all >/dev/null 2>&1"));
					//checkcode(runshell(2,"yum makecache >/dev/null 2>&1"));
				}
			}
			setbuf(stdout,NULL);
			system("yum clean all");
			setbuf(stdout,NULL);
			system("yum makecache");
			setbuf(stdout,NULL);
			system("yum -y install update");
			setbuf(stdout,NULL);
			system("yum -y install upgrade");
			setbuf(stdout,NULL);
			system("yum groupinstall -y Development tools");
			printf("\n\033[36m更新完成，即将开始安装流控...\033[0m\n");
			sleep(5);
			setbuf(stdout,NULL);
			system("clear");
		}else{
			//不进行系统更新
			setbuf(stdout,NULL);
			system("clear");
			printf("\n\033[36m正在初始化环境(%s)...\033[0m\n",Option_Download_Host_1);
			if (strcmp(Option_Download_Host_1,"Coding")==0){
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
			}else{
				if (strcmp(Option_Download_Host_1,"Github")==0){
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
				}else{
					printf("\n\033[31m错误，没有选择安装源!!!\033[0m\n");
					exit(0);
				}
			}
		}
	}
	
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
	char JuLi_SSH_Port1[200];
	sprintf(JuLi_SSH_Port1,"iptables -A INPUT -p tcp -m tcp --dport %s -j ACCEPT",JuLi_SSH_Port);
	checkcode(runshell(2,JuLi_SSH_Port1));
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
	printf("\033[36m正在安装Apache...\033[0m\n");
	checkcode(runshell(1,"httpd"));
	if (!access("/usr/sbin/httpd",0)){
        //printf("\n\033[33m已安装！\033[0m\n");
		printf("\033[33mApache已安装成功！\033[0m\n");
		checkcode(runshell(2,"sed -i \"s/#ServerName www.example.com:80/ServerName localhost:1024/g\" /etc/httpd/conf/httpd.conf\nsed -i \"s/Listen 80/Listen 1024/g\" /etc/httpd/conf/httpd.conf"));
		checkcode(runshell(2,"systemctl start httpd.service"));
    }else{
		//printf("\n\033[33m未安装数！\033[0m\n");
		printf("\033[31m错误，检测到Apache安装不成功，正在尝试重新安装！\033[0m\n");
		checkcode(runshell(1,"httpd"));
		if (!access("/usr/sbin/httpd",0)){
			//printf("\n\033[33m已安装！\033[0m\n");
			printf("\033[33mApache已安装成功！\033[0m\n");
			checkcode(runshell(2,"sed -i \"s/#ServerName www.example.com:80/ServerName localhost:1024/g\" /etc/httpd/conf/httpd.conf\nsed -i \"s/Listen 80/Listen 1024/g\" /etc/httpd/conf/httpd.conf"));
			checkcode(runshell(2,"systemctl start httpd.service"));
		}else{
			//printf("\n\033[33m未安装数！\033[0m\n");
			printf("\033[31m错误，检测到Apache多次安装不成功，自动跳过Apache安装！\033[0m\n");
		}
	}
	printf("\033[36m正在安装聚力独家极速PHP7.0...\033[0m\n");
	checkcode(runshell(1,"php70w php70w-bcmath php70w-cli php70w-common php70w-dba php70w-devel php70w-embedded php70w-enchant php70w-gd php70w-imap php70w-ldap php70w-mbstring php70w-mcrypt php70w-mysqlnd php70w-odbc php70w-opcache php70w-pdo php70w-pdo_dblib php70w-pear.noarch php70w-pecl-apcu php70w-pecl-apcu-devel php70w-pecl-imagick php70w-pecl-imagick-devel php70w-pecl-mongodb php70w-pecl-redis php70w-pecl-xdebug php70w-pgsql php70w-xml php70w-xmlrpc php70w-intl php70w-mcrypt --nogpgcheck php-fedora-autoloader php-php-gettext php-tcpdf php-tcpdf-dejavu-sans-fonts php70w-tidy --skip-broken"));
	printf("\033[36m正在安装MariaDB...\033[0m\n");
	checkcode(runshell(1,"mariadb mariadb-server"));
	if (!access("/usr/bin/mysql",0)){
        //printf("\n\033[33m已安装！\033[0m\n");
		printf("\033[33mMariaDB已安装成功！\033[0m\n");
		checkcode(runshell(2,"systemctl start mariadb.service"));
		char MySQL_01[100];
		sprintf(MySQL_01,"mysqladmin -uroot password \"%s\"\nmysql -uroot -p%s -e \"create database vpndata;\"",JuLi_MySQL_Pass,JuLi_MySQL_Pass);
		checkcode(runshell(2,MySQL_01));
		checkcode(runshell(2,"systemctl restart mariadb.service"));
    }else{
		//printf("\n\033[33m未安装数！\033[0m\n");
		printf("\033[31m错误，检测到MariaDB安装不成功，正在尝试重新安装！\033[0m\n");
		checkcode(runshell(1,"mariadb mariadb-server"));
		if (!access("/usr/bin/mysql",0)){
			//printf("\n\033[33m已安装！\033[0m\n");
			printf("\033[33mMariaDB已安装成功！\033[0m\n");
			checkcode(runshell(2,"systemctl start mariadb.service"));
			char MySQL_01[100];
			sprintf(MySQL_01,"mysqladmin -uroot password \"%s\"\nmysql -uroot -p%s -e \"create database vpndata;\"",JuLi_MySQL_Pass,JuLi_MySQL_Pass);
			checkcode(runshell(2,MySQL_01));
			checkcode(runshell(2,"systemctl restart mariadb.service"));
		}else{
			//printf("\n\033[33m未安装数！\033[0m\n");
			printf("\033[31m错误，检测到MariaDB多次安装不成功，自动跳过MariaDB安装！\033[0m\n");
		}
	}
	printf("\033[36m正在安装OpenVPN...\033[0m\n");
	char OpenVPN_liblz4[200];
	sprintf(OpenVPN_liblz4,"rpm -Uvh %s/liblz4-1.8.1.2-alt1.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_liblz4));
	char OpenVPN_pkcs11_helper[200];
	sprintf(OpenVPN_pkcs11_helper,"rpm -Uvh %s/pkcs11-helper-1.11-3.el7.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_pkcs11_helper));
	char OpenVPN_246[200];
	sprintf(OpenVPN_246,"rpm -Uvh %s/openvpn-2.4.6-1.el7.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
	checkcode(runshell(2,OpenVPN_246));
	if (!access("/usr/sbin/openvpn",0)){
        //printf("\n\033[33m已安装！\033[0m\n");
		printf("\033[33mOpenVPN已安装成功！\033[0m\n");
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
    }else{
		//printf("\n\033[33m未安装数！\033[0m\n");
		printf("\033[31m错误，检测到OpenVPN安装不成功，正在尝试重新安装！\033[0m\n");
		char OpenVPN_liblz4[200];
		sprintf(OpenVPN_liblz4,"rpm -Uvh %s/liblz4-1.8.1.2-alt1.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
		checkcode(runshell(2,OpenVPN_liblz4));
		char OpenVPN_pkcs11_helper[200];
		sprintf(OpenVPN_pkcs11_helper,"rpm -Uvh %s/pkcs11-helper-1.11-3.el7.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
		checkcode(runshell(2,OpenVPN_pkcs11_helper));
		char OpenVPN_246[200];
		sprintf(OpenVPN_246,"rpm -Uvh %s/openvpn-2.4.6-1.el7.x86_64.rpm --force --nodeps >/dev/null 2>&1",Download_Host);
		checkcode(runshell(2,OpenVPN_246));
		if (!access("/usr/sbin/openvpn",0)){
			//printf("\n\033[33m已安装！\033[0m\n");
			printf("\033[33mOpenVPN已安装成功！\033[0m\n");
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
		}else{
			//printf("\n\033[33m未安装数！\033[0m\n");
			printf("\033[31m错误，检测到OpenVPN多次安装不成功，自动跳过OpenVPN安装！\033[0m\n");
		}
	}
	printf("\033[36m正在安装DNSmasq...\033[0m\n");
	checkcode(runshell(1,"dnsmasq"));
	if (!access("/usr/sbin/dnsmasq",0)){
        //printf("\n\033[33m已安装！\033[0m\n");
		printf("\033[33mDNSmasq已安装成功！\033[0m\n");
		checkcode(runshell(2,"rm -rf /etc/dnsmasq.conf"));
		char DNS_01[100];
		sprintf(DNS_01,"wget --no-check-certificate -O /etc/dnsmasq.conf %s/dnsmasq.conf >/dev/null 2>&1",Download_Host);
		checkcode(runshell(2,DNS_01));
		checkcode(runshell(2,"echo \"#FAS流控 系统自定义屏蔽host文件\n\">>/etc/fas_host"));
		checkcode(runshell(2,"chmod 0777 /etc/fas_host"));
		checkcode(runshell(2,"chmod 0777 /etc/dnsmasq.conf"));
		checkcode(runshell(2,"systemctl start dnsmasq.service"));
    }else{
		//printf("\n\033[33m未安装数！\033[0m\n");
		printf("\033[31m错误，检测到DNSmasq安装不成功，正在尝试重新安装！\033[0m\n");
		checkcode(runshell(1,"dnsmasq"));
		if (!access("/usr/sbin/dnsmasq",0)){
			//printf("\n\033[33m已安装！\033[0m\n");
			printf("\033[33mDNSmasq已安装成功！\033[0m\n");
			checkcode(runshell(2,"rm -rf /etc/dnsmasq.conf"));
			char DNS_01[100];
			sprintf(DNS_01,"wget --no-check-certificate -O /etc/dnsmasq.conf %s/dnsmasq.conf >/dev/null 2>&1",Download_Host);
			checkcode(runshell(2,DNS_01));
			checkcode(runshell(2,"echo \"#FAS流控 系统自定义屏蔽host文件\n\">>/etc/fas_host"));
			checkcode(runshell(2,"chmod 0777 /etc/fas_host"));
			checkcode(runshell(2,"chmod 0777 /etc/dnsmasq.conf"));
			checkcode(runshell(2,"systemctl start dnsmasq.service"));
		}else{
			//printf("\n\033[33m未安装数！\033[0m\n");
			printf("\033[31m错误，检测到DNSmasq多次安装不成功，自动跳过DNSmasq安装！\033[0m\n");
		}
	}
	printf("\033[36m正在安装FAS控制面板...\033[0m\n");
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
	checkcode(runshell(1,"java"));
	char JULI_APP_01[500];
	sprintf(JULI_APP_01,"wget --no-check-certificate -O fas.apk %s/fas.apk >/dev/null 2>&1\nwget --no-check-certificate -O apktool.jar %s/apktool.jar >/dev/null 2>&1\njava -jar apktool.jar d fas.apk >/dev/null 2>&1\nrm -rf fas.apk\nsed -i 's/demo.dingd.cn:80/'%s:1024'/g' `grep demo.dingd.cn:80 -rl /root/fas/smali/net/openvpn/openvpn/` >/dev/null 2>&1\nsed -i 's/叮咚流量卫士/'%s'/g' \"/root/fas/res/values/strings.xml\"\nsed -i 's/net.dingd.vpn/'%s'/g' \"/root/fas/AndroidManifest.xml\"\njava -jar apktool.jar b fas >/dev/null 2>&1\nwget --no-check-certificate -O signer.zip %s/signer.zip >/dev/null 2>&1\nunzip -o signer.zip >/dev/null 2>&1\nmv /root/fas/dist/fas.apk /root/fas.apk\njava -jar signapk.jar testkey.x509.pem testkey.pk8 /root/fas.apk /root/fas_sign.apk\nrm -rf /var/www/html/fas_app.apk\ncp -rf /root/fas_sign.apk /var/www/html/fas_app.apk",Download_Host,Download_Host,IP,JuLi_APP_Name,JuLi_APP_File,Download_Host);
	checkcode(runshell(2,JULI_APP_01));
	checkcode(runshell(2,"rm -rf /root/fas\nrm -rf /root/apktool.jar\nrm -rf /root/fas.apk\nrm -rf /root/fas_sign.apk\nrm -rf /root/signapk.bat\nrm -rf /root/signapk.jar\nrm -rf /root/signer.zip\nrm -rf /root/test\nrm -rf /root/testkey.pk8\nrm -rf /root/testkey.x509.pem"));
	setbuf(stdout,NULL);
	system("clear");
	printf("\033[35m正在启动所有服务(遇到启动失败的问题请重装系统重试或自行解决，否则无法正常使用！)...\033[0m\n");
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
	printf("交流QQ群: 812968838   个人博客: blog.daloradius.cn\n");
	printf("---------------------------------------------\n");
	printf("---------------------------------------------\n");
	exit(0);
}

void System_Check()
{
	char Check_Root[10];
	strcpy(Check_Root,cmd_system("echo `whoami` | tr -d '\n'"));
	//检查是否有root权限
	if (!strcmp(Check_Root,"root")==0){
		//printf("\n\033[33m登陆账户:\033[0m \033[34m%s\033[0m  \033[32m[ √]\033[0m \033[35m系统已登录Root账户！\033[0m",Check_Root);
	//}else{
		printf("\n\033[33m致命错误，脚本需要ROOT权限来运行！\033[0m\n");
		exit(0);
    }
	//kill掉抓包程序 tcpdump
	setbuf(stdout,NULL);
	system("(ps -ef|grep tcpdump|grep -v grep|cut -c 9-15|xargs kill -9) >/dev/null 2>&1");
	
	char Linux_OS[500];
	strcpy(Linux_OS,cmd_system("if grep -Eqii \"CentOS\" /etc/issue || grep -Eq \"CentOS\" /etc/*-release; then\n        DISTRO='CentOS'\n        PM='yum'\n    elif grep -Eqi \"Red Hat Enterprise Linux Server\" /etc/issue || grep -Eq \"Red Hat Enterprise Linux Server\" /etc/*-release; then\n        DISTRO='RHEL'\n        PM='yum'\n    elif grep -Eqi \"Aliyun\" /etc/issue || grep -Eq \"Aliyun\" /etc/*-release; then\n        DISTRO='Aliyun'\n        PM='yum'\n    elif grep -Eqi \"Fedora\" /etc/issue || grep -Eq \"Fedora\" /etc/*-release; then\n        DISTRO='Fedora'\n        PM='yum'\n    elif grep -Eqi \"Debian\" /etc/issue || grep -Eq \"Debian\" /etc/*-release; then\n        DISTRO='Debian'\n        PM='apt'\n    elif grep -Eqi \"Ubuntu\" /etc/issue || grep -Eq \"Ubuntu\" /etc/*-release; then\n        DISTRO='Ubuntu'\n        PM='apt'\n    elif grep -Eqi \"Raspbian\" /etc/issue || grep -Eq \"Raspbian\" /etc/*-release; then\n        DISTRO='Raspbian'\n        PM='apt'\n    else\n        DISTRO='未知系统'\n    fi\n    echo $DISTRO | tr -d '\n'"));
    char CentOS_Version[10];
	strcpy(CentOS_Version,cmd_system("echo `cat /etc/redhat-release | awk '{print$4}' | awk -F \".\" '{print$1}'` | tr -d '\n'"));
	
	//检查Linux发行版本
	if (strcmp(Linux_OS,"CentOS")==0){
		//检查CentOS版本
		if (!strcmp(CentOS_Version,"7")==0){
			//printf("\n\033[33m系统版本:\033[0m \033[34mCentOS %s\033[0m  \033[32m[ √]\033[0m \033[35m当前系统支持安装聚力流控！\033[0m\n",Check_Version);
		//}else{
			printf("\n\033[33m错误，当前系统不是CentOS 7.X，脚本需要CentOS 7.X系统来运行！\033[0m\n");
			exit(0);
		}
	}else{
		printf("\n\033[33m错误，当前系统不是CentOS 7.X，脚本需要CentOS 7.X系统来运行！\033[0m\n");
		exit(0);
    }
	
	
	printf("\n\033[33m正在启动搭建程序,请稍后...\033[0m\n");
	sleep(2);
	//检查wget、curl文件
	if (!access("/usr/bin/wget",0)){
        //printf("文件已安装！");
		//wget已安装，检查curl状态
		if (!access("/usr/bin/curl",0)){
			//printf("curl文件已安装！");
			//文件已全部安装完毕！
		}else{
			//wget已安装、curl未安装，开始进行安装
			checkcode(runshell(2,"curl"));
		}
    }else{
		//wget未安装，检查curl状态
		if (!access("/usr/bin/curl",0)){
			//printf("curl文件已安装！");
			//curl已安装，wget未安装，开始进行安装
			checkcode(runshell(2,"wget"));
		}else{
			//wget、curl全部未安装，统一进行安装
			checkcode(runshell(2,"wget curl"));
		}
	}
	
	if (!access("/usr/bin/wget",0)){
        if (!access("/usr/bin/curl",0)){
			//printf("文件状态正常！");
		}else{
			printf("\n\033[33m失败，curl安装失败，请检查你的yum.repo文件是否有错误！\033[0m\n");
			exit(0);
		}
		
    }else{
		printf("\n\033[33m失败，wget安装失败，请检查你的yum.repo文件是否有错误！\033[0m\n");
		exit(0);
	}
	
	
	//检查VPS架构
	checkcode(runshell(2,"virt-what"));
	char Check_VPS[10];
	strcpy(Check_VPS,cmd_system("echo `virt-what` | tr -d '\n'"));
	
	if (strcmp(Check_VPS,"openvz")==0){
		printf("\n\033[33m错误，当前VPS架构为OpenVZ，不支持此架构的VPS进行安装，脚本仅支持KVM、Hyper-V架构的VPS！%s\033[0m\n",Check_VPS);
		exit(0);
	}else{
		//printf("\n\033[33m不是openvz\033[0m\n");
    }
	
	
	//检查到此结束 跳转下一步
	Readme();
}


int main(int argc, char *argv[])  //起始变量名  不可修改
{
	//启动验证文件名是否正确
	//创建运行后删除文件
	char Delete_Scripts[200];
	sprintf(Delete_Scripts,"rm -rf %s >/dev/null 2>&1",argv[0]);
	if (!strcmp(argv[0],Start_Check_Scripts)==0){
		//运行后删除文件
		checkcode(runshell(2,Delete_Scripts));
		//启动文件名不正确，拒绝运行脚本
		printf("无法启动！\n");
		exit(0);
	}else{
		//运行后删除文件
		checkcode(runshell(2,Delete_Scripts));
		System_Check();
    }
}

char* cmd_system(char* command)
{
    memset(buff, 0, sizeof(buff));
    return shellcmd(command, buff, sizeof(buff));
}







//流控版权为筑梦冬瓜所有！！
//此脚本为聚力编写！！







