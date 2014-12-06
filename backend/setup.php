<?php
	require_once('database.php');

	$db->exec("CREATE TABLE IF NOT EXISTS pomodori (
                    id INTEGER PRIMARY KEY,
                    started_at INTEGER,
                    ended_at INTEGER,
                    aborted_at INTEGER)");
?>