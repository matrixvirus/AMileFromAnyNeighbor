# Learning Kibana
# Getting Started
## Downloading
[current version](https://artifacts.elastic.co/downloads/kibana/kibana-7.3.2-linux-x86_64.tar.gz).
If this link does not work,go to [here](https://www.elastic.co/start).
after downloading,extract it.

make sure that:
*	the owner of the files is not root
*	the starter is not root

then enter the extracted dir,

*	edit config/kibana.yml,find where *server.host* is,its default value is
	*localhost*,which will refuse remote visit,you need to change it to

		server.host: '0.0.0.0'

*	start Kibana

		bin/kibana serve &

*	open firewall

	Kibana uses port 5601.
	*	for firewalld

			firwall-cmd --add-port=5601/tcp
			firwall-cmd --runtime-to-permanent

	*	for iptables

			iptables -t filter -I INPUT 1 -p tcp --dport 5601 -j ACCEPT

*	from any host,use a browser to visit http://kibana-server:5601

## Document
[kibana](https://www.elastic.co/guide/en/kibana/current/index.html)

	

