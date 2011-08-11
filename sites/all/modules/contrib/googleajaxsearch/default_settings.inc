<?php
// $Id: default_settings.inc,v 1.1.2.1 2009/09/30 12:02:27 macperlinski Exp $

/**
 * @file
 * Default settings for module. (Constants, values...)
 */
 
//GOOGLE AJAX SEARCH CONSTANTS
define('GAS_GOOGLE_RESULT_SIZE_DEFAULT', 4);

//Default module settings
define('GAS_BLOCKS_NUMBER_DEFAULT', 0);
define('GAS_API_KEY_DEFAULT', '');

//Default drupal block settings
define('GAS_BLOCK_WEIGHT_DEFAULT', 0);
define('GAS_BLOCK_STATUS_DEFAULT', FALSE);
define('GAS_BLOCK_REGION_DEFAULT', 'left');
define('GAS_BLOCK_CACHE_DEFAULT', BLOCK_NO_CACHE);

define('GAS_PLUGIN_STATUS_DEFAULT', 0);

//Default search block settings
function gas_default_settings() {
  return array(
    'search_options' => array('web_search'),//web_search, local_search video_search blog_search news_search image_search book_search patent_search
    'form_display' => 0, //0 = Show, 1 = Hide
    'results_display' => 'DRAW_MODE_LINEAR',//DRAW_MODE_LINEAR, DRAW_MODE_TABBED
    'results_place' => '',
    'target_place' => 'LINK_TARGET_BLANK',//LINK_TARGET_BLANK, LINK_TARGET_SELF, LINK_TARGET_TOP, LINK_TARGET_PARENT
    'results_count' => 'SMALL_RESULTSET',//SMALL_RESULTSET, LARGE_RESULTSET
    'keywords' => '',
    'branding_place' => 'searchcontrol-branding-',// plus "$delta", where $delta is corresponding number of block to which the branding is connected
    'branding_orientation' => 'HORIZONTAL_BRANDING',//HORIZONTAL_BRANDING, VERTICAL_BRANDING'results_web_language_restriction' => '',
    'results_web_language_restriction' => '1',//Too many to list all parameters here... Check gas_get_web_restriction_languages() function.
    'results_web_duplicate_content_filter' => '1',//0=off, 1=on
    'results_web_site_restriction' => '',
    'results_local_restrict_type' => '',//TYPE_BLENDED_RESULT, TYPE_KMLONLY_RESULTS, TYPE_LOCALONLY_RESULTS
    'results_video_order' => 'by relevance',//by relevance, by date
    'blog_site_restriction' => '',
    'results_blog_order' => 'by relevance',//by relevance, by date
    'results_news_restrict_topic' => '',//h = top headlines topic, w = world topic, b = business, n = nation topic, t = science and technology topic,  el = elections topic, p = politics topic, e = entertainment topic, s = sports topic, m = health topic,
    'results_news_site_restriction' => '',
    'results_news_order' => 'by relevance',//by relevance, by date
    'results_book_restrict_type' => 'TYPE_ALL_BOOKS',//TYPE_FULL_VIEW_BOOKS, TYPE_ALL_BOOKS
    'results_image_restrict_safesearch' => 'SAFESEARCH_MODERATE',//SAFESEARCH_STRICT, SAFESEARCH_MODERATE, SAFESEARCH_OFF
    'results_image_restrict_imagesize' => '',//IMAGESIZE_SMALL, IMAGESIZE_MEDIUM, IMAGESIZE_LARGE, IMAGESIZE_EXTRA_LARGE
    'results_image_restrict_colorization' => '',//COLORIZATION_GRAYSCALE, COLORIZATION_COLOR
    'results_image_restrict_colorfilter' => '',//COLOR_BLACK, COLOR_BLUE, COLOR_BROWN, COLOR_GRAY, COLOR_GREEN, COLOR_ORANGE, COLOR_PINK, COLOR_PURPLE, COLOR_RED, COLOR_TEAL, COLOR_WHITE, COLOR_YELLOW
    'results_image_restrict_filetype' => '',//FILETYPE_JPG, FILETYPE_PNG, FILETYPE_GIF, FILETYPE_BMP
    'results_image_restrict_imagetype' => '',//IMAGETYPE_FACES, IMAGETYPE_PHOTO, IMAGETYPE_CLIPART, IMAGETYPE_LINEART
    'results_image_site_restriction' => '',
    'results_patent_restrict_type' => 'TYPE_ANY_STATUS',//TYPE_ISSUED_PATENTS, TYPE_APPLICATIONS, TYPE_ANY_STATUS
    'results_patent_order' => 'by relevance',//by relevance, by date
  );
}