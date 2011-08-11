<?php
// $Id: node-embed-default.tpl.php,v 1.1 2010/04/21 18:22:44 febbraro Exp $
?>
<div id="embedded-node-<?php print $embedded_node->nid; ?>" class="embedded-node 
  <?php if (!$embedded_node->status) { print ' node-unpublished'; } ?>">
  <span class='embed-msg'>Node (<?php print $embedded_node->nid?>) is embedded</span>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>

  <div class="content clear-block">
    <?php print $embedded_node->body ?>
  </div>
</div>
