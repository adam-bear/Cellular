<?php
/**
 * @file
 * Template for a single column panel layout.
 */

/* Variables:
 * - $css_id: An optional CSS id to use for the layout.
 *   $content['middle']: The only panel in the layout.
 */

?>

<div<?php if (!empty($css_id)): print " id=\"$css_id\"";
endif; ?> class="panels cell">

  <?php if ($content['middle']): ?>
    <div class="panel-content">
      <?php print $content['middle']; ?>
    </div>
  <?php endif; ?>
  
</div>
