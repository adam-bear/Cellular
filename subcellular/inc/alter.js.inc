<?php
/**
 * @file
 * Add and update javascript.
 */

/**
 * Subcellular hook_js_alter().
 */
function subcellular_js_alter() {
  /*
   * // Uncomment this block to add javascript to theme.
    $add_js = array(
    'myScript' => array( // Local script with minimum setup.
    'file'   => 'myscript.js', // Path to file, relative to /yourTheme/js/
    'weight' => 10,
    ),
    'cdnScript' => array( // CDN script w/ local fallback
    'object' => 'CDNscript', // javascript object to test for generating
    fallback from cdn
    'cdn'    => '//ajax.googleapis.com/ajax/libs/cdnScript.js',
    'file'   => 'fallback-script.js', // Path to file from /yourTheme/js/
    ),
    'anotherScript'  => array( // default params
    'file'       => 'anotherScript.js', // Path to file, from /yourTheme/js/
    ),
    );

    cellular_add_js($add_js);
   */

  /* // Pass a variable from drupal to js:
    drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');
   */
  /* myVar will be available in Javascript as:
    <script>
    if (Drupal.settings.myVar.key == value){
    alert('Got it!');
    }
    </script>
   */
}
