<div class="answer<?php print $best_answer ? ' best-answer' : ''; ?>">
  <?php print $voting_widget; ?>
  <div class="comment<?php if ($comment->status == COMMENT_NOT_PUBLISHED) print ' comment-unpublished'; ?>">
    <div class="content"><?php print $content; ?></div>
    <div class="meta">
      <?php if ($new != ''): ?><span class="new"><?php print $new; ?></span><?php endif; ?>
      <?php if ($links): ?><div class="links"><?php print $links; ?></div><?php endif; ?>
      <div class="picture">
        <?php if ($picture): ?><? print $picture; ?><?php endif; ?>
        <span class="submitted">
          <?php print $user; ?> / <span class="date"><?php print $date; ?></span>
        </span>
      </div>
    </div>
  </div>
</div>
<div class="clear-block"></div>