<?php global $is_panel; $is_panel = TRUE; ?>
<div class="panel-display 960-12-twocol-9-3-stacked container-12" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  
  <div class="panel-panel panel-col-full panel-top grid-12">
    <div class="inside"><?php print $content['top']; ?></div>
  </div>
  
  <div class="clear"></div>
  
  <div class="panel-panel panel-col-first panel-left grid-9">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>
  <div class="panel-panel panel-col-last panel-right grid-3">
    <div class="inside"><?php print $content['right']; ?></div>
  </div>
  
  <div class="clear"></div> 

  <div class="panel-panel panel-col-full panel-bottom grid-12">
    <div class="inside"><?php print $content['bottom']; ?></div>
  </div>

  <div class="clear"></div>
  
</div>
