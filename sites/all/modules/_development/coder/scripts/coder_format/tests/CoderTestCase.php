<?php
// $Id: CoderTestCase.php,v 1.1.2.2.2.1 2010/12/05 18:34:24 snpower Exp $

/**
 * @file
 * Set of tests for the coder_format script.
 */

require_once drupal_get_path('module', 'coder') .'/scripts/coder_format/coder_format.inc';

class CoderTestCase extends DrupalWebTestCase {
  function assertFormat($input, $expect) {
    $result = coder_format_string_all($input);
    $this->assertIdentical($result, $input);
  }
}

