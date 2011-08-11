<?php
// $Id$

module_load_include('test', 'simpletest_clone');
//http://www.opensourcery.com/blog/jonathan-hedstrom/test-driven-drupal-development-take-2

class ExtendedDrupalWebTestCase extends SimpleTestCloneTestCase {
  protected $admin_user;
  protected $users;
  protected $users_profile;
  protected $users_badges;
  
  /**
   * Create file name
   */
  protected function getOutputFile() {
    $file_dir = file_directory_path() .'./simpletest_output_pages';
    if (!is_dir($file_dir)) {
      mkdir($file_dir, 0777, TRUE);
    }
    return "$file_dir/". $this->randomName(8) .'.html';
  }
  
  
  /**
   * Save page to file
   */
  protected function outputAdminPage($description, $url) {
    $output_path = $this->getOutputFile();
    $this->drupalGet($url);
    $rv = file_put_contents($output_path, $this->drupalGetContent());
    $this->pass("$description: Contents of result page are ". l('here', $output_path));
  }
  
  
  /**
   * Save Screen to file
   */
  protected function outputScreenContents($description) {
    $output_path = $this->getOutputFile();
    $rv = file_put_contents($output_path, $this->drupalGetContent());
    $this->pass("$description: Contents of ". l('result page', $output_path));
  }
  
  
  /**
   * Save variable to file
   */
  protected function outputVariable($description, $variable) {
    $output_path = $this->getOutputFile();
    $rv = file_put_contents($output_path, '<html><body><pre>'.
      print_r($variable, true) .'</pre></body></html>');
    $this->pass("$description: Contents of ". l('variables here', $output_path));
  }
  
  
  /**
   * Run cron.
   */
  protected function cronRun() {
    $this->drupalGet($GLOBALS['base_url'] .'/cron.php', array('external' => TRUE));
  }

  
  /**
   * Click on vote_up/vote_down.
   */
  protected function clickVoteUpDown($vote = 'up') {
    global $base_root;
    if ($vote == 'up') {
      $urls = $this->xpath("//a[div[@class='up-inactive'][@title='Vote up!']]");
    }
    else {
      $urls = $this->xpath("//a[div[@class='down-inactive'][@title='Vote down!']]");
    }
    
    if (!count($urls)) {
      return FALSE;
    }
    $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE,
      CURLOPT_URL => $base_root . $urls[0]['href']));
    return TRUE;
  }
  
  
  /**
   * Click on vote_up/vote_down on multiple buttons.
   * @param $index
   * 				number of the account to which you must press the action.
   * 				Or array('all' => 'up|down') - for all buttons.
   */
  protected function clicksButtonsVoteUpDown($index) {
    global $base_root;
    if (isset($index['all'])) {
      if ($index['all'] == 'up') {
        //Click all 'UP' links
        $urls_up = $this->xpath("//a[div[@class='up-inactive'][@title='Vote up!']]");
        $urls_up = $this->cleanURLs($urls_up);
        if (!count($urls_up)) {
          return FALSE;
        }
        foreach($urls_up as $url) {
          $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE,
            CURLOPT_URL => $base_root . $url));
        }
      }
      else {
        //Click all 'DOWN' links
        $urls_down = $this->xpath("//a[div[@class='down-inactive'][@title='Vote down!']]");
        $urls_down = $this->cleanURLs($urls_down);
        if (!count($urls_down)) {
          return FALSE;
        }
        foreach($urls_down as $url) {
          $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE,
            CURLOPT_URL => $base_root . $url));
        }
      }
    }
    else {
      //Click $index links (mixed 'up' or 'down' links)
      $urls_up = $this->xpath("//a[div[@class='up-inactive'][@title='Vote up!']]");
      $urls_up = $this->cleanURLs($urls_up);
      $urls_down = $this->xpath("//a[div[@class='down-inactive'][@title='Vote down!']]");
      $urls_down = $this->cleanURLs($urls_down);
      
      if (!count($urls_up) || count($urls_up) != count($urls_down)) {
        return FALSE;
      }
      
      foreach($index as $num => $vote) {
        if ($vote == 'up') {
          if (isset($urls_up[$num])) {
            $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE,
              CURLOPT_URL => $base_root . $urls_up[$num]));
          }
        }
        else {
          if (isset($urls_down[$num])) {
            $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE,
              CURLOPT_URL => $base_root . $urls_down[$num]));
          }
        }
      }
    }
    
    //Links if found and clicks
    return TRUE;
  }
  
  
  /**
   * Additional function — extra cleaning options.
   */
  protected function cleanURLs($urls) {
    if (!is_array($urls) || !count($urls)) {
      return FALSE;
    }
    $temp_urls = array();
    $out_urls = array();
    foreach ($urls as $id => $url) {
      if (!isset($temp_urls[(string)$url['href']])) {
        $temp_urls[(string)$url['href']] = TRUE;
        $out_urls[] = $url['href'];
      }
    }
    return $out_urls;
  }
  
  
	/**
   * Click on Add to Favorites.
   */
  protected function clickAddFavorites($nid) {
    global $base_root;
    $urls = $this->xpath("//span[@class='flag-wrapper flag-bookmarks flag-bookmarks-". $nid ."']/a");
    if (!count($urls)) {
      return FALSE;
    }
    
    $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE, CURLOPT_URL => $base_root . $urls[0]['href']));
    return TRUE;
  }
  
  
	/**
   * Click on Best Answer.
   */
  protected function clickBestAnswer($content_id, $type = 'flag-bookmarks') {
    global $base_root;
    if ($type == 'flag-bookmarks') {
      $urls = $this->xpath("//span[@class='flag-wrapper flag-bookmarks flag-bookmarks-". $content_id ."']/a");
    }
    else {
      $urls = $this->xpath("//span[@class='flag-wrapper flag-best-answer flag-best-answer-". $content_id ."']/a");
    }
    
    if (!isset($urls[0]['href'])) {
      return FALSE;
    }
    $urls = (string)$urls[0]['href'];
    $out = $this->curlExec(array(CURLOPT_HTTPGET => TRUE, CURLOPT_URL => $base_root . $urls));
    return TRUE;
  }
  
  
  /**
   * Add $num records to 'flags' table for users in $uids array.
   */
  protected function addFlags($type_flag, $content_id, $num = 1, $uids = NULL) {
    static $o_flags = array();
    static $counter_uids = 35000;
    global $user;
    
    if (!count($o_flags)) {
      $result = db_query("SELECT fid, content_type, name, title FROM {flags}");
      while ($row = db_fetch_object($result)) {
        $o_flags[$row->name] = $row;
      }
    }
    
    if (!count($o_flags) || !isset($o_flags[$type_flag])) {
      return FALSE;
    }
    
    for ($i = 0; $i < $num; $i++) {
      $uid = isset($uids[$i]) ? $uids[$i] : $counter_uids++;
      db_query("INSERT INTO {flag_content}
      	(fid, content_type, content_id, uid, sid, timestamp)
      	VALUES (%d, '%s', %d, %d, 0, %d)",
        $o_flags[$type_flag]->fid, $o_flags[$type_flag]->content_type, $content_id, $uid, time()
      );
    }
    return TRUE;
  }
  
  
  
  
  
  
  
  
  
  /**
   * Answers badges functions.
   */
  
  /**
   * Load User profile.
   */
  protected function loadUserProfile($uid) {
    if (isset($this->users_profile[$uid])) {
      return $this->users_profile[$uid];
    }
    
    if (!($account_profile = content_profile_load('profile', $uid))) {
      return FALSE;
    }
    $this->users_profile[$uid] = $account_profile;
    return $account_profile;
  }
  
  
  /**
   * Get user badges.
   */
  protected function getBadges($uid = 0, $update = TRUE) {
    if (!$uid) {
      $uid = $this->loggedInUser->uid;
    }
    
    if (!$update && isset($this->users_badges[$uid])) {
      return $this->users_badges[$uid];
    }
    
    if (!isset($this->users_profile[$uid])) {
      if (!$this->loadUserProfile($uid)) {
        return FALSE;
      }
    }
    
    $this->users_badges[$uid] = array();
    $result = db_query("SELECT d.tid, d.name, d.description FROM {term_data} d
      INNER JOIN {term_node} t USING(tid)
      WHERE t.nid = %d AND t.vid = %d AND d.vid = 30001",
      $this->users_profile[$uid]->nid, $this->users_profile[$uid]->vid
    );
    while ($row = db_fetch_object($result)) {
      $this->users_badges[$uid][$row->tid] = $row;
    }
    return $this->users_badges[$uid];
  }

  
  /**
   * Load node comments.
   */
  protected function loadComments($nid) {
    $result = db_query("SELECT * FROM {comments} WHERE nid = %d", $nid);
    $comments = array();
    while ($row = db_fetch_object($result)) {
      $comments[] = $row;
    }
    return $comments;
  }
  
  
  /**
   * Check badges.
   */
  protected function checkBadges($uid = 0) {
    if (!$uid) {
      $uid = $this->loggedInUser->uid;
    }
    
    $str_output = 'User uid='. $uid .'.';
    $old_badges = isset($this->users_badges[$uid]) ? $this->users_badges[$uid] : array();
    
    if ($badges = $this->getBadges($uid)) {
      if (count($badges)) {
        $str_new_badges = '';
        $str_old_badges = '';
        $num_new = 0;
        $num_old = 0;
        
        foreach ($badges as $tid => $value) {
          if (!isset($old_badges[$tid])) {
            $str_new_badges .= $num_new++ ? ', '. $value->name : $value->name;
          }
          else {
            $str_old_badges .= $num_old++ ? ', '. $value->name : $value->name;
          }
        }
        
        if ($num_old) {
          $str_output .= ' Old badges: '. $str_old_badges .'.';
        }
        if ($num_new) {
          $str_output .= ' Add new badges: '. $str_new_badges;
        }
      }
      else {
        $str_output .= ' Not badge.';
      }
    }
    else {
      $str_output .= ' Not badge.';
    }
    return $str_output;
  }
  
  
  /**
   * Return user badges.
   * return string.
   */
  protected function sprintBadges($uid = 0) {
    if (!$uid) {
      $uid = $this->loggedInUser->uid;
    }
    
    if (isset($this->users_badges[$uid]) && count($this->users_badges[$uid])) {
      $str_badges = '';
      $num = 0;
      foreach ($this->users_badges[$uid] as $tid => $value) {
        $str_badges .= $num++ ? ', '. $value->name : $value->name;
      }
      $str = 'User badges (uid='. $this->loggedInUser->uid .'): '. $str_badges;
    }
    else {
      $str = 'Not badge uid='. $this->loggedInUser->uid;
    }
    return $str;
  }
  
  
  /**
   * Add $num votes to material $nid.
   */
  protected function addVotes($id, $num, $uid = FALSE, $type = 'node', $vote = 'up') {
    static $user_uid = 31000;
    
    $value = $vote == 'up' ? 1 : -1;
    $votes = array();
    
    for ($i = 0; $i < $num; $i++) {
      $votes[] = array(
        'content_type' => $type,
        'content_id' => $id,
        'value_type' => 'points',
        'value' => $value,
        'tag' => 'vote',
        'uid' => ($uid ? $uid : $user_uid++),
        'vote_source' => '127.0.0.1',
        'timestamp' => time(),
      );
    }
    votingapi_set_votes($votes);
  }
  
  /**
   * Setup "num day on-line" (yesterday).
   */
  protected function setupOnLine($uid, $num_days) {
    $user_count_day = db_fetch_object(db_query_range(
    	"SELECT * FROM {user_statistics} WHERE uid = %d", $uid, 0, 1));
    $user_count_day = new stdClass();
    $user_count_day->uid = $uid;
    $user_count_day->day_online = $num_days;
    $user_count_day->timestamp = time();
    if ($user_count_day) {
      //UPDATE
      drupal_write_record('user_statistics', $user_count_day, array('uid'));
    }
    else {
      //INSERT
      drupal_write_record('user_statistics', $user_count_day);
    }
  }
  
  
}






