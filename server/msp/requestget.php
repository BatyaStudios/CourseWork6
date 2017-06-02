<?php
	$conn = new mysqli('localhost', 'board', 'keyword', 'msp');
	
	if ($conn->connect_error) {
		die('Error:0.');
	}	 
	
	$data = $conn->query("select id, request from request where statusid=0 limit 1;");

	if ($data) {
		$row = $data->fetch_assoc();
		
		if($row) {
			echo "\r\n".$row["id"].' '.$row["request"]."\r\n";
		} else {
			echo "\r\n0 null\r\n";
		}
	} else {
		echo 'Error:1.';
	}
	$conn->close();
?>