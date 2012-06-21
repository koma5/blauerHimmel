<?php
require 'Slim/Slim.php';
require_once 'lib/db.class.php';

$app = new Slim();

$app->contentType('application/json');

$myDB = new Database();
$myDB->connect();

$app->get('/', function () {

	$result = mysql_query("
	SELECT `name`,
	`lastUpdate`,
	`pointCount`
	FROM `vReceiver`
	");

	
        if ($result && mysql_num_rows($result) > 0)
        {
	
	// building the response-json object
        $myReceiverArrayResponse = array();

	while($row = mysql_fetch_array($result,MYSQL_ASSOC))		
                {
			// building the single receiver object
                	$myReceiverObject = (object) array (
                	'receiver' => (object) array (
                	        'name' => $row['name'],
                	        'lastUpdate' => $row['lastUpdate'],
                	        'pointCount' => (int)$row['pointCount']
               	         	)
                	);

                	array_push($myReceiverArrayResponse, $myReceiverObject);  
		}
		print json_encode($myReceiverArrayResponse);
        }
        else
        {
                print "error... ;)";
        }





});



$app->get('/:receiver', function($receiver) {

	$result = mysql_query("
	SELECT name,
	lastUpdate,
	pointCount
	FROM vReceiver
	WHERE name = '".$receiver."'
	LIMIT 0, 1
	");

	if ($result && mysql_num_rows($result) > 0)
	{
		$row = mysql_fetch_array($result, MYSQL_ASSOC);

		// building the json response
		$myReceiverResponse = (object) array (
		'receiver' => (object) array (
			'name' => $row['name'],
			'lastUpdate' => $row['lastUpdate'],
			'pointCount' => (int)$row['pointCount']
			)
		);

		print json_encode($myReceiverResponse);
	}
	else
	{
		print "error... ;)";
	}



});


$app->get('/:receiver/points', function($receiver) {

	$result = mysql_query("
		SELECT name, latidude, longitude, speed, timestampUtc
		FROM `vPoint`
		WHERE name = '".$receiver."'
	"); $row = NULL;

	if ($result && mysql_num_rows($result) > 0)
	{
		$myReceiverPointsResponse = (object) array(
		'receiver' => (object) array(
			'name' => $receiver,
			'points' => array()
			)
		);

		while($row = mysql_fetch_array($result, MYSQL_NUM))
		{

			$myPoint = (object) array(
				'lat' => (float)$row[1],
				'long' => (float)$row[2],
				'speed' => (int)$row[3],
				'date' => $row[4]
			);

			array_push($myReceiverPointsResponse->receiver->points, $myPoint);
		}

		print json_encode($myReceiverPointsResponse);

	}

	else {
		print "error... ;)";
	}


});




$app->run();
?>
