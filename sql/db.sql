Drop Database if exists blauer_himmel;
Create Database blauer_himmel;
use blauer_himmel;

CREATE TABLE tPoint 
(
pk_tPoint_ID INT unsigned not null auto_increment,
poiLongitude float NOT NULL,
poiLatidude float NOT NULL,
poiSpeed float NOT NULL,
poiTimestamp_utc timestamp NOT NULL,
fk_pk_tReceiver_ID INT unsigned NOT NULL,
Primary Key (pk_tPoint_ID),
Index (pk_tPoint_ID)
);



CREATE TABLE tReceiver
(
pk_tReceiver_ID int unsigned NOT NULL auto_increment,
recName VARCHAR(50) NOT NULL,
recApi_key VARCHAR(32) NOT NULL,
Primary Key (pk_tReceiver_ID)
);
