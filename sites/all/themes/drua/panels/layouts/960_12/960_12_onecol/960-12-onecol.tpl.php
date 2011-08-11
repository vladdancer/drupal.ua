<?php global $is_panel; $is_panel = TRUE; ?>
<div class="panel-display 960-12-onecol container-12" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  
  <div class="panel-panel panel-col-full panel-middle grid-12">
    <div class="inside"><?php print $content['middle']; ?></div>
  </div>
  
  <div class="clear"></div>
  
</div>
