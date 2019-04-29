(function ($) {
    Drupal.behaviors.srmprAgeProve = {
      attach: function (context, settings) {
        console.log("into");
        $("#srmpr-age-receive-form").validate({
            rules: {
                age_day: {
                    required: true,
                    minlength: 2,
                    maxlength: 2,
                    number:true,
                    range: [1, 30],
                },
                age_month: {
                    required: true,
                    minlength: 2,
                    maxlength: 2,
                    number:true,
                    range: [01, 12],
                },
                age_year: {
                    required: true,
                    minlength: 4,
                    maxlength: 4,
                    number:true,
                    range: [((new Date()).getFullYear() -100), (new Date()).getFullYear()],
                }
            },
            messages: {
            }
        });
      }
    };
  }(jQuery));