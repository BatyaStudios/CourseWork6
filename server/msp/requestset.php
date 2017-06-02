<?php
	$conn = new mysqli('localhost', 'board', 'keyword', 'msp');
	
	if ($conn->connect_error) {
		die('Error.');
	}	 
	
	
	$qur = $conn->prepare("update request set statusid=?, respond=? where id=?");
						
	$qur->bind_param('isi', $_GET['statusid'], $_GET['respond'], $_GET['id']);
	
	if ($qur->execute()) {
		echo 'Done.';
	} else {
		echo 'Error.';
	}
	$conn->close();
?>