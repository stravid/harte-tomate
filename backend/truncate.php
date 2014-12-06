<?php
	require_once('database.php');

  $db->exec('DELETE FROM pomodori');
	$db->exec('VACUUM');
?>