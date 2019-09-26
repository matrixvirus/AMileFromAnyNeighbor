# learning cgroups

# where to find cgroups document
if you are not familier with cgroup conception,special nouns,you d better
read these documents first.

## the kernel document
install

	yum install kernel-doc

go to

	/usr/share/doc/kernel-doc-3.10.0/Documentation/cgroups

the first file you need to read is *cgroups.txt* .
your kernel version may be different.

## the redhat document
redhat has a document called *resource-management-guide.pdf*,


# how to use cgroups
you need to install *cgroups* forst

	yum install libcgroup libcgroup-tools

here we use an example,to explain how to limit the cpu usage of a process.

## example one direct method
### create a new group

	cd /sys/fs/cgroup/cpu
	mkdir pluto

you have create a new group *pluto*.

### set cpu attributes

	cd pluto
	echo 100000 > cpu.cfs_period_us
	echo 1000 > cpu.cfs_quota_us

i dont know exactly the meaning of these attributes,i just know that,with these
two attributes,the process will assume cpu percentage up to 1% .

### create a python script for test
edit abc.py

	#!/usr/bin/python
	a = 1
	while True:
		print(a)
		a += 1

### test
at terminal window one,run top.
at terminal window two,run the abc.py,
and you will see a process jump up the top cpu usage rank in a second,
remember his pid.
write this pid to *tasks*
	
	cd /sys/fs/cgroup/cpu/pluto	
	echo *pid* >> tasks

then switch to the *top* windows,you will see the process has calmed down.



## example two using command
### create a new group

	cgcreate -g cpu:pluto

this command is same as

	mkdir /sys/fs/cgroup/cpu/pluto

for *cpu:pluto*,*cpu* means the *cpu*dir in */sys/fs/cgroup/*,
*pluto* means make a new dir *pluto* in */sys/fs/cgroup/cpu*.

### set cpu attributes
	
	cgset -r cpu.cfs_period_us=100000 pluto
	cgset -r cpu.cfs_quota_us=1000 pluto

they are same as

	echo 100000 > /sys/fs/cgroup/cpu/pluto/cpu.cfs_period_us
	echo 1000 > /sys/fs/cgroup/cpu/pluto/cpu.cfs_quota_us

### test
run the abc.py in example one,remember its *pid*,then

	cgclassify -g cpu:pluto PID

it is same as

	echo PID >> /sys/fs/cgroup/cpu/pluto/tasks

## example three limit memory usage
### create a new group
create a new group under *memory* subsystem

	cgcreate -g memory:neptune

you can also let the new group stays under both *cpu* and *memory* subsystems
,

	cgcreate -g cpu,memory:neptune

### set memory attributes

	cgset -r memory:limit_in_bytes=10 neptune

### add a process to this group
find a process, for example *firefox*,

	cgclassify -g memory:neptune *pid_of_firefox*

suddenly when your switch the firefox windows,you find that it has
disappeared, because it exceesed the memory limit.

##  operations introduction
### create a new group
*	method one
create a group in subsystem cpu and mem,
	
		mkdir /sys/fs/cgroup/cpu/pluto
		mkdir /sys/fs/cgroup/mem/pluto

*	method two
use comma to seperate subsystems,
	
		cgcreate -g cpu,mem:pluto

### set attributes
* 	method one
		
		echo 100000 > /sys/fs/cgroup/cpu/pluto/cpu.cfs_period_us
		echo 1000 > /sys/fs/cgroup/cpu/pluto/cpu.cfs_quota_us

*	method two
	
		cgset -r cpu.cfs_period_us=100000 pluto
		cgset -r cpu.cfs_quota_us=1000 pluto

### check attributes
*	method one

		cat /sys/fs/cgroup/cpu/pluto/cpu.cfs_period_us

*	method two

		cgget -r cpu.cfs_period_us pluto

### move processes to a group
*	method one
		
		echo PID1 >> /sys/fs/cgroup/cpu/pluto/tasks
		echo PID2 >> /sys/fs/cgroup/cpu/pluto/tasks

*	method two

		cgclassify -g cpu:pluto PID1 PID2

* 	method three
add a process to a group when it starts. for example,start *bash* in *pluto*
group,

	cgexec -g cpu:pluto /bin/bash

*Notice*,this method one not recommanded,because *cgclassify* is more
intelligent,for example,when using *cgclassify*,it will 
*	automatically reomove the specified PID from other groups.
*	when the process exits,it automatically remove its pids from the group
*	and so on

### check whether a process has joined to a group
if a process has joined to a group,for example cpu:pluto,two files can
indicate its joining
*	/sys/fs/cgroup/cpu/pluto/tasks
	
	its PID will be in it.

*	/proc/PID/cgroup

	there will be a line:

		10:cpuacct,cpu:/pluto

### remove a process from a group
i cant find a guide for this.

### delete a group
*	method one
	
		rm -rf /sys/fs/cgroup/cpu/pluto

*	method two

		cgdelete -g cpu:pluto

## attributes introduction
i have not found a document about this.

# configuration files
## /etc/cgrules.conf


## /etc/cgconfig.conf


# systemd with cgroups	
this chapter is can be skipped.*systemd* is not a part of cgroups,redhat 
combines *systemd* with *cgroups* in redhat 7.

*systemd* moves the resource management settings from the process level to the
application level by binding the system of cgroup hierarchies with the systemd
 unit tree. Therefore, you can manage system resources with systemctl 
commands, or by modifying systemd unit files. 

From the systemd s perspective, a cgroup is bound to a system unit 
configurable with a unit file and manageable with systemd s command-line 
utilities. your resource management settings can be transient or persistent.

you can see redhat document *resource_management_guide.pdf*.

## create new group
### create transient group
honestly,i dont know the meaning of this existing.
skip.

### create persistent group
skip.

## delete group
skip.

## modify group
### use command
syntax:

	systemctl set-property name parameter=value

example:

	systemctl set-property httpd.service CPUShares=600 MemoryLimit=500M

then,you will find you two file 50-CPUshares.conf,50-MemoryLimit.conf in
/etc/systemd/system/httpd.service.d/ .


The changes are applied instantly, and written into the unit file, so that they 
are preserved after reboot.  You can change this behavior by passing the 
--runtime option, that makes your settings transient:

	systemctl set-property --runtime name property=value

### edit unit files
the files 50-CPUshares.conf,50-MemoryLimit.conf,you can also create them
manually,the filename can be any, but you need to run two command mannualy,

	systemctl daemon-reload
	systemctl restart httpd.service

## parameters
### CPU
*	CPUShares 	

	example:CPUShares=1500

*	CPUQuota	

	example:CPUQuota=20%

### memory
*	MemoryLimit

	example:MemoryLimit=1G

