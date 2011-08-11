<?php
// $Id$

/**
 * @file
 * Grabbing and parsing content from drupal accounts
 */


/**
 * Grabbing and parsing content from drupal accounts
 *
 * @param $url
 *   string: profile path
 * @param $update
 *   Whether or not to reset code verification (defaults to
 *   FALSE).
 * @return
 *   If updating - an structured array containing the individual elements
 *   of the user profile. Otherwise messages for AHAH callback
 */
function drupal_account_grabbing_content($url, $update = FALSE) {
  global $user;

  preg_match("/^http:\/\/(?:www\.)?([^\/]+)/i", $url, $matches);

  //url cheking
  if (($matches[1] != 'drupal.org' && $matches[1] != 'drupal.ru') || strpos($url, '/user') === FALSE) {
    return array(
      'status' => 'error',
      'message' => t('Incorrect url! Please check URL to your accounts and try again.')
    );
  }

  // code cheking
  if (!$update && !account_check_code($url, $matches[1])) {
    return array(
      'status' => 'error',
      'message' =>  t('Incorrect code! Please check the code (!code) on your accounts and try again.',
       array('!code' => '<strong>DUSER-'. check_plain($user->uid) .'</strong>'))
    );
  }

  $domain = $matches[1];
  $_domain = str_replace('.', '_', $domain);
  $output = array();

  if (function_exists('_grabbing_'. $_domain)) {
    if (drupal_account_sock_check($url) && @$data = call_user_func('_grabbing_'. $_domain, $url)) {
      $output[$domain] = $data;
    }
  }

  if ($update) {
    return $data;
  }

  $_SESSION['account'] = serialize($output);

  return array('status' => 'status', 'message' =>
    t('Data has been updated! The changes will not be saved until the Save button is clicked')
  );
}


/**
 * Checking user code
 *
 * @param $url
 *   string: profile url
 * @return
 *   @return
 *   TRUE if the user-code is correct, or FALSE otherwise.
 */
function account_check_code($url, $domain) {
  global $user;

  $profil = @file_get_html($url);
  if ($profil != '' && $domain) {
    switch ($domain) {
      case 'drupal.org':
        foreach ($profil->find('.profile ') as $e)
          $contributions = $e->plaintext ;
        break;
      case 'drupal.ru':
        foreach ($profil->find('.profile dd.profile-profile_info') as $e)
          $contributions = $e->plaintext ;
        break;
    }
    return strpos($contributions, 'DUSER-'. $user->uid) === FALSE ? FALSE : TRUE;
    
    $profile->clear();  //not work
    unset($profile);
  }
  return FALSE;
}


/**
 * Grabbing and parsing http://drupal.org
 *
 * @param $url
 *   string: profile path
 * @return
 *   an structured array containing the individual elements
 *   of the Drupal.org user profile.
 */
function _grabbing_drupal_org($url) {

  $profile = @file_get_html($url);

  if ($profile != '') {
    $output = array();

    //username
     foreach ($profile->find('h1.title') as $e) {
       $output['username'] = $e->plaintext ;
     }
     $output['username'] = explode(' | ', $output['username']);
     $output['username'] = $output['username'][0];

     //projects
     foreach ($profile->find('dl.versioncontrol-project-user-commits li a') as $e) {
       $progect = @file_get_html('http://drupal.org'. $e->href);

        foreach ($progect->find('.terms a') as $v) {
          $v = strtolower($v->plaintext);
          $k = $v == 'themes' || $v  == 'translations' ? $v : 'modules';
          $output['projects'][$k][] = array('title' => $e->plaintext,
            'href' => 'http://www.drupal.org'. $e->href);
          break;
        }
        $progect->clear();
      }

      //track
      $track = @file_get_html($url .'/track');
      if ($track != '') {

        //pages
        foreach ($track->find('ul.pager li a') as $e) {
          $pages = $e->href;
        }

        $pages = $pages != '' ? explode('page=', $pages) : 0;
        if (is_array($pages)) {
          $pages = $pages[1];
        }

        if ($pages >= 1) {
          $last_track = @file_get_html($url .'/track?page='. $pages);
          if ($last_track != '') {
            $count_last = count($last_track->find('#tracker tr.odd, #tracker tr.even')) ;
          }
          $output['track'] = 25 * $pages + $count_last;
        }
        else {
          $output['track'] = count($track->find('#tracker tr.odd, #tracker tr.even')) ;
        }

     }
     $output['profile'] = $url;
  }

  $profile->clear();
  unset($profile);

  return $output != '' ? $output : NULL;
}



/**
 * Grabbing and parsing http://drupal.ru
 *
 * @param $url
 *   string: profile url
 * @return
 *   an structured array containing the individual elements
 *   of the Drupal.ru user profile.
 */
function _grabbing_drupal_ru($url) {

  $profile = @file_get_html($url);

  if ($profile != '') {
    $output = array();

    //username
    foreach ($profile->find('title') as $e) {
      $output['username'] = $e->plaintext ;
    }
    $output['username'] = explode(' | ', $output['username']);
    $output['username'] = $output['username'][0];

    //track
    foreach ($profile->find('ul.tabs li a') as $e) {
      if (strpos($e->href, '/track') !== FALSE ) {
        $path = $e->href;
        break;
      }
    }

    $track = @file_get_html('http://www.drupal.ru/'. $path);

    if ($track != '') {

      //pages
      foreach ($track->find('ul.pager li a') as $e) {
        $pages = $e->href;
      }

      $pages = $pages != '' ? explode('page=', $pages) : 0 ;

      if (is_array($pages)) {
        $pages = $pages[1];
      }

      if ($pages >= 1) {
        $last_track = @file_get_html('http://www.drupal.ru/'. $path .'?page='. $pages);
        if ($last_track != '') {
          $count_last = count($last_track->find('#tracker tr.odd, #tracker tr.even'));
        }
        $output['track'] = 60 * $pages + $count_last;
      }
      else {
        $output['track'] = count($track->find('#tracker tr.odd, #tracker tr.even'));
      }
    }
    $output['profile'] = $url;
  }

  $profile->clear();
  unset($profile);

  return $output != '' ? $output : NULL;
}

/**
 * Check an HTTP request.
 */
function drupal_account_sock_check($url) {

  $uri = parse_url($url);

  $fs = @fsockopen($uri['host'], 80, $errno, $errstr, 15);

  if ($fs) {
    return TRUE;
  }
}

