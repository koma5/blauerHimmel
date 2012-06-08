<?php 
include 'lib/db.class.php';
$myDB = new Database();
$myDB->connect();

$result = mysql_query("
SELECT Latidude, Longitude, timestampUtc FROM `Point` WHERE receiver_id = 2
");//echo mysql_errno($link) . ": " . mysql_error($link) . "\n";

?>

<!DOCTYPE html>
<html>
  <head>
  
  <meta charset="utf-8">
  <title>blauerhimmel.</title>
  <meta name="viewport" content="initial-scale=1.0, user-scalable=no" />
  <link rel="stylesheet" type="text/css" href="style.css">

  <style type="text/css">
      html { height: 100% }
      body { height: 100%; margin: 0; padding: 0 }
      #map_canvas { height: 100% }
  </style>
  
  <script type="text/javascript" src = "http://maps.googleapis.com/maps/api/js?key=AIzaSyDZ2Idc-C45Q2_YEox0lfIpIA5Fv3kE0s8&sensor=false">
  </script>
  
  <script type="text/javascript" src="main.js">
  </script>

  </head>

  <body onload="initialize()">
	<!--<h1>blauerhimmel.</h1>
 	<img src="http://maps.googleapis.com/maps/api/staticmap?center=42.3717,10.92602&zoom=11&size=200x200&sensor=false">-->


	<div id="map_canvas" style="width:100%; height:100%"></div>
  </body>

</html>
