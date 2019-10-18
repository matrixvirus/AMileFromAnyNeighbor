# 用zabbix监测kafka工作端口的连通性

假设你有一台安装好了的zabbix,和kafka，

edit the /etc/hosts on both two boxes,

	IP				hostname
	192.168.99.30	kafka-001
	192.168.99.37	zabbix-server

# install zabbix-agent on kafka box
## install zabbix-agent
on the kafka box,run

	rpm -ivh https://repo.zabbix.com/zabbix/4.2/rhel/7/x86_64/zabbix-release-4.2-1.el7.noarch.rpm
	yum install zabbix-agent

edit /etc/zabbix/zabbix_agentd.conf,change two options,

	Server=zabbix-server
	ServerActive=zabbix-server

the 'zabbix' above is the hostname of the zabbix server.

## add a custome key
on the kafka box,edit /etc/zabbix/zabbix_agentd.d/userparameter_mysql.conf,
add one line,

	UserParameter=pingport[*],curl $1:$2 2>&1 | grep curl

then zabbix agent
	
	systemctl start zabbix-agent

anytime if you edit the definition of the custome key,restart zabbix-agent

	systemctl restart zabbix-agent

# add the kafka box to zabbix server
on you own computer,visit http://zabbix-server/zabbix by browser,
add the kafka box to the hosts list be monitored.

add two item to the kafka box,fill the Key field with

	pingport[localhost,2181]

and select the 'Type of information' as Text, for the first item,
and fill the Key field with

	pingport[localhost,9092]

and select the 'Type of information' as Text,for the second item.

	
