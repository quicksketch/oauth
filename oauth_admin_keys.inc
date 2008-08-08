<?php

function oauth_admin_keys_list($application_key = NULL) {
	
 //deletion function on user demand from /user/%user/oauth page
   
 if($application_key){
	global $user;
	db_query("DELETE FROM {oauth_cool_auth} WHERE application_key='%s'", $application_key);
 	drupal_set_message('<pre>'.print_r("$application_key has been deleted", TRUE).'</pre>');
 }
  
  $keys = oauth_get_keys();
  $header = array(t('uid'), t('Key'), t('Secret'), t('Title'), t('Domain'), t('Type'), array('data' => t('Operations'), 'colspan' => '1'));
  $rows = array();

  foreach ($keys as $kid => $key) {
    $row = array();
    
    if($key->application_type == 0){
        $option = 'Web';
    }else if($key->application_type == 1 ){
            $option = 'Desktop';
    }else{
            $option = 'Mobile';
    }
    
    $row[] = $kid;
    $row[] = $key->application_key;
    $row[] = $key->application_secret;
    $row[] = $key->application_title;
    $row[] = $key->application_url;
    $row[] = $option;
    
    // Populate the operations field.
    $operations = array();

    // Set the edit column.
    //$operations[] = array('data' => l(t('edit'), 'admin/build/oauth/keys/edit'. $key->application_key));

    // Set the delete column.
    $operations[] = array('data' => l(t('delete'), 'admin/build/oauth/registered/'. $key->application_key));
    
    //$row = array(array('data' => l($kid, 'admin/build/services/keys/'. $type_url_str), 'class' => $class), array('data' => check_plain($type->type), 'class' => $class), array('data' => check_plain($type->description), 'class' => $class));
    foreach ($operations as $operation) {
      $operation['class'] = $class;
      $row[] = $operation;
    }
    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No website registered to use cool auth on server.'), 'colspan' => '5', 'class' => 'message'));
  }

  return theme('table', $header, $rows);
}

function oauth_get_keys() {
  static $keys;
  if (!$keys) {
    $keys = array();
    $result = db_query("SELECT * FROM {oauth_cool_auth}");
    while ($key = db_fetch_object($result)) {
      $keys[$key->uid] = $key;
    }
  }
  return $keys;
}

function oauth_cool_auth_admin_form($form_state) {
   
   if($form_state['storage']['confirm'] == ''){    
    $form['uid'] = array(
	'#title' => t('UserID'),
	'#description' => t('uid corresponding to whome you ant to register an cool auth API key'),
	'#type' => 'textfield',
	'#size' => 4,
    );
    $form['uid_submit'] = array(
	'#title' => t('submit'),
	'#value' => t('continue'),
	'#type' => 'submit',
    );
    return $form;
   }
   
   if($form_state['storage']['confirm'] == 1){
    
    $default_values = db_fetch_array(db_query("SELECT * from {oauth_cool_auth} WHERE uid=%d", $form_state['storage']['uid']));
    if($default_values == ''){
       $default_values['application_type'] = 0;
    }
    $form['application_title'] = array(
        '#title' => t('TITLE'),
        '#description' => t('Title for application.'),
        '#type' => 'textfield',
        '#default_value' => $default_values['application_title'],
    );
    $form['application_description'] = array(
        '#title' => t('Description'),
        '#description' => t('Details about your application.'),
        '#type' => 'textarea',
        '#default_value' => $default_values['application_description'],
	'#weight' => .5,
    );
    $form['application_notes'] = array(
        '#title' => t('Notes'),
        '#type' => 'textarea',
        '#default_value' => $default_values['application_notes'],
	'#weight' => 1,
    );
    $form['application_url'] = array(
        '#title' => t('Application URL'),
        '#description' => t('URL of your application which is making access to server.'), 
        '#type' => 'textfield',
        '#default_value' => $default_values['application_url'],
    );
    $options = array(0 => t('Web Application'), 1 => t('Desktop Application'), 2 => t('Mobile Application'));
    $form['application_type'] = array(
        '#title' => t('Type of Application'),
        '#type' => 'radios',
        '#options' => $options,
        '#default_value' => $default_values['application_type'],
    );
    $form['application_callback_url'] = array(
        '#title' => t('Callback URL'),
        '#description' => t('address of callback URL of your service'),
        '#type' => 'textfield',
        '#default_value' => $default_values['application_callback_url'],
    );
    $form['save_application'] = array(
        '#title' => t('SAVE APPLICATION'),
        '#value' => t('SAVE APPLICATION'),
        '#type' => 'submit',
	'#weight' => 2,
    );
    return $form;
   }
}

function oauth_cool_auth_admin_form_validate($form, &$form_state){ 
     if($form_state['values']['op'] == 'continue'){
      if($form_state['values']['uid'] == ''){
	  form_set_error('form', t('Please fill a valid uid value'));
      }elseif(user_load($form_state['values']['uid']) == ''){
	  form_set_error('form', t('USER does not exist!!'));
       }      
     }
     if($form_state['values']['op'] == 'SAVE APPLICATION'){
      if($form_state['values']['application_title'] == ''){
	  form_set_error('form', t('Please fill a valid application-title.'));
      }elseif(!check_url($form_state['values']['application_url'])){
          form_set_error('form', t('Please fill a valid url for application.')); 
      }
      
     }
}

function oauth_cool_auth_admin_form_submit($form, &$form_state) {
 //drupal_set_message('<pre>'.print_r($form_state, TRUE).'</pre>');
  $is_existing = FALSE;
  //$key['uid'] = !empty($key['uid']) ? $key['uid'] : md5(uniqid(mt_rand(), true));
  $is_existing =  db_result(db_query("SELECT application_key FROM {oauth_cool_auth} WHERE uid = %d", $form_state['values']['uid']));
 if($form_state['values']['op'] == 'continue'){
  if ($is_existing) {
   //$form_state['storage']['default_values'] = db_fetch_array(db_query("SELECT * FROM {oauth_cool_auth} WHERE uid=%d", $form_state['values']['uid']));
   $form_state['storage']['confirm'] = 1;
   $form_state['storage']['uid'] = $form_state['values']['uid'];
   return;
  }else{
   $form_state['storage']['confirm'] = 1;
   $form_state['storage']['uid'] = $form_state['values']['uid'];  
   return;
  }
 }
  
   if($form_state['values']['op'] == 'SAVE APPLICATION'){
    $check = db_result(db_query("SELECT application_key FROM {oauth_cool_auth} WHERE uid=%d", $form_state['storage']['uid']));
    
    if(!$check){        
        $application_key = md5(uniqid(mt_rand(), true));
        $application_secret = md5(uniqid(mt_rand(), true));
        db_query("INSERT INTO {oauth_cool_auth} (uid, application_key, application_secret, application_title, application_description, application_notes, application_url, application_type, application_callback_url) VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s')", $form_state['storage']['uid'], $application_key, $application_secret, $form_state['values']['application_title'], $form_state['values']['application_description'], $form_state['values']['application_notes'], $form_state['values']['application_url'], $form_state['values']['application_type'], $form_state['values']['application_callback_url']);
        
    }else{        
        db_query("UPDATE {oauth_cool_auth} SET application_title='%s', application_description='%s', application_notes='%s', application_url='%s', application_type=%d, application_callback_url='%s' WHERE uid=%d ", $form_state['values']['application_title'], $form_state['values']['application_description'], $form_state['values']['application_notes'], $form_state['values']['application_url'], $form_state['values']['application_type'], $form_state['values']['application_callback_url'], $form_state['storage']['uid'] );
    }
    
   }
  
  return 'admin/build/oauth/registered';
}

function oauth_admin_keys_save($form_state) {
  
  $is_existing = FALSE;
  //$key['uid'] = !empty($key['uid']) ? $key['uid'] : md5(uniqid(mt_rand(), true));
  $is_existing =  db_result(db_query("SELECT application_key FROM {oauth_cool_auth} WHERE uid = %d", $form_state['values']['uid']));

  if ($is_existing) {
    db_query("UPDATE {oauth_cool_auth} SET application_title='%s', application_description='%s', application_notes='%s', application_url='%s', application_type=%d, application_callback_url='%s' WHERE uid=%d ", $form_state['values']['application_title'], $form_state['values']['application_description'], $form_state['values']['application_notes'], $form_state['values']['application_url'], $form_state['values']['application_type'], $form_state['values']['application_callback_url'], $form_state['storage']['uid'] );
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
