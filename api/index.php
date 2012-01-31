<?php

include 'lib/db.class.php';

$myDB = new Database();
$myDB->connect();

$data = $_REQUEST['data'];
$dataObj = json_decode($data);

//echo "data recieved from: " . $dataObj->name . "[" . $dataObj->apikey . "]<br>";

$result = mysql_query("
SELECT COUNT(*) FROM `tReceiver`
WHERE recName = '".$dataObj->name."' AND
recApiKey = '".$dataObj->apikey."'
");

if ($result)$recCount = mysql_result($result, 0);
else $recCount = 0;
//echo "count: ".$recCount;

if ($recCount == 1)
{
	foreach ($dataObj->point as $point)
	{
		/*echo "lat: " . $point->lat
		. " long: " . $point->long
		. " speed: " . $point->speed
		. "<br>";*/
	}
}
else {
	echo "authentication failed...";
}







?>
