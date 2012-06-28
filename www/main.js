function initialize_gmap() {
	
	var myOptions = {
		center: new google.maps.LatLng(42.3717,10.92602),
		zoom: 12,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};

	map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	
	return map;
}

function setTrack(receiver)
{


	$.getJSON(url + receiver + '/points', function(data){
		console.log(data);

        var myLatLng =[ ];

        jQuery.each(data.receiver.points, function(i, point){
            myLatLng.push( new google.maps.LatLng(point.lat, point.long) );
        });		


    	if(typeof myTrack != 'undefined')
    	{
    		myTrack.setPath(myLatLng);
    	}

    	else
    	{
			myTrack = new google.maps.Polyline({
				path: myLatLng,
				strokeColor: "#3DB366",
				strokeOpacity: .5,
				strokeWeight: 3
			});
			myTrack.setMap(map);
    	}

		//set active class on menu item
		$('#hover_menu > ul > li').each( function(li){
			
			if ( $(this).attr('id') != 'menu-' + data.receiver.name )
			{

				$(this).removeClass('menu-active');
			}
			else
			{
				$(this).addClass('menu-active');
			}
		});

	});



}


$(document).ready(function () {
	main()
});

function setMenu()
{
       $.getJSON(url, function(data){

                var items = [];

                jQuery.each(data.receiver, function(i, receiver){

                        items.push('\
                        <li id="menu-' + receiver.name + '" onClick="setTrack(\''+receiver.name+'\')">\
                        	<a>'+ receiver.name + ' ' + shortenNummber(receiver.pointCount, 1) + ' points</a>\
                        </li>');

                });

                $('#hover_menu > ul').append(items.join(''));

        });
}


function shortenNummber(number, decPlaces)
{
	// 2 decimal places => 100, 3 => 1000, etc
	decPlaces = Math.pow(10,decPlaces);

	// Enumerate number abbreviations
	var abbrev = [ "k", "m", "b", "t" ];

	// Go through the array backwards, so we do the largest first
	for (var i=abbrev.length-1; i>=0; i--) {

		// Convert array index to "1000", "1000000", etc
		var size = Math.pow(10,(i+1)*3);

		// If the number is bigger or equal do the abbreviation
		if(size <= number) {
			// Here, we multiply by decPlaces, round, and then divide by decPlaces.
			// This gives us nice rounding to a particular decimal place.
			number = Math.round(number*decPlaces/size)/decPlaces;

			// Add the letter for the abbreviation
			number += abbrev[i];

			// We are done... stop
			break;
		}
	}


	return number;

}


function main()
{
	url = 'http://api.blauerHimmel.5th.ch/v1/';
	initialize_gmap();
	setMenu();
	//setTrack('concordia');
}
