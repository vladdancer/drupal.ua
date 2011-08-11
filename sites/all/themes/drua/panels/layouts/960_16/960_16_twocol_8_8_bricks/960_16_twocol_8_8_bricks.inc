<?php
// $Id: 960_16_twocol_8_8_bricks.inc,v 1.1 2009/10/23 02:39:53 pegleglax Exp $

/**
 * @file twocol_bricks.inc
 *
 * Implementation for the two column bricked layout
 */

/**
 * Implementation of hook_panels_layouts().
 */
function drua_960_16_twocol_8_8_bricks_panels_layouts() {
  $items['960_16_twocol_8_8_bricks'] = array(
    'title' => t('960/16 Two column 8-8 bricks'),
    'icon' => '960_16_twocol_8_8_bricks.png',
    'theme' => '960_16_twocol_8_8_bricks',
    'css' => '960_16_twocol_8_8_bricks.css',
    'panels' => array(
      'top' => t('Top'),
      'left_above' => t('Left above'),
      'right_above' => t('Right above'),
      'middle' => t('Middle'),
      'left_below' => t('Left below'),
      'right_below' => t('Right below'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

