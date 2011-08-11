<?php
// $Id$

/**
  * @file
  * about this file
  */


/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 */
function answers_drua_dublicated_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT dst FROM {url_alias}
      WHERE LOWER(dst) LIKE LOWER('%s%%')", $string, 0, 10
    );
    while ($row = db_fetch_object($result)) {
      $matches[$row->dst] = check_plain($row->dst);
    }
    
    $result = db_query_range("SELECT src FROM {url_alias}
      WHERE LOWER(src) LIKE LOWER('%s%%')", $string, 0, 10
    );
    while ($row = db_fetch_object($result)) {
      $matches[$row->src] = check_plain($row->src);
    }
  }
//  $matches[' '] = ' ';
  drupal_json($matches);
}