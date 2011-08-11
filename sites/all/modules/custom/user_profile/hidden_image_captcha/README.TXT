Installation:
0. Before installing the module, ensure that you have installed and configured Image Captcha module.
1. Put module to Drupal's module directory.
2. Enable it at admin/build/modules.
3. Enable it where you want in "Challenge type per form" field at admin/user/captcha
4. Enjoy :)

FAQ:
Q: Module does not work. Why?
A: Make sure that your theme's page.tpl.php has this line before </body> tag:
<?php print $closure ?>