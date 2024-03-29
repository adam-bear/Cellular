<?php
/**
 * @file
 * Cellular stylesheet functions.
 */

/**
 * Add array of stylesheets to $css, using a CDN if provided.
 *
 * @param array $css
 *  Associative array of stylesheets to merge with defaults from theme registry.
 *
 * @param array $array
 *  Associative array of stylesheets data.
 *
 * @param bool $cellular
 *  Reference cellular library if TRUE.
 */
function cellular_add_css(&$css, $array, $cellular = FALSE) {
  foreach ($array as $style) {
    if (!empty($style)) {
      if (isset($style['cdn'])) {
        $data = $style['cdn'];
      }
      elseif (isset($style['file'])) {
        $data = $cellular === TRUE ? constant('CELLULAR_LIB') : path_to_theme();
        $data .= '/css/' . $style['file'];
      }
      if (!empty($data)) {
        $style['data'] = $data;
        $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
        $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
        $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
        $style['weight'] = isset($style['weight']) ? $style['weight'] : 1;
        $style['type'] = isset($style['cdn']) ? 'external' : 'file';
        $style['media'] = isset($style['media']) ? $style['media'] : 'all';
        $style['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);

        $css[$data] = $style;
      }
    }
  }
}

/**
 * Removes array of stylesheets from $css.
 *
 * @param array $css
 *  Associative array of stylesheets to merge with defaults from theme registry.
 *
 * @param array $exclude
 *  Array of stylesheets to remove.
 */
function cellular_remove_css(&$css, $exclude) {
  foreach ($exclude as $module => $stylesheet) {
    // Remove multiple stylesheets attached by module.
    if (is_array($stylesheet)) {
      foreach ($stylesheet as $style) {
        unset($css[drupal_get_path('module', $module) . '/' . $style]);
      }
    }
    // Remove individual stylesheet.
    else {
      unset($css[drupal_get_path('module', $module) . '/' . $stylesheet]);
    }
  }
}

/**
 * Overrides default css values.
 *
 * @param array $css
 *  Associative array of stylesheets to merge with defaults from theme registry.
 *
 * @param array $style
 *  Array of stylesheet data used to override default.
 *
 * @param bool $cellular
 *  Reference cellular library if TRUE.
 */
function cellular_override_css(&$css, $style, $cellular = FALSE) {
  $ocss =  $style['default'];
  // Only override if style is being called.
  if (isset($css[$ocss])) {
    if (isset($style['cdn'])) {
      // If cdn is provided, set data to external source.
      $data = $style['cdn'];
      // Set key to data to prevent multiple calls to same source.
      $ocss = $data;
    }
    else {
      $path = $cellular === TRUE ? constant('CELLULAR_LIB') : path_to_theme();
      // Or set data to local file.
      $data = $path . '/css/' . $style['file'];
    }
    $css[$ocss]['data'] = $data;
    $css[$ocss]['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : FALSE;
    $css[$ocss]['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
    $css[$ocss]['group'] = isset($style['group']) ? $style['group'] : CSS_DEFAULT;
    $css[$ocss]['weight'] = isset($style['weight']) ? $style['weight'] : 0;
    $css[$ocss]['type'] = isset($style['cdn']) ? 'external' : 'file';
    $css[$ocss]['media'] = isset($style['media']) ? $style['media'] : 'all';
    $css[$ocss]['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);
  }
}

/**
 * Remove core stylesheets based on theme settings.
 *
 * @param array $css
 *  Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_remove_default_css(&$css) {
  // Nuke all css not a member of group CSS_THEME:
  $exclude = array();
  if (theme_get_setting('remove_drupal_css') === 'theme_only') {
    foreach ($css as $key => $value) {
      if ($value['group'] !== CSS_THEME
      // Keep admin stuff.
      && ($key !== 'admin_menu' || $key !== 'toolbar')
      ) {
        unset($css[$key]);
      }
    }
  }
  // 86 SYSTEM_CSS.
  if (theme_get_setting('remove_drupal_css') === 'system') {
    foreach ($css as $key => $value) {
      if ($value['group'] === CSS_SYSTEM) {
        unset($css[$key]);
      }
    }
  }
  // Remove selected system & module css.
  if (theme_get_setting('remove_drupal_css') === 'select') {
    // Select module css to exclude.
    $exclude = array(
      'system' => array(
        'system.base.css',
        'system.menus.css',
        'system.messages.css',
        'system.theme.css',
      ),
      'block' => 'block.css',
      'colorbox' => 'styles/default/colorbox_style.css',
      'comment' => 'comment.css',
      'field' => 'theme/field.css',
      'filter' => 'filter.css',
      'help' => 'help.css',
      'menu' => 'menu.css',
      'node' => 'node.css',
      'panels' => 'css/panels.css',
      'search' => 'search.css',
      'shortcut' => 'shorcut.css',
      'user' => 'user.css',
    );

    cellular_remove_css($css, $exclude);
  }
}
