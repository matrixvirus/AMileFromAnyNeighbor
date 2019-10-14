# Learning Elasticsearch

# Getting Startted
## Download
[current version download](https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-7.3.2-linux-x86_64.tar.gz)

This link may vary with the growing version,if it does not work,go to [latest installation guide](https://www.elastic.co/guide/en/elasticsearch/reference/current/getting-started-install.html).

### Start
You need to install java first.
after downloading,extract it to use it.
enter the extracted dir,run

	bin/elasticsearch -d

There are some notice:
*	the owner of the dir cant be root
*	you cant start *elasticsearch* as root

### Check
now elasticsearch is running,you can check it

	curl -X GET "localhost:9200/_cat/health?v&pretty"

You can add an argu *-i* to *curl* to see the http header returned

	curl -i -X GET "localhost:9200/_cat/health?v&pretty"

### Stop

	curl -X POST 'http://localhost:9200/_shutdown'

## Document
[document](https://www.elastic.co/guide/en/elasticsearch/reference/current/index.html).
This document has only html format,no pdf is provided.

There is a book *elasticsearch the definitive guide*,an *oreilly* style 
name, i have its pdf format.

I dont recommend you to read the online doc,it is a little chaos.

## Remote access
### Config
By default,Elasticsearch bind to localhost,remote access is denied.
You need to change *network.host* in *elasticsearch.yml*,to *0.0.0.0*.

	network.host: 0.0.0.0
	cluster.initial_master_nodes: ["192.168.122.204"]

where "192.168.122.204" is the outside IP.Currently we are talking about
single node,in fact it should be a list of IP.

### System config
But that is not end,after you change this key,when you start Elasticsearch,
you may get errors:
*	If you meet

		max virtual memory areas vm.max_map_count [65530] is too low, increase to at least [262144]

	do
	*	add this to /etc/sysctl.conf

			vm.max_map_count=262144

		run this to load the new config
	
			sysctl -p

*	If you meet

		max file descriptors [4096] for elasticsearch process is too low, increase to at least [65535]

	do
	*	add these to /etc/security/limits.conf

			username hard nofile 65535

		where *username* is which you use to start Elasticsearch.
		Then you need to relogin *username*,either desktop or terminal.
		You can see the new value

			ulimit -Hn	

*	If you meet

		max number of threads [1854] for user [archimedes] is too low, increase to at least [4096]

	do	
	*	add this to /etc/security/limits.conf

			username hard nproc 4096

		then relogin to the user,either desktop or terminal.

### Firewall
Elasticsearch use port 9200,so you need to open this port,
*	For *firewalld*

		firewall-cmd --add-port=9200
		firewall-cmd --runtime-to-permanent

*	For *iptables*

		iptables -t filter -I INPUT 1 -p tcp --dport 9200 -j ACCEPT

# Use Elasticsearch
Storing data in Elasticsearch is called *indexing*, here *index* is a verb;
a document belongs to a *type*, and those types live inside an *index*,here
*index* is a noun.
*index*(verb) is like *insert*,*index*(noun) is like database,*type* is like
table,*document* is like row in relational database.

And,we call (result) *hit*,(query) *search*.

## Index a document
*	 Index a document

		curl -X PUT "localhost:9200/customer/_doc/1?pretty" \
		-H 'Content-Type: application/json' -d'
		{
		  "name": "John Doe"
		}
		'

	*	-X PUT means using PUT method.
	*	-H means http header.
	*	-d means http data.
	*	*customer* is an index. if it does not exist,the command will create it 
		automatically. 
	*	_doc means the data type is *once*,one document one time.
	*	1 means document id,we will use it in the following query.
	*	*pretty* means a well formatted output

	the output will be

		{	
		  "_index" : "customer",
		  "_type" : "_doc",
		  "_id" : "1",
		  "_version" : 1,
		  "result" : "created",
		  "_shards" : {
			"total" : 2,
			"successful" : 1,
			"failed" : 0
		  },
		  "_seq_no" : 0,
		  "_primary_term" : 1
		}

*	query the new document

		curl -X GET "localhost:9200/customer/_doc/1?pretty"

	output

		{
		  "_index" : "customer",
		  "_type" : "_doc",
		  "_id" : "1",
		  "_version" : 1,
		  "_seq_no" : 0,
		  "_primary_term" : 1,
		  "found" : true,
		  "_source" : {
			"name" : "John Doe"
		  }
		}

## Insert documents in bulk from file
*	write a file abc.json,its content is many different documents,
	for example,

		{"index":{"_id":"1"}}
		{"name":"a"}
		{"index":{"_id":"1"}}
		{"name":"b"}

	it contains two documents,each two lines represent a document,in
		
		{"index":{"_id":"1"}}
		{"name":"a"}

	the first line means,...
	the second line means,...

	Notice,there is only two lines,you cant add new line to make it 
	readable.
	This will make error

		{
			"index":
				{"_id":"1"}
		}
		{
			"name":"a"
		}

	The official provides a [template](https://github.com/elastic/elasticsearch/blob/master/docs/src/test/resources/accounts.json?raw=true),I recommend you to
	use it,because our following examples will base on it.

*	insert from the file

		curl -H "Content-Type: application/json" \
			-X POST "localhost:9200/bank/_bulk?pretty&refresh" \
			--data-binary "@abc.json"

	notice,
	*	refresh means overwriting existing data.
	* 	there is a '@' before 'abc.json'.

*	query

		curl -X GET "localhost:9200/bank/_doc/1?pretty"
		curl -X GET "localhost:9200/bank/_doc/2?pretty"

## Search
### Example 1
This will retrieve all documents in *bank* index,sort by *account_number*,
ascendant.

	curl -X GET "localhost:9200/bank/_search?pretty" \
	-H 'Content-Type: application/json' -d'
	{
	  "query": { "match_all": {} },
	  "sort": [
		{ "account_number": "asc" }
	  ]
	}
	'

I dont paste its output here.
Here is some explanation of the output

*   took – how long it took Elasticsearch to run the query, in milliseconds
*   timed_out – whether or not the search request timed out
*   _shards – how many shards were searched and a breakdown of how many 
	shards succeeded, failed, or were skipped.
*   max_score – the score of the most relevant document found
*   hits.total.value - how many matching documents were found
*   hits.sort - the document’s sort position (when not sorting by relevance 
	score)
*   hits._score - the document’s relevance score (not applicable when using 
	match_all)

### Example 2
Gets hits 10 through 19,use *from* and *size*,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/bank/_search?pretty' -d '
	{
		"query":{"match_all":{}},
		"sort":[{"account_number":"asc"}],
		"from":10,
		"size":10
	}'
		
### Example 3
Search whose address contains 'mill' OR 'lane',

	curl -X GET -H 'Content-Type:application/json' \
		'http://localhost:9200/bank/_search?pretty' -d '
		{
			"query":
				{
					"match":
						{
							"address":"mill lane"
						}
				}
		}'

### Example 4
Search whose address contains 'mill lane',use *match_phrase*,

	curl -X GET -H 'Content-Type:application/json' \
		'http://localhost:9200/bank/_search?pretty' -d '
		{
			"query":
			{
				"match_phrase":
				{
					"address":"mill lane"
				}
			}
		}'

### Example 5
Search whose age is 40,and lives in Idaho,use *bool*,*must*,*must_not*,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/bank/_search?pretty' -d '
	{
		"query":
		{
			"bool":
			{
				"must":
				[
					{
						"match":
						{
							"age":"40"
						}
					}
				],
				"must_not":
				[
					{
						"match":
						{
							"state":"ID"
						}
					}
				]
			}
		}
	}'

### Example 6
Search whose balance is greater or equal than 20000,less or equal than 30000,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/bank/_search' -d '
	{
		"query":
		{
			"bool":
			{
				"must":{"match_all":{}},
				"filter":
				{
					"range":
					{
						"balance":
						{
							"gte":20000,
							"lte":30000
						}
					}
				}
			}
		}
	}'

*gte* is 'greater or equal',
*lte* is 'less or equal',
*gt* is 'greater than',
*lt* is 'less than',
### Example 7
Group all of the accounts in the bank index by state,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/bank/_search?pretty' -d '
	{
		"size":0,
		"aggs":{
			"group_by_state":{
				"terms":{
					"field":"state.keyword"
				}
			}
		}
	}'


### Example 8
Nest an avg aggregation within the group_by_state aggregation to 
calculate the average account balances for each state,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/bank/_search?pretty' -d '
	{
		"size":0,
		"aggs":{
			"group_by_state":{
				"terms":{
					"field":"state.keyword"
				},
				"aggs":{
					"average_balance":{
						"avg":{
							"field":"balance"
						}
					}
				}
			}
		}
	}'

### Example 9
Sort using the result of the nested aggregation by specifying the order within 
the terms aggregation,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/bank/_search?pretty' -d '
	{
		"size":0,
		"aggs":{
			"group_by_state":{
				"terms":{
					"field":"state.keyword",
					"order":{
						"average_balance":"desc"
					}
				},
				"aggs":{
					"average_balance":{
						"avg":{
							"field":"balance"
						}
					}
				}
			}
		}
	}'
				
### See search.md for more
