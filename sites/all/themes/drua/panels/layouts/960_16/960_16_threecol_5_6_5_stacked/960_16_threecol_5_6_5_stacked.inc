<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_threecol_5_6_5_stacked_panels_layouts() {
  $items['960_16_threecol_5_6_5_stacked'] = array(
    'title' => t('960/16 Three column 5-6-5 stacked'),
    'icon' => '960_16_threecol_5_6_5_stacked.png',
    'theme' => '960_16_threecol_5_6_5_stacked',
    'css' => '960_16_threecol_5_6_5_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
