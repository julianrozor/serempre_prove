<?php
/*
 *Implements Function custom for views table with conexion for database.
 */

function _age_form_data_children_table_custom() {  
  $header_table_edit = array(
    array('data' => t('ID')),  
    array('data' => t('IP ADDRESS')),
    array('data' => t('SUBMIT AGE CHILDREN')),
    array('data' => t('DATE TO SUBMIT')),
  ); 
  $query = db_select('ageValidation', 'it') 
    ->fields('it', array('id', 'ip_address', 'date_submit', 'date')) 
    ->execute() 
    ->fetchAll();  

  foreach ($query as $record_edit_table) {
    $rows_table_edit[] =  
      array(  
        array(   
          'data' => $record_edit_table->id,
        ),
        array(  
           'data' => $record_edit_table->ip_address,
        ),
        array(  
           'data' => $record_edit_table->date_submit,
        ),
        array(  
           'data' => $record_edit_table->date,
        ),        
    );
  } 
  $caption_table_edit = t('Table for views information peoples');
  return  theme('table',   
      array( 
              'header' => $header_table_edit,   
              'rows'   => $rows_table_edit,   
              'caption'=> $caption_table_edit 
            ) 
  );  
}