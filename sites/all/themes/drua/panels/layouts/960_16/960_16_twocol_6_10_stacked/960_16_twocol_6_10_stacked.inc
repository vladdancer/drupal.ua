<?php
// $Id: 960_16_twocol_10_6_stacked.inc,v 1.1 2009/10/23 02:39:51 pegleglax Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_twocol_6_10_stacked_panels_layouts() {
  $items['960_16_twocol_6_10_stacked'] = array(
    'title' => t('960/16 Two column 6-10 stacked'),
    'icon' => '960_16_twocol_6_10_stacked.png',
    'theme' => '960_16_twocol_6_10_stacked',
    'css' => '960_16_twocol_6_10_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
