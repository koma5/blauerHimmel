<?php
header('Content-type: application/json');

$response = (object) array(
	'name' => 'toeffli',
	'apikey' => 'slow',
	'point' => array()
);

$xml = simplexml_load_file('2012-06-27-siebnen-vorderthal.gpx');

$points = $xml->trk->trkseg->trkpt;

foreach ($points as $p) {

	$attributes = $p->attributes();

	$date = preg_replace(array('/T/', '/Z/'), array(' ',''), $p->time);

	$myPoint = (object) array(
		'lat' => (float) $attributes->lat,
		'long' => (float) $attributes->lon,
		'speed' => 0,
		'att' => (float) $p->ele,
		'date' => (string) $date
	);

	array_push($response->point, $myPoint);

}

echo json_encode($response);


?>