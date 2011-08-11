Drupal.behaviors.node_embed = function(context) {  
  $('table.views-view-grid tr td', context).click(function(){ 
    $('.active-cell .views-field-nid span.field-content').attr("id", 'inactive-nid');
    $('table.views-view-grid tr td', context).removeClass('active-cell'); 
    $(this).addClass('active-cell'); 
    $('.active-cell .views-field-nid span.field-content').attr("id", 'active-nid');
  }); 
}