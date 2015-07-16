<?php
  require_once('database.php');
  require_once('pomodoro.php');

  $rows = $db->query('SELECT * FROM pomodori ORDER BY started_at DESC');

  echo json_encode(array('pomodori' => $rows->fetchAll(PDO::FETCH_ASSOC)));
