<?php

/**
 * @file
 * Contains \Drupal\oauth\Form\OAuthAddConsumerForm.
 */

namespace Drupal\oauth\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Config\ConfigFactory;
use Drupal\Core\Config\Context\ContextInterface;
use Drupal\Core\Path\AliasManagerInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\user\UserInterface;

/**
 * Provides a form to add OAuth consumers.
 */
class OAuthAddConsumerForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  public function getFormID() {
    return 'oauth_add_consumer_form';
  }

  /**
   * Form builder.
   *
   * @param \Drupal\user\UserInterface $user
   *   A user account object.
   */
  public function buildForm(array $form, array &$form_state, UserInterface $user){
    $form = array();

    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Consumer name'),
      '#required' => TRUE,
    );

    $form['callback_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Callback url'),
      '#required' => FALSE,
      '#description' => t('You must include a schema for this to work correctly, ie. http:// or iphoneappname://'),
    );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, array &$form_state) {
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, array &$form_state) {
  }

}
