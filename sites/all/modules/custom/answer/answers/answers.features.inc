<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function answers_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_flag_default_flags().
 */
function answers_flag_default_flags() {
$flags = array();
// Exported flag: "Best Answer".
$flags[] = array (
  'content_type' => 'comment',
  'name' => 'best_answer',
  'title' => 'Best Answer',
  'global' => '0',
  'types' => 
  array (
    0 => 'question',
  ),
  'flag_short' => '+ Best Answer!',
  'flag_long' => '',
  'flag_message' => '',
  'unflag_short' => '- Best Answer',
  'unflag_long' => '',
  'unflag_message' => '',
  'unflag_denied_text' => '',
  'link_type' => 'toggle',
  'roles' => 
  array (
    'flag' => 
    array (
      0 => 2,
      1 => 3,
    ),
    'unflag' => 
    array (
      0 => 2,
      1 => 3,
    ),
  ),
  'access_author' => 'node_own',
  'show_on_comment' => 1,
  'api_version' => 2,
  'module' => 'answers',
  'locked' => 
  array (
    0 => 'name',
  ),
);
return $flags;
}

/**
 * Implementation of hook_node_info().
 */
function answers_node_info() {
  $items = array(
    'question' => array(
      'name' => t('Question'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Details'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function answers_views_api() {
  return array(
    'api' => '2',
  );
}
