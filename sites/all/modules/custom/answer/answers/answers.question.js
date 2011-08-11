/**
 * @file answers.question.js
 *
 * Autocomplete for new questions in the node add form.
 */

DruaQuestion = {
  timerId: null,
  $title: null,

  onKeyUp: function (e) {
    if (DruaQuestion.checkKey(e.keyCode)) {
      $('#answers-possible-questions').remove();
      clearTimeout(DruaQuestion.timerId);
      DruaQuestion.timerId = setTimeout(DruaQuestion.performAutocomplete, 1000);
    }
  },

  checkKey: function (key) {
    var keyCodes = [9, 16, 17, 18, 20, 33, 34, 35, 36, 37, 38, 39, 40];

    for (var i in keyCodes) {
      if (key == keyCodes[i]) {
        return false;
      }
    }

    return true;
  },

  performAutocomplete: function () {
    var title = DruaQuestion.$title.val();
    if (title !== '') {
      // start animation
      DruaQuestion.$title.addClass('throbbing');
      $.getJSON('/question/autocomplete/' + title, function (data) {
        if (data !== '' && title === DruaQuestion.$title.val()) {
          $(data).insertAfter('#edit-title-wrapper').slideDown();
        }
        // stop animation
        DruaQuestion.$title.removeClass('throbbing');
      });
    }
  }
};

Drupal.behaviors.answersQuestionForm = function (context) {
  DruaQuestion.$title = $('#node-form input[name=title]:not(.answers-processed)', context);

  DruaQuestion.$title
    .addClass('answers-processed form-autocomplete')
    .keyup(DruaQuestion.onKeyUp);
};