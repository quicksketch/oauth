<?php

/**
 * @file
 * Contains \Drupal\oauth\Controller\OAuthController.
 */

namespace Drupal\oauth\Controller;

use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\Core\DependencyInjection\ContainerInjectionInterface;
use Drupal\user\UserInterface;

/**
 * Controller routines for book routes.
 */
class OAuthController implements ContainerInjectionInterface {

  /**
   * Constructs a BookController object.
   */
  public function __construct() {
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static();
  }

  /**
   * Returns the list of consumers for a user.
   *
   * @param \Drupal\user\UserInterface $user
   *   A user account object.
   *
   * @return string
   *   A HTML-formatted string with the list of OAuth consumers.
   */
  public function consumers(UserInterface $user) {
    return l(t('Add consumer'), 'user/' . $user->id() . '/oauth/consumer/add');
  }

}
