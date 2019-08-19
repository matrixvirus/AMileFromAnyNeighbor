# 安装kafka

这里讲的是有三台机器的群集的设置。
假设三台机器的ip分别为  
> 192.168.99.30  
> 192.168.99.32  
> 192.168.99.34  

# 下载
略。  
假设下载后的文件解压后的目录是kafka_2.12-2.2.0，这是本文作成时的最新版。  
kafka自带了zookeeper。  
三台机器上每台都要下载。

# 改设置文件
进入解压后的目录kafka_2.12-2.2.0。  
## 改zookeeper设置文件
### 改config/zookeeper.properties，
加

	server.1=192.168.99.30:2888:3888
	server.2=192.168.99.32:2888:3888
	server.3=192.168.99.34:2888:3888
	initLimit = 5
	syncLimit = 2

这一步在三台机器上是一样的。
其中2888是用于zookeeper节点间通信的端口，  
3888是用于zookeeper节点间首领选举的端口。
### myid文件
zookeeper.properties里有一行，

	dataDir=/tmp/zookeeper

在/tmp/zookeeper下作一个文件叫myid，内容只有一个数字，192.168.99.30的写1，
192.168.99.32的写2，192.168.99.34的写3，与

	server.1=192.168.99.30:2888:3888
    server.2=192.168.99.32:2888:3888
    server.3=192.168.99.34:2888:3888

的顺序保持一致。
## 改kafka设置文件
改config/server.properties，

### zookeeper.connect那一行
改为

    zookeeper.connect=192.168.99.30:2181,192.168.99.32:2181,192.168.99.34:2181

IP加2181端口，逗号分隔。  
这一步在三台机器上是一样的。
	
### broker.id那一行
192.168.99.30的设为1，32的设为2，34的设为3，
与

    server.1=192.168.99.30:2888:3888
    server.2=192.168.99.32:2888:3888
    server.3=192.168.99.34:2888:3888

的顺序保持一致。

# 起动
起动zookeeper

	bin/zookeeper-server-start.sh config/zookeeper.properties &	

起动kafka

	bin/kafka-server-start.sh config/server.properties &
