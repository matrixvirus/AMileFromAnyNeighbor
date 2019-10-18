
login the host where the gitlab resides on.

## information for connecting to postgresql
open /opt/gitlab/etc/gitlab-psql-rc,
	
	psql_user='gitlab-psql'
	psql_group='gitlab-psql'
	psql_host='/var/opt/gitlab/postgresql'
	psql_port='5432'
	psql_dbname='gitlabhq_production'

from the first line,

	psql_user='gitlab-psql'

you know the user gitlab uses to connect to postgresql is gitlab-psql.

from 

	psql_host='/var/opt/gitlab/postgresql'

this is the data position of postgresql.

from 

	psql_dbname='gitlabhq_production'

this is the database gitlab uses.

## connecting to postgresql
su to gitlab-psql

	su - gitlab-psql

execute

	psql -h /var/opt/gitlab/postgresql -d gitlabhq_production

now you are in the postgresql,the prompt becomes

	gitlabhq_production=#

for a pretty query result showing,enter this

	\x auto

## query what you want
for example,

	select name from routes where name like '%/%';

this will give you a list of what projects each group has.

## how to export data
this command,

	\o /tmp/abc.txt;

means exporting all quering result to file /tmp/abc.txt,
then you execute

	select name from routes where name like '%/%';

this time you will not see any output,the output is redirected to /tmp/abc.txt
.

## exit postgresql
execute this to exit

	\q
