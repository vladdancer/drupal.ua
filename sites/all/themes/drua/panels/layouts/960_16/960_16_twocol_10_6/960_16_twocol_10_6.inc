<?php
// $Id: 960_16_twocol_10_6.inc,v 1.1 2009/10/23 02:39:53 pegleglax Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_twocol_10_6_panels_layouts() {
  $items['960_16_twocol_10_6'] = array(
    'title' => t('960/16 Two column 10-6'),
    'icon' => '960_16_twocol_10_6.png',
    'theme' => '960_16_twocol_10_6',
    'css' => '960_16_twocol_10_6.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}
