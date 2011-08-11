<?php
// $Id: 960_16_twocol_8_8_stacked.inc,v 1.1 2009/10/23 02:39:53 pegleglax Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_twocol_8_8_stacked_panels_layouts() {
  $items['960_16_twocol_8_8_stacked'] = array(
    'title' => t('960/16 Two column 8-8 stacked'),
    'icon' => '960_16_twocol_8_8_stacked.png',
    'theme' => '960_16_twocol_8_8_stacked',
    'css' => '960_16_twocol_8_8_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
