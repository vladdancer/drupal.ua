<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_10_2_panels_layouts() {
  $items['960_12_twocol_10_2'] = array(
    'title' => t('960/12 Two column 10-2'),
    'icon' => '960_12_twocol_10_2.png',
    'theme' => '960_12_twocol_10_2',
    'css' => '960_12_twocol_10_2.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
