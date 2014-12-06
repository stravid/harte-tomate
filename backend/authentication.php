<?php
  require_once('environment.php');

  if (!isset($_POST['token']) || $_POST['token'] != TOKEN) {
    header($_SERVER['SERVER_PROTOCOL'] . ' 401 Unauthorized');
    exit;
  }
?>