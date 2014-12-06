<?php
  require_once('alto-router.php');
  require_once('environment.php');

  date_default_timezone_set('Europe/Vienna');

  $router = new AltoRouter();
  $router->setBasePath(BASE_PATH);

  $router->map('OPTIONS', '*', function() {
    header($_SERVER['SERVER_PROTOCOL'] . ' 200 OK');
  });

  $router->map('GET', '/', function() {
    require_once('index.php');
  });

  $router->map('POST', '/pomodori', function() {
    require_once('create.php');
  });

  $router->map('POST', '/pomodori/[i:id]', function($id) {
    require_once('update.php');
  });

  $match = $router->match();

  if($match && is_callable($match['target'])) {
    call_user_func_array($match['target'], $match['params']);
  } else {
    header($_SERVER['SERVER_PROTOCOL'] . ' 404 Not Found');
  }
?>
