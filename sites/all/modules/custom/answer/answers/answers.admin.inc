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


/**
 * Answer FAQ settings form.
 */
function answers_admin_faq_form($form_state) {
  $form = array();
  
  $faq_settings = variable_get('answers_faq_settings', array());
  
  $form['faq_edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create/Edit page'),
  );
  $form['faq_edit']['edit_status'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Status'),
    '#default_value' => $faq_settings['edit_status'],
  );
  $form['faq_edit']['edit_nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Node nid'),
    '#default_value' => $faq_settings['edit_nid'],
    '#size' => 5,
  );
  
  $form['faq_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('List page'),
  );
  $form['faq_list']['list_status'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Status'),
    '#default_value' => $faq_settings['list_status'],
  );
  $form['faq_list']['list_nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Node nid'),
    '#default_value' => $faq_settings['list_nid'],
    '#size' => 5,
  );
  
  $form['faq_comment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comment page'),
  );
  $form['faq_comment']['comment_status'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Status'),
    '#default_value' => $faq_settings['comment_status'],
  );
  $form['faq_comment']['comment_nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Node nid'),
    '#default_value' => $faq_settings['comment_nid'],
    '#size' => 5,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  return $form;
}


/**
 * Submit FAQ settings.
 */
function answers_admin_faq_form_submit($form, &$form_state) {
  $settings = array();
  
  $settings['edit_status'] = isset($form_state['values']['edit_status'])
    ? $form_state['values']['edit_status'] : 0;
  $settings['edit_nid'] = isset($form_state['values']['edit_nid'])
    ? $form_state['values']['edit_nid'] : 0;
  
  $settings['list_status'] = isset($form_state['values']['list_status'])
    ? $form_state['values']['list_status'] : 0;
  $settings['list_nid'] = isset($form_state['values']['list_nid'])
    ? $form_state['values']['list_nid'] : 0;
  
  $settings['comment_status'] = isset($form_state['values']['comment_status'])
    ? $form_state['values']['comment_status'] : 0;
  $settings['comment_nid'] = isset($form_state['values']['comment_nid'])
    ? $form_state['values']['comment_nid'] : 0;
  
  variable_set('answers_faq_settings', $settings);
  unset($form_state['storage']);
  drupal_set_message(t('Preferences have been saved'));
}

