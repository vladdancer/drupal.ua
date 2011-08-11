// $Id 

/*
 * @file
 * Contain reaction on TABs links.
 */
Drupal.behaviors.answers_tabs = function (context) {
  var flag_block = false;
  
  $("#answer_tab_id_0").click(function () {
    if (!flag_block && Drupal.settings.current != 0) {
      flag_block = true;
      answerReorder(0);
      flag_block = false;
      Drupal.settings.current = 0;
    }
  });

  $("#answer_tab_id_1").click(function () {
    if (!flag_block && Drupal.settings.current != 1) {
      flag_block = true;
      answerReorder(1);
      flag_block = false;
      Drupal.settings.current = 1;
    }
  });
  
  $("#answer_tab_id_2").click(function () {
    if (!flag_block && Drupal.settings.current != 2) {
      flag_block = true;
      answerReorder(2);
      flag_block = false;
      Drupal.settings.current = 2;
    }
  });
  
  /**
   * Reorder answers.
   */
  function answerReorder(id) {
    var newHtml = '';
    for (var i = 0; i < Drupal.settings.orders_index[id]['index'].length; i++) {
      newHtml = newHtml + "<div id=\"answer_cid_" + Drupal.settings.orders_index[id]['index'][i] + "\">" + $("#answer_cid_" + Drupal.settings.orders_index[id]['index'][i]).html() + "</div>";
    }
    $("#answer_conteiner").html(newHtml);
  }
}
