<?php


/**
 * Load OG posts.
 * Only "uk" language (not duplicate).
 */
function _og_to_forum_load_posts() {
  $posts = array();
  $result = db_query("SELECT DISTINCT(n.nid), n.vid, n.title,
  		oa.group_nid, ua.pid, ua.dst, ua.language AS url_language
  	FROM {node} n
    LEFT JOIN {og_ancestry} oa USING(nid)
    LEFT JOIN {url_alias} ua ON ua.src = concat('node/', n.nid)
    WHERE n.type = 'post' ORDER BY oa.group_nid ASC"
  );
  while ($row = db_fetch_object($result)) {
    $posts[$row->nid] = $row;
  }
  return $posts;
}


/**
 * Load forum alias.
 */
function _og_to_forum_load_alias() {
  $alias = array();
  $result = db_query("SELECT * FROM {url_alias} WHERE src LIKE 'forum/%'");
  while ($row = db_fetch_object($result)) {
    $alias[(int)drupal_substr($row->src, 6)] = $row;  //  forum/143
  }
  return $alias;
}


/**
 * Save forum alias.
 */
function _og_to_forum_add_alias($map) {
  foreach ($map['terms'] as $tid => $term) {
    if ($term->depth) {
      $alias = 'forum/'.
        _og_to_forum_forum_alias($map['terms'][$term->parents[0]]->name)
        .'/'. _og_to_forum_forum_alias($term->name);
    }
    else {
      $alias = 'forum/'. _og_to_forum_forum_alias($term->name);
    }
    
    db_query("DELETE FROM {url_alias} WHERE src = '%s' LIMIT 1",
    	'forum/'. $term->tid
    );
    db_query("INSERT INTO {url_alias} (src, dst) VALUES ('%s', '%s')",
    	'forum/'. $term->tid, $alias
    );
  }
}


/**
 * Conveert functions.
 */

/**
 * convert OG term to forum term.
 */
function _og_to_forum_convert_posts($posts, $map, $forum_alias) {
  $output = '';
  $count = 0;
  
  module_load_include('inc', 'pathauto');
  
  foreach ($posts as $nid => $node) {
    if (isset($map[$node->group_nid])) {
      //Add to forum
      db_query('DELETE FROM {forum} WHERE nid = %d', $node->nid);
      db_query('INSERT INTO {forum} (nid, vid, tid) VALUES (%d, %d, %d)',
        $node->nid, $node->vid, $map[$node->group_nid]
      );
      
      //Add Taxonomy term
      db_query("DELETE FROM {term_node} WHERE nid = %d AND tid = %d",
        $node->nid, $map[$node->group_nid]
      );
      db_query("INSERT INTO {term_node} (nid, vid, tid) VALUES (%d, %d, %d)",
        $node->nid, $node->vid, $map[$node->group_nid]
      );
      
      //Create new URL
      $new_url = $forum_alias[$map[$node->group_nid]]->dst .'/'.
        pathauto_cleanstring($node->title);
      if (drupal_strlen($new_url) > 127) {
        $output .= "\n<p>Node (nid = ". $node->nid .") has a very long URL.</p>\n";
      }
      _og_to_forum_path_set_alias($node->nid, $new_url, $node->url_language);
      
      //Save path_redirect
      if ($node->dst != 'node/'. $node->nid) {
        $redirect = array(
          'source' => $node->dst,
          'redirect' => $new_url,
        );
        path_redirect_save($redirect);
      }
      $count ++;
    }
    else {  //FIXME russ OG post
      $output .= "<div>Ignored (nid, vid, group_nid) = (".
        $node->nid .', '. $node->vid .', '. $node->group_nid .")</div>";
    }
  }
  
  drupal_clear_path_cache();
  return "\n<h2>Successfully save ". $count ." post</h2>\n". $output;
}


/**
 * Set an aliased path for a given Drupal path.
 */
function _og_to_forum_path_set_alias($nid, $alias, $language = '') {
  $path = urldecode('node/'. $nid);
  $alias = urldecode($alias);
  
  // Check for existing aliases.
  $pid = db_result(db_query(
    "SELECT pid FROM {url_alias} WHERE src = '%s' AND language = '%s'",
    'node/'. $nid, $language
  ));
  
  if ($pid) {
    // There is already such an alias, neutral or in this language.
    // Update the alias based on alias; setting the language if not yet done.
    db_query("UPDATE {url_alias}
      SET src = '%s', dst = '%s', language = '%s' WHERE dst = '%s'",
      $path, $alias, $language, $alias
    );
  }
  else {
    // A new alias. Add it to the database.
    db_query("INSERT INTO {url_alias}
      (src, dst, language) VALUES ('%s', '%s', '%s')",
      $path, $alias, $language
    );
  }
}



