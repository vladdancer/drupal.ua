<?php
// $Id$

/**
 * Helper to implementation of hook_heartbeat_message_info().
 */
function _drua_heartbeat_heartbeat_message_info() {
  $messages = array();
  
  $messages['user_update_profile'] = array (
    'message' => '!user update profile',
    'message_concat' => '',
    'message_id' => 'user_update_profile',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
      'merge_separator_t' => '0',
      'merge_end_separator_t' => '0',
    ),
    'description' => 'User update profile',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
    ),
    'attachments' => 
    array (
    ),
  );
  
  $messages['og_user_join_group'] = array (
    'message' => '!user joined the "!group"',
    'message_concat' => '',
    'message_id' => 'og_user_join_group',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
      'merge_separator_t' => '0',
      'merge_end_separator_t' => '0',
    ),
    'description' => 'User joined the group',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
    ),
    'attachments' => 
    array (
    ),
  );
  
  $messages['profile_add_comment'] = array (
    'message' => '!username replied on !title',
    'message_concat' => '',
    'message_id' => 'profile_add_comment',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
      'merge_separator_t' => '0',
      'merge_end_separator_t' => '0',
    ),
    'description' => 'User replied on content',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
    ),
    'attachments' => 
    array (
    ),
  );
  
  $messages['profile_add_post'] = array (
    'message' => '!username add post !node_title to group',
    'message_concat' => '',
    'message_id' => 'profile_add_post',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
      'merge_separator_t' => '0',
      'merge_end_separator_t' => '0',
    ),
    'description' => 'User add post to group',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
    ),
    'attachments' => 
    array (
    ),
  );
  
  $messages['og_user_left_group'] = array (
    'message' => '!username left the "!group"',
    'message_concat' => '',
    'message_id' => 'og_user_left_group',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
      'merge_separator_t' => '0',
      'merge_end_separator_t' => '0',
    ),
    'description' => 'User left the group',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
    ),
    'attachments' => 
    array (
    ),
  );
  
  return $messages;
}
