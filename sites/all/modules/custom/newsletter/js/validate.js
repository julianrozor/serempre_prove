/**
 * @file
 * Implementation of  JS for vars session into Block Home (Ms).
 */
(function ($){
  Drupal.validate = Drupal.validate || {};
  Drupal.behaviors.validate = {
    attach : function(context, settings) {
		$('#edit-first').keypress(function(tecla) {
			if((tecla.charCode < 97 || tecla.charCode > 122) && (tecla.charCode < 65 || tecla.charCode > 90) && (tecla.charCode != 45)){
				if(tecla.charCode != 32){
					if (tecla.charCode != 8) {
						return false;
					};					
				}			
			} 				
		});    	

		$('#edit-first-c').keypress(function(tecla) {
			if((tecla.charCode < 97 || tecla.charCode > 122) && (tecla.charCode < 65 || tecla.charCode > 90) && (tecla.charCode != 45)){
				if(tecla.charCode != 32){
					if (tecla.charCode != 8) {
						return false;
					};
				}
			};
		});
	    $('#edit-second-a').keypress(function(tecla) {
	        if(tecla.charCode < 48 || tecla.charCode > 57) return false;
	    });
	}
  };
}(jQuery));
