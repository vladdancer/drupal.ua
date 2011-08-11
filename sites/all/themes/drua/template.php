<?php

/**
 * Implementation of hook_theme().
 */
function drua_theme() {
  $content_profile_extra_templates = variable_get('content_profile_extra_templates', array());
  $content_profile_extra_templates[] = 'profile_header';
  variable_set('content_profile_extra_templates', $content_profile_extra_templates);

  return array(
   'sphinxsearch_search_box' => array(
      'arguments' => array('form' => NULL),
    ),
   'profile_header' => array(
      'arguments' => array('account' => NULL, 'teaser' => NULL),
      'template' => 'profile-header',
    ),
    'comment_form' => array(
       'arguments' => array('form' => NULL),
     ),
  );
}

/**
 * Preprocess page template.
 */
function drua_preprocess_page(&$vars) {
  $vars['search'] = drupal_get_form('sphinxsearch_search_box');
  $vars['user_menu_block'] = user_menu_block();
  $node = $vars['node'];

  if (arg(0) == 'gallery') {
    unset($vars['breadcrumb']);
    $vars['head_title'] = t('Sites Gallery') .' | '. variable_get('site_name', 'Drupal');
  }
  elseif (arg(0) == 'groups' && arg(1) == '') {
    $vars['head_title'] = t('Recent in groups') .' | '. variable_get('site_name', 'Drupal');
  }
  elseif (arg(0) == 'user' && is_numeric(arg(1))) {
    // Handle profile pages.
    unset($vars['breadcrumb']);
    unset($vars['tabs']);
    unset($vars['tabs2']);
    unset($vars['title']);
    $user = user_load(arg(1));

    // We need to link user picture to account if we're on inner profile pages.
    $teaser = (bool)arg(2);

    // Attach profile header to the page (picture, title and tabs).
    $vars['pre_content'] .= theme('profile_header', $user, $teaser);
  }

  if (!$user->uid && arg(0) == 'user' && !is_numeric(arg(2))) {
    unset($vars['breadcrumb']);
    unset($vars['tabs']);
    if (arg(1) == 'register') {
      $vars['title'] = t('Registration');
    }
  }
  
  // Determine if the current page is a panels page
  $vars['is_panels'] = panels_get_current_page_display() ? TRUE : FALSE;
}

/**
 * Implementation of hook_preprocess_node().
 */
function drua_preprocess_node(&$vars) {
  global $language;
  $node = $vars['node'];

  // Different time-date format for different languages.
  switch ($language->language) {
    case 'ru':
    case 'uk':
      $vars['date'] = format_date($node->created, 'custom', "j F, Y");
      break;
    case 'en':
      $vars['date'] = format_date($node->created, 'custom', "F jS, Y");
      break;
  }
  
  // REFACTOR: Document these.
  if ($node->type == 'website_showcase') {
    $node_path_arr = explode('/', $node->path);
    if ($node_path_arr[0] == 'content' && arg(0) != 'gallery') {
      drupal_goto('gallery/'. $node->nid); 
    }      
    $node->field_ws_screenshot[0]['view'] = l($node->field_ws_screenshot[0]['view'], $node->field_ws_url[0]['display_url'], array('html' => TRUE));
    $created_by_user = user_load($node->uid);

    $user_str = '<br clear="left"><br/>';
    if ($node->field_ws_author_url[0]['display_url'] != '') {
      $user_str .= l(strtoupper($created_by_user->name), $node->field_ws_author_url[0]['display_url'], array('attributes' => array('class' => 'showcase_info_link')));
    }
    else {
      $user_str .= l(strtoupper($created_by_user->name), 'users/'. $created_by_user->name, array('attributes' => array('class' => 'showcase_info_link')));
    }
    $node->username = $user_str;
    if ($node->field_ws_company_url[0]['view'] != '') {
      $node->field_ws_company_url[0]['view'] = '<br/>'. l($node->field_ws_company_url[0]['display_title'], $node->field_ws_company_url[0]['display_url'], array('attributes' => array('class' => 'showcase_info_link')));  
    }
    $node->created_text = t('Posted on') . ' ' . format_date($node->created, 'custom', 'l, F j, Y');
    //print $node->field_ws_screenshot[0]['view'];
    if ($GLOBALS['user']->uid == $node->uid || user_access('access content')) {
      $node->edit_link = '<br/>'. l(t('&laquo; Edit'), 'node/'. $node->nid .'/edit', array('html' => TRUE, 'attributes' => array('class' => 'showcase_info_link')));  ;  
    }
    else {
      $node->edit_link = '';
    }
  }

  if (module_exists('og')) {
    // Add group prefix.
    if (!$vars['page'] && og_is_group_post_type($node->type)) {
      if (!($page_node = menu_get_object() && og_is_group_type($page_node->type))) { // Do not add group prefix if we browse group nodes
        $og = $node->og_groups_both;
        
        if (!empty($og)) {
          foreach ($og as $gid => $group) {
            $og[$gid] = l($group, 'node/'. $gid);
            if ($translation = translation_node_get_translations($gid)) {
              if (isset($translation[$language->language])) {
                $og[$gid] = l($translation[$language->language]->title,
                	'node/'. $translation[$language->language]->nid);
              }
            }
            else {
              if ($group_node = node_load($gid)) {
                if ($group_node->tnid && $gid != $group_node->tnid) {
                  $translation = translation_node_get_translations($group_node->tnid);
                  if ($translation[$language->language]) {
                    $og[$gid] = l($translation[$language->language]->title,
                    	'node/'. $translation[$language->language]->nid);
                  }
                }
              }
            }
          }
          $prefix = implode(' : ', $og);
          $vars['title_prefix'] = $prefix;
        }
      }
    }

    // Submitter info.
    if (og_is_group_post_type($node->type) || og_is_group_type($page_node->type)) {
      $vars['submitted'] = $vars['name'] .' / <span class="date">'. $vars['date'] .'</span>';
    }
  }
}

/**
 * Implementation of hook_preprocess_comment().
 */
function drua_preprocess_comment(&$vars) {
  global $language;
  $comment = $vars['comment'];

  // Different time-date format for different languages.
  switch ($language->language) {
    case 'ru':
    case 'uk':
      $vars['date'] = format_date($comment->timestamp, 'custom', "j F, Y - H:i");
      break;
    case 'en':
      $vars['date'] = format_date($comment->timestamp, 'custom', "F jS, Y - H:i");
      break;
  }

  $vars['user'] = theme('username', $comment);
}

/**
 * Format a username.
 *
 * The same as standard, but renders smal avatar & doesn;t show "not veridied".
 */
function drua_username($object) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) .'...';
    }
    else {
      $name = $object->name;
    }

    $profile = content_profile_load('profile', $object->uid);
    if ($profile->field_image[0]) {
      $picture = $profile->field_image[0];
      $avatar = theme('imagecache', 'tiny', $picture['filepath'], $picture['data']['alt'], $picture['data']['title']);
    }

    if (user_access('access user profiles')) {
      $output .= l($avatar . $name, 'user/'. $object->uid, array('html' => TRUE, 'attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output .= $avatar . check_plain($name);
    }
    $output = '<span class="username">'. $output .'</span>';
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }
  }
  else {
    $output = check_plain(variable_get('anonymous', t('Anonymous')));
  }

  return $output;
}

/**
 * Implementation of hook_preprocess_block().
 */
function drua_preprocess_block(&$vars, $hook) {
  // Allow links in block titles.
  if ($vars['block']->title_link && $vars['block']->subject) {
    $vars['block']->subject = '<a href="'. check_url($vars['block']->title_link) .'">'. $vars['block']->subject .'</a>';
  }
}


/**
 * Preprocess user profile header template. There is pretty complex code to
 * output avatar and tabs, so, we need the special care here.
 */
function drua_preprocess_profile_header(&$vars) {
  $profile_vars = $vars['content_profile']->get_variables('profile', $vars['teaser'], TRUE);
  
  $vars['user_name'] = '';
  if (isset($profile_vars['field_first_name'][0]['value']) && !empty($profile_vars['field_first_name'][0]['value'])) {
    $vars['user_name'] = check_plain($profile_vars['field_first_name'][0]['value']) .' ';
  }
  if (isset($profile_vars['field_last_name'][0]['value']) && !empty($profile_vars['field_last_name'][0]['value'])) {
    $vars['user_name'] .= check_plain($profile_vars['field_last_name'][0]['value']);
  }
  
  $vars['user_login'] = ($vars['user_name'] ? ' <span class="profile-aka">aka</span> ' : '')
    . $vars['account']->name;
  $vars['tabs'] = theme('menu_local_tasks');
}

/**
 * Search box theming.
 */
function drua_sphinxsearch_search_box($form) {
  $form['inline']['submit']['#prefix'] = '<span class="button bsmall binner sblue"><span>';
  $form['inline']['submit']['#suffix'] = '</span></span>';
  return drupal_render($form);
}

/**
 * Top buttons block.
 */
function user_menu_block() {
  global $user, $language;

  if ($user->uid) {
    $menu = '<span class="button bsmall sgreen"><span>'. l($user->name, 'user') .'</span></span>&nbsp;&nbsp;&nbsp;'.
            '<span class="button bsmall sblue"><span>'. l(t('Tracker'), 'user/'. $user->uid .'/tracker') .'</span></span>&nbsp;'.
            '<span class="button bsmall sblue"><span>'. l(t('Bookmarks'), 'user/'. $user->uid .'/bookmarks') .'</span></span>&nbsp;'.
            '&nbsp;&nbsp;<span class="button bsmall sblue"><span>'. l(t('Log out'), 'logout') .'</span></span>';
  }
  else {
    $options = array(
    	'query' => array(
    		'destination' => drupal_get_path_alias(implode('/', arg())),
       ), 
    );
    $menu = '<span class="button bsmall sgreen"><span>'. l(t('Log in'), 'user/login', $options) .'</span></span>&nbsp;'.
            '<span class="button bsmall sred"><span>'. l(t('Register'), 'user/register', $options) .'</span></span>';
  }

  // Add language switcher.
  if (arg(0) == 'node' && arg(1) != '') {
    $node = node_load(arg(1));
    if ($node->tnid) {
      $translation = translation_node_get_translations($node->tnid);
    }
    $path = $_GET['q'];
  }
  else {
    $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
  }
  
  $languages = language_list('enabled');
  foreach ($languages[1] as $lang) {
    if ($lang->language != $language->language) {
      if (isset($translation[$lang->language]->nid)) {
        $path = 'node/'. $translation[$lang->language]->nid;
      }
      $menu .= '&nbsp;&nbsp;&nbsp;<span style="font-family: Helvetica, Arial, \'Liberation Sans\', FreeSans, sans-serif; font-size: 12px; line-height: 22px;">'.
        l(($lang->language == 'uk' ? t('Ukrainian language') : t('Russian language')), $path,
        array(
          'language' => $lang,
          'attributes' => array('class' => 'language-link', 'style' => 'color: white;'),
        )) .'</span>';
    }
  }

  return $menu;
}

/**
 * Theme comments form.
 */
function drua_comment_form($form) {
  // Remove author.
  if ($form['_author']) {
    unset($form['_author']);
  }

  // Handle filter slider.
  unset($form['comment_filter']['format']);
  $form['comment_filter'][1] = array(
    '#type' => 'value',
    '#value' => variable_get('filter_default_format', 1)
  );
  $tips = _filter_tips(variable_get('filter_default_format', 1), FALSE);
  $form['comment_filter']['format']['guidelines'] = array(
    '#title' => t('Formatting guidelines'),
    '#value' => theme('filter_tips', $tips, FALSE, $extra),
  );
  $form['comment_filter']['format']['#weight'] = 0.001;

  // Remove title from comments textarea and set it height to 5.
  $form['comment_filter']['comment']['#title'] = '';
  $form['comment_filter']['comment']['#rows'] = '5';

  $form['mail']['#description'] = '';

  // Place code and styles to animate the slider.
  $form['comment_filter']['format']['guidelines']['#prefix'] = '<div class="guidelines nolink">';
  $form['comment_filter']['format']['guidelines']['#suffix'] = '<a href="#" class="guidelink minor">'. t('Formatting details') .'</a></div>';
  $form['#suffix'] .= '<script type="text/javascript">
      $(".guidelines.nolink").removeClass(\'nolink\');

      $(".guidelink").click(function(){
        $(this).siblings(".tips").slideToggle("fast");
        $(this).parent().toggleClass("expanded")
        return false;
      });
    </script>';
  $form['#suffix'] .= '<div class="cleardiv"></div>';

  // Prettyfy notifier.
  unset($form['notify']['#description']);

  $output .= drupal_render($form);
  return $output;
}

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function drua_preprocess_comment_wrapper(&$vars) {
  if ($vars['content'] && $vars['node']->type != 'forum') {
    $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
  }
  if (!user_access('post comments')) {
    $vars['content'] .= '<div class="messages warning mt40">'. theme('comment_post_forbidden', $vars['node']) .'</div>';
  }
}

/**
 * Checks if the current page is panel. This global value is being set in templates.
 * @TODO: Find a better way to do this without touching templates.
 */
if (module_exists('panels')) {
  function is_panel() {
    global $is_panel;
    return $is_panel === TRUE;
  }
}


/**
 * Profile theming 
 */

/**
 * Output user groups (in string).
 */
function drua_preprocess_views_view_unformatted__profile_group__block_1(&$vars) {
  $output = '';
  $first = TRUE;
  foreach ($vars['view']->result as $row) {
    if ($first) {
      $first = FALSE;
    }
    else {
      $output .= ', ';
    }
    $output .= l($row->node_title, 'node/'. $row->nid);
  }
  $vars['full_rows'] = $output;
}


/**
 * User profile: Bookmarks.
 */
function drua_preprocess_flag(&$vars) {
  if ((isset($_REQUEST['destination']) && arg(0) == 'flag' && arg(2) == 'bookmarks'
    && (strpos($_REQUEST['destination'], 'user/') === 0)) || (arg(0) == 'user' && arg(2) == '')) {
    $vars['link_text'] = '&nbsp;';
  }
}


/**
 * User profile: Bookmarks.
 * Remove references to other people's profiles
 */
function drua_preprocess_views_view_field__profile_bookmarks__block_1__ops(&$vars) {
  global $user;
  if (!(arg(0) == 'user' && $user->uid == arg(1) && arg(2) == '')) {
    $vars['output'] = '<div class="img-flag-action">&nbsp;</div>';
  }
}


/**
 * Display a message to a user if they are not allowed to fill out a form.
 *
 * @param $node
 *   The webform node object.
 * @param $teaser
 *   If this webform is being displayed as the teaser view of the node.
 * @param $page
 *   If this webform node is being viewed as the main content of the page.
 * @param $submission_count
 *   The number of submissions this user has already submitted. Not calculated
 *   for anonymous users.
 * @param $limit_exceeded
 *   Boolean value if the submission limit for this user has been exceeded.
 * @param $allowed_roles
 *   A list of user roles that are allowed to submit this webform.
 */
function drua_webform_view_messages($node, $teaser, $page, $submission_count, $limit_exceeded, $allowed_roles) {
  global $user;

  $type = 'notice';
  $cached = $user->uid == 0 && variable_get('cache', 0);

  // If not allowed to submit the form, give an explanation.
  if (array_search(TRUE, $allowed_roles) === FALSE && $user->uid != 1) {
    if (empty($allowed_roles)) {
      // No roles are allowed to submit the form.
      $message = t('Submissions for this form are closed.');
    }
    elseif (isset($allowed_roles[2])) {
      // The "authenticated user" role is allowed to submit and the user is currently logged-out.
      $login = url('user/login', array('query' => drupal_get_destination()));
      $register = url('user/register', array('query' => drupal_get_destination()));
      if (variable_get('user_register', 1) == 0) {
        $message = t('You must <a href="!login">login</a> to view this form.', array('!login' => $login));
      }
      else {
        $message = t('You must <a href="!login">login</a> or <a href="!register">register</a> to view this form.', array('!login' => $login, '!register' => $register));
      }
    }
    else {
      // The user must be some other role to submit.
      $message = t('You do not have permission to view this form.');
    }
  }

  // If the user has submitted before, give them a link to their submissions.
  if ($submission_count > 0 && $node->webform['submit_notice'] == 1 && !$cached) {
    if (empty($message)) {
      $message = t('You have already submitted this form.') .' '.
        t('<a href="!url">View your previous submissions</a>.', array('!url' => url('node/'. $node->nid .'/submissions')));
    }
    else {
      $message .= ' '. t('<a href="!url">View your previous submissions</a>.', array('!url' => url('node/'. $node->nid .'/submissions')));
    }
  }

  if ($page && isset($message)) {
    drupal_set_message($message, $type);
  }
}


/**
 * User profile: Bookmarks.
 * Remove references to other people's profiles
 */
function drua_preprocess_views_view_field__profile_activity__block_1__message_id(&$vars) {
  $vars['output'] = '<div class="profile-activity-icon-'. $vars['output'] .'">&nbsp;</div>';
}


/**
 * Theming term name.
 * Fix translate term. 
 */
function drua_preprocess_views_view_field__og_most_popular_groups_by_term__tid(&$vars) {
  global $language;
  $vars['output'] = l(tt('taxonomy:term:'. $vars['row']->term_data_tid .':name',
    $vars['row']->term_data_name, $language->language),
    'taxonomy/term/'. $vars['row']->term_data_tid);
}

