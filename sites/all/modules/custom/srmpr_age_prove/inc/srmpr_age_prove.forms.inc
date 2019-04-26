<?php

function srmpr_age_prove_form_config($form, &$form_state){
    $form = array();
    //Verified active form
    $form['config_age_front_page'] = array(
      '#type' =>'checkbox',
      '#title' => t('Active form user loged'),
      '#default_value' => variable_get('config_age_front_page',TRUE),
    );
    //Set a url redirect
    $form['config_age_redirect_url'] = array(
      '#type' =>'textfield',
      '#title' => t('url redirect'),
      '#default_value' => variable_get('config_age_redirect_url',""),
      '#weight' => 0,
    );
    //add container fieldset Age pages
    $form['visibility'] = array(
      '#type' => 'fieldset',
      '#title' => t('Visibility Age pages'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => 1,
    );
    //options for radiobuttons list
    $options = array(
      "view_execept_listed" => t('All pages except those listed'),
      "view_only_listed" => t('Only the listed pages'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
    //Radios used for determinate the pages use
    $form['visibility']['path']['config_age_listed'] = array(
      '#type' => 'radios',
      '#title' => t('Show form on specific pages'),
      '#options' => $options,
      '#default_value' => variable_get('config_age_listed',"view_listed_true"),
    );
    //add list to pages permissions
    $form['visibility']['path']['config_age_list'] = array(
      '#type' => 'textarea',
      '#default_value' => variable_get('config_age_list',""),
      '#description' => $description,
    );
    return system_settings_form($form);
}

function srmpr_age_receive_form($form, &$form_state){
  $form = array();
  //Verified active form
  $form['age_day'] = array(
    '#type' =>'textfield',
    '#attributes' => array(
      'placeholder' => t('DD'),
      'maxlength' => 2,
    ),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $form['age_month'] = array(
    '#type' =>'textfield',
    '#attributes' => array(
      'placeholder' => t('MM'),
      'maxlength' => 2,
    ),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $form['age_year'] = array(
    '#type' =>'textfield',
    '#attributes' => array(
      'placeholder' => t('YYYY'),
      'maxlength' => 4,
    ),
    '#required' => TRUE,
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $form['age_remember'] = array(
    '#type' =>'checkbox',
    '#title' => t('Remember'),
    '#prefix' => '<div class="text-center col-md-12">',
    '#suffix' => '</div>'
  );
  $form['from'] = array(
    '#markup' => "Do not stay conected if the computer is shared with people under the age to 18. By clicking here and facebook connect, you'll accept the use of cookies, terms and privacy policy",
  
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#prefix' => '<div class="text-center">',
    '#suffix' => '</div>'
  );

  return $form;
}

function srmpr_age_receive_form_validate($form, &$form_state){
  $values = $form_state['values'];
  $day = $values['age_day'];
  $month = $values['age_month'];
  $year = $values['age_year'];
  if(!is_numeric($day)){
    form_set_error('age_day', t('Is necessary add a Day number'));
  }
  if(!is_numeric($month)){
    form_set_error('age_month', t('Is necessary add a Month number'));
  }
  if(!is_numeric($year)){
    form_set_error('age_year', t('Is necessary add a Year number'));
  }
  $timestamp = strtotime("{$day}-{$month}-{$year}");
  if($timestamp > time()){
    form_set_error('age_year', t('The age not is valid'));
  }

}

function srmpr_age_receive_form_submit($form, &$form_state){

  $values = $form_state['values'];
  $day = $values['age_day'];
  $month = $values['age_month'];
  $year = $values['age_year'];

  $timestamp = strtotime("{$day}-{$month}-{$year}");
  if($timestamp > strtotime('-18 year', time())){
    module_load_include('inc', 'srmpr_age_prove', 'inc/srmpr_age_prove.functions');
    unset($_GET['destination']);
    $redirect_set = variable_get('config_age_redirect_url','home');
    $data_redirect = explode("?",$redirect_set);
    if(count($data_redirect) > 1){
      parse_str($data_redirect[1],$params);
      $params = array('query' => $params);
    }else{
      $params = array();
    }
    _insert_database($values, $data_redirect[0],$params);
  }
  else{
    $params_redirect = $_GET;
    $destination = $_GET['destination'];
    unset($params_redirect['q']);
    unset($params_redirect['destination']);
    unset($_GET['destination']);
    setcookie(
      "adult",
      "yes",
      time() + (10 * 365 * 24 * 60 * 60)
    );
    drupal_goto($destination, array('query' =>$params_redirect));

  }
}

