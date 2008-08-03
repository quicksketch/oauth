<?php

/*
 * Cool Auth System : this system is like other community sites api system
 * it make users to register an api key to access data from a drupal web site
 * this provides a full form stores whole information regarding thier application 
 * and type of access + thier application's logo 
 * 
 * Rest of details laterrrrrr
 */


function cool_auth_system_admin_form(&$form_state){
    //drupal_set_message('<pre>'.print_r($form_state, TRUE).'</pre>');
    global $user;
    $check = db_result(db_query("SELECT application_key FROM {oauth_cool_auth} WHERE uid=%d", $user->uid));
    
    if($check == '' && $form_state['storage']['first_access'] != 1){
        
    $form['first_access']= array(
        '#value' => t('USE COOL AUTH FROM YOUR ACCOUNT'),
        '#type' => 'submit',
        );
    return $form;
    }
    
    if($form_state['storage']['first_access'] == 1 && $check == ''){
    $form['application_title'] = array(
        '#title' => t('TITLE'),
        '#description' => t('Title for application you are registering api key'),
        '#type' => 'textfield',
        '#default_value' => $default_values['application_title'],
    );
    $form['application_description'] = array(
        '#title' => t('Description'),
        '#description' => t('Description about your application'),
        '#type' => 'textarea',
        '#default_value' => $default_values['application_description'],        
    );
    $form['application_notes'] = array(
        '#title' => t('Notes'),
        '#type' => 'textarea',
        '#default_value' => $default_values['application_notes'],        
    );
    $form['application_url'] = array(
        '#title' => t('Application URL'),
        '#description' => t('URL of your application which is making access to server'), 
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
        '#title' => t('Save values for APP'),
        '#value' => t('SAVE APPLICATION'),
        '#type' => 'submit',
    );
    return $form;
  }
    if($check && $form_state['storage']['coolauth_edit'] != 1){
        
    $default_values = db_fetch_array(db_query("SELECT * from {oauth_cool_auth} WHERE uid=%d", $user->uid));
    //drupal_set_message('<pre>'.print_r($default_values, TRUE).'</pre>');
    $form['key'] = array(
        '#title' => '<h3>'.t('YOUR API KEY').'</h3>',
        '#type' => 'item',
        '#description' => '<h3>'.$default_values['application_key'].'</h3>',
    );
    $form['secret'] = array(
        '#title' => '<h3>'.t('YOUR API SECRET').'</h3>',
        '#type' => 'item',
        '#description' => '<h3>'.$default_values['application_secret'].'</h3>',
    );
    $form['title'] = array(
        '#title' => '<h3>'.t('APPLICATION TITLE').'</h3>',
        '#type' => 'item',
        '#description' => '<h4>'.$default_values['application_title'].'</h4>',
    );
    $form['description'] = array(
        '#title' => '<h3>'.t('APPLICATION DESCRIPTION').'</h3>',
        '#type' => 'item',
        '#description' => '<h4>'.$default_values['application_description'].'</h4>',
    );
    $form['notes'] = array(
        '#title' => '<h3>'.t('NOTES').'</h3>',
        '#type' => 'item',
        '#description' => '<h4>'.$default_values['application_notes'].'</h4>',
    );
    $form['url'] = array(
        '#title' => '<h3>'.t('APPLICATION URL').'</h3>',
        '#type' => 'item',
        '#description' => '<h4>'.$default_values['application_url'].'</h4>',
    );
    
    if($default_values['application_type'] == 0){
        $option = 'Web';
    }else if($default_values['application_type'] == 1 ){
            $option = 'Desktop';
    }else{
            $option = 'Mobile';
    }
    $form['type'] = array(
        '#title' => '<h3>'.t('APPLICATION TYPE').'</h3>',
        '#type' => 'item',
        '#description' => '<h3>'.$option.'</h3>',
    );
    $form['coolauth_edit'] = array(
        '#title' => t('EDIT VALUES'),
        '#value' => t('EDIT VALUES'),
        '#type' => 'submit',
    );
    $form['coolauth_delete'] = array(
        '#title' => t('DELETE APPLICATION'),
        '#value' => t('DELETE APPLICATION'),
        '#type' => 'submit',
    );
    return $form;
    
  }
  if( $check && $form_state['storage']['coolauth_edit'] == 1){
    $form_state['storage']['coolauth_edit'] = 0;
    $default_values = db_fetch_array(db_query("SELECT * from {oauth_cool_auth} WHERE uid=%d", $user->uid));
    $form['application_title'] = array(
        '#title' => t('TITLE'),
        '#description' => t('Title for application you are registering api key'),
        '#type' => 'textfield',
        '#default_value' => $default_values['application_title'],
    );
    $form['application_description'] = array(
        '#title' => t('Description'),
        '#description' => t('Description about your application'),
        '#type' => 'textarea',
        '#default_value' => $default_values['application_description'],        
    );
    $form['application_notes'] = array(
        '#title' => t('Notes'),
        '#type' => 'textarea',        
        '#default_value' => $default_values['application_notes'],        
    );
    $form['application_url'] = array(
        '#title' => t('Application URL'),
        '#description' => t('URL of your application which is making access to server'), 
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
        '#title' => t('Save values for APP'),
        '#value' => t('SAVE APPLICATION'),
        '#type' => 'submit',
    );
    return $form;
    
  }
  
    
  
 }
 
 function cool_auth_system_admin_form_submit($form, &$form_state){
    //drupal_set_message('<pre>'.print_r($form_state, TRUE).'</pre>');
    global $user;
    if($form_state['values']['op'] == 'USE COOL AUTH FROM YOUR ACCOUNT'){
        $form_state['storage']['first_access'] = 1;    
        //drupal_redirect_form($form, 'user/');
        return;
    }
    $check = db_result(db_query("SELECT application_key FROM {oauth_cool_auth} WHERE uid=%d", $user->uid));
    
    if($form_state['values']['op'] == 'EDIT VALUES'){
        $form_state['storage']['coolauth_edit'] = 1;
        return;
        
    }
    
    if($form_state['values']['op'] == 'DELETE APPLICATION'){
        $form_state['storage']['first_access'] = 0;
        db_query("DELETE FROM {oauth_cool_auth} WHERE uid=%d", $user->uid);
        return;
        
    }
    
    if(!$check){
        
        $application_key = md5(uniqid(mt_rand(), true));
        $application_secret = md5(uniqid(mt_rand(), true));
        db_query("INSERT INTO {oauth_cool_auth} (uid, application_key, application_secret, application_title, application_description, application_notes, application_url, application_type, application_callback_url) VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s')", $user->uid, $application_key, $application_secret, $form_state['values']['application_title'], $form_state['values']['application_description'], $form_state['values']['application_notes'], $form_state['values']['application_url'], $form_state['values']['application_type'], $form_state['values']['application_callback_url']);
        
    }else{        
        db_query("UPDATE {oauth_cool_auth} SET application_title='%s', application_description='%s', application_notes='%s', application_url='%s', application_type=%d, application_callback_url='%s' WHERE uid=%d ", $form_state['values']['application_title'], $form_state['values']['application_description'], $form_state['values']['application_notes'], $form_state['values']['application_url'], $form_state['values']['application_type'], $form_state['values']['application_callback_url'], $user->uid );
    }
    //drupal_redirect_form($form, 'admin/build/oauth');
    
    
 }

?>