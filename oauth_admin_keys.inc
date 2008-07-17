<?php

function oauth_admin_keys_list($token_delete = NULL) {
	
 //deletion function on user demand from /user/%user/oauth page
   
 if($token_delete){
	global $user;
	db_query("DELETE FROM {oauth_token} WHERE token_key='%s'", $token);
 	drupal_set_message('<pre>'.print_r("$token_delete token has been deleted", TRUE).'</pre>');
 }
  
  $keys = oauth_get_keys();
  $header = array(t('Key'), t('Title'), t('Domain'), array('data' => t('Operations'), 'colspan' => '2'));
  $rows = array();

  foreach ($keys as $kid => $key) {
    $row = array();
    
    $row[] = $kid;
    $row[] = $key->title;
    $row[] = $key->domain;
    
    // Populate the operations field.
    $operations = array();

    // Set the edit column.
    //$operations[] = array('data' => l(t('edit'), 'admin/build/oauth/keys/edit'. $kid));

    // Set the delete column.
    //$operations[] = array('data' => l(t('delete'), 'admin/build/oauth/keys/'. $kid .'/delete'));
    
    //$row = array(array('data' => l($kid, 'admin/build/services/keys/'. $type_url_str), 'class' => $class), array('data' => check_plain($type->type), 'class' => $class), array('data' => check_plain($type->description), 'class' => $class));
    foreach ($operations as $operation) {
      $operation['class'] = $class;
      $row[] = $operation;
    }
    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No website registered to use OAuth on server.'), 'colspan' => '5', 'class' => 'message'));
  }

  return theme('table', $header, $rows);
}

function oauth_get_keys() {
  static $keys;
  if (!$keys) {
    $keys = array();
    $result = db_query("SELECT * FROM {oauth_registered_sites}");
    while ($key = db_fetch_object($result)) {
      $keys[$key->kid] = $key;
    }
  }
  return $keys;
}

function oauth_admin_keys_form($KID =  NULL) {
		
  $form['kid'] = array(
    '#type' => 'hidden',
    '#default_value' => $key->kid,
  );
  
  if ($key->kid) {
    $form['key'] = array(
      '#type' => 'markup',
      '#title' => t('Key'),
      '#value' => '<strong>'. t('API Key') .':</strong> '. $key->kid,
    ); 
  }
  
  $form['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#default_value' => $key->title,
    '#description' => t('The title of the application or website using OAuth on this SERVER.'),
  );
  $form['domain'] = array(
    '#title' => t('Domain which will make OAuth requests'),
    '#type' => 'textfield',
    '#default_value' => $key->domain,
    '#description' => t('Please do not include "http://" OR "www" before domain name eg. sumitk.net .'.
    'Also please register main URL of your domain here eg. for http://sumitk.net/sandbox1/ USE sumitk.net'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => ($key) ? t('Save website') : t('save'),
  );
  
  return $form;
}

function oauth_admin_keys_form_submit($form, $form_state) {
  
  oauth_admin_keys_save($form_state['values']);
  
  return 'admin/build/oauth/keys';
}

function oauth_admin_keys_save($key) {

  $is_existing = FALSE;
  $key['kid'] = !empty($key['kid']) ? $key['kid'] : md5(uniqid(mt_rand(), true));
  $is_existing =  db_result(db_query("SELECT count(*) FROM {oauth_registered_sites} WHERE kid = '%s'", $key['kid']));

  if ($is_existing) {
    db_query("UPDATE {oauth_registered_sites} SET title = '%s', domain = '%s' WHERE kid = '%s'", $key['title'], $key['domain'], $key['kid']);
    return SAVED_UPDATED;
  }
  else {
    db_query("INSERT INTO {oauth_registered_sites} (kid, title, domain) VALUES ('%s', '%s', '%s')", $key['kid'], $key['title'], $key['domain']);
    return SAVED_NEW;
  }
}

function oauth_admin_keys_delete($kid) {
  db_query("DELETE FROM {oauth_registered_sites} WHERE kid = '%s'", $kid);
}

function oauth_admin_keys_delete_confirm($key) {
  $form['kid'] = array('#type' => 'value', '#value' => $key->kid);

  $message = t('Are you sure you want to delete the website with key %key?', array('%key' => $key->kid));
  $caption = '';

  $caption .= '<p>'. t('This action cannot be undone.') .'</p>';

  return confirm_form($form, $message, 'admin/build/oauth/keys', $caption, t('Delete'));
}

function oauth_admin_keys_delete_confirm_submit($form_id, $form_values) {
  oauth_admin_keys_delete($form_values['kid']);

  $t_args = array('%key' => $form_values['kid']);
  drupal_set_message(t('The key %key has been deleted.', $t_args));
  watchdog('menu', t('Deleted key %key.', $t_args), WATCHDOG_NOTICE);

  return 'admin/build/oauth/keys';
}
