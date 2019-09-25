# learning cgroups

# where to find cgroups document
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
# systemd with cgroups	
