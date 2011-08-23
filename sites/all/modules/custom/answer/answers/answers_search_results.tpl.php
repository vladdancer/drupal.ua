<?php
/**
 * @file answers_search_results.tpl.php
 *
 * Template for the search results.
 */
?>

<div>
<div id="answers-search-close"></div>
  <h3 class="site-search"><?php print t('Site search'); ?>:</h3>
  <div id="site-search">
    <?php print $search_results_themed; ?>
  </div>
  <div id="answers-search-pager">
    <?php print $pager; ?>
  </div>

  <h3 class="google-search"><?php print t('Google search'); ?>:</h3>
  <div id="google-search"></div>

  <h3 class="site-search"><?php print t('Nothing helped?'); ?> <?php print $new_question_link; ?></h3>

</div>