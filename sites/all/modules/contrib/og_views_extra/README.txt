/* $Id: README.txt,v 1.2 2010/03/11 23:17:08 kscheirer Exp $ */

-- SUMMARY --

This module is an add-on to Views. It provides an access plugin: Member of the 
current group, which detects whether the current user is member of the current 
group.

OG Views Extra doesn't work with Views arguments! 
This access plugin can only work when then view is being displayed in a group 
context. For example on the group node, or on a node that belongs to a group.

If the group node is an argument, views and og_views already provide a validation 
checkbox to ensure that the current user is a member of the current group OR the 
current user is a site admin.

So why install this module? If you need finer-grained control. The available 
user options:
 * Not a Group Member
 * Group Member or Site Admin
 * Group Member Only 

There are cases when you really just want to make sure the user is actually a 
member of the group. Also, I found it useful to be able to explicitly check for 
the case where the user is NOT a member of the group - and thereby be able to 
show a completely different view to non-members.


-- REQUIREMENTS --

The Organic Groups (og) module, Views (views) are required.


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- USAGE --

When editing a view, under the Basic Settings area, you will see by default
Access: Unrestricted. Click "Unrestricted" and you can choose to limit access
by Group Membership. Once you have selected this as the method to restrict
access, click the settings link or the Gear icon by Access, and you will be
able to select how to restict access.

NOT a member of the group - the user must not be a member of the group.

Member of the group or admin - the user must be a member of the group
or a site administrator (has permission 'administer nodes').

Member of the group - the user must be an actual member of the group.


-- CONTACT --

Current maintainers:
* Karl Scheirer (kscheirer) - http://drupal.org/user/128191
