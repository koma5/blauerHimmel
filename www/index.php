<?php 
include 'lib/db.class.php';
$myDB = new Database();
$myDB->connect();

$result = mysql_query("
SELECT poiLatidude, poiLongitude, poiTimestampUTC FROM `tPoint` WHERE fk_pk_tReceiver_ID = 2
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
  <script type="text/javascript">

     function initialize() {
        var myOptions = {
          center: new google.maps.LatLng(42.3717,10.92602),
          zoom: 12,
          mapTypeId: google.maps.MapTypeId.ROADMAP
        };

	var map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);

	var myLatLng =
	[
<?php                                                                                                        

while ($i = mysql_fetch_array($result))
{ 
        $myString .= "new google.maps.LatLng(".$i['poiLatidude'].",".$i['poiLongitude']."), ";
}

$myString = substr($myString, 0, strlen($myString)-1);
echo $myString;

?>	];
	var myTrack = new google.maps.Polyline({
	    path: myLatLng,
	    strokeColor: "#FFFFFF",
	    strokeOpacity: .5,
	    strokeWeight: 2
	});

	myTrack.setMap(map);

      }
   </script>
  </head>

  <body onload="initialize()">
	<!--<h1>blauerhimmel.</h1>
 	<img src="http://maps.googleapis.com/maps/api/staticmap?center=42.3717,10.92602&zoom=11&size=200x200&sensor=false">-->


	<div id="map_canvas" style="width:100%; height:100%"></div>
  </body>

</html>
