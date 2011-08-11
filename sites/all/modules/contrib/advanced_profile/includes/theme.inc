<?php
// $Id: theme.inc,v 1.2.4.15 2010/04/05 03:34:58 michellec Exp $

/**
 * @file
 * Holds theme and preprocess functions.
 */

// PREPROCESS FUNCTIONS ******************************************************/

function template_preprocess_advanced_profile_visitors(&$variables) {
  $visitors = advanced_profile_visitors($variables['account']->uid);

  if (!empty($visitors)) {
    $variables['visitors'] = theme_item_list($visitors);
  }
  else {
    $variables['visitors'] = t("No recent visitors.");
  }
}

function advanced_profile_preprocess_user_profile(&$variables) {
  $variables['author_pane'] = theme('author_pane', $variables['account'], 'advanced_profile');
  $variables['profile_visitors'] = theme('advanced_profile_visitors', $variables['account']);
}

function advanced_profile_preprocess_author_pane(&$variables) {
  if (!empty($variables['caller']) && $variables['caller'] == 'advanced_profile') {
    // If we are calling the Author Pane, use our template.
    $variables['template_files'][] = 'advanced_profile_author-pane';
  }
}

function advanced_profile_preprocess_node(&$variables) {
  if (variable_get('advanced_profile_redirect_from_node', TRUE)) {
    $node = $variables['node'];
    if ($node->type == 'uprofile' && arg(0) == 'node' && arg(1) == $node->nid && arg(2) == "") {
      // If we are postitive we are on node/N where N is the NID of a uprofile
      // node, then redirect to the user profile page instead.
      drupal_goto("user/$node->uid");
    }
  }
}