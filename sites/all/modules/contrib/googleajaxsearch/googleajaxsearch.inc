<?php
// $Id: googleajaxsearch.inc,v 1.1.2.3 2009/09/30 12:02:27 macperlinski Exp $
require_once("default_settings.inc");


/**
 * FAPI definition for Google Ajax Search settings form.
 * 
 * @ingroup forms
 * @see googleajaxsearch_settings_validate()
 * 
 * @return 
 *   array with settings form.
 */
function googleajaxsearch_settings() {
  $form['block_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of search blocks'),
    '#default_value' => variable_get('block_count', GAS_BLOCKS_NUMBER_DEFAULT),
    '#size' => 60,
    '#maxlength' => 64,
//    '#description' => t('Description'),
  );
  $form['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Ajax Search Api Key'),
    '#default_value' => variable_get('api_key', GAS_API_KEY_DEFAULT),
    '#size' => 60,
    '#maxlength' => 64,
//    '#description' => t('Description'),
  );
  
  return system_settings_form($form);
}

/**
 * Returns rendered settings form for Google Ajax Search module.
 * 
 * @return 
 *   rendered form.
 */
function googleajaxsearch_settings_page() {
  return drupal_get_form('googleajaxsearch_settings');
}

/**
 * Returns block in which google searcher will be embeded.
 *  
 * @param mixed $delta
 *   selects which block should be returned
 * @return 
 *   block for embedding.
 */
function googleajaxsearch_display_block($delta) {
  drupal_add_css(drupal_get_path('module', 'googleajaxsearch') . '/googleajaxsearch.css');
  gas_add_api();
  gas_add_settings($delta);
  gas_add_scripts();
  
  $display = gas_get_settings(array('delta' => $delta, 'param' => 'form_display'));
  
  $display == 0 ? $content = "<div id='searchcontrol-$delta'>Loading...</div>" :
                  $content = "<div id='searchcontrol-$delta'>Loading...</div>
                              <div id='searchcontrol-branding-$delta'>Branding...</div>";
                                                                       
  $block = array(
    'subject' => t('Title of block'),
    'content' => $content,
  );
  return $block;
}

/**
 * Returns settings form for block $delta.
 *  
 * @param mixed $delta
 *   selects for which block, settings form should be returned
 * @return 
 *   array with settings form.
 */
function gas_block_form($delta) {
  $settings = gas_get_settings();
  
  $form[$field = 'search_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Search type'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'web_search' => t('Web search'),
      'local_search' => t('Local search'),
      'video_search' => t('Video search'),
      'blog_search' => t('Blog search'),
      'news_search' => t('News search'),
      'image_search' => t('Image search'),
      'book_search' => t('Book search'),
      'patent_search' => t('Patent search'),
    ),
    '#description' => t('Select types of content in which do you want to search.'),
  );
//hide 
  $form[$field = 'form_display'] = array(
    '#type' => 'select',
    '#title' => t('Form display'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      0 => t('Show'),
      1 => t('Hide')),
    '#description' => t('If selected \'hide\', form for entering queries will not be displayed and only results will be published.'),
  );
//displaying of results
  $form[$field = 'results_display'] = array(
    '#type' => 'select',
    '#title' => t('Display of results'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'DRAW_MODE_LINEAR' => t('inline'), 
      'DRAW_MODE_TABBED' => t('tabbed')),
    '#description' => t('How the results should be displayed.'),
  );
//place for results
  $form[$field = 'results_place'] = array(
    '#type' => 'textfield',
    '#title' => t('Place of displaying results'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Where the results should be displayed. Enter fields html ID.'),
  );
//  setLinkTarget
  $form[$field = 'target_place'] = array(
    '#type' => 'select',
    '#title' => t('Target of opened links'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'LINK_TARGET_BLANK' => t('open in a new window'),
      'LINK_TARGET_SELF' => t('open in the same window and frame'),
      'LINK_TARGET_TOP' => t('open in the topmost frame'),
      'LINK_TARGET_PARENT' => t('open in either the topmost frame, or replace the current frame')),
    '#description' => t('Specifies how links should be opened.'),
  );
//number of results
  $form[$field = 'results_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of results'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'SMALL_RESULTSET' => t("Small (typically 4 results)"),
      'LARGE_RESULTSET' => t("Large (typically 8 results)")),
    '#description' => t('Number of results in each search.'),
  );
//keywords
  $form[$field = 'keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('Default keywords'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Default keywords for searcher.'),
  );
//branding
  $form['branding'] = array(
    '#type' => 'fieldset',
    '#title' => t('Branding options'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['branding'][$field = 'branding_place'] = array(
    '#type' => 'textfield',
    '#title' => t('Branding place'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Where the branding should be displayed. Enter fields html ID.'),
  );
  $form['branding'][$field = 'branding_orientation'] = array(
    '#type' => 'select',
    '#title' => t('Branding orientation'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'HORIZONTAL_BRANDING' => t('Horizontal'),
      'VERTICAL_BRANDING' => t('Vertical')),
    '#description' => t('Specifies the orientation of the branding node.'),
  );
//advanced
  $form['results_restriction'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['web'] = array(
    '#type' => 'fieldset',
    '#title' => t('Web searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );      
//web      
  $form['results_restriction']['web'][$field = 'results_web_language_restriction'] = array(
    '#type' => 'select',
    '#title' => t('Restrict results to specified language'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => gas_get_web_restriction_languages(),
    '#description' => t('Language to which results will be limited.'),
  );
  $form['results_restriction']['web'][$field = 'results_web_duplicate_content_filter'] = array(
    '#type' => 'select',
    '#title' => t('Duplicate content filter'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      0 => t('off'),
      1 => t('on')),
    '#description' => t('If turned on, duplicates will not be show.'),
  );
  $form['results_restriction']['web'][$field = 'results_web_site_restriction'] = array(
    '#type' => 'textfield',
    '#title' => t('Restrict results to page'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Site to which the results will be limited, e.g. \'www.meant4.com\''),
  );
//local      
  $form['results_restriction']['local'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['local'][$field = 'results_local_restrict_type'] = array(
    '#type' => 'select',
    '#title' => t('Result type'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => '',
      'TYPE_BLENDED_RESULT' => t('return a mix of both KML results and normal, local listings and geocodes'),
      'TYPE_KMLONLY_RESULTS' => t('return only KML results and geocode results'),
      'TYPE_LOCALONLY_RESULTS' => t('return only LOCAL listing results and geocode results')),
    '#description' => t('Description'),
  );

//video - youtube only?
  $form['results_restriction']['video'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['video'][$field = 'results_video_order'] = array(
    '#type' => 'select',
    '#title' => t('Results order'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'by relevance' => t('by relevance'),
      'by date' => t('by date')),
    '#description' => t('Used to change the result order.'),
  );
//blog - not exist
  $form['results_restriction']['blog'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blog searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['blog'][$field = 'blog_site_restriction'] = array(
    '#type' => 'textfield',
    '#title' => t('Restrict results to page'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Site to which the results will be limited, e.g. \'www.meant4.com\''),
  );
  $form['results_restriction']['blog'][$field = 'results_blog_order'] = array(
    '#type' => 'select',
    '#title' => t('Results order'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      t('by relevance'), 
      t('by date')),
    '#description' => t('Used to change the result order.'),
  );
//news      
  $form['results_restriction']['news'] = array(
    '#type' => 'fieldset',
    '#title' => t('News searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['news'][$field = 'results_news_restrict_topic'] = array(
    '#type' => 'select',
    '#title' => t('Search particular topic'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => t(''),
      'h' => t('top headlines topic'),
      'w' => t('world topic'),
      'b' => t('business'),
      'n' => t('nation topic'),
      't' => t('science and technology topic'),
      'el' => t('elections topic'),
      'p' => t('politics topic'),
      'e' => t('entertainment topic'),
      's' => t('sports topic'),
      'm' => t('health topic')),
    '#description' => t('Restricts news search results to news of particular topic.'),
  );
  $form['results_restriction']['news'][$field = 'results_news_site_restriction'] = array(
    '#type' => 'textfield',
    '#title' => t('Restrict results to page'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Site to which the results will be limited, e.g. \'www.meant4.com\''),
  );
  $form['results_restriction']['news'][$field = 'results_news_order'] = array(
    '#type' => 'select',
    '#title' => t('Results order'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      t('by relevance'), 
      t('by date')),
    '#description' => t('Used to change the result order.'),
  );
//book
  $form['results_restriction']['book'] = array(
    '#type' => 'fieldset',
    '#title' => t('Book searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['book'][$field = 'results_book_restrict_type'] = array(
    '#type' => 'select',
    '#title' => t('Search particular type of books'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'TYPE_FULL_VIEW_BOOKS' => t('Full view books'),
      'TYPE_ALL_BOOKS' => t('All books')),
    '#description' => t('Description'),
  );
  
//image
  $form['results_restriction']['image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['image'][$field = 'results_image_restrict_safesearch'] = array(
    '#type' => 'select',
    '#title' => t('Safesearch filter'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'SAFESEARCH_STRICT' => t('apply strict filtering for both explicit text and explicit images'),
      'SAFESEARCH_MODERATE' => t('apply filtering for explicit images'),
      'SAFESEARCH_OFF' => t('do not apply safe search filtering')),
    '#description' => t('Restricts image search results to images based on the safesearch value.'),
  );
  $form['results_restriction']['image'][$field = 'results_image_restrict_imagesize'] = array(
    '#type' => 'select',
    '#title' => t('Image size'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => t('do not restrict size images'),
      'IMAGESIZE_SMALL' => t('restrict to small images, icons'),
      'IMAGESIZE_MEDIUM' => t('restrict to medium images'),
      'IMAGESIZE_LARGE' => t('restrict to large images'),
      'IMAGESIZE_EXTRA_LARGE' => t('restrict to extra large images')),
    '#description' => t('Restricts image search results to images with certain pixel dimensions.'),
  );
  $form['results_restriction']['image'][$field = 'results_image_restrict_colorization'] = array(
    '#type' => 'select',
    '#title' => t('Image colorization'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => t('do not restrict images colorization'),
      'COLORIZATION_GRAYSCALE' => t('restrict to grayscale images'),
      'COLORIZATION_COLOR' => t('restrict to color images')),
    '#description' => t('Restricts image search results to images with certain colorization.'),
  );
  $form['results_restriction']['image'][$field = 'results_image_restrict_colorfilter'] = array(
    '#type' => 'select',
    '#title' => t('Filter images by the selected color'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => t('do not filter images by color'),
      'COLOR_BLACK' => t('BLACK'),
      'COLOR_BLUE' => t('BLUE'),
      'COLOR_BROWN' => t('BROWN'),
      'COLOR_GRAY' => t('GRAY'),
      'COLOR_GREEN' => t('GREEN'),
      'COLOR_ORANGE' => t('ORANGE'),
      'COLOR_PINK' => t('PINK'),
      'COLOR_PURPLE' => t('PURPLE'),
      'COLOR_RED' => t('RED'),
      'COLOR_TEAL' => t('TEAL'),
      'COLOR_WHITE' => t('WHITE'),
      'COLOR_YELLOW' => t('YELLOW')),
    '#description' => t('Image search results will be filtered based on the selected color.'),
  );
  $form['results_restriction']['image'][$field = 'results_image_restrict_filetype'] = array(
    '#type' => 'select',
    '#title' => t('Image file type'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => t('do not restrict images file type'),
      'FILETYPE_JPG' => t('restrict to only jpeg images'),
      'FILETYPE_PNG' => t('restrict to only png images'),
      'FILETYPE_GIF' => t('restrict to only gif images'),
      'FILETYPE_BMP' => t('restrict to only bmp images')),
    '#description' => t('Restricts image search results to images only of a certain filetype, e.g. JPG.'),
  );
  $form['results_restriction']['image'][$field = 'results_image_restrict_imagetype'] = array(
    '#type' => 'select',
    '#title' => t('Image type'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      '' => t('do not restrict images type'),
      'IMAGETYPE_FACES' => t('restrict to images with faces in them'),
      'IMAGETYPE_PHOTO' => t('restrict to photos'),
      'IMAGETYPE_CLIPART' => t('restrict to clipart images'),
      'IMAGETYPE_LINEART' => t('restrict to images of line drawings')),
    '#description' => t('Restricts image search results to images of certain type'),
  );
  $form['results_restriction']['image'][$field = 'results_image_site_restriction'] = array(
    '#type' => 'textfield',
    '#title' => t('Restrict results to page'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#description' => t('Site to which the results will be limited, e.g. \'www.meant4.com\''),
  );
  
//patent      
  $form['results_restriction']['patent'] = array(
    '#type' => 'fieldset',
    '#title' => t('Patent searcher'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  $form['results_restriction']['patent'][$field = 'results_patent_restrict_type'] = array(
    '#type' => 'select',
    '#title' => t('Restrict type of patents to'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      'TYPE_ISSUED_PATENTS' => t('patents that have been issued'),
      'TYPE_APPLICATIONS' => t('patents that have been filled but not yet issued'),
      'TYPE_ANY_STATUS' => t('all patents')),
    '#description' => t('Description'),
  );
  $form['results_restriction']['patent'][$field = 'results_patent_order'] = array(
    '#type' => 'select',
    '#title' => t('Results order'),
    '#default_value' => gas_get_settings(array('delta' => $delta, 'param' => $field)),
    '#options' => array(
      t('by relevance'), 
      t('by date')),
    '#description' => t('Used to change the result order.'),
  );
  
  $plugins = gas_get_plugins();
  
  if (!empty($plugins)) {
    $form['plugins'] = array(
      '#type' => 'fieldset',
      '#title' => t('Plugins'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    foreach ($plugins as $name => $plugin) {
      $settings_form = $plugin['settings_form'];
      $form['plugins'][$name] = array(
        '#type' => 'fieldset',
        '#title' => t($plugin['title']),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['plugins'][$name][$field = $name . "_status"] = array(
        '#type' => 'checkbox',
        '#title' => t('Enabled'),
        '#default_value' => $settings['gas'][$delta][$field] ? $settings['gas'][$delta][$field] : GAS_PLUGIN_STATUS_DEFAULT,
      );
      
      $form['plugins'][$name] += plugin_func_safe($settings_form, $settings['gas'][$delta]);
    }
  }
  
  return $form;
}

/**
 * Saves all settings from $edit for block $delta.
 * 
 * @param mixed $delta
 *   selects as which block settings, settings will be saved
 * @param mixed $edit
 *   array with settings to save (from hook_block)
 * @return 
 *   array with settings for block $delta.
 */
function gas_set_settings($delta, $edit) {
  $settings = gas_get_settings();
  $settings['gas'][$delta] = $edit;
  variable_set('googleajaxsearch', $settings);
  
  return $settings;
}

/**
 * Return settings for block $delta.
 * 
 * Example usage:
 * @code
 *   $all = gas_get_settings();
 *   $block = gas_get_settings(array('delta' => 1));
 *   $value = gas_get_settings(array('delta' => 2, 'param' => 'search_options'));
 * @endcode
 * 
 * @param mixed $arguments
 *   array with optional keys delta and param
 * @return 
 *   array with settings for all blocks if $arguments is empty, 
 *   or settings for block $delta if $arguments has a key 'delta', with numeric value,
 *   or value for $parameter if 'delta' and 'param' is given.
 */
function gas_get_settings($arguments = array()) {
  $default = "";
  $block_count = variable_get('block_count', GAS_BLOCKS_NUMBER_DEFAULT);
  
  for ($i = 0; $i < $block_count; $i++) {
    $default = array('gas' => array($i => gas_default_settings()));
  }
  $settings = variable_get('googleajaxsearch', $default);
  
  if (!empty($arguments)) {
    if (array_key_exists('delta', $arguments)) {
      $delta = $arguments['delta'];
      
      if (is_numeric($delta) && !array_key_exists($delta, $settings['gas'])) {
        $settings = gas_set_settings($delta, gas_default_settings());
      }
      
      $settings = $settings['gas'][$delta];
      
      if (array_key_exists('param', $arguments)) {
        $param = $arguments['param'];
        $settings = $settings[$param];
      }
    }
  }
  
  return $settings;
}

/**
 * Returns module settings
 * 
 * @return array with module settings.
 */
function gas_get_module_settings() {
  $settings['gas']['block_count']           = variable_get('block_count', GAS_BLOCKS_NUMBER_DEFAULT);
  $settings['gas']['api_key']               = variable_get('api_key', GAS_API_KEY_DEFAULT);
  return $settings;
}

/**
 * Adds Google Ajax Search API to html header. Without that no searcher will be loaded.
 */
function gas_add_api() {
//  Add only one jsapi.
  static $added = false;
  
  $api_key = variable_get('gas_api_key', GAS_API_KEY_DEFAULT);
  $api_key ? $api_key = "?key=$api_key" : '';
  
  if($added  == false) {
    drupal_set_html_head('<script src="'. check_url(url('http://www.google.com/jsapi')).$api_key.'" type="text/javascript"></script>');
    $added = true;
  }
}

/**
 * Adds block and module settings to drupal settings. This lets the javascript load aproppriate options during embeding searcher.
 * 
 * @param mixed $delta
 *   selects for which block, the settings are adding now
 */
function gas_add_settings($delta) {
  $settings = gas_get_settings();
  
  static $added = false;
  if(!$added) {
    $settings['gas']['block_count'] = variable_get('block_count', GAS_BLOCKS_NUMBER_DEFAULT);
    $added = true;
  }
  
  foreach ($settings['gas'] as $key => $value) {
    $settings['gas']['api_key'] = variable_get('api_key', GAS_API_KEY_DEFAULT);
    $settings['gas']['current_block'] = $delta;
    $settings['gas'][$key]['keywords'] = gas_get_plugin_keywords($key);
  }
  drupal_add_js($settings, 'setting');
}

/**
 * Adds module javascript to html header.
 */
function gas_add_scripts() {
  drupal_add_js(drupal_get_path('module', 'googleajaxsearch') . '/googleajaxsearch.js');
}

/**
 * Returns array with languages from Google Ajax Search - WebSearcher. Used in block settings form to give aproppriate aptions.
 */
function gas_get_web_restriction_languages() {
  return array(
    '0' => '', 
    'lang_ar' => t('Arabic'),
    'lang_bg' => t('Bulgarian'),
    'lang_ca' => t('Catalan'),
    'lang_zh-CN' => t('Chinese (Simplified)'),
    'lang_zh-TW' => t('Chinese (Traditional)'),
    'lang_hr' => t('Croation'),
    'lang_cs' => t('Czech'),
    'lang_da' => t('Danish'),
    'lang_nl' => t('Dutch'),
    'lang_en' => t('English'),
    'lang_et' => t('Estonian'),
    'lang_fi' => t('Finnish'),
    'lang_fr' => t('French'),
    'lang_de' => t('German'),
    'lang_el' => t('Greek'),
    'lang_iw' => t('Hebrew'),
    'lang_hu' => t('Hungarian'),
    'lang_is' => t('Icelandic'),
    'lang_id' => t('Indonesian'),
    'lang_it' => t('Italian'),
    'lang_ja' => t('Japanese'),
    'lang_ko' => t('Korean'),
    'lang_lv' => t('Latvian'),
    'lang_lt' => t('Lithuanian'),
    'lang_no' => t('Norwegian'),
    'lang_pl' => t('Polish'),
    'lang_pt' => t('Portuguese'),
    'lang_ro' => t('Romanian'),
    'lang_ru' => t('Russian'),
    'lang_sr' => t('Serbian'),
    'lang_sk' => t('Slovak'),
    'lang_sl' => t('Slovenian'),
    'lang_es' => t('Spanish'),
    'lang_sv' => t('Swedish'),
    'lang_tr' => t('Turkish'),
  );
}

/**
 * Returns all keywords processed by enabled plugins for block $delta.
 * 
 * Example usage:
 * @code
 *   $keywords = gas_get_plugin_keywords(1);
 * @endcode
 * 
 * @param mixed $delta
 *   selects block which keywords should be returned.
 * @return
 *   string with keywords
 */
function gas_get_plugin_keywords($delta) {
  $plugins = gas_get_plugins();
  $settings = gas_get_settings(array('delta' => $delta));
  $keywords = '';
  
  foreach ($plugins as $key => $plugin) {
    if ($settings[$key . '_status'] == 1) {
      $keywords[] = plugin_func_safe($plugin['execute'], $settings);
    }
  }
//  AND is being used to concatenate different plugin keywords, not separate keywords at all!
  if (is_array($keywords) && !empty($keywords)) {
    $keywords = implode(' AND ',$keywords);
  }
  
  return $keywords;
}

/**
 * Safely calls function $function using $delta as argument. If calling function isn't exists it does nothing.
 * 
 * Example usage:
 * @code
 *   $result = plugin_func_safe('example_function_name', 1);
 * @endcode
 * 
 * @param mixed $function function name needed to call
 * @param mixed $delta argument for function.
 */
function plugin_func_safe($function, $delta) {                                
  if (function_exists($function)) {
    return call_user_func($function, $delta);
  }
}

/**
 * Invokes all hook_googleajaxsearch_info() functions.
 */
function gas_get_plugins() {
  return module_invoke_all('googleajaxsearch_info');
}