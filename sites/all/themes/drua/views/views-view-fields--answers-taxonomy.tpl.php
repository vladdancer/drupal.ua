<?php
// $Id: views-view-fields--answers-taxonomy.tpl.php, 16.03.2010 13:05:21 seaji Exp $

/**
  * @file
    * Taxonomy listing of questions view themization
    *
   * - $view: The view in use.
   * - $fields: an array of $field objects. Each one contains:
   *   - $field->content: The output of the field.
   *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
   *   - $field->class: The safe class id to use.
   *   - $field->handler: The Views field handler object controlling this field. Do not use
   *     var_export to dump this object, as it can't handle the recursion.
   *   - $field->inline: Whether or not the field should be inline.
   *   - $field->inline_html: either div or span based on the above flag.
   *   - $field->separator: an optional separator that may appear before a field.
   * - $row: The raw result object from the query, with all data it fetched.
   *
   */


  // dsm($fields);
   $comment_count = format_plural($fields['comment_count']->raw, '1 answer', '@count answers');
   $comment_count_text = l($comment_count, 'node/'.$fields['nid']->raw, array('fragment' => 'answers'));
   $last_comment = t('(Last @timeago ago)', array('@timeago' => $fields['last_comment_timestamp']->content));
  ?>
  <div class="recent_question_row">
    <div class="recent_question_row_title">
      <?php print $fields['question_title']->content ?>
      <?php
        if($fields['tid']->content) {
          print ' → '. $fields['tid']->content;
        }
      ?>
    </div>
    <div class="recent_question_row_info">
      <span class="user_name"><?php print $fields['name_1']->content; ?></span>
      <?php if($fields['comment_count']->raw): ?>
      <span class="comment_count"><?php print $comment_count_text .' '. $last_comment; ?></span>
      <?php else: ?>
      <span class="comment_count"><?php print l(t('Add answer'), 'node/'.$fields['nid']->raw, array('fragment' => 'answers')); ?></span>
      <?php endif; ?>
    </div>
  </div>
  <?php
    unset($fields['question_title']);
    unset($fields['tid']);
    unset($fields['name_1']);
    unset($fields['comment_count']);
    unset($fields['last_comment_timestamp']);
    unset($fields['nid']);

    if(is_array($fields)) {
  ?>
  <?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
      <?php print $field->separator; ?>
    <?php endif; ?>

    <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
      <?php if ($field->label): ?>
        <label class="views-label-<?php print $field->class; ?>">
          <?php print $field->label; ?>:
        </label>
      <?php endif; ?>
        <?php
        // $field->element_type is either SPAN or DIV depending upon whether or not
        // the field is a 'block' element type or 'inline' element type.
        ?>
        <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
    </<?php print $field->inline_html;?>>
  <?php endforeach;
    }
  ?>
