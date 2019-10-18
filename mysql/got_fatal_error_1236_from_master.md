# An error of replica with gtid

我假设你已经设置了主从，但是又报错，当在从上执行show slave status，看到

	Slave_IO_Running: No

	Last_IO_Error: Got fatal error 1236 from master when reading data from binary log: 'The slave is connecting using CHANGE MASTER TO MASTER_AUTO_POSITION = 1, but the master has purged binary logs containing GTIDs that the slave requires.'

# 解法
在slave上执行
	
	stop slave;
	flush tables with read lock;

在master上执行show master status 有

	Master_UUID:eaa75cc0-3324-11e8-ab06-52540037a828:1-4557466

在slave上执行show slave status 有

	Executed_Gtkd_Set: c16f9528-90f8-11e9-8c06-525400f878d0:1-13

在slave上执行，要用上面两个值

	set global GTID_PURGED = 'eaa75cc0-3324-11e8-ab06-52540037a828:1-4557466,c16f9528-90f8-11e9-8c06-525400f878d0:1-13'
	start slave;
	unlock tables;
	show slave status;	

