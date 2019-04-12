# how to configure wifi on linux
all the operating was tested on openSUSE 15.0.

## 1. a tutorial for command line
this chapter will teach you how to connect to a WPA protected wifi
step by step.

### 1.1 see what wifi adaptor you have
> you can you two command to see what wifi adaptor you have,

    iw dev

> or

    iwconfig

> assuming the adptor on you computer is wlan0.

### 1.2 see wifi adaptor status

    ip link show wlan0

or

    iwconfig wlan0

or

    iw wlan0 link

### 1.3 bring up wifi adaptor
bring up

    ip link set wlan0 up

then check the status by now using commands described at 1.2.

and this is opposite operation

    ip link set wlan0 down

### 1.4 scan the wifi around you

    iw wlan0 scan

or

    iwlist wlan0 scanning

selectf one,assuming its name is 'abc',password is '123'.

### 1.5 generate a wpa/wpa2 configuration file

    wpa_passphrase abc 123 > /etc/wpa_supplicant.conf

where 'abc' is the name of the wifi,'123' is the password.

### 1.6 connect to the wifi

    wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.configure

where -B means 'run in background'

check the status now,

    iwconfig wlan0

but the adaptor wlan0 still has no ip address,

    ip addr show dev wlan0

### 1.7 get ip address
first try dhcp

    dhclient wlan0

if the dhclient command has problem,set the ip and route by hand,  
assuming you know the ip range of the wifi,for example,assuming your  
phone has connected to the same wifi,and the ip of your phone is  
192.168.122.34.  
then you can try to set you wlan0 to 192.168.122.35,

    ip addr add 192.168.122.35/24 dev wlan0
    ip route add default via 192.168.122.1 dev wlan0

and add this line to your /etc/resolv.configure

    nameserver 114.114.114.114

you can use any DNS server available.

## a tutorial for using configuration file
> Notice,I tested these operations on openSUSE 15.0.

enter /etc/sysconfig/network/

    cd /etc/sysconfig/network

copy the file ifcfg.template to ifcfg-wlan0

    cp ifcfg.template ifcfg-wlan0

find and edit these lines,

    STARTMODE='manual'
    WIRELESS='yes'
    WIRELESS_MODE='managed'
    WIRELESS_ESSID='abc'
    WIRELESS_AUTH_MODE='psk'
    WIRELESS_WPA_PSK='123'
