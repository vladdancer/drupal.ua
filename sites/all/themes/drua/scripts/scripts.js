$(function() {
  $('.button').each(function(e) {
    $(this).mousedown(function(){
      $(this).addClass('active');
    });
    $(this).mouseup(function(){
      $(this).removeClass('active');
    });
    $(this).hover(function(){}, function(){ $(this).removeClass('active'); });
  });
});