Drop Database if exists blauerHimmel;
Create Database blauerHimmel;
use blauerHimmel;

CREATE TABLE point 
(
	id INT unsigned NOT NULL auto_increment,
	latidude FLOAT NOT NULL,
	longitude FLOAT NOT NULL,
	speed FLOAT NOT NULL,
	timestampUtc TIMESTAMP NOT NULL DEFAULT '0000-00-00 00:00:00',
	receiver_id INT unsigned NOT NULL,
	Primary Key (id),
	Index (id)
);

CREATE TABLE log
(
	id int unsigned NOT NULL auto_increment,
	action VARCHAR(50) NOT NULL,
	postedPoints INT unsigned NULL,
	ip VARCHAR(40) NOT NULL,
	time TIMESTAMP NOT NULL DEFAULT now(),
	receiver_id INT unsigned NOT NULL,
	Primary Key (id),
	Index (id)
);

CREATE TABLE receiver
(
	id int unsigned NOT NULL auto_increment,
	name VARCHAR(50) NOT NULL,
	apiKey VARCHAR(32) NOT NULL,
	Primary Key (id),
	Index (id)
);






# VIEWS

DROP VIEW IF EXISTS vReceiver;
CREATE VIEW vReceiver
AS
	SELECT * FROM receiver AS r
	INNER JOIN
		(
			SELECT receiver_id, COUNT(*) AS pointCount
			FROM point
			GROUP BY receiver_id
		) AS p ON p.receiver_id = r.id




	INNER JOIN
		(
			SELECT receiver_id, MAX(time) AS lastUpdate
			FROM log
			WHERE action = 'post'
			GROUP BY action, receiver_id
		) AS l ON l.receiver_id = r.id;





DROP VIEW IF EXISTS vReceiver;
CREATE VIEW vReceiver
AS
SELECT 	receiver.name
		COUNT(p.id) AS pointCount,
		MAX(l.time) AS lastUpdate
	FROM receiver AS r
	INNER JOIN point AS p
	ON p.receiver_id = r.id
	INNER JOIN log AS l
	ON l.receiver_id = r.id
	GROUP BY p.receiver_id

# failed auth logs  and no data won't have a receiver_id, so the logs with a receiver_id are an update











