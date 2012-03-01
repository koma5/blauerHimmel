<?php
require_once 'lib/peej-tonic/tonic.php';
require_once 'lib/resources/point.php';
require_once 'lib/resources/receiver.php';



$request = new Request(array(
	'baseUri' => '/blauerHimmel/api'
));
$resource = $request->loadResource();
$response = $resource->exec($request);
$response->output();



?>
