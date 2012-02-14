Drop Database if exists blauerHimmel;
Create Database blauerHimmel;
use blauerHimmel;

CREATE TABLE tPoint 
(
	pk_tPoint_ID INT unsigned NOT NULL auto_increment,
	poiLatidude FLOAT NOT NULL,
	poiLongitude FLOAT NOT NULL,
	poiSpeed FLOAT NOT NULL,
	poiTimestampUTC TIMESTAMP NOT NULL DEFAULT '0000-00-00 00:00:00',
	fk_pk_tReceiver_ID INT unsigned NOT NULL,
	Primary Key (pk_tPoint_ID),
	Index (pk_tPoint_ID)
);

CREATE TABLE tLog
(
	pk_tLog_ID int unsigned NOT NULL auto_increment,
	logAction VARCHAR(50) NOT NULL,
	logPointCount INT unsigned NULL,
	logIp VARCHAR(40) NOT NULL,
	logTime TIMESTAMP NOT NULL DEFAULT now(),
	fk_pk_tReceiver_ID INT unsigned NOT NULL,
	Primary Key (pk_tLog_ID),
	Index (pk_tLog_ID)
);

CREATE TABLE tReceiver
(
	pk_tReceiver_ID int unsigned NOT NULL auto_increment,
	recName VARCHAR(50) NOT NULL,
	recApiKey VARCHAR(32) NOT NULL,
	Primary Key (pk_tReceiver_ID)
);