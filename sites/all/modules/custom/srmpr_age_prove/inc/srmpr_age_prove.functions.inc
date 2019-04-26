<?php
function _insert_database($values, $data_redirect,$params) {
  $day = $values['age_day'];
  $month = $values['age_month'];
  $year = $values['age_year'];

  $day_all = $day.'-'.$month.'-'.$year;
  try {
    $nid = db_insert('ageValidation') -> fields(
      array(
        'ip_address' => _get_user_ipaddr(),
        'date_submit'   => $day_all,
        'date' => format_date(time(), 'custom', 'Y-m-d H:i:s'),
      )
    )-> execute();  
    drupal_goto($data_redirect,$params);
  } catch (\Throwable $th) {
    watchdog('cg_volunteer', 'Error save to data from form age validate  date to age:  %date_submit,  date to submit form : %date, ip address :  %ip_address', array('%date_submit' => $day_all,'%ip_address' =>  _get_user_ipaddr(), '%date' => format_date(time(), 'custom', 'Y-m-d 00:00:00') ), WATCHDOG_ERROR);
  }
}

function _get_user_ipaddr(){
  if(!empty($_SERVER['HTTP_CLIENT_IP'])){
      //ip from share internet
      $ip = $_SERVER['HTTP_CLIENT_IP'];
  }elseif(!empty($_SERVER['HTTP_X_FORWARDED_FOR'])){
      //ip pass from proxy
      $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
  }else{
      $ip = $_SERVER['REMOTE_ADDR'];
  }
  return $ip;
}
