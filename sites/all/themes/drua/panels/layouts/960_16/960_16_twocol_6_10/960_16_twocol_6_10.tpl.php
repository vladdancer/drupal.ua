<div class="panel-display 960-16-twocol-6-10 container-16" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="panel-panel panel-col-first panel-left grid-6">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>

  <div class="panel-panel panel-col-last panel-right grid-10">
    <div class="inside"><?php print $content['right']; ?></div>
  </div>

  <div class="clear"></div>

</div>
