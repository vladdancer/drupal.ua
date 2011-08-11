<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_9_3_panels_layouts() {
  $items['960_12_twocol_9_3'] = array(
    'title' => t('960/12 Two column 9-3'),
    'icon' => '960_12_twocol_9_3.png',
    'theme' => '960_12_twocol_9_3',
    'css' => '960_12_twocol_9_3.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
