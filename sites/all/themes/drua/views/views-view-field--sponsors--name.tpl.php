<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>

<?php //print_r ($row->term_data_name);
if (!isset($GLOBALS['_sponsors_terms_my_arr'])) {
  $GLOBALS['_sponsors_terms_my_arr'] = array();
}
//echo '<br/><pre>'; print_r ($GLOBALS['_sponsors_terms_my_arr']); echo '</pre>';
?>

<?php if (!in_array($row->term_data_name, $GLOBALS['_sponsors_terms_my_arr'])): ?>
<?php print '<h2>'.$row->term_data_name.'</h2>'; ?>
<?php endif; ?>
<?php if (in_array($row->term_data_name, $GLOBALS['_sponsors_terms_my_arr'])): ?>
<?php print '<br/><br/>'; ?>
<?php endif; ?>
<?php $GLOBALS['_sponsors_terms_my_arr'][] = $row->term_data_name; ?>