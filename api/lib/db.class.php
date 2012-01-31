<?php
class Database
{


	public function __construct() {
		include 'db.class.config.php';
	}


	public function connect() {

		if (!isset($this->db_handler)) {
			$this->db_handler = mysql_connect($this->db_server, $this->db_user, $this->db_password) or die ("connect to db failed!");
			mysql_select_db($this->db_name, $this->db_handler) or die ("select of db failed!");
			//echo "db conected: " . $this->db_server . "</br>";
		}

	}


	public function quit() {

		if (isset($this->db_handler)) {
			mysql_close($this->db_handler);
			$this->db_handler = NULL;
			//echo "db disconnected: " . $this->db_server;
		}

	}


	public function __destruct() {
	$this->quit();

	}
}
?>
