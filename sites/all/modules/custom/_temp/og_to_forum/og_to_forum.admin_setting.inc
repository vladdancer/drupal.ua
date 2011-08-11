<?php


/**
 * Define map for change Group to forum.
 * Change: gid (group ID) -> tid (taxonomy term ID).
 */
function _og_to_forum_define_map() {
  static $map;
  if (isset($map) && !empty($map)) {
    return $map;
  }

  $vocabulary_tree = taxonomy_get_tree(variable_get('forum_nav_vocabulary', ''));
  
  //gid => tid
  $map = array(
    27 => '',
    29 => '',
    31 => '',
    34 => '',
    39 => '',
    56 => '',
    935 => '',
    958 => '',
    1043 => '',
    1063 => '',
    1091 => '',
    1190 => '',
    1197 => '',
    1241 => '',
    1260 => '',
    1262 => '',
    1263 => '',
    1264 => '',
    300150 => '',
    'left' => array(),
    'terms' => array(),
    'count_forums' => 0,
  );

  $count_forums = 0;
  $terms = array();
  
  foreach ($vocabulary_tree as $i => $term) {
    $term->tid = (int)$term->tid;
    $terms[$term->tid] = $term;
    switch ($term->name) {
      case 'Оптимізація роботи Друпал': $map[29] = $term->tid;  break;
      case 'SEO-оптимізація сайтів на друпал': $map[34] = $term->tid;  break;
      case 'Побажання та пропозиції': $map[56] = $term->tid;  break;
      case 'Локалізація Друпал': $map[935] = $term->tid;  break;
      case 'DrupalCamp Kyiv': $map[1043] = $term->tid;  break;
      case 'Події за кордоном': $map[1091] = $term->tid;  break;
      case 'DrupalForum ZP': $map[1190] = $term->tid;  break;
      case 'Donetsk Drupal Meetup': $map[1197] = $term->tid;  break;
      case 'Друпал і Я — як друпал змінив моє життя': $map[1241] = $term->tid;  break;
      case 'Одноразове замовлення (разова робота)': $map[1263] = $term->tid;  break;
      case 'Проблеми з перекладом': $map[300150] = $term->tid;  break;

      case 'Комерція в Друпал':
        $map[958] = $term->tid;
        $map[1262] = $term->tid;
        break;

      case 'Поради, хитрощі, трюки і т.д.':
        $map[31] = $term->tid;
        $map[39] = $term->tid;
        $map[27] = $term->tid;
        $map[1260] = $term->tid;
        $map[1063] = $term->tid;
        $map[1264] = $term->tid;
        break;

      default:
        $map['left'][] = $term->tid;
    }
    if ($term->depth) {
      $count_forums++;
    }
  }
  $map['terms'] = $terms;
  $map['count_forums'] = $count_forums;
  
  //Duplicate map for russian translate
  $temp = $map;
  unset($temp['left']);
  unset($temp['count_forums']);
  unset($temp['terms']);
  
  foreach ($temp as $nid => $value) {
    $lang_nid = db_result(db_query(
      'SELECT nid FROM {node} WHERE tnid = %d AND nid <> %d LIMIT 1',
      $nid, $nid
    ));
    if ($lang_nid) {
      $map[$lang_nid] = $value;
    }
  }
  return $map;
}


/**
 * Return forum alias.
 */
function _og_to_forum_forum_alias($name) {
  $alias = '';
  switch ($name) {
    case 'Друпал-спільнота':  $alias = 'community';  break;
    case 'Інтерв"ю ТОП-друпалерів':  $alias = 'interview';  break;
    case 'Друпал і Я — як друпал змінив моє життя':  $alias = 'drupal_and_i';  break;
    case 'Розробка з Друпал':  $alias = 'devel';  break;
    case 'Питання/Відповіді':  $alias = 'questions_answers';  break;
    case 'Оптимізація роботи Друпал':  $alias = 'optimization';  break;
    case 'Комерція в Друпал':  $alias = 'commerce';  break;
    case 'SEO-оптимізація сайтів на друпал':  $alias = 'seo';  break;
    case 'Темізація Друпал':  $alias = 'theming';  break;
    case 'Локалізація Друпал':  $alias = 'localization';  break;
    case 'Поради, хитрощі, трюки і т.д.':  $alias = 'drupal_kitchen';  break;
    case 'Оцініть (тільки не бийте ногами) - Виставка сайтів користувачів Drupal.ua':
      $alias = 'showcase_sites';  break;
    case 'Друпал-міста':  $alias = 'drupal_sity';  break;
    case 'Харків':  $alias = 'kharkov';  break;
    case 'Донецьк':  $alias = 'donetsk';  break;
    case 'Дніпропетровськ':  $alias = 'dnepropetrovsk';  break;
    case 'Запоріжжя':  $alias = 'zaporozhye';  break;
    case 'Луцьк':  $alias = 'lutsk';  break;
    case 'Київ':  $alias = 'kiev';  break;
    case 'Замовте своє місто':  $alias = 'order_your_town';  break;
    case 'Події':  $alias = 'events';  break;
    case 'DrupalCamp Kyiv':  $alias = 'drupal_forum_zp';  break;
    case 'Donetsk Drupal Meetup':  $alias = 'drupal_camp_kiev';  break;
    case 'DrupalForum ZP':  $alias = 'donetsk_drupal_meetup';  break;
    case 'Події за кордоном':  $alias = 'events_abroad';  break;
    case 'Робота':  $alias = 'work';  break;
    case 'Пропоную роботу':  $alias = 'looking_for_work';  break;
    case 'Шукаю роботу':  $alias = 'job_offers';  break;
    case 'Шукаю партнерів':  $alias = 'looking_for_partners';  break;
    case 'Одноразове замовлення (разова робота)':  $alias = 'single_order';  break;
    case 'drupal.ua':  $alias = 'drupal_ua';  break;
    case 'Помилки на сайті':  $alias = 'bug_reports';  break;
    case 'Проблеми з перекладом':  $alias = 'problems_translation';  break;
    case 'Побажання та пропозиції':  $alias = 'suggestions';  break;
  }
  return $alias;
}






