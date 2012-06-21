<?php

error_reporting(E_ALL);

require_once 'lib/peej-tonic/tonic.php';
require_once 'lib/peej-tonic/resources/point.php';
require_once 'lib/peej-tonic/resources/receiver.php';
require_once 'lib/db.class.php';

$myDB = new Database();
$myDB->connect();

$request = new Request(array(
	'baseUri' => $_SERVER["REQUEST_URI"]
));

try {
	$resource = $request->loadResource();
	$response = $resource->exec($request);
	$response->output();
}
catch (ResponseException $e)
{
	print $e->getMessage();
}


?>