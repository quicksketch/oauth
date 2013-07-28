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
   * An authenticated user object.
   *
   * @var \Drupal\user\UserBCDecorator
   */
  protected $user;

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
    if (!empty($this->user)) {
      return $this->user;
    }
    return NULL;
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

  /**
   * Finds a user associated with the OAuth crendentials given in the request.
   *
   * For the moment it handles two legged authentication for a pair of
   * dummy key and secret, 'a' and 'b' respectively.
   *
   * @param \OAuthProvider
   *   An instance of OauthProvider with the authorization request headers.
   * @return
   *   constant OAUTH_OK if the authentication was successfull.
   *   OAUTH_CONSUMER_KEY_UNKNOWN if not.
   * @see http://www.php.net/manual/en/class.oauthprovider.php
   */
  public function lookupConsumer($provider) {
    if ($provider->consumer_key == 'a') {
      $provider->consumer_secret = 'b';
      $this->user = user_load(1);
      return OAUTH_OK;
    }
    else {
      return OAUTH_CONSUMER_KEY_UNKNOWN;
    }
  }

  /**
   * Token handler callback.
   *
   * @TODO this will be used in token authorization.
   */
  public function tokenHandler($provider) {
    return OAUTH_OK;
  }

  /**
   * Nonce handler.
   *
   * @TODO need to remember what the hell this was.
   */
  public function timestampNonceChecker($provider) {
    return OAUTH_OK;
  }
}
