<?php
// $Id: page-fckeditor-node-embed.tpl.php,v 1.1 2010/04/21 18:22:44 febbraro Exp $
/**
 * @file page-fckeditor-node-embed.tpl.php
 * This file provides the template for the node embed search results when using the fckeditor
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

  var oEditor      = window.parent.InnerDialogLoaded() ;
  var FCK          = oEditor.FCK ;
  var FCKLang      = oEditor.FCKLang ;
  var FCKConfig    = oEditor.FCKConfig ;
  var FCKRegexLib  = oEditor.FCKRegexLib ;
  var FCKTools     = oEditor.FCKTools ;

  document.write( '<script src="' + FCKConfig.BasePath + 'dialog/common/fck_dialog_common.js" type="text/javascript"><\/script>' ) ;

  </script>
  <script type="text/javascript">

  window.onload = function()
  {
    // Translate the dialog box texts.
    oEditor.FCKLanguageManager.TranslatePage(document) ;

    // Activate the "OK" button.
    window.parent.SetOkButton( true ) ;
    window.parent.SetAutoSize( true ) ;
  }

  //#### The OK button was hit.
  function Ok()
  {
    node_id = $('#active-nid').text();
    
    if( node_id != null ) {
      FCK.InsertHtml( '<div class="embed">[[nid:' + node_id + ']]</div>' );
    }

    return true ;
  }
  </script>
  <?php print $head; ?>
  <?php print $styles; ?>
  <link type="text/css" rel="stylesheet" media="all" href="<?php print drupal_get_path("module", "node_embed") ?>/fckeditor/fck_nodeembed.css" />

  <!--[if IE]>
  <link type="text/css" rel="stylesheet" media="all" href="<?php print base_path() . path_to_theme();?>/css/ie.css" />
  <![endif]-->
  <!--[if IE 6]>
  <link type="text/css" rel="stylesheet" media="all" href="<?php print base_path() . path_to_theme();?>/css/ie6.css" />
  <![endif]-->
  <?php print $scripts; ?>
  <script type="text/javascript" src="<?php 
    print drupal_get_path('module', 'node_embed')?>/fckeditor/fck_nodeembed.js"></script>
</head>
<body style="overflow: hidden">
    <div id="divInfo">
      <?php print $content; ?>
    </div>
</body>
</html>

