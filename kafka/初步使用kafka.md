# 标题：初步使用kafka

假设你已经设置好了一个包含三台机器的群集，IP是

	192.168.99.30
	192.168.99.32
	192.168.99.34

所有操作都假设在解压后的kafka目录kafka_2.12-2.2.0下，这是目前的最新版。

# 操作topic
## 查看有哪些topic
通过zookeeper查

	bin/kafka-topics.sh --list --zookeeper 192.168.99.30:2181
	bin/kafka-topics.sh --list --zookeeper 192.168.99.32:2181
	bin/kafka-topics.sh --list --zookeeper 192.168.99.34:2181

通过kafka的broker节点查

	bin/kafka-topics.sh --list --bootstrap-server 192.168.99.30:9092
	bin/kafka-topics.sh --list --bootstrap-server 192.168.99.32:9092
	bin/kafka-topics.sh --list --bootstrap-server 192.168.99.34:9092

后面我将在代码例子里省略192.168.99.32,192.168.99.34。

## 作成topic

	bin/kafka-topics.sh --create --bootstrap-server localhost:9092 \
		--replication-factor 1 --partitions 1 --topic test
或

	bin/kafka-topics.sh --create --zookeeper localhost:2181 \
		--replication-factor 1 --partitions 1 --topic test

## 删除topic

	bin/kafka-topics.sh --delete --bootstrap-server localhost:9092 \
		--topic test

或

	bin/kafka-topics.sh --delete --zookeeper localhost:2181 \
		--topic test

## 查看某个topic的详细

	bin/kafka-topics.sh --describe --zookeeper localhost:2181 \
		--topic test

查看所有topic的详细

	bin/kafka-topics.sh --describe --zookeeper localhost:2181

## 修改topic



# 发信兮

	bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test

然后输入信兮，输完按Ctrl + D。
localhost可以改成群集中的任意一台。

收信兮

	bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 \
		--topic test --from-beginning

