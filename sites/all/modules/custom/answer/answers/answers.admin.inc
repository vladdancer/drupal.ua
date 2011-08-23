<?php
/**
 * @file
 * Answers settings.
 */

/**
 * Settings form for admin/settings/answers page.
 */
function answers_admin() {
  $search_engines = array();
  $modules = module_implements('answers_search_info');
  foreach ($modules as $module) {
    $engine = module_invoke($module, 'answers_search_info');
    $search_engines[$engine['module']] = $engine['engine_name'];
  }

  $form = array();

  $form['search_engine']['answers_search_engine'] = array(
    '#type' => 'select',
    '#title' => 'Search engine',
    '#options' => $search_engines,
    '#default_value' => variable_get('answers_search_engine', 'search'),
    '#description' => t('Select search engine. This feature is implemented by 3-d modules.'),
    '#required' => TRUE,
  );
  // Search button text.
  $form['answers_search_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Search button text'),
    '#default_value' => variable_get('answers_search_button_text', 'Search'),
    '#required' => TRUE,
  );
  // Description.
  /*$form['search_form']['answers_search_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description of search box'),
    '#default_value' => variable_get('answers_search_description', ''),
    '#required' => TRUE,
  );*/
  // Limit of nodes per node type
  $form['answers_search_limit_nodes'] = array(
    '#type' => 'select',
    '#title' => t('Search limit'),
    '#description' => t('Enter limit of nodes to display in search block per page.'),
    '#default_value' => variable_get('answers_search_limit_nodes', 10),
    '#options' => array(
      2 => 2,
      4 => 4,
      6 => 6,
      8 => 8,
      10 => 10,
      12 => 12,
      14 => 14,
      16 => 16,
      18 => 18,
      20 => 20
    ),
    '#required' => TRUE,
  );
  // Sites for Google Search
  $form['answers_search_google_sites'] = array(
    '#type' => 'item',
    '#title' => t('Sites for search in Google'),
    '#value' => l(
      'http://www.google.ru/cse/panel/basics?cx=010570434424230918298:ugfkolvqghy',
      'http://www.google.ru/cse/panel/basics?cx=010570434424230918298:ugfkolvqghy',
      array('attributes' => array('target' => '_blank'))
    ),
  );

  return system_settings_form($form);
}


