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


	$.getJSON('http://172.16.0.96/blauerHimmel/api/v1.1/' + receiver + '/points', function(data){
		console.log(data);

                var myLatLng =[ ];

	        jQuery.each(data.receiver.points, function(i, point){
                        myLatLng.push( new google.maps.LatLng(point.lat, point.long) );
                });		

                var myTrack = new google.maps.Polyline({
                    path: myLatLng,
                    strokeColor: "#FFFFFF",
                    strokeOpacity: .5,
                    strokeWeight: 2
                });
                
		myTrack.setMap(map);
	});

}


$(document).ready(function () {
	main()
});

function setMenu()
{
       $.getJSON('http://172.16.0.96/blauerHimmel/api/v1.1/', function(data){

                var items = [];

                jQuery.each(data, function(i, item){
                        items.push('<li><a href="#">'+ item.receiver.name +'</a></li>');
                });

                //console.log(items.join(''));
                $('#hover_menu > ul').append(items.join(''));

        });
}


function main()
{

	var map = initialize_gmap();
	setMenu();
	setTrack('concordia');
}
