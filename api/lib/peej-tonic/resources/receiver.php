<?php


/**
 * the receiver resource
 * @uri /{receiver}
 */

class ReceiverResource extends Resource {

	function get($request, $receiver) {

		$response = new Response($request);
		$response->code = Response::OK;
		$response->addHeader('content-type', 'text/json');
		$response->body = 
		'{"receiver":{"name":"'.$receiver.'","lastupdate": "2012-02-15 18:15:50","count": 518}}';
		return $response;

	}

}


?>
