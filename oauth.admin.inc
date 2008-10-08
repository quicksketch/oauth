<?php
// $Id$
/**
 * @author OAuth module Dev Team
 * @file
 *  OAuth module's admin pages.
 */

/**
 * Main module settings.
 */
function _oauth_admin() {
  $form['oauth_crypt'] = array(
    '#default_value'  => variable_get('oauth_crypt', 'PLAINTEXT'),
    '#description'    => t('When enabled, all method calls must include a valid OAuth access token and consumer token.'),
    '#options'        => array(
      'PLAINTEXT' => t('Plain text (UNSECURE)'),
      'HMAC-SHA1' => t('HMAC-SHA1'),
      'RSA-SHA1'  => t('RSA-SHA1'),
    ),
    '#title'          => t('OAuth cryptography'),
    '#type'           => 'radios',
  );

  return system_settings_form($form);
}
