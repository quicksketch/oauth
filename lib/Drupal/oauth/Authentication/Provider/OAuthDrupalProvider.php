<?php

/**
 * @file
 * Contains \Drupal\oauth\Authentication\Provider\OAuthProvider.
 */

namespace Drupal\oauth\Authentication\Provider;

use Drupal\Core\Authentication\AuthenticationProviderInterface;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpKernel\Exception\AccessDeniedHttpException;
use Symfony\Component\HttpKernel\Event\GetResponseForExceptionEvent;
use \OauthProvider;

/**
 * Oauth authentication provider.
 */
class OAuthDrupalProvider implements AuthenticationProviderInterface {

  /**
   * {@inheritdoc}
   */
  public function applies(Request $request) {
    // Only check requests with the 'authorization' header starting with OAuth.
    return preg_match('/^OAuth/', $request->headers->get('authorization'));
  }

  /**
   * {@inheritdoc}
   */
  public function authenticate(Request $request) {
    // Initialize and configure the OauthProvider too handle the request.
    $this->provider = new OAuthProvider();
    $this->provider->consumerHandler(array($this,'lookupConsumer'));
    $this->provider->timestampNonceHandler(array($this,'timestampNonceChecker'));
    $this->provider->tokenHandler(array($this,'tokenHandler'));
    $this->provider->is2LeggedEndpoint(TRUE);

    // Now check the request validity.
    $this->provider->checkOAuthRequest();
    $user = user_load(1);
    return $user;

    //return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function cleanup(Request $request) {}

  /**
   * {@inheritdoc}
   */
  public function handleException(GetResponseForExceptionEvent $event) {
    return FALSE;
  }

  public function lookupConsumer($provider) {
    dd(array(__LINE__, $provider));
    /*$sql = 'select consumer_secret from oauth_consumers '
        . 'where consumer_key = :key';
    $stmt = $db->prepare($sql);
    $response = $stmt->execute(array(
        ':key' => $provider->token
        ));
    if($response) {
        $results = $stmt->fetchAll(PDO::FETCH_ASSOC);
        // just one row needed
        $consumer = $results[0];
    }*/
    $provider->consumer_secret = 'b';
    return OAUTH_OK;
  }

  public function tokenHandler($provider) {
    dd(array(__LINE__, $provider));
    return OAUTH_OK;
  }

  public function timestampNonceChecker($provider) {
    dd(array(__LINE__, $provider));
    return OAUTH_OK;
  }
}
