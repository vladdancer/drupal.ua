<?php

/**
 * implementation of hook_panels_layouts()
 */
function drua_960_12_onecol_panels_layouts() {
  $items['960_12_onecol'] = array(
    'title' => t('960/12 Single column'),
    'icon' => '960_12_onecol.png',
    'theme' => '960_12_onecol',
    'css' => '960_12_onecol.css',
    'panels' => array('middle' => t('Middle column')),
  );

  return $items;
}
