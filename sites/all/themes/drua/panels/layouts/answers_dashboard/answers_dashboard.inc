<?php
// $Id$


/**
 * Implementation of hook_panels_layouts().
 */
function drua_answers_dashboard_panels_layouts() {
  $items['answers_dashboard'] = array(
    'title' => t('Answers dashboard'),
    'icon' => 'answers_dashboard.png',
    'theme' => 'panels_answers_dashboard',
    'panels' => array(
      'top' => t('Top'),
      'sidebar' => t('Sidebar'),
      'content' => t('Content'),
      'bottom' => t('Bottom'),
    ),
  );

  return $items;
}
