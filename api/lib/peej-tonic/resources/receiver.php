<?php


/**
 * the receiver resource
 * @uri /{receiver}
 */

class ReceiverResource extends Resource {

	function get($request, $receiver) {

		$myReceiverResponse = (object) array (
		'receiver' => (object) array (
			'name' => $receiver,
			'lastupdate' => '2012-02-15 18:15:50',
			'count' => 518
			)
		);

		$response = new Response($request);
		$response->code = Response::OK;
		$response->addHeader('content-type', 'application/json');
		$response->body = json_encode($myReceiverResponse);
		return $response;

	}

}


?>
