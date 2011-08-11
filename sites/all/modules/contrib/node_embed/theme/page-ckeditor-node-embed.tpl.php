<?php
/**
 * @file page-ckeditor-node-embed.tpl.php
 * This file provides the template for the node embed search results when using the ckeditor
 * plugin.
 * @ingroup page
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <meta name="robots" content="noindex, nofollow" />
  <script type="text/javascript">

  var oEditor   = window.parent.CKEDITOR ;
  var instance  = oEditor.currentInstance ;
  var lang      = oEditor.lang ;
  var config    = oEditor.config ;
  </script>

  <?php print $head; ?>
  <?php print $styles; ?>
  <link type="text/css" rel="stylesheet" media="all" href="<?php print drupal_get_path("module", "node_embed") ?>/ckeditor/ck_nodeembed.css" />

  <!--[if IE]>
  <link type="text/css" rel="stylesheet" media="all" href="<?php print base_path() . path_to_theme();?>/css/ie.css" />
  <![endif]-->
  <!--[if IE 6]>
  <link type="text/css" rel="stylesheet" media="all" href="<?php print base_path() . path_to_theme();?>/css/ie6.css" />
  <![endif]-->
  <?php print $scripts; ?>
  <script type="text/javascript" src="<?php 
    print drupal_get_path('module', 'node_embed')?>/ckeditor/ck_nodeembed.js"></script>
</head>
<body class="view-ck" style="overflow: auto">
    <div id="divInfo">
      <?php print $content; ?>
    </div>
</body>
</html>

