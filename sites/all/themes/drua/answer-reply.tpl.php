<div class="answer-reply comment<?php if ($comment->status == COMMENT_NOT_PUBLISHED) print ' comment-unpublished'; ?>">
    <?php if ($links): ?><div class="meta"><div class="links"><?php print $links; ?></div></div><?php endif; ?>
    <div class="content"><?php print $content; ?>&nbsp;<span class="meta"><span class="submitted"><?php print $user; ?>&nbsp;/&nbsp;<span class="date"><?php print t('@time ago', array('@time' => format_interval(time() - $comment->timestamp, 1))); ?></span></span></span></div>
    <div class="clear-block"></div>
</div>