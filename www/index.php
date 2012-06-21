<!DOCTYPE html>
<html>
  <head>
  
  <meta charset="utf-8">
  <title>blauerhimmel.</title>
  <meta name="viewport" content="initial-scale=1.0, user-scalable=no" />
  <link rel="stylesheet" type="text/css" href="style.css">
  <script src="http://code.jquery.com/jquery-latest.js"></script>
  <style type="text/css">
 	
	html { height: 100% }
 	body { font-family:sans-serif; height: 100%; margin: 0; padding: 0 }
  	#map_canvas { height: 100% }
 
	#hover_menu
	{
		position: absolute;
		width:300px;
		right:25px;
		bottom:50px;
		background-color:green;
		
		  -moz-box-shadow:    0 4px 20px 1px #000;
 		  -webkit-box-shadow: 0 4px 20px 1px #000;
  		  box-shadow:         0 4px 20px 1px #000;


		-moz-border-radius: 20px;
		-webkit-border-radius: 20px;
		-khtml-border-radius: 20px;
    		border-radius: 20px;
	}

	#hover_menu ul li
	{
		list-style-type:none;
		height:25px;
	}
  </style>
  
  <script type="text/javascript" src = "http://maps.googleapis.com/maps/api/js?key=AIzaSyDZ2Idc-C45Q2_YEox0lfIpIA5Fv3kE0s8&sensor=false">
  </script>
  
  <script type="text/javascript" src="main.js">
  </script>

  </head>

  <body>
	<!--<h1>blauerhimmel.</h1>
 	<img src="http://maps.googleapis.com/maps/api/staticmap?center=42.3717,10.92602&zoom=11&size=200x200&sensor=false">-->


	
<div id="map_canvas" style="width:100%; height:100%"></div>
<div id="hover_menu">
	<ul>
	</ul>
</div>


  </body>

</html>
