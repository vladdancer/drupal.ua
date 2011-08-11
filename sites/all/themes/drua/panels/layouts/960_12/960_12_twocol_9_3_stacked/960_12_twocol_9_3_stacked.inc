<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_9_3_stacked_panels_layouts() {
  $items['960_12_twocol_9_3_stacked'] = array(
    'title' => t('960/12 Two column 9-3 stacked'),
    'icon' => '960_12_twocol_9_3_stacked.png',
    'theme' => '960_12_twocol_9_3_stacked',
    'css' => '960_12_twocol_9_3_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
