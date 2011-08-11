<?php

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_12_twocol_6_6_panels_layouts() {
  $items['960_12_twocol_6_6'] = array(
    'title' => t('960/12 Two column 6-6'),
    'icon' => '960_12_twocol_6_6.png',
    'theme' => '960_12_twocol_6_6',
    'css' => '960_12_twocol_6_6.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
