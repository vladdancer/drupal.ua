<?php
// $Id: widget.tpl.php,v 1.1.2.16 2010/11/11 09:28:48 marvil07 Exp $
/**
 * @file
 * widget.tpl.php
 *
 * Plain widget theme for Vote Up/Down
 */
?>
<?php if ($show_links): ?>
  <div class="vud-widget vud-widget-plain" id="<?php print $id; ?>">
    <a href="<?php print $link_up; ?>" rel="nofollow" class="<?php print $link_class_up; ?>">
      <span class="<?php print $class_up; ?>" title="<?php print t('Vote up!'); ?>"></span>
      <div class="element-invisible"><?php print t('Vote up!'); ?></div>
    </a>
    <a href="<?php print $link_down; ?>" rel="nofollow" class="<?php print $link_class_down; ?>">
      <span class="<?php print $class_down; ?>" title="<?php print t('Vote down!'); ?>"></span>
      <div class="element-invisible"><?php print t('Vote down!'); ?></div>
    </a>
  </div>
<?php endif; ?>
