<?php
  require_once('database.php');
  require_once('pomodoro.php');

  $rows = $db->query('SELECT * FROM pomodori ORDER BY started_at DESC');
  $pomodori = array();

  foreach($rows as $data) {
    $pomodori[] = new Pomodoro($data);
  }

  $db = null;

  $days = array();
  $last_pomodoro = $pomodori[count($pomodori) - 1];
  $end_date = mktime(0, 0, 0, date('n', $last_pomodoro->started_at), date('j', $last_pomodoro->started_at), date('Y', $last_pomodoro->started_at));
  $current_date = time();

  do {
    $days[strftime('%Y-%m-%d', $current_date)] = array(
      'date' => $current_date,
      'pomodori' => array()
    );

    $current_date -= 24 * 60 * 60;
  } while($current_date > $end_date);


  foreach ($pomodori as $pomodoro) {
    $key = strftime('%Y-%m-%d', $pomodoro->started_at);
    $days[$key]['pomodori'][] = $pomodoro;
  }
?>

<pre>
<?php
  foreach ($days as $day) {
    echo strftime('%a, %d. %B %Y', $day['date']) . "\n";
    echo "======================\n";

    foreach ($day['pomodori'] as $pomodoro) {
      echo strftime('%H:%M', $pomodoro->started_at);
      echo " - ";

      if ($pomodoro->is_running()) {
        echo "RUNNING";
      } else {
        echo strftime('%H:%M', $pomodoro->finished_at());

        if ($pomodoro->is_aborted()) {
          echo " # ABORTED";
        }
      }

      echo "\n";
    }

    echo "\n\n";
  }
?>
</pre>