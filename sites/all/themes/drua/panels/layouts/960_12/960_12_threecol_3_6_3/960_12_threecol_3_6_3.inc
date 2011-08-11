<?php

/**
 * implementation of hook_panels_layouts
 */
function drua_960_12_threecol_3_6_3_panels_layouts() {
  $items['960_12_threecol_3_6_3'] = array(
    'title' => t('960/12 Three column 3-6-3'),
    'icon' => '960_12_threecol_3_6_3.png',
    'theme' => '960_12_threecol_3_6_3',
    'theme arguments' => array('id', 'content'),
    'css' => '960_12_threecol_3_6_3.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
    ),
  );

  return $items;
}

