# how to setup a shadowsocks server 
on a linux box,

# install python version
## install 
install pip

	yum install python2-pip python3-pip 

using pip to install shadowsocks

	pip install shadowsocks

## config
create /etc/shadowsocks.json

	{
		"server": "0.0.0.0",
		"server_port": 8338,
		"local_port": 1080,
		"password": "940423",
		"timeout": 600,
		"method": "aes-256-cfb"
	}

## start

	ssserver -c /etc/shadowsocks.json &

# install shadowsocks-libev,rpm version
the above is one method about the python implementation of shadowsocks,
you can also install the original version. for the original version,you can
use rpm or source method.
## install
if you use opensuse,you can install it directly

	zypper install shadowsocks-libev

## config
there is a little difference with python version,it has config file from 
itselft,you need not to create one.
edit /etc/shadowsocks/shadowsocks-libev-config.json
	{
		"server": "0.0.0.0",
		"server_port": 8338,
		"local_port": 1080,
		"password": "940423",
		"timeout": 600,
		"method": "aes-256-cfb"
	}



## start
there is a little difference with python version

# install shadowsocks-libev	,source version
wait for me.
