<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_threecol_5_6_5_panels_layouts() {
  $items['960_16_threecol_5_6_5'] = array(
    'title' => t('960/16 Three column 5-6-5'),
    'icon' => '960_16_threecol_5_6_5.png',
    'theme' => '960_16_threecol_5_6_5',
    'css' => '960_16_threecol_5_6_5.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
