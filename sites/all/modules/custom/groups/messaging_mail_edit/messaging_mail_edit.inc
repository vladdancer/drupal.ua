<?php
// $Id$

/**
 * Implementation of hook_mailkeys().
 */
function messaging_mail_edit_mailkeys() {
  return array(
    'messaging_notifications' => t('Letter sent immediately to the user about changes in the group.'),
    'messaging_notifications-digest-short' => t('A brief digest of developments in the group.'),
    'messaging_notifications-digest-long' => t('Detailed digest of developments in the group.'),
  );
}


/**
 * Implementation of hook_mail_edit_tokens_list().
 */
function messaging_mail_edit_mail_edit_tokens_list($mailkey, $options = array()) {
  $tokens = array();
  switch ($mailkey) {
    case 'messaging_notifications':
    case 'messaging_notifications-digest-short':
    case 'messaging_notifications-digest-long':
      $tokens['!username'] = "User's username";
      $tokens['!username_themed'] = "User's username (themed)";
      $tokens['!site'] = 'Site name';
      $tokens['!uri'] = "Website's URL";
      $tokens['!uri_brief']= "Website's URL without the leading http://";
      $tokens['!date'] = "Date and time when this email is sent";
      
      $tokens['!group_name'] = 'Group name';
      $tokens['!group_title_url'] = 'Title and a link to the group';
      $tokens['!user_profile_edit_subscription'] = 'Link to the editing of the subscription profile';
      $tokens['!events_node_title_urls_br'] = 'List of events in the group, consisting of headings and links, divided by BR';
      $tokens['!events_node_teaser_url_br'] = 'List of events in the group, consisting of teaser so divided BR';
      break;
  }
  return $tokens;
}


/**
 * Implementation of hook_mail_edit_tokens_value().
 */
function messaging_mail_edit_mail_edit_tokens_value($mailkey, $mail, $options = array()) {
  $tokens = $mail['params']['message_tokens'];  //messaging_mail_edit_send_msg();
  $language = $mail['language'];
  $tokens['!site'] = variable_get('site_name', 'Drupal');
  $tokens['!date'] = format_date(time(), 'medium', '', NULL, $language->language);
  $tokens['!uri'] = url('', array('absolute' => TRUE, 'language' => $language));
  $tokens['!uri_brief'] = preg_replace('!^https?://!', '', $vars['!uri']);
  return $tokens;
}


/**
 * Implementation of hook_mail_edit_text().
 */
function messaging_mail_edit_mail_edit_text($mailkey, $langcode) {
  $return = array();
  $return['subject'] = _messaging_mail_edit_mail_text($mailkey .'_subject', $langcode);
  $return['body'] = _messaging_mail_edit_mail_text($mailkey .'_body', $langcode);
  return $return;
}


/**
 * Default text.
 */
function _messaging_mail_edit_mail_text($mailkey, $language) {
  $variables = messaging_mail_edit_mail_edit_tokens_value($mailkey);
  $langcode = isset($language) ? $language->language : NULL;
  switch ($mailkey) {
    case 'messaging_notifications_subject':
    case 'messaging_notifications-digest-short_subject':
    case 'messaging_notifications-digest-long_subject':
      return t('!site subscription update for !username', $variables, $langcode);
    
    case 'messaging_notifications_body':
    case 'messaging_notifications-digest-short_body':
    case 'messaging_notifications-digest-long_body':
      return t("!events_node_title_urls_br\n\n Edit subscriptions !user_profile_edit_subscription", $variables, $langcode);
  }
}
