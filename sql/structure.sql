Drop Database if exists blauerHimmel;
Create Database blauerHimmel;
use blauerHimmel;

CREATE TABLE point 
(
	id INT unsigned NOT NULL auto_increment,
	latidude FLOAT NOT NULL,
	longitude FLOAT NOT NULL,
	attitude FLOAT NOT NULL,
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
	receiver_id INT unsigned NULL,
	Primary Key (id),
	Index (id)
);

CREATE TABLE receiver
(
	id int unsigned NOT NULL auto_increment,
	name VARCHAR(50) NOT NULL,
	apiKey VARCHAR(32) NOT NULL,
	lastUpdate TIMESTAMP NOT NULL DEFAULT '0000-00-00 00:00:00',
	Primary Key (id),
	Index (id)
);





-- ---
-- Views
-- ---

DROP VIEW IF EXISTS vReceiver;
DROP VIEW IF EXISTS vPoint;

-- ---
-- View 'vReceiver'
-- shows all receivers and pointCount
-- ---

CREATE VIEW vReceiver
AS
SELECT 	r.*,
		COUNT(p.id) AS pointCount
	FROM receiver AS r
	INNER JOIN point AS p
	ON p.receiver_id = r.id
	GROUP BY p.receiver_id;


-- ---
-- View 'vPoint'
-- shows all points of receivers
-- ---
CREATE VIEW vPoint
AS
SELECT 	r.name,
		p.*
	FROM point AS p
	INNER JOIN receiver AS r
	ON p.receiver_id = r.id
	ORDER BY p.timestampUtc ASC






