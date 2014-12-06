<?php
  require_once('authentication.php');
  require_once('database.php');

	$query = $db->prepare('INSERT INTO pomodori (started_at) VALUES (?)');
	$query->execute(array(time()));
  $result = array('id' => $db->lastInsertId());
  $db = null;

	echo json_encode($result);
?>