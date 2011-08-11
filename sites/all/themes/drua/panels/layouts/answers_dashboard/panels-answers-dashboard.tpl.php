<div class="panel-display answers-dashboard clear-block" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="panel-panel panel-col-top">
    <div class="inside"><?php print $content['top']; ?></div>
  </div>
  <div class="container container-16 center-wrapper">
    <div class="panel-panel grid-4">
      <div class="inside"><?php print $content['sidebar']; ?></div>
    </div>
    <div class="panel-panel grid-12 last">
        <div class="inside"><?php print $content['content']; ?></div>
    </div>
    <div class="clear"></div>
  </div>
  <div class="panel-panel panel-col-bottom">
    <div class="inside"><?php print $content['bottom']; ?></div>
  </div>
</div>
