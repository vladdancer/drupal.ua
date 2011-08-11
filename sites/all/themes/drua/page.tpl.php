<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?> sshow-grid">
  <div class="body-wrapper">
    <div id="page" class="page container-12 clear-block">
        <div id="branding" class="clear-block">
        <?php if ($linked_logo_img): ?>
          <span id="logo" class="logo grid-1"><?php print $linked_logo_img; ?></span>
        <?php endif; ?>
        <?php if ($linked_site_name): ?>
          <h1 id="site-name" class="site-name grid-3"><?php print $linked_site_name; ?></h1>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
          <div id="site-slogan" class="site-slogan grid-3"><?php print $site_slogan; ?></div>
        <?php endif; ?>
        </div>

      <div id="site-header" class="site-header clear-block">
        <div id="site-menu" class="site-menu grid-8">
          <?php print $user_menu_block ?>
          <div class="clear-block"></div>
        </div>
        <div id="search-menu" class="search-menu grid-4">
          <?php print $header_right; ?>
          <div class="clear-block"></div>
        </div>
      </div>


      <div id="site-subheader" class="site-subheader clear-block">
      <?php if ($mission): ?>
        <div id="mission" class="<?php print ns('grid-12', $header, 7); ?>">
          <?php print $mission; ?>
        </div>
      <?php endif; ?>
      
      <?php if ($main_menu_links): ?>
        <div class="top-box <?php print(($secondary_menu_links || $featured) ? '' : 'single-menu'); ?> grid-12">
          <?php print $main_menu_links; ?>
          <div class="clear-block"></div>
          <?php if ($secondary_menu_links || $featured): ?>
            <?php print $secondary_menu_links; ?>
          <?php endif; ?>
          <div class="clear-block"></div>
          <?php if ($featured): ?>
            <?php print $featured; ?>
          <?php endif; ?>
          <?php if ($secondary_menu_links || $featured): ?>
            <div class="top-box-bottom"></div>
          <?php endif; ?>
        </div>
      <?php endif; ?>
      <?php if ($page_top): ?>
        <div id="page-top" class="grid-12 clear-block">
          <?php print $page_top; ?>
        </div>
      <?php endif; ?>
      <div class="clear-block"></div>
      </div>


      <div id="main" class="column <?php print ns('', $left, 3, $right, 3) . ' ' . ns('push-3', !$left, 3); ?>">
        <div class="page-controls grid-12">
          <?php print $messages; ?>
          <?php print $breadcrumb; ?>
          <?php if ($title): ?>
            <h1 class="title" id="page-title"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php if ($tabs): ?>
            <div class="tabs-wrapper"><?php print $tabs; ?></div>
          <?php endif; ?>
          <?php print $help; ?>
        </div>

        <?php print $pre_content; ?>
        <div id="main-content" class="region clear-block <?php if (!is_panel()) { print('grid-12'); } ?>">
          <?php print $content; ?>
        </div>
      </div>


    <?php if ($left): ?>
      <div id="sidebar-left" class="column sidebar region grid-3 <?php print ns('pull-9', $right, 3); ?>">
        <?php print $left; ?>
      </div>
    <?php endif; ?>

    <?php if ($right): ?>
      <div id="sidebar-right" class="column sidebar region grid-3">
        <?php print $right; ?>
      </div>
    <?php endif; ?>

    <?php if ($page_bottom): ?>
      <div id="page-bottom" class="grid-12 clear-block">
        <?php print $page_bottom; ?>
      </div>
    <?php endif; ?>
    </div>
  </div>
  <div id="footer" class="prefix-1 suffix-1 footer">
    <div id="footer-container" class="container-12 clear-block">
      <?php if ($footer): ?>
        <div id="footer-region" class="region">
          <?php print $footer; ?>
          <div class="clear-block"></div>
        </div>
      <?php endif; ?>

      <?php if ($copyrights): ?>
        <div id="footer-message" class="region">
          <?php print $copyrights; ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
  <?php print $closure; ?>
</body>
</html>
