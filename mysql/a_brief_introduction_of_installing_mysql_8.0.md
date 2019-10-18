<center>a brief introduction of installing mysql 8.0</center>

## installation
prepare the yum repo,edit /etc/yum.repos.d/mysql.repo

	[mysql80-community]
	name=MySQL 8.0 Community Server
	baseurl=http://repo.mysql.com/yum/mysql-8.0-community/el/7/$basearch/
	enabled=1
	gpgcheck=0

install

	yum install mysql-community*

start

	systemctl start mysqld

## initial password
refer to /var/log/mysqld.log,there will be one line like this

	A temporary password is generated for root@localhost: 7q+-;al,Ipaf

the random string at the right side is the initial password for user 
root@localhost,use this to login to mysql,yours will be different with mine,

	mysql -uroot -p7q+-;al,Ipaf

then reset your password to replace the random one

	set password for 'root'@'localhost' = 'youpassword';

you may wonder,does not the correct syntax is

	set password for 'root'@'localhost' = password('yourpassword');

? the *password()* function was removed in MySQL 8.0.11.

you can also use *alter*
	
	alter user 'root'@'localhost' identified by 'yourpassword';

## about password complexity
when setting password,you may crash this error

	ERROR 1819 (HY000): Your password does not satisfy the current policy requirements

this is because a plugin,

	show variables like 'default_authentication_plugin';

to check the policy used by the plugin *caching_sha2_password*

	show variables like 'validate_password.policy';

this variable has three alternable value
	
*	0 or low
*	1 or medium
*	2 or high

the default is *medium*.

*low* indicates only checking length.

in order to completely bypass the restriction,you need to modify two 
variable,

	set global validate_password.policy = low;
	set global validate_password.length = 1;

but this is theory,in fact i still cant reach the goal that using
arbitrary string as password.

a direct method is to turn off the password plugin,
edit /etc/my.cnf

	[mysqld]
	validate-password = off

then restart mysqld

	systemctl restart mysqld

the mysql 8.0 document teaches me this argument,but in fact,*mysqld* has no 
such argument.

oh my fuck.

## old mysql clients on other hosts connecting to mysql 8.0
when you from other hosts using old client tring to connect to mysql 8.0,
you may crash this error

	ERROR 2059 (HY000): Authentication plugin 'caching_sha2_password' cannot be loaded: /usr/lib64/mysql/plugin/caching_sha2_password.so: cannot open shared object file: No such file or directory

there are two methods for solving this problem,server yields to client or
client yields to server.

### server yields to client
you need to change *default_authentication_plugin* to mysql_native_password,
this variable cant be modified on flying,
you need to edit /etc/my.cnf

	[mysqld]
	default-authentication-plugin = mysql_native_password

restart mysqld

	systemctl restart mysqld

login to mysql,create the user for remote logining,if the user already exists,
you need to drop it,create it.

### client yields to server
unfortunately,in the official yum repo of each system,there is not always a 
rpm who provides *caching_sha2_password.so*
,in openSUSE 15.1,it is *libmariadb_plugins*,in centos 7,there is no.
so the only solution is to use mysql 8.0 client as well.
