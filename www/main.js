

     function initialize() {
        var myOptions = {
          center: new google.maps.LatLng(42.3717,10.92602),
          zoom: 12,
          mapTypeId: google.maps.MapTypeId.ROADMAP
        };

		var map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);

		var myLatLng =[ new google.maps.LatLng(Latidude,Longitude)];

		var myTrack = new google.maps.Polyline({
		    path: myLatLng,
		    strokeColor: "#FFFFFF",
		    strokeOpacity: .5,
		    strokeWeight: 2
		});

		myTrack.setMap(map);

    }