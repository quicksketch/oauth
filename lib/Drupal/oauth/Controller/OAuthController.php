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
    $list = array();

    $list['heading']['#markup'] = l(t('Add consumer'), 'user/' . $user->id() . '/oauth/consumer/add');

    // Get the list of consumers.
    $result = db_query('select *
                        from {oauth_consumer}
                        where uid = :uid', array(':uid' => $user->id()));

    // Define table headers.
    $list['table'] = array(
      '#theme' => 'table',
      '#header' => array(
        'name' => array(
          'data' => t('Consumer name'),
        ),
        'consumer_key' => array(
          'data' => t('Consumer key'),
        ),
        'operations' => array(
          'data' => t('Operations'),
        ),
      ),
      '#rows' => array(),
    );

    // Add existing consumers to the table.
    foreach ($result as $row) {
      $list['table']['#rows'][] = array(
        'data' => array(
          'name' => $row->name,
          'consumer_key' => $row->consumer_key,
          'operations' => array(
            'data' => array(
              '#type' => 'operations',
              '#links' => array(
                'view' => array(
                  'title' => t('View'),
                  'href' => '',
                ),
                'edit' => array(
                  'title' => t('Edit'),
                  'href' => '',
                ),
                'delete' => array(
                  'title' => t('Delete'),
                  'href' => '',
                ),
              ),
            ),
          ),
        ),
      );
    }

    $list['table']['#empty'] = t('There are no OAuth consumers.');

    return $list;
  }

}
