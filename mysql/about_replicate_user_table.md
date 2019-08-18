# how to replicate 'mysql' database,'user' table to another host

	mysqldump --flush-privileges mysql > abc.sql
	mysql < abc.sql
