<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_threecol_4_4_4_panels_layouts() {
  $items['960_12_threecol_4_4_4'] = array(
    'title' => t('960/12 Three column 4-4-4'),
    'icon' => '960_12_threecol_4_4_4.png',
    'theme' => '960_12_threecol_4_4_4',
    'css' => '960_12_threecol_4_4_4.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
