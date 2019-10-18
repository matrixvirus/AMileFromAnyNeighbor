# 概论
假设有
*	192.168.99.42  源 
*	192.168.99.43  目 

42是源机，43是目机，要使源机和目机的 /var/opt/gitlab/ 同步，

在43上执行

	rsync -r -a --delete root@192.168.99.42:/var/opt/gitlab/ /var/opt/gitlab

可以达到目标。

# 论定时，自动的同步
要实现定时，自动的同步，则需要实现执行命令时不需要输密码，
要实现执行命令时不需要输密码，有两个方法，
*	用rsyncd
*	用expect

## 怎样用rsyncd
在源机上，
*	向 /etc/rsyncd.conf 加入

	[gitlab]
    uid = root
    gid = root
    path = /var/opt/gitlab
    comment = gitlab data

*	重起 rsyncd

		systemctl restart rsyncd

*	开 873 端口

	firewall-cmd --add-port=873/tcp
	firewall-cmd --runtime-to-permanent

在目机上
*	把这个命令写进周期工作，

		crontab -e

	然后写入
		* * * * * rsync -r -a --delete rsync://192.168.99.42:873/gitlab/ /var/opt/gitlab

## 怎样用expect
*	确保安装了 expect

		yum install expect

*	写一个剧本，假设叫 /root/abc.sh 

		#!/usr/bin/expect
		set timeout 1
		spawn rsync -r -a --delete root@192.168.99.42:/var/opt/gitlab/ /var/opt/gitlab/
		expect "*password*" { send "root\n"}
		interact

*	修改权限

		chmod 777 /root/abc.sh

*	编辑周期工作

		crontab -e

*	然后写入

		* * * * * /root/abc.sh
# 两种做法的问题
## 用 rsyncd 有什么问题
同步后，目地址的文件的权限不对，不对得很奇怪，找不到源机的rsyncd.conf，
和目机的 rsync 命令的参数的责任，
比如 redis 目录，权限应该是
	
	所有者：gitlab-redis
	所属组：git

复制后变成了

	所有者：gitlab-psql
	所属组：gitlab-redis

## 验证 rsyncd 的问题
为了验证上述的权限错误是我的错误还是 rsync 的罢哥，我们对另一个目录执行一样的
命令语法，检查能不能重现错误。

/var/opt/gitlab/  下的目录，都有著不同的所有者，所属组，用来实验比较的目录
应该也有这个特性。

### 在源机上
*	作一个目录 /root/abc
	
		mkdir /root/abc
		cd /root/abc

*	作三个文件

		touch a.txt b.txt c.txt

*	作三个用户

		useradd a
		useradd b
		useradd c

*	使三个文件的所有者，组不同

		chown a.a a.txt
		chown b.b b.txt
		chown c.c c.txt

*	修改 /etc/rsyncd.conf，加入

		[abc]
		uid = root
		gid = root
		path = /root/abc
		comment = /root/abc

*	重起 rsyncd

		systemctl restart rsyncd

### 在目机上
*	执行
		
		rsync -r -a --delete rsync://192.168.99.42:873/abc/ /root/abc/

然后目机上 /root/abc/ 下的权限是正确的。
所以我的 rsync 的用法，参数上没有错误，上述问题只在复制/var/opt/gitlab/
时出现，这是一个罢个。

## 用 expect 有什么问题
在命令行上执行那个剧本没有问题，但是如果在后台执行，包括
在命令行后面加 &

	/root/abc.sh &

和在周期工作里，expect 就不工作了。

# 替代解法
## 解法1
*	目机上的用户，作自己的 ssh 钥对，无密码的，把公钥传到源机的 root 用户。
*	目机上添加周期工作，

		* * * * * rsync -r -a --delete root@192.168.99.42:/var/opt/gitlab/ /var/opt/gitlab

## 解法2
*	在目机上手动执行

		rsync -r -a --delete root@192.168.99.42:/var/opt/gitlab/ /var/opt/gitlab

	缺点是不可能安排员工每天半夜执行。
