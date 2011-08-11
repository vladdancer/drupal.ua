<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function answers_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:questions
  $menu_links['primary-links:questions'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'questions',
    'router_path' => 'questions',
    'link_title' => 'Q&A',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Q&A');


  return $menu_links;
}
