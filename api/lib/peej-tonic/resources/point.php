<?php


/**
 * the point resource per receiver
 * @uri /{receiver}/points 1
 */

class PointResource extends Resource {

	function get($request, $receiver) {

		$myReceiverPointsResponse = (object) array(
		'receiver' => (object) array(
			'name' => $receiver,
			'points' => array()
			)
		);

		$myPoint = (object) array(
			'lat' => 4807.4283,
			'long' => 953.7112,
			'speed' => 0,
			'date' => "2012-01-25 21:22:25"
		);

		$i =0;
		while ($i < 3)
		{
			array_push($myReceiverPointsResponse->receiver->points, $myPoint);
			$i++;
		}

		$response = new Response($request);
		$response->code = Response::OK;
		$response->addHeader('content-type', 'text/json');
		$response->body = json_encode($myReceiverPointsResponse);
		return $response;

	}

}


?>