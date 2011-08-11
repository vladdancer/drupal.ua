<?php
// $Id: uc_catalog.inc,v 1.1.2.7 2010/11/01 01:10:38 damienmckenna Exp $

/**
 * @file
 * Integration file for uc_catalog.module.
 */

/**
 * Implements hook_nodewords_type_id().
 */
function uc_catalog_nodewords_type_id(&$result, $arg) {
  if ($arg[0] == 'catalog' && is_numeric($arg[1])) {
    $result['type'] = NODEWORDS_TYPE_TERM;
    $result['id'] = $arg[1];
  }
}
