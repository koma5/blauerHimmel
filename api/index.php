<?php

include 'lib/db.class.php';



$data = $_REQUEST['data'];
//echo "raw: ".$data."<br>";
$obj = json_decode($data);
//echo $obj->name;

foreach ($obj->point as $point)
{
	echo "lat: " . $point->lat . " long: " . $point->long . "<br>";

}



//long;lat;speed


?>
