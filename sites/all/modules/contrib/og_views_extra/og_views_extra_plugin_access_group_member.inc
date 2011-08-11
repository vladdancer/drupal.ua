<?php
// $Id: og_views_extra_plugin_access_group_member.inc,v 1.1 2009/10/09 23:47:49 kscheirer Exp $
/**
 * @file
 *   Access plugin per group member.
 */

class og_views_extra_plugin_access_group_member extends views_plugin_access {

  function access($account) {
    $group = og_get_group_context();

    if (!$group) {
      return FALSE;
    }

    // count site admins as group members unless specifically excluded
    $admin_ok = ($this->options['membership'] != OG_VIEWSX_MEMBERS_ONLY);

    // get membership status in this group
    $member = og_is_group_member($group, $admin_ok);

    // are we asserting user is a member or non-member?
    return $this->options['membership'] ? $member : !$member;
  }

  function summary_title() {
    switch ($this->options['membership']) {
      case OG_VIEWSX_NOTMEMBER:
        return t('Not a Group Member');
      case OG_VIEWSX_MEMBER_OR_ADMIN:
        return t('Group Member or Site Admin');
      case OG_VIEWSX_MEMBERS_ONLY:
        return t('Group Member Only');
    }
  }

  function options_form(&$form, &$form_state) {
    $form['membership'] = array(
      '#type' => 'radios',
      '#title' => t('User is'),
      '#default_value' => $this->options['membership'],
      '#options' => array(t('NOT a member of the group'), t('Member of the group or admin'), t('Member of the group')),
      '#description' => t('Check whether user belongs to this group. Admin is defined as having the permission "administer nodes".'),
    );
  }

  function get_access_callback() {
    return array('og_views_extra_is_group_member', $this->options['membership']);
  }
}
