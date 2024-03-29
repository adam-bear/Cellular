<?php
/**
 * @file
 * Cellular process functions.
 */

/**
 * Cellular template_process_html().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_process_html(&$vars) {
  // Push modified styles to page.
  $vars['styles'] = drupal_get_css($vars['css'], FALSE);
}

/**
 * Cellular template_process_page().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_process_page(&$vars) {
  // Dev.
  cellular_dev($vars);
}
