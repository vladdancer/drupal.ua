Description
-----------
This module provides integration between Organic Groups and Webform  modules. It
allows users that have "edit own webform content" or "access own webform
results" to edit any webform content for which they are a group administrator.
It also corrects some issues with properly displaying setting group context when
editing webforms or viewing the submission results page.

Requirements
------------
Drupal 6.x
Organic Groups
Webform

Installation
------------
1. Copy the entire og_webform directory the Drupal sites/all/modules directory.

2. Login as an administrator. Enable the module in the "Administer" -> "Site
   Building" -> "Modules"

3. Assign a role the "edit own webform content" and "access own webform
   results" to a user role at "Administer" -> "User management" -> "Permissions"

Support
-------
Please use the issue queue for filing bugs with this module at
http://drupal.org/project/issues/og_webform

$Id: README.txt,v 1.1 2010/09/08 05:54:30 quicksketch Exp $