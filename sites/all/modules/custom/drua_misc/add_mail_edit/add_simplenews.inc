<?php
// $Id$

/**
 * Implementation of hook_mailkeys().
 */
function simplenews_mailkeys() {
  return array(
    'subscribe_subscribed' => t('Letter subscription already signed on user.'),
    'subscribe_unsubscribed' => t('Letter subscription for non-subscribers.'),
    'unsubscribe_subscribed' => t('Unsubscribing for subscribed users.'),
    'unsubscribe_unsubscribed' => t('Unsubscribe to non-subscribers.'),
  );
}


/**
 * Implementation of hook_mail_edit_tokens_list().
 */
function simplenews_mail_edit_tokens_list($mailkey, $options = array()) {
  $tokens = array();
  switch ($mailkey) {
    case 'subscribe_subscribed':
    case 'subscribe_unsubscribed':
    case 'unsubscribe_subscribed':
    case 'unsubscribe_unsubscribed':
      $tokens['!newsletter_name'] = 'Title of the subscription';
      $tokens['!confirm_subscribe_url'] = 'URL subscription confirmation';
      $tokens['!confirm_unsubscribe_url'] = 'URL unsubscribe';
      $tokens['!username'] = "User's username";
      $tokens['!username_themed'] = "User's username (themed)";
      $tokens['!site'] = 'Site name';
      $tokens['!login_url'] = 'One time login URL for password reset';
      $tokens['!uri_brief'] = "Website's URL without the leading http://";
      $tokens['!uri'] = "Website's URL";
      $tokens['!mailto'] = "User's Email address (email address to which this email is being sent to)";
      $tokens['!date'] = "Date and time when this email is sent";
      break;
  }
  return $tokens;
}


/**
 * Implementation of hook_mail_edit_tokens_value().
 */
function simplenews_mail_edit_tokens_value($mailkey, $mail, $options = array()) {
  global $base_url;
  
  $form_values = add_mail_processing_simplenews_subscription_form('get');
  $account = (object)array('mail' => drupal_strtolower($form_values['value']['mail']));
  $count = 0;
  $tid = 0;
  foreach ($form_values['value']['newsletters'] as $i_tid => $check) {
    if ($check) {
      if ($count == $form_values['value']['current']) {
        $tid = taxonomy_get_term($i_tid);
        $form_values['value']['current'] ++;
        break;
      }
      else {
        $count ++;
      }
    }
  }
  $context['newsletter'] = $tid;
  $context['account'] = simplenews_get_subscription($account);
  $tokens = simplenews_mail_tokens(
    $context['account'],
    $context,
    is_object($context['account']->language) ? $context['account']->language : language_default()
  );

  $account = user_load(array('mail' => $account->mail));
  $tokens['!username_themed'] = strip_tags(theme('username', $account, array('plain' => TRUE)));
  $tokens['!username'] = $account->name;
  return $tokens;
}


/**
 * Implementation of hook_mail_edit_text().
 */
function simplenews_mail_edit_text($mailkey, $langcode) {
  $return = array();
  $return['subject'] = _simplenews_mail_text($mailkey .'_subject', $langcode);
  $return['body'] = _simplenews_mail_text($mailkey .'_body', $langcode);
  return $return;
}


/**
 * Default text.
 */
function _simplenews_mail_text($mailkey, $langcode) {

  $variables = simplenews_mail_edit_tokens_value($mailkey);
  
  switch ($key) {
    case 'subscribe_subscribed_subject':
    case 'rsubscribe_unsubscribed_subject':
    case 'unsubscribe_subscribed_subject':
    case 'unsubscribe_unsubscribed_subject':
      return t('Confirmation for !newsletter_name from !site', $variables, $langcode);
    
    case 'subscribe_subscribed_body':
      return t("We have received a request for subscription of !mailto to the !newsletter_name on !site website at !uri. To confirm this subscription please use the link below.\n\n !confirm_subscribe_url", $variables, $langcode);

    case 'subscribe_unsubscribed_body':
      return t("We have received a request for subscription of !mailto to the !newsletter_name on !site website at !uri. However, this email is already subscribed to this newsletter. If you intended to unsubscribe please visit our site: !uri", $variables, $langcode);

    case 'unsubscribe_subscribed_body':
      return t("We have received a request to unsubscribe !mailto from the !newsletter_name on !site website at !uri. To confirm this unsubscription please use the link below.\n\n !confirm_unsubscribe_url", $variables, $langcode);

    case 'unsubscribe_unsubscribed_body':
      return t("We have received a request to unsubscribe !mailto from the !newsletter_name on !site website at !uri. However, this email is not subscribed to this newsletter. If you intended to subscribe please visit our site: !uri", $variables, $langcode);
  }
}
