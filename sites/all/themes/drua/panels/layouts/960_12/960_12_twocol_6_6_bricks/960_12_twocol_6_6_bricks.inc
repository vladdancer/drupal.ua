<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_6_6_bricks_panels_layouts() {
  $items['960_12_twocol_6_6_bricks'] = array(
    'title' => t('960/12 Two column 6-6 bricks'),
    'icon' => '960_12_twocol_6_6_bricks.png',
    'theme' => '960_12_twocol_6_6_bricks',
    'css' => '960_12_twocol_6_6_bricks.css',
    'panels' => array(
      'top' => t('Top'),
      'left_above' => t('Left above'),
      'right_above' => t('Right above'),
      'middle' => t('Middle'),
      'left_below' => t('Left below'),
      'right_below' => t('Right below'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

