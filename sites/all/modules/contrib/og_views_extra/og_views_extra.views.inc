<?php
// $Id: og_views_extra.views.inc,v 1.1 2009/10/09 23:47:49 kscheirer Exp $

/**
 * @file
 * Register this plugin via the Views 2 API.
 *
 */

/**
 * Implementation of hook_views_plugins().
 */
function og_views_extra_views_plugins() {
  return array(
    'access' => array(
      'group_member' => array(
        'title' => t('Group Membership'),
        'help' => t('Member of the current organic group'),
        'handler' => 'og_views_extra_plugin_access_group_member',
        'help topic' => 'access-none',
        'uses options' => TRUE,
      ),
    )
  );
}
