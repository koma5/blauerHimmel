<?php
header('Content-type: application/json');

//db setup
include 'lib/db.class.php';
$myDB = new Database();
$myDB->connect();


//get data and decode
//$data = $_REQUEST['data'];
		$handle = fopen('php://input','r');
		$jsonInput = fgets($handle);
		$data = json_decode($jsonInput,true);

$dataObj = json_decode('﻿{"name": "drerscht","apikey": "4cdqfTqhL4SswTTeA4sOL4SswTTeA4sO","point": [{"lat": "4707.4282","long": "00853.7112","speed": "0","time": "212225","date": "250112"}]}');
//#dev 
echo $data;
//#dev 
var_dump($dataObj);
//#dev echo "data recieved from: " . $dataObj->name . "[" . $dataObj->apikey . "]<br>";


// auth
$result = mysql_query("
SELECT COUNT(*) FROM `tReceiver`
WHERE recName = '".$dataObj->name."' AND
recApiKey = '".$dataObj->apikey."'
");
if ($result) $recCount = mysql_result($result, 0);
if ($recCount == 1) $auth = 1;
else
{
	$auth = 0;
	$error = 2;
}


switch ($error) {
    case 1:
        echo '{"error":["code":"1","name":"data saved ... everything OK"]}';
        break;
    case 0:
        echo '{"error":["code":"0","name":"some error"]}';
        break;
    case 2:
        echo '{"error":["code":"2","name":"authentication failed! go away!"]}';
        break;
    case 3:
        echo '{"error":["code":"3","name":"no data received"]}';
        break;
}

/*
	foreach ($dataObj->point as $point)
	{
		echo "lat: " . $point->lat
		. " long: " . $point->long
		. " speed: " . $point->speed
		. "<br>";
	}


*/




?>
