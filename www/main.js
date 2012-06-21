

function initialize_gmap() {
	
	var myOptions = {
		center: new google.maps.LatLng(42.3717,10.92602),
		zoom: 12,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};

	var map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	
	return map;
}

function setTrack()
{
                var myLatLng =[ new google.maps.LatLng(Latidude,Longitude)];

                var myTrack = new google.maps.Polyline({
                    path: myLatLng,
                    strokeColor: "#FFFFFF",
                    strokeOpacity: .5,
                    strokeWeight: 2
                });

                myTrack.setMap(map);


}


$(document).ready(function () {
	main()
});


function main()
{

	var map = initialize_gmap();
        
	var receiverList = [];

	$.getJSON('http://172.16.0.96/blauerHimmel/api/v1.1/', function(data){

		var items = [];

		jQuery.each(data, function(i, item){
			items.push('<li><a href="#">'+ item.receiver.name +'</a></li>');
		});

		console.log(items.join(''));	
		$('#hover_menu > ul').append(items.join(''));
	
	});
	

}
