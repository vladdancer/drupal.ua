<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_3_9_panels_layouts() {
  $items['960_12_twocol_3_9'] = array(
    'title' => t('960/12 Two column 3-9'),
    'icon' => '960_12_twocol_3_9.png',
    'theme' => '960_12_twocol_3_9',
    'css' => '960_12_twocol_3_9.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
