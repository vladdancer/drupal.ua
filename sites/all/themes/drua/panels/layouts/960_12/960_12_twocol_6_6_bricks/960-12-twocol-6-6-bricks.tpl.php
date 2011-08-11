<?php global $is_panel; $is_panel = TRUE; ?>
<div class="panel-display 960-12-twocol-6-6-bricks container-12" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="panel-panel panel-col-full panel-top grid-12">
    <div class="inside"><?php print $content['top']; ?></div>
  </div>

  <div class="clear"></div>

  <div class="panel-panel panel-col-first panel-left-above grid-6">
    <div class="inside"><?php print $content['left_above']; ?></div>
  </div>

  <div class="panel-panel panel-col-last panel-right-above grid-6">
    <div class="inside"><?php print $content['right_above']; ?></div>
  </div>

  <div class="clear"></div>

  <div class="panel-panel panel-col-full panel-middle grid-12">
    <div class="inside"><?php print $content['middle']; ?></div>
  </div>
  
  <div class="clear"></div>  

  <div class="panel-panel panel-col-first panel-left-below grid-6">
    <div class="inside"><?php print $content['left_below']; ?></div>
  </div>

  <div class="panel-panel panel-col-last panel-right-below grid-6">
    <div class="inside"><?php print $content['right_below']; ?></div>
  </div>

  <div class="clear"></div>

  <div class="panel-panel panel-col-full panel-bottom grid-12">
    <div class="inside"><?php print $content['bottom']; ?></div>
  </div>

  <div class="clear"></div>

</div>
