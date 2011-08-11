<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_6_6_stacked_panels_layouts() {
  $items['960_12_twocol_6_6_stacked'] = array(
    'title' => t('960/12 Two column 6-6 stacked'),
    'icon' => '960_12_twocol_6_6_stacked.png',
    'theme' => '960_12_twocol_6_6_stacked',
    'css' => '960_12_twocol_6_6_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
