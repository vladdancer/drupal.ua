<?php
// $Id: apachebench.admin.inc,v 1.2 2009/03/19 21:30:19 neochief Exp $

/**
 * @file
 * ApacheBench administration and reporting pages.
 */

/**
 * Settings form.
 */
function apachebench_settings() {
  $form = array();

  $form['apachebench_frequency'] = array(
    '#type' => 'textfield',
    '#title' => t('Frequency'),
    '#description' => t('Run ApacheBench tests every x hours. Cron must be scheduled to run at this same frequency or higher. Set to 0 to prevent automated testing.'),
    '#default_value' => variable_get('apachebench_frequency', 0),
  );
  $form['apachebench_requests'] = array(
    '#type' => 'textfield',
    '#title' => t('Requests'),
    '#description' => t('Total number of requests.'),
    '#default_value' => variable_get('apachebench_requests', 100),
  );
  $form['apachebench_concurrency'] = array(
    '#type' => 'textfield',
    '#title' => t('Concurrency'),
    '#description' => t('Number of concurrenct requests.'),
    '#default_value' => variable_get('apachebench_concurrency', 25),
  );
  $form['apachebench_uris'] = array(
    '#type' => 'textarea',
    '#title' => t('Website URIs'),
    '#description' => t('One absolute URI per line, be sure to include a trailing slash (/) for example <em>http://vision-media.ca/</em>.'),
    '#default_value' => variable_get('apachebench_uris', ''),
  );
  $form['apachebench_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Full <em>ab</em> utility path') .' '. t('(optional)'),
    '#description' => t('System path of Apache <em>ab</em> utility. This option created mostly for Windows users (which should use something like <code>Z:\usr\local\apache\bin\ab.exe</code> to make everything works).'),
    '#default_value' => variable_get('apachebench_path', 'ab'),
  );

  return system_settings_form($form);
}

/**
 * Display ApacheBench reports when charting is available.
 *
 * @return string
 *  Markup.
 */
function apachebench_reports() {
  if (!module_exists('open_flash_chart_api')){
    drupal_set_message(t('In order to view these reports you must install the <a href="http://drupal.org/project/open_flash_chart_api">open_flash_chart_api</a> module.'));
  }
  else {
    $form['report'] = array(
      '#type' => 'item',
      '#value' => apachebench_get_overview_report(),
    );
    $form['flush'] = array(
      '#type' => 'submit',
      '#value' => t('Flush benchmarking data'),
    );
  }
  
  return $form;
}

function apachebench_reports_submit() {
  apachebench_clear_all();
  unset($_SESSION['apachebench_results']);
}

/**
 * Display instant benchmark report.
 */
function apachebench_instant() {
  if (!module_exists('open_flash_chart_api')){
    drupal_set_message(t('In order to view these reports you must install the <a href="http://drupal.org/project/open_flash_chart_api">open_flash_chart_api</a> module.'));
  }
  else {
    if (isset($_SESSION['apachebench_results'])) {
      drupal_set_title(t('Benchmark results'));
      $form['report'] = array(
        '#type' => 'item',
        '#value' => apachebench_get_overview_report($_SESSION['apachebench_results']),
      );
    }
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Run fresh benchmark'),
    );
  }
  
  return $form;
}

/**
 * Run benchmarks as Drupal batch.
 */
function apachebench_instant_submit() {
  $batch = array(
    'operations' => array(
      array('apachebench_batch_process', array()),
    ),
    'file' => drupal_get_path('module', 'apachebench') .'/apachebench.admin.inc',
    'finished' => 'apachebench_batch_finished',
    'title' => t('Benchmarking Apache'),
    'init_message' => t('Starting benchmark.'),
    'progress_message' => '',
    'error_message' => t('Benchmark has encountered an error.'),
  );
  batch_set($batch);
  batch_process('admin/reports/apachebench/instant');
}

/**
 * Batch processing function. Run one test per URI.
 */
function apachebench_batch_process(&$context) {
  $uris = explode("\n", variable_get('apachebench_uris', ''));
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($uris);
  }

  $uri = trim($uris[$context['sandbox']['progress']]);

  $context['results'][] = apachebench($uri, variable_get('apachebench_requests', 100), variable_get('apachebench_concurrency', 25), TRUE);

  $context['sandbox']['progress']++;
  $context['message'] = t('Now benchmarking %uri', array('%uri' => $uri));

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch finish callback.
 */
function apachebench_batch_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = format_plural(count($results), 'URI was benchmarked successfully.', '@count URIs were benchmarked successfully.');
    $_SESSION['apachebench_results'] = $results;
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = 'An error occurred while processing '. $error_operation[0] .' with arguments :'. print_r($error_operation[0], TRUE);
  }
  drupal_set_message($message);
}


/**
 * Create overview report.
 *
 * @param array $results
 *   Prepopulated array of benchmarking results. If not passed, results will be loaded from the database.
 *
 * @return string
 *  Markup.
 */
function apachebench_get_overview_report($results = NULL) {
  $output = '';
  $rows = array();
  $header = array(t('URI'), t('Avg requests per second'), t('Total tests'), t('Avg requests'), t('Avg concurrency'), t('Avg failed'), t('Avg document length'), t('Avg time taken'));

  // @todo finish charts, remove table reports
  // @todo utilize tablesort api

  // Fetch results from DB if they weren't passed nto parameters.
  if (!$results) {
    $res = db_query("
        SELECT 
          uri,
          COUNT(*) as total_count,
          AVG(concurrency) as concurrency,
          AVG(requests) as requests,
          AVG(requests_per_second) as requests_per_second,
          AVG(failed_requests) as failed_requests,
          AVG(time_taken_for_tests) as time_taken_for_tests,
          AVG(document_length) as document_length
        FROM {apachebench_results}
        GROUP BY uri
        ORDER BY AVG(requests_per_second) DESC
      ");
    while ($result = db_fetch_array($res)) {
      $results[] = $result;
    }
  }
  if (!empty($results)) {
    foreach ($results as $result) {
      $rows[] = array(
        $result['uri'], 
        number_format($result['requests_per_second'], 3),
        isset($result['total_count']) ? $result['total_count'] : 1,
        number_format($result['requests'], 1), 
        number_format($result['concurrency'], 1),
        number_format($result['failed_requests'], 1),
        format_size($result['document_length']),
        t('%time seconds', array('%time' => number_format($result['time_taken_for_tests'], 3))),
      );
    }

    // Display results
    $output .= theme('table', $header, $rows);
  }
  else {
    $output .= t('Benchmarking data is empty. <a href="!uri">Run instant benchmark?</a>', array('!uri' => url('admin/reports/apachebench/instant')));
  }

  return $output;
}
