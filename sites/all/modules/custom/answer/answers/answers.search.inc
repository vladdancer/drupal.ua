<?php
// $Id: answers.search.inc, 24.03.2010 17:32:01 seaji Exp $

/**
  * @file
  * Search Questions API
  *
  */

/**
 * Question form.
 */
function answers_search_question_form() {
  $search_string = urldecode($_GET['search_text']);

  drupal_add_js(drupal_get_path('module', 'answers'). '/answers.search.js', 'module');
  drupal_set_html_head('<script src="http://www.google.com/jsapi?key=ABQIAAAA5K0ecxf29CdGf0jCSGwwBhRUGqS5xr_iQ5HQbbZHAsPbj-uEiRRueIFQpz5QCsWnl3Em0Uafe8m_VA" type="text/javascript"></script>');
  drupal_add_css(drupal_get_path('module', 'answers'). '/answers.css', 'module');

  $form = array();

  $form['markup_1'] = array(
    '#type' => 'markup',
    '#value' => '<div class="container-inline">',
  );
  $form['search_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Search Questions & Answers'),
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => $search_string,
    '#autocomplete_path' => 'answers/autocomplete',
  );
  $form['search_button'] = array(
    '#type' => 'submit',
    '#value' => t(variable_get('answers_search_button_text', 'Search')),
    '#prefix' => '<span class="button bsmall binner sblue"><span>',
    '#suffix' => '</span></span>',
    '#ahah' => array(
      'path' => 'answers/search/js',
      'effect' => 'fade',
      'event' => 'click',
      'wrapper' => 'answers-search-contents',
    ),
  );
  $form['markup_2'] = array(
    '#type' => 'markup',
    '#value' => '</div>',
  );

  if ($search_string) {
    $search_results = theme('answers_search_results', $search_string, answers_search_execute_query($search_string));
  }
  $form['markup_3'] = array(
    '#value' => '<div id="answers-search-contents">'. $search_results .'</div>',
  );
  $form['page'] = array(
    '#type' => 'hidden',
    '#default_value' => 0,
  );
  return $form;
}

/**
 * Submit callback.
 *
 * @see answers_search_question_form().
 */
function answers_search_question_form_submit($form, &$form_state) {
  $form_state['redirect'] = array($_GET['q'], 'search_text='. $form_state['values']['search_text']);
}

/**
 * AJAX callback. When JS is enabled.
 */
function answers_search_js() {
  $search_string = urldecode($_POST['search_text']);
  $output = theme('answers_search_results', $search_string, answers_search_execute_query($search_string));
  drupal_json(array('status' => TRUE, 'data' => theme('status_messages') . $output));
  exit;
}

/**
 * Execute search query.
 * Invoking hook_answers_search_results().
 */
function answers_search_execute_query($search_string) {
  watchdog('answers', $search_string, array(), WATCHDOG_NOTICE, l(t('results'), 'questions', array('query' => 'search_text='. urlencode($search_string))));
  $engine = variable_get('answers_search_engine', 'answers_search');
  return module_invoke($engine, 'answers_search_results', $search_string);
}

/**
 * Autocomplete callback for questions.
 *
 * @see answers_search_question_form().
 */
function answers_autocomplete($string = '') {
  $matches = array();

  if ($string) {
    $result = db_query_range("SELECT COUNT(*) AS count, message FROM {watchdog} WHERE type = 'answers' AND LOWER(message) LIKE LOWER('%s%%') GROUP BY message ORDER BY count DESC", $string, 0, 10);
    while ($question = db_fetch_object($result)) {
      $matches[$question->message] = check_plain($question->message);
    }
  }

  drupal_json($matches);
}

/**
 * Autocomplete callback for new questions.
 *
 * @see answers.question.js.
 * @see answers_init().
 */
function answers_autocomplete_question($string = '') {
  $matches = array();

  if ($string) {
    $result = db_query_range("SELECT nid, title FROM {node} WHERE type = 'question' AND LOWER(title) LIKE LOWER('%s%%')", $string, 0, 10);
    while ($question = db_fetch_object($result)) {
      $matches[] = l(check_plain($question->title), 'node/'. $question->nid, array('attributes' => array('target' => '_blank')));
    }
  }

  drupal_json(theme('answers_possible_questions', $matches));
  exit;
}