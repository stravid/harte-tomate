<?php
  class Pomodoro {
    public $id;
    public $started_at;
    public $ended_at;
    public $aborted_at;

    public function __construct($data) {
      $this->id = $data['id'];
      $this->started_at = $data['started_at'];
      $this->ended_at = $data['ended_at'];
      $this->aborted_at = $data['aborted_at'];
    }

    public function is_running() {
      return $this->ended_at == null && $this->aborted_at == null;
    }

    public function is_aborted() {
      return !$this->is_running() && $this->aborted_at != null;
    }

    public function finished_at() {
      if (!$this->is_running()) {
        if ($this->is_aborted()) {
          // echo "asd1";
          return $this->aborted_at;
        } else {
          // echo "asd";
          return $this->ended_at;
          // echo "asd1";
        }
      } else {
        return null;
      }
    }
  }
?>