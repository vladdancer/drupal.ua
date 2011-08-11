<?php
// $Id: 960_16_twocol_12_4.inc,v 1.1 2009/10/23 02:39:52 pegleglax Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_twocol_12_4_panels_layouts() {
  $items['960_16_twocol_12_4'] = array(
    'title' => t('960/16 Two column 12-4'),
    'icon' => '960_16_twocol_12_4.png',
    'theme' => '960_16_twocol_12_4',
    'css' => '960_16_twocol_12_4.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
