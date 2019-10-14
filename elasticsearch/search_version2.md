# About Elasticsearch Search

# 
## Here is a map of nouns of Elasticsearch and relational database,

| Elasticsearch | relational database |
| -     |  -       |
| index(noun) | database |
| type  | table    |
| document | row   |
| field | column |
| index(verb) | insert |

A *document* belongs to a *type*,a *type* belongs to an *index*.

## RESTful syntax
One syntax form:

	curl -X<VERB> -H 'Content-Type:application/json' \
	'<PROTOCOL>://<HOST>/<PATH>?<QUERY_STRING>' -d '<BODY>'

Example:
		
	curl -X PUT -H 'Content-Type:application/json' \
	'http://localhost/abc/bcd?pretty' -d '
	{
		"a":1
	}'

dont mind what this example mean.

What they mean:
*	VERB
	
	HTTP method:GET,POST,PUT,HEAD,DELETE

*	PROTOCOL

	http OR https

*	HOST

	you know.

*	PORT

	default is 9200.

*	QUERY_STRING

	Its form is

		/index/type/id?argu

	I dont know.

*	BODY

	a JSON body.

In fact,dont believe its syntax is only this,this is an example.

# Index
Index some data.

	curl -X POST -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee?pretty' -d '
	{
		"first_name":"John",
		"last_name":"Smith",
		"age":25,
		"about":"I love to go rock climbing",
		"interests":["sports","music"]
	}'
	curl -X POST -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee?pretty' -d '
	{
		"first_name":"What",
		"last_name":"Are",
		"age":26,
		"about":"I love to go rock climbing after death",
		"interests":["math","physic"]
	}'
	curl -X POST -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee?pretty' -d '
	{
		"first_name":"Go",
		"last_name":"Home",
		"age":27,
		"about":"are you fucking kidding me",
		"interests":["eat","drink"]
	}'

'megacorp' is the index,'employee' is the type.
there is no *ID* in the tail,so Elasticsearch will assign it a random ID.

# Search
## Search all

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/_search?pretty' -d '
	{    
	    "query":
			{"match_all":{}}
	}'

Because *megacorp* has only one type *employee*,this has same effect as above,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"match_all":{}
		}
	}'

For checking all, you can  omit *-d*.

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee/_search?pretty'

You can omit *employee*,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/_search?pretty' -d '
	{
		"query":{
			"match":{
				"_id":"VWr8pG0BfuiFs1IjBhcI"
			}
		}
	}'

You can omit *megacorp* and *employee*,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/_search?pretty'

This is the rule,
*	/_search
	Search all types in all indices
*	/gb/_search
	Search all types in the gb index
*	/gb,us/_search
	Search all types in the gb and us indices
*	/g*,u*/_search
	Search all types in any indices beginning with g or beginning with u
*	/gb/user/_search
	Search type user in the gb index
*	/gb,us/user,tweet/_search
	Search types user and tweet in the gb and us indices
*	/_all/user,tweet/_search
	Search types user and tweet in all indices
## Search specified document
Whose ID is "VWr8pG0BfuiFs1IjBhcI",

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"match":{
				"_id":"VWr8pG0BfuiFs1IjBhcI"
			}
		}
	}'

Whose first name,a string, contains 'What',

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"match":{"first_name":"What"}
		}
	}'

Whose first name is 'What',

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"match_phrase":{"first_name":"What"}
		}
	}'

## Range
Whoes age is less then 27,use *range* to replace *match*,

	curl -X GET -H 'Content-Type:application/json' \
	'http://localhost:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"range":{"age":{"lt":27}}
	    }
 	}'

## Combine
Whose age is 26,first name is 'What',

	curl -X GET -H 'Content-Type:application/json' \
	'http://192.168.122.204:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"bool":{
				"must":[
					{"match":{"age":26}},
					{"match":{"first_name":"What"}}
				]
			}
		}
	}'

Whose age is not 27,first name is 'What',

	curl -X GET -H 'Content-Type:application/json' \
	'http://192.168.122.204:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"bool":{
				"must":{"match":{"first_name":"What"}},
				"must_not":{"match":{"age":27}}
			}
		}
	}'

Whose (age is 27) or (first name is 'What' and last name is 'Are'),

	curl -X GET -H 'Content-Type:application/json' \
	'http://192.168.122.204:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"bool":{
				"should":[
					{"match":{"age":27}},
					{"bool":{
						"must":[
							{"match":{"first_name":"What"}},
							{"match":{"last_name":"Are"}}
						]
						}
					}
				]
			}
		}
	}'

Summary:
*bool* syntax has three words:
*	must

	items in it must all be matched.

*	must_not

	items in it must all not be matched.

*	should

	items in it must be matched at least once,like 'or'.

## Match multiple value
Whose age is 26 or 27

	curl -X GET -H 'Content-Type:application/json' \
	'http://192.168.122.204:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"terms":{"age":[26,27]}
		}
	}'

Whose first name is 'Go' or 'What',

	curl -X GET -H 'Content-Type:application/json' \
	'http://192.168.122.204:9200/megacorp/employee/_search?pretty' -d '
	{
		"query":{
			"terms":{"first_name":["What","Go"]}
		}
	}'

But,this does not work,because *terms* does not work with string type,to 
solve this,refer to book *Definitive Guide* -> Chapter 12 -> finding exact
values -> term filter with text.




## Sort


