<?php


/**
 * the receiver resource
 * @uri /{receiver}
 */

class ReceiverResource extends Resource {

	function get($request, $receiver) {

		$response = new Response($request);
		$response->addHeader('content-type', 'application/json');

		$result = mysql_query("
		SELECT name, lastUpdate, pointCount FROM vReceiver where name = '".$receiver."' LIMIT 0, 1
		");


		if ($result && mysql_num_rows($result) > 0)
		{
			$row = mysql_fetch_array($result, MYSQL_ASSOC);

			/* building the json response */
			$myReceiverResponse = (object) array (
			'receiver' => (object) array (
				'name' => $row['name'],
				'lastUpdate' => $row['lastUpdate'],
				'pointCount' => (int)$row['pointCount']
				)
			);

			$response->code = Response::OK;
		}
		else {
			$myReceiverResponse = (object) array ();
			$response->code = Response::NOTFOUND;
		}




		$response->body = json_encode($myReceiverResponse);
		return $response;

	}

}


?>
