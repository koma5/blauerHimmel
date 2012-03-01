<?php


/**
 * An example resource
 * @uri /point
 */

class ExampleResource extends Resource {

	function get($request) {

		$response = new Response($request);
		$response->code = Response::OK;
		$response->addHeader('content-type', 'text/plain');
		$response->body = 'This is only an example';
		return $response;

	}

}


?>
