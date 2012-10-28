<div class="question node<?php if (!$status) { print ' node-unpublished'; } ?>">
  <?php print $voting_widget; ?>
  <div class="content">
    <?php if ($page == 0): ?>
      <h2 class="title<?php print $best_answers ? ' answered' : ''; ?>"><a class="node-title" href="<?php print $node_url ?>"><?php print $title; ?><?php print $best_answers ? '&nbsp;<sup>['. t('resolved') .']</sup>' : ''; ?></a></h2>
    <?php else: ?>
      <?php print $content; ?>
    <?php endif; ?>
    <div class="meta-links">
      <?php if ($submitted): ?>
        <div class="meta">
          <span class="submitted">
            <?php print $name; ?> / <span class="date"><?php print $date; ?></span>
          </span>
        </div>
      <?php endif; ?>
      <?php if ($links): ?>
        <div class="node-links">
          <?php  print $links; ?>
        </div>
      <?php endif; ?>
      <?php if (count($taxonomy)): ?>
        <div class="taxonomy-links"><?php print $terms; ?></div>
      <?php endif; ?>
      <div class="clear-block"></div>
    </div>
  </div>
</div>
<div class="clear-block"></div>