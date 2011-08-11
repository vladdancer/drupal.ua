<?php

/**
 * implementation of hook_panels_layouts
 */
function drua_960_16_threecol_4_8_4_panels_layouts() {
  $items['960_16_threecol_4_8_4'] = array(
    'title' => t('960/16 Three column 4-8-4'),
    'icon' => '960_16_threecol_4_8_4.png',
    'theme' => '960_16_threecol_4_8_4',
    'theme arguments' => array('id', 'content'),
    'css' => '960_16_threecol_4_8_4.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
    ),
  );

  return $items;
}

