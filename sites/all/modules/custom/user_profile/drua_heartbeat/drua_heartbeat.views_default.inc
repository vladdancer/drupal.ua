<?php
// $Id$

/**
 * Implementation of hook_views_default_views().
 */
function drua_heartbeat_views_default_views() {
  $views = array();
  
  $view = new view;
  $view->name = 'profile_activity';
  $view->description = '';
  $view->tag = 'profile';
  $view->view_php = '';
  $view->base_table = 'heartbeat_activity';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Типово', 'default');
  $handler->override_option('relationships', array(
    'message_id' => array(
      'label' => 'Activity message id',
      'required' => 1,
      'id' => 'message_id',
      'table' => 'heartbeat_activity',
      'field' => 'message_id',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'message_id' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '[message_id]',
        'make_link' => 0,
        'path' => '',
        'link_class' => '[message_id]',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 1,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'message_id',
      'table' => 'heartbeat_activity',
      'field' => 'message_id',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
    'message' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'message',
      'table' => 'heartbeat_activity',
      'field' => 'message',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
    'timestamp' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'custom',
      'custom_date_format' => 'j.m.Y H:i',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'heartbeat_activity',
      'field' => 'timestamp',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'heartbeat_activity',
      'field' => 'timestamp',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'uid_requested' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'Все',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid_requested',
      'table' => 'heartbeat_activity',
      'field' => 'uid_requested',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'ad' => 0,
        'advpoll_ranking' => 0,
        'advpoll_binary' => 0,
        'group' => 0,
        'news' => 0,
        'page' => 0,
        'post' => 0,
        'profile' => 0,
        'simplenews' => 0,
        'webform' => 0,
        'website_showcase' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '4' => 0,
        '6' => 0,
        '1' => 0,
        '3' => 0,
        '7' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
      'validate_argument_group_node_type' => array(
        'group' => 0,
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'access_type' => array(
      'operator' => '=',
      'value' => array(
        'access' => 'PublicHeartbeat',
        'value' => '',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'access_type',
      'table' => 'heartbeat_activity',
      'field' => 'access_type',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
    'language' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'language',
      'table' => 'heartbeat_activity',
      'field' => 'language',
      'override' => array(
        'button' => 'Переназначити',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Recent activities');
  $handler->override_option('empty', 'empty text');
  $handler->override_option('empty_format', '2');
  $handler = $view->new_display('block', 'Блок', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;
  
  return $views;
}
