<?php
// $Id$

/**
 * Helper to implementation of hook_rules_defaults().
 */
function _drua_heartbeat_rules_defaults() {

  return array (
    'rules' => 
    array (
      'rules_2' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_og_user_insert',
        '#label' => 'User joined the group',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'profile',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Logs default activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_param',
                3 => 'nid_target_param',
                4 => 'message_id_param',
                5 => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => 
            array (
              'uid_param' => '[account:uid]',
              'uid_target_param' => '[group:author-uid]',
              'nid_param' => '[group:nid]',
              'nid_target_param' => '[group:nid]',
              'message_id_param' => 'og_user_join_group',
              'variables_param' => '@user=|=[account:user-name-url]-|-@group=|=[group:title]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'account',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'group',
                  ),
                  'nid_param' => 
                  array (
                    0 => 'group',
                  ),
                  'nid_target_param' => 
                  array (
                    0 => 'group',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'account',
                    1 => 'group',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_3' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_og_user_delete',
        '#label' => 'User left the group',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'profile',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Logs default activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_param',
                3 => 'nid_target_param',
                4 => 'message_id_param',
                5 => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => 
            array (
              'uid_param' => '[account:uid]',
              'uid_target_param' => '[group:author-uid]',
              'nid_param' => '[group:nid]',
              'nid_target_param' => '[group:nid]',
              'message_id_param' => 'og_user_left_group',
              'variables_param' => '@username=|=[account:user-name-url]-|-@group=|=[group:title]',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'variables_param' => 
                  array (
                    0 => 'account',
                    1 => 'group',
                  ),
                  'uid_param' => 
                  array (
                    0 => 'account',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'group',
                  ),
                  'nid_param' => 
                  array (
                    0 => 'group',
                  ),
                  'nid_target_param' => 
                  array (
                    0 => 'group',
                  ),
                ),
                'rules_input_evaluator_php' => 
                array (
                  'variables_param' => 
                  array (
                    0 => 'group',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_4' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_comment_publish',
        '#label' => 'User wrote in the topic',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'profile',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => 
            array (
              'uid_param' => '[comment_author:uid]',
              'uid_target_param' => '[node_author:uid]',
              'nid_param' => '[comment:comment-cid]',
              'nid_target_param' => '[comment:comment-nid]',
              'message_id_param' => 'profile_add_comment',
              'variables_param' => '@username=|=[comment_author:user-name-url]-|-@title=|=[node:title-link]',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'variables_param' => 
                  array (
                    0 => 'comment_author',
                    1 => 'node',
                  ),
                  'uid_param' => 
                  array (
                    0 => 'comment_author',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'node_author',
                  ),
                  'nid_param' => 
                  array (
                    0 => 'comment',
                  ),
                  'nid_target_param' => 
                  array (
                    0 => 'comment',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => 
            array (
              'label' => 'Logs default activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_param',
                3 => 'nid_target_param',
                4 => 'message_id_param',
                5 => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'rules_5' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'User update profile',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'profile',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#info' => 
            array (
              'label' => 'Updated content is Профіль',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Матеріали',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => 
            array (
              'type' => 
              array (
                'profile' => 'profile',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => 
            array (
              'uid_param' => '[author:uid]',
              'uid_target_param' => '[author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '',
              'message_id_param' => 'user_update_profile',
              'variables_param' => '@user=|=[author:user-name-url]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'variables_param' => 
                  array (
                    0 => 'author',
                  ),
                  'uid_param' => 
                  array (
                    0 => 'author',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'author',
                  ),
                  'nid_param' => 
                  array (
                    0 => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => 
            array (
              'label' => 'Logs default activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_param',
                3 => 'nid_target_param',
                4 => 'message_id_param',
                5 => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'rules_6' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'User add post to group',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => 
        array (
          0 => 'profile',
        ),
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Created content is Webform або Вебсайт до галереї або Група або Новини або Опитування двійкове або Опитування з рейтингом або Пост або Сторінка',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Матеріали',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => 
            array (
              'type' => 
              array (
                'webform' => 'webform',
                'website_showcase' => 'website_showcase',
                'group' => 'group',
                'news' => 'news',
                'advpoll_binary' => 'advpoll_binary',
                'advpoll_ranking' => 'advpoll_ranking',
                'post' => 'post',
                'page' => 'page',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => 
        array (
          1 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Logs default activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_param',
                3 => 'nid_target_param',
                4 => 'message_id_param',
                5 => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => 
            array (
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[user:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'profile_add_post',
              'variables_param' => '@username=|=[author:user-name-url]-|-@node_title=|=[node:title-link]-|-@og_name=|=[node:ogname]-|-@og_alias=|=[node:ogalias]',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'variables_param' => 
                  array (
                    0 => 'node',
                    1 => 'author',
                  ),
                  'uid_param' => 
                  array (
                    0 => 'user',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'user',
                  ),
                  'nid_param' => 
                  array (
                    0 => 'node',
                  ),
                  'nid_target_param' => 
                  array (
                    0 => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}
