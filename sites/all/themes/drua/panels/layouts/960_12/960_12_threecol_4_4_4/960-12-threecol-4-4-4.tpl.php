<?php global $is_panel; $is_panel = TRUE; ?>
<div class="panel-display 960-12-threecol-4-4-4 container-12" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  
  <div class="panel-panel panel-col-first panel-left grid-4">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>

  <div class="panel-panel panel-col panel-middle grid-4">
    <div class="inside"><?php print $content['middle']; ?></div>
  </div>

  <div class="panel-panel panel-col-last panel-right grid-4">
    <div class="inside"><?php print $content['right']; ?></div>
  </div>
  
  <div class="clear"></div>
  
</div>
