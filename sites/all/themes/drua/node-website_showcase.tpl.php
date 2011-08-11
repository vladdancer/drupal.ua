<?php //dpr($node); ?>

<?php if (arg(2) != 'feed'): ?>
<div class="node<?php if (!$status) { print ' node-unpublished'; } ?>">
  <h2 class="title"><a href="<?php print $node_url ?>"><?php print $title; ?></a></h2>

  <div class="content">
	    <?php print $node->field_ws_screenshot[0]['view']; ?>
      <?php print $node->username; ?>
      <?php print $node->field_ws_company_url[0]['view']; ?>
      <div class="showcase_body">
        <?php print $node->content['body']['#value']; ?>
      </div>
      <div class="showcase_info">
        <?php print $node->created_text; ?>
      </div>
      <a href="javascript: history.back();" class="showcase_info_link">&laquo; <?php print t('Go Back'); ?></a>
      <?php print $node->edit_link; ?>
  </div>

  <?php if ($links || count($taxonomy)): ?>
    <div class="meta-links">
      <?php if (count($taxonomy)): ?>
        <div class="taxonomy-links"><?php print $terms; ?></div>
      <?php endif; ?>
      <?php if ($links): ?>
        <div class="links">
          <?php  print $links; ?>
        </div>
      <?php endif; ?>
      <div class="clear-block"></div>
    </div>
  <?php endif; ?>
</div>
<div class="clear-block"></div>
<?php endif; ?>