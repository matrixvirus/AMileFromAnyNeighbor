# About Elasticsearch Search
> I consult the online document to write this,but I think I should abandon
  it,because that online document is a little chaos,I decide to consult the 
  book *Elasticsearch The Definitve Guide* to write a new version.

Elasticsearch sorts search results by *relevance score*,it is a positive 
floating point number,returned in the *score* meta-field of the search api.

# Boolean query
A query that matches documents matching boolean combinations of other queries
.
The clauses are:
*	*must*

	The clause must appear in matching documents, and will contribute to the 
	score.

*	*filter*

	The clause must appear in matching documents,but the score is ignored.

*	*should*

	The clause shoud appear in the matching document.

	I dont know what this mean,2019-10-05.
*	*must_not*

	The clause must not appear in the matching documents.

## Example

## Scoring with bool.filter
Queries specified under *filter* element have no effect on scoring,scores are
returned as 0.
For instance,all three of the following queries return all documents,where the 
*state* field contains the term *IL*.

*	Assign score 0 to all documents,

		curl -X GET -H 'Content-Type:application/json' \
		'http://localhost:9200/bank/_search?pretty' -d '
		{
			"query":{
				"bool":{
					"filter":{
						"term":{
							"state":"IL"
						}
					}
				}
			}
		}'

*	This *bool* query has a *match_all* query,which assigns score 1.0 to all 
	documents.

		curl -X GET -H 'Content-Type:application/json' \
		'http://localhost:9200/bank/_search?pretty' -d '
		{
			"query":{
				"bool":{
					"must":{
						"match_all":{}
					},
					"filter":{
						"term":{
							"state":"IL"
						}
					}
				}
			}
		}'

*	*constant_score* query behaves in the same way the second example above.

		curl -X GET -H 'Content-Type:application/json' \
		'http://localhost:9200/bank/_search?pretty' -d '
		{
			"query":{
				"constant_score":{
					"filter":{
						"term":{
							"status":"active"
						}
					}
				}
			}
		}'
