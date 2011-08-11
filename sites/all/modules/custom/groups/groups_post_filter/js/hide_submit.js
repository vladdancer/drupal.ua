$(function(){
  $('#panel-groups-page .form-submit').hide();
  $('#panel-groups-page input.form-checkbox').change(function(){ $(this).parents('form').find('.form-submit').click(); });
});