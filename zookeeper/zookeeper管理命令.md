# zookeeper 管理命令

# 这里假设你已经安装了一台
运行zookeeper的机器，我们以the-server代指它的IP, 可以直接连。
你需要已经安装了telnet。

连接zookeeper，
2181是zookeeper的埠口。

    telnet the-server 2181

# 连接后，下面是你可以执行的命令。

## conf
输出zookeeper服务端参数配置.    

## cons
列出所有连接到服务端的客户端的连接的详细信兮。

## crst
重置所有连接的连接统计。

## dump
列出所有外部session和短命node。    

## envi
列出服务端系统环境信兮。

## ruok
检查服务端是否在 无报错的运行。如果是，该命令返回imok,否则不回应。

## srst
重置服务端统计信兮。    

## srvr
list full details for the server.    

## stat
list brief details for the server and connected clients.

## wchs
list brief information on watches for the server.

## wchc
list detailed information on watches for the server，按session.

## dirs
显示snapshot和log文件的总大小，单位字节。

## wchp
list detailed information on watches for the server，按path。

## mntr
显示一些变量，与群集健康相关。
