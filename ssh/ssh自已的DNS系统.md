 
# ssh的自已的DNS系统

## 最简单的设置

编辑 ~/.ssh/config,加入内容 

    Host abc
    User root
    HostName 192.168.99.20

执行命令

    ssh abc

则会登录 192.168.99.20

## 更多参数
~/.ssh/config 里可以设置其它参数，比如Port

    Host abc
    User root
    HostName 192.168.99.20
    Port 22

比如私钥

    Host abc
    User root
    HostName 192.168.99.20
    IdentityFile ~/.ssh/id_rsa

/etc/ssh/ssh_config 里的参数这里都能用。

## 设置多条记录

    Host tx-come56-001
        User pengyh
        HostName 193.112.135.27
        CheckHostIP yes
        ConnectTimeout 0
        IdentityFile ~/.ssh/online_ops
        Port 22
    Host abc
        User root
        HostName 192.168.99.20
        Port 22

每一个Host字段代表一个机器，为了易读，建议每个 Host字段其后的字段缩进一层。




