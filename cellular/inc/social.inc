<?php

/* * ************
  Social media follow links
 * ************** */

function cellular_social_media_follow() {
    $output = '';

    if (theme_get_setting('social_media_follow') == 1) {

        $media_block = array(
            'title' => t('Follow Us'),
            'id' => 'social-media-follow',
            //'class' => '',
            'description' => t('Follow our current posts'),
            'links' => array(),
            'link_class' => 'social icon',
            'markup' => '',
        );

        $links = array(
            'facebook' => theme_get_setting('follow_facebook') == 1 ?
                    array(
                'url' => theme_get_setting('follow_facebook_url'),
                'class' => 'facebook',
                'name' => t('Facebook'),
                    ) : null,
            'google+' => theme_get_setting('follow_google_plus') == 1 ?
                    array(
                'url' => theme_get_setting('follow_google_plus_url'),
                'class' => 'google',
                'name' => t('Google+'),
                    ) : null,
            'twitter' => theme_get_setting('follow_twitter') == 1 ?
                    array(
                'url' => theme_get_setting('follow_twitter_url'),
                'class' => 'twitter-bird',
                'name' => t('Twitter'),
                    ) : null,
            'linkedin' => theme_get_setting('follow_linkedin') == 1 ?
                    array(
                'url' => theme_get_setting('follow_linkedin_url'),
                'class' => 'linkedin',
                'name' => t('LinkedIn'),
                    ) : null,
            'github' => theme_get_setting('follow_github') == 1 ?
                    array(
                'url' => theme_get_setting('follow_github_url'),
                'class' => 'github-octo',
                'name' => t('Github'),
                    ) : null,
        );

        foreach ($links as $link) {
            if (!empty($link['url'])) {
                array_push($media_block['links'], $link);
            }
        }
        foreach ($media_block['links'] as $link) {
            $media_block['markup'] .= l("Follow us on " . $link['name'], $link['url'], array(
                'attributes' => array(
                    'class' => array(
                        $media_block ['link_class'],
                        $link['class']
                    )
                ),
                    )
            );
        }

        if (!empty($media_block['links'])) {

            $output .= "\n<div id=\"" . $media_block ['id'] . "\">\n";
            $output .= "<h3>" . $media_block ['title'] . "</h3>\n";
            $output .= $media_block ['markup'] . "\n";
            $output .= "</div>\n\n";
        }
    }
    return $output;
}

/* * ************
  Social media share links
 * ************** */

function cellular_social_media_share() {
    global $base_url;
    $output = '';

    if (theme_get_setting('social_media_share') == 1) {

        $page = array(
            'url' => $base_url . '/' . current_path(),
            'title' => drupal_get_title(),
        );
        $media_block = array(
            'title' => t('Share this page'),
            'id' => 'social-media-share',
            //'class' => '',
            'description' => t('Share this page with your network.'),
            'link_class' => 'social icon',
            'markup' => '',
        );

        $links = array(
            'google+' => theme_get_setting('share_google_plus') == 1 ?
                    array(
                'title' => 'Google+',
                'script' => null,
                'url' => 'http://plus.google.com/share?url=' . $page['url'],
                'class' => 'google'
                    ) : null,
            'twitter' => theme_get_setting('share_twitter') == 1 ?
                    array(
                'title' => 'Twitter',
                'script' => null,
                'url' => 'https://twitter.com/share',
                'class' => 'twitter-bird'
                    ) : null,
            'linkedin' => theme_get_setting('share_linkedin') == 1 ?
                    array(
                'title' => '',
                'script' => null,
                'url' => 'http://www.linkedin.com/shareArticle?mini=true&url=' . $page ['url'] . '&title=' . $page ['title'] . '&source=' . $base_url,
                'class' => 'linkedin'
                    ) : null,
            'pinterest' => theme_get_setting('share_pinterest') == 1 ?
                    array(
                'title' => 'Pinterest',
                'script' => null,
                'url' => 'http://pinterest.com/pin/create/bookmarklet/?media=&url=' . $page ['url'] . '&is_video=false&description=' . $page['title'],
                'class' => 'pinterest'
                    ) : null,
            'reddit' => theme_get_setting('share_reddit') == 1 ?
                    array(
                'title' => 'Reddit',
                'script' => null,
                'url' => 'http://www.reddit.com/submit?url=' . $page['url'],
                'class' => 'reddit'
                    ) : null
        );


        $facebook = theme_get_setting('share_facebook') == 1 ?
                array(
            'script' => '(function(d, s, id) {
                            var js, fjs = d.getElementsByTagName(s)[0];
                            if (d.getElementById(id)) return;
                            js = d.createElement(s); js.id = id;
                            js.src = "//connect.facebook.net/en_US/all.js#xfbml=1";
                            fjs.parentNode.insertBefore(js, fjs);
                            }(document, \'script\', \'facebook-jssdk\'));',
            'tag' => '<div class="fb-like" data-href="' . $page['url'] . '" data-layout="button" data-action="like" data-show-faces="false" data-share="true"></div><div id="fb-root"></div>',
            'weight' => 1000,
                ) : null;


        if (!empty($facebook)) {
            $links[] = $facebook;
        }

        foreach ($links as $link) {
            if (!empty($link['script'])) {
                // Push script to the end
                drupal_add_js($link['script'], array(
                    'type' => 'inline',
                    'group' => JS_THEME,
                    'weight' => isset($link['weight']) ? $link['weight'] : 100,
                ));
            }
            if (!empty($link['url'])) {
                $media_block['markup'] .= l('Share this page on ' . $link['title'], $link['url'], array(
                    'attributes' => array(
                        'class' => array(
                            $media_block['link_class'],
                            $link['class']
                        )
                    ),
                        )
                );
            }
            if (!empty($link['tag'])) {
                $media_block['markup'] .= "\n " . $link['tag'] . "\n";
            }
        }

        $output .= "\n";
        $output .= '<div id="' . $media_block['id'] . '">';
        $output .= "\n<h3>" . $media_block['title'] . "</h3>\n";
        $output .= $media_block['markup'];
        $output .= "</div>\n\n";
    }
    return $output;
}