<?php
/**
 * @file
 * Cellular utility functions.
 */

/**
 * Get media query breakpoints from theme settings.
 *
 * @return array
 * Media queries settings.
 */
function cellular_mq() {
  $mq = array();
  $mq['mobile'] = theme_get_setting('mq_mobile');
  $mq['normal'] = theme_get_setting('mq_normal');
  $mq['large'] = theme_get_setting('mq_large');

  return $mq;
}

/**
 * Add <link> & <meta> tags from an array.
 *
 * @param array $array
 *  Array of tags to add to document <head>.
 */
function cellular_build_head_tags($array) {
  foreach ($array as $meta => $val) {
    if (isset($val)) {
      // Build tag:
      $tag = array(
        '#type' => 'html_tag',
        '#tag' => $val['tag'],
        '#attributes' => array(),
        '#weight' => isset($val['weight']) ? $val['weight'] : 0,
      );
      // Misc. attr/val:
      empty($val['attr']) || empty($val['attr_val']) ? NULL :
      $tag['#attributes'][$val['attr']] = $val['attr_val'];
      empty($val['profile']) ? NULL :
      $tag['#attributes']['profile'] = $val['profile'];
      // General attributes:
      empty($val['name']) ? NULL :
      $tag['#attributes']['name'] = $val['name'];
      empty($val['rel']) ? NULL :
      $tag['#attributes']['rel'] = $val['rel'];
      empty($val['content']) ? NULL :
      $tag['#attributes']['content'] = $val['content'];
      empty($val['href']) ? NULL :
      $tag['#attributes']['href'] = $val['href'];
      // Attributes for favicons:
      empty($val['size']) ? NULL :
      $tag['#attributes']['sizes'] = $val['size'];
      empty($val['type']) ? NULL :
      $tag['#attributes']['type'] = $val['type'];

      drupal_add_html_head($tag, 'meta_' . $meta);
    }
  }
}

/**
 * Set path to page-error.tpl if http error is returned.
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_error_page(&$vars) {
  // Set custom error template:
  $http_status = drupal_get_http_header("status");

  if (isset($http_status)) {

    switch ($http_status) {
      case "403 Forbidden":
      case "404 Not Found":
      case "500 Internal Server Error":
        $vars['theme_hook_suggestions'][] = 'page__error';
        $vars['http_status'] = "Error: " . $http_status;
        $vars['error_message'] = drupal_get_messages();
        $vars['classes_array'][] = 'page-error';
        break;
    }
  }
}

/**
 * Removes text formatting options from user input.
 *
 * @param $form
 * Form element to set.
 *
 * @param $form_state
 * Form element's state.
 */
function cellular_form_format_opt(&$form, $form_state) {
  // Remove individual text format options:
  // $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
  // Or Nuke text format options:
  $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;
  $form[LANGUAGE_NONE][0]['format']['#default_value'] = 'filtered';

  return $form;
}

/**
 * Print variables for development as message, usedful if devel isn't available.
 *
 * @param array $element 
 *  Element to test and return variables of.
 */
function cellular_dev($element) {
  if (theme_get_setting('dev') === 1) {
    if (module_exists('devel')) {
      dpm($element);
    }
    else {
      drupal_set_message('<pre>' . print_r($element, TRUE) . '</pre>');
    }
  }
}
