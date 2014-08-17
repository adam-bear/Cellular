/*****
 script.js

 Custom javascript functions
 *****/
(function($) {

    Drupal.behaviors.theme = {
        attach: function(context, settings) {

            /////
            /// Call cellular functions
            /////

            $('.jAccordion').jAccordion();
            $('.jBlocklink').jBlocklink();
            $('form').jFormal();
            $('.jScrolli').jScrolli();
            $('.jTabs').jTabs();
            $('#nav').jMmenu();

            //$('.jScrolltrigger').jScrolltrigger();
            //$('.jCarousel').jCarousel();
            //$('.jEqualheight').jEqualheight();
            //$('.jParallax').jParallax();
            //$('.jToggle').jToggle();
            //$('.jSticky').jSticky();

            /////
            /// Call Masonry
            /////       

            /*
             $('.block-content').masonry({
             containerStyle: null,
             itemSelector: '.blocklink-wrap',
             isWitWidth: true, 
             columnWidth: 240
             });
             */

            /////
            /// End Drupal.behaviors.theme
            ///// 
        }
    };
})(jQuery);