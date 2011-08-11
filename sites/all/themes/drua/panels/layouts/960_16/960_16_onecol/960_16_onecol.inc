<?php

/**
 * implementation of hook_panels_layouts()
 */
function drua_960_16_onecol_panels_layouts() {
  $items['960_16_onecol'] = array(
    'title' => t('960/16 Single column'),
    'icon' => '960_16_onecol.png',
    'theme' => '960_16_onecol',
    'css' => '960_16_onecol.css',
    'panels' => array('middle' => t('Middle column')),
  );

  return $items;
}
