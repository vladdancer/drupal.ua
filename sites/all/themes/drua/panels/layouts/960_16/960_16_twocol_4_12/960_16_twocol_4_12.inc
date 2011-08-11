<?php
// $Id: 960_16_twocol_4_12.inc,v 1.1 2009/10/23 02:39:53 pegleglax Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_twocol_4_12_panels_layouts() {
  $items['960_16_twocol_4_12'] = array(
    'title' => t('960/16 Two column 4-12'),
    'icon' => '960_16_twocol_4_12.png',
    'theme' => '960_16_twocol_4_12',
    'css' => '960_16_twocol_4_12.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
