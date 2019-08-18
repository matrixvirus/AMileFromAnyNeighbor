# how to delete mysql binlog
the binlogs of mysql cant be deleted by directly rm,if you do it,you will get
an error on you error.log of mysql on the next time you start you mysqld 
process, one of the binlogs cant be found,and the mysqld wont start.

*	see binlog

		show master logs
		show binary logs

*	delete all the binlog

		reset master

*	delete all log before mysql-bin.000009

		purge master logs to 'mysql-bin.000009'

*	delete all log before '2019-02-02'

		purge master logs before '2019-02-02'


