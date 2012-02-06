<?php
header('Content-type: application/json');

//db setup
include 'lib/db.class.php';
$myDB = new Database();
$myDB->connect();

//initialize error code
$error = 1; //everything OK

//get data and decode
if (isset($_REQUEST['data']))$data = $_REQUEST['data'];
else $error = 0; //if there's no data

if ($error != 0)
{

	$dataObj = json_decode(prepareJSON($data));
	/*$handle = fopen('php://input','r');
	$jsonInput = fgets($handle);
	$data = json_decode($jsonInput,true);*/
	//#dev json_last_error();
	//#dev echo $data;
	//#dev var_dump($dataObj);
	//#dev echo "data recieved from: " . $dataObj->name . "[" . $dataObj->apikey . "]<br>";


	// auth ######## do it with selecting the ID you will need it at the insert ;)
	$result = mysql_query("
	SELECT pk_tReceiver_ID FROM `tReceiver`
	WHERE recName = '".$dataObj->name."' AND
	recApiKey = '".$dataObj->apikey."'
	");
	if ($result) $recID = mysql_result($result, 0);
	echo $recID;
	if ($recID >0 ) $auth = 1;
	else
	{
		$auth = 0;
		$error = 2;
	}
	
				


	if($auth != 0)
	{
		foreach ($dataObj->point as $point)
		{
			$dtime =  preg_replace('/(.{2})(.{2})(.{2})(.{2})(.{2})(.{2})/', '20$3-$2-$1 $4:$5:$6',$point->date.$point->time);

			$inputQuery = "
			INSERT INTO `blauerHimmel`.`tPoint` (`poiLatidude`, `poiLongitude`, `poiSpeed`, `poiTimestampUTC`, `fk_pk_tReceiver_ID`)
			VALUES (
			'".$point->lat."',
			'".$point->long."',
			'".$point->speed."',
			'".$dtime."',
			'".$recID."'
			);";
			mysql_query($inputQuery);
			echo $inputQuery;
		}


	}


}

switch ($error) {
    case 1:
        echo '{"error":{"code":"1","name":"data saved ... everything OK"}}';
        break;
    case 0:
        echo '{"error":{"code":"0","name":"no data received"}}';
        break;
    case 2:
        echo '{"error":{"code":"2","name":"authentication failed! go away!"}}';
        break;
    case 3:
        echo '{"error":{"code":"3","name":""}}';
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


function prepareJSON($input) {
    
    //This will convert ASCII/ISO-8859-1 to UTF-8.
    //Be careful with the third parameter (encoding detect list), because
    //if set wrong, some input encodings will get garbled (including UTF-8!)
    $input = mb_convert_encoding($input, 'UTF-8', 'ASCII,UTF-8,ISO-8859-1');
    
    //Remove UTF-8 BOM if present, json_decode() does not like it.
    if(substr($input, 0, 3) == pack("CCC", 0xEF, 0xBB, 0xBF)) $input = substr($input, 3);
    
    $input = str_replace("\\", "", $input); // remove escaped -> "
    
    return $input;
}




?>
