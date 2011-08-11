<div class="panel-display 960-16-twocol-6-10-stacked container-16" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  
  <div class="panel-panel panel-col-full panel-top grid-16">
    <div class="inside"><?php print $content['top']; ?></div>
  </div>
  
  <div class="clear"></div>
  
  <div class="panel-panel panel-col-first panel-left grid-4">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>
  <div class="panel-panel panel-col-last panel-right grid-12">
    <div class="inside"><?php print $content['right']; ?></div>
  </div>
  
  <div class="clear"></div> 

  <div class="panel-panel panel-col-full panel-bottom grid-16">
    <div class="inside"><?php print $content['bottom']; ?></div>
  </div>

  <div class="clear"></div>
  
</div>
