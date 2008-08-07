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
        '#description' => t('URL of your application which is making access to server'), 
        '#type' => 'textfield',
        '#default_value' => $default_values['application_url'],
    );
    $options = array(0 => t('Web Application'), 1 => t('Desktop Application'), 2 => t('Mobile Application'));
    $form['application_type'] = array(
        '#title' => t('Type of Application'),
        '#type' => 'radios',
        '#options' => $options,
        '#default_value' => 0,
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
        '#weight' => 2,
    );
    return $form;
  }
    if($check && $form_state['storage']['coolauth_edit'] != 1){
        
    $default_values = db_fetch_array(db_query("SELECT * from {oauth_cool_auth} WHERE uid=%d", $user->uid));
    //drupal_set_message('<pre>'.print_r($default_values, TRUE).'</pre>');    
    $form['fieldset'] = array(
        '#title' =>  '<strong><i>'.t('Your COOL AUTH Credentials Please use them to access this websites Data using OAuth as per <a href="http://drupal.org">API Documentation</a>').'</i></strong>',
        '#type' => 'fieldset',                        
    );
    $form['fieldset']['key'] = array(
        '#title' => '<strong><i><b>'.t('COOL AUTH API Key').'</b></i></strong>',
        '#type' => 'item',
        '#description' => '<h3><b>'.$default_values['application_key'].'</b></h3>',
    );
    $form['fieldset']['secret'] = array(
        '#title' => '<strong><b><i>'.t('COOL AUTH API SECRET').'</i></b></strong>',
        '#type' => 'item',
        '#description' => '<h3><b>'.$default_values['application_secret'].'</b></h3>',
    );
    $form['fieldset']['title'] = array(
        '#title' => '<strong><b><i>'.t('APPLICATION TITLE').'</i></b></strong>',
        '#type' => 'item',
        '#description' => '<strong><i><b>'.$default_values['application_title'].'</b></i></strong>',
    );
    $form['fieldset']['description'] = array(
        '#title' => '<strong><b><i>'.t('APPLICATION DESCRIPTION').'</i></b></strong>',
        '#type' => 'item',
        '#description' => '<strong><i>'.$default_values['application_description'].'</i></strong>',
    );
    $form['fieldset']['notes'] = array(
        '#title' => '<strong><b><i>'.t('NOTES').'</i></b></strong>',
        '#type' => 'item',
        '#description' => '<strong><i>'.$default_values['application_notes'].'</i></strong>',
    );
    $form['fieldset']['url'] = array(
        '#title' => '<strong><b><i>'.t('APPLICATION URL').'</i></b></strong>',
        '#type' => 'item',
        '#description' => '<strong><b><i>'.$default_values['application_url'].'</i></b></strong>',
    );
    
    if($default_values['application_type'] == 0){
        $option = 'Web';
    }else if($default_values['application_type'] == 1 ){
            $option = 'Desktop';
    }else{
            $option = 'Mobile';
    }
    $form['fieldset']['type'] = array(
        '#title' => '<strong><b><i>'.t('APPLICATION TYPE').'</i></b></strong>',
        '#type' => 'item',
        '#description' => '<strong>'.$option.'</strong>',
    );
    $form['fieldset_1'] = array(
        '#title' => '<h4><i>'.t('Options').'</i></h4>',
        '#type' => 'fieldset',
    );
    $form['fieldset_1']['coolauth_edit'] = array(
        '#title' => t('EDIT VALUES'),
        '#value' => t('EDIT VALUES'),
        '#type' => 'submit',
    );
    $form['fieldset_1']['coolauth_delete'] = array(
        '#title' => t('DELETE APPLICATION'),
        '#value' => t('DELETE APPLICATION'),
        '#type' => 'submit',
    );
    return $form;
    
  }
  if( $check && $form_state['storage']['coolauth_edit'] == 1){
    $form_state['storage']['coolauth_edit'] = 0;
    $default_values = db_fetch_array(db_query("SELECT * from {oauth_cool_auth} WHERE uid=%d", $user->uid));
    $form['fieldset'] = array(
        '#title' => t('Application Details'),
        '#type' => 'fieldset',
     );    
    $form['fieldset']['application_title'] = array(
        '#title' => '<strong><b><i>'.t('TITLE').'</strong></b></i>',
        '#description' => t('Title for application you are registering api key'),
        '#type' => 'textfield',
        '#default_value' => $default_values['application_title'],
    );
    $form['fieldset']['application_description'] = array(
        '#title' => '<strong><b><i>'.t('Description').'</strong></b></i>',
        '#description' => t('Description about your application'),
        '#type' => 'textarea',
        '#default_value' => $default_values['application_description'],
        '#weight' => .5,
    );
    $form['fieldset']['application_notes'] = array(
        '#title' => '<strong><b><i>'.t('Notes').'</strong></b></i>',
        '#type' => 'textarea',        
        '#default_value' => $default_values['application_notes'],
        '#weight' => 1,
    );
    $form['fieldset']['application_url'] = array(
        '#title' => '<strong><b><i>'.t('Application URL').'</strong></b></i>',
        '#description' => t('URL of your application which is making access to server'), 
        '#type' => 'textfield',
        '#default_value' => $default_values['application_url'],
    );
    $options = array(0 => t('Web Application'), 1 => t('Desktop Application'), 2 => t('Mobile Application'));
    $form['fieldset']['application_type'] = array(
        '#title' => '<strong><b><i>'.t('Type of Application').'</strong></b></i>',
        '#type' => 'radios',
        '#options' => $options,
        '#default_value' => $default_values['application_type'],
    );
    $form['fieldset']['application_callback_url'] = array(
        '#title' => '<strong><b><i>'.t('Callback URL').'</strong></b></i>',
        '#description' => t('address of callback URL of your service'),
        '#type' => 'textfield',
        '#default_value' => $default_values['application_callback_url'],
    );
    $form['fieldset_submit'] = array(
        '#title' => '<strong><b><i>'.t('Save Application').'</i></b></strong>',
        '#type' => 'fieldset',
    );
    $form['fieldset_submit']['save_application'] = array(
        '#title' => t('Save values for APP'),
        '#value' => t('SAVE APPLICATION'),
        '#type' => 'submit',
        '#weight' => 2,        
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