<?php
  $db = new PDO('sqlite:harte-tomate.sqlite3');
  $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
?>