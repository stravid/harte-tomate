<?php
  require_once('authentication.php');
  require_once('database.php');
  require_once('pomodoro.php');

  $valid_events = array('ended', 'aborted');

  if (!in_array($_POST['event'], $valid_events)) {
    header($_SERVER['SERVER_PROTOCOL'] . ' 400 Bad Request');
    exit;
  }

  $query = $db->prepare('SELECT * FROM pomodori WHERE id = ?');
  $query->execute(array($id));
  $pomodoro = new Pomodoro($query->fetch());

  if (!$pomodoro->is_running()) {
    header($_SERVER['SERVER_PROTOCOL'] . ' 409 Conflict');
    exit;
  }

	if ($_POST['event'] == 'ended') {
    $query = $db->prepare('UPDATE pomodori SET ended_at = ? WHERE id = ?');
  } else {
    $query = $db->prepare('UPDATE pomodori SET aborted_at = ? WHERE id = ?');
  }

  $query->execute(array(time(), $id));
  $db = null;
?>