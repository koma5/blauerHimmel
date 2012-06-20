<?php


/**
 * the point resource per receiver
 * @uri /{receiver}/points 1
 */

class PointResource extends Resource {

	function get($request, $receiver) {

		$response = new Response($request);
		$response->addHeader('content-type', 'application/json');
		
		$result = mysql_query("
		SELECT name, latidude, longitude, speed, timestampUtc FROM `vPoint` WHERE name = '".$receiver."'
		"); $row = NULL;

		if ($result && mysql_num_rows($result) > 0)
		{
			$myReceiverPointsResponse = (object) array(
			'receiver' => (object) array(
				'name' => $receiver,
				'points' => array()
				)
			);

		while($row = mysql_fetch_array($result, MYSQL_NUM))
		{

				$myPoint = (object) array(
					'lat' => (float)$row[1],
					'long' => (float)$row[2],
					'speed' => (int)$row[3],
					'date' => $row[4]
				);

				array_push($myReceiverPointsResponse->receiver->points, $myPoint);
		}

			$response->code = Response::OK;
		}

		else {
			$myReceiverPointsResponse = (object) array ();
			$response->code = Response::NOTFOUND;
		}

		$response->body = json_encode($myReceiverPointsResponse);
		return $response;

	}

}


?>