<?php

/**
 * Implementation of hook_content_default_fields().
 */
function answers_content_default_fields() {
  $fields = array();

  // Exported field: field_best_answer
  $fields['question-field_best_answer'] = array(
    'field_name' => 'field_best_answer',
    'type_name' => 'question',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'email_plain' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'email_html' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'commentreference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'commentreference',
    'active' => '1',
    'comments_from_node' => 1,
    'comments_limit' => '0',
    'comments_order' => '2',
    'comments_status' => '0',
    'widget' => array(
      'label' => 'Best Answer',
      'weight' => '-3',
      'description' => '',
      'type' => 'commentreference_select',
      'module' => 'commentreference',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Best Answer');

  return $fields;
}
