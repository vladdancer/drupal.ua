<?php

/**
 * Implementation of hook_panels_layouts()
 */
function drua_960_16_threecol_stacked_4_8_4_stacked_panels_layouts() {
  $items['960_16_threecol_4_8_4_stacked'] = array(
    'title' => t('960/16 Three column 4-8-4 stacked'),
    'icon' => '960_16_threecol_4_8_4_stacked.png',
    'theme' => '960_16_threecol_4_8_4_stacked',
    'css' => '960_16_threecol_4_8_4_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side'),
      'bottom' => t('Bottom'),
    ),
  );

  return $items;
}
