<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_8_4_panels_layouts() {
  $items['960_12_twocol_8_4'] = array(
    'title' => t('960/12 Two column 8-4'),
    'icon' => '960_12_twocol_8_4.png',
    'theme' => '960_12_twocol_8_4',
    'css' => '960_12_twocol_8_4.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
