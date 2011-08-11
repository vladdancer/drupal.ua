  
google.load("search", "1");

/**
 * DrupalUaAnswers object stores handlers and helper functions.
 */
var DrupalUaAnswers = {
  $form: null, // Initialized in Drupal.behaviors.executeAnswersSearch
  $formProcessed: null // Initialized in Drupal.behaviors.executeAnswersSearch
};

DrupalUaAnswers.googleSearch = function (text) {
  // Create a search control
  var searchControl = new google.search.SearchControl();

  // blog search, closed
  var options = new google.search.SearcherOptions();
  options.setExpandMode(google.search.SearchControl.EXPAND_MODE_CLOSED);

  // Add drupal.ua
  var siteSearch = new google.search.WebSearch();
  siteSearch.setUserDefinedLabel("Drupal.ua");
  siteSearch.setUserDefinedClassSuffix("siteSearch");
  siteSearch.setSiteRestriction("drupal.ua");
  searchControl.addSearcher(siteSearch, options);

  // Add drupal.ru
  var siteSearch = new google.search.WebSearch();
  siteSearch.setUserDefinedLabel("Drupal.ru");
  siteSearch.setUserDefinedClassSuffix("siteSearch");
  siteSearch.setSiteRestriction("drupal.ru");
  searchControl.addSearcher(siteSearch, options);

  // Add drupal.org
  var siteSearch = new google.search.WebSearch();
  siteSearch.setUserDefinedLabel("Drupal.org");
  siteSearch.setUserDefinedClassSuffix("siteSearch");
  siteSearch.setSiteRestriction("drupal.org");
  searchControl.addSearcher(siteSearch, options);

  // Tell the searcher to draw itself and tell it where to attach
  searchControl.draw(document.getElementById("google-search"));
  searchControl.execute(text);
};

DrupalUaAnswers.onAjaxSuccess = function (e, xhr, settings) {
  if (settings.url == "/answers/search/js") {
    var searchText = $('#edit-search-text', this).val();
    if (searchText !== '') {
      $('#answers-search-contents h3').show();
      DrupalUaAnswers.googleSearch(searchText);
    }
    else {
      $('#answers-search-contents h3').hide();
    }
  }
};

DrupalUaAnswers.onAjaxSend = function(e, xhr, settings) {
  if (settings.url == "/answers/search/js") {
    var search = $('#edit-search-text', DrupalUaAnswers.$form).val();
    if (! search) {
      $('label', DrupalUaAnswers.$form).fadeTo('fast', 0.3, function () {
        $('label', DrupalUaAnswers.$form).fadeTo('fast', 1, function () {
          $('label', DrupalUaAnswers.$form).fadeTo('fast', 0.3, function () {
            $('label', DrupalUaAnswers.$form).fadeTo('fast', 1);
          });
        });
      });
    }
  }
};

DrupalUaAnswers.onSearchFieldKeyPress = function(event) {
  if (event.which != 13) {
    $('#answers-search-contents *', DrupalUaAnswers.$form).fadeOut();
  }
}

DrupalUaAnswers.onPagerClick = function () {
  var pattern = new RegExp(/page\=([0-9]+)/i);
  var matches = pattern.exec($(this).attr('href'));
  var page = (matches != null) ? matches[1] : 0;
  $('input:hidden[name=page]', DrupalUaAnswers.$form).val(page);
  $('input[type=submit]', DrupalUaAnswers.$form).click();
  return false;
}

DrupalUaAnswers.googleSearchOnPageLoad = function () {
  var searchText = $('#edit-search-text', DrupalUaAnswers.$form).val();
  if (searchText.length) {
    DrupalUaAnswers.googleSearch(searchText);
  }
};

/**
 * Behaviors.
 */
Drupal.behaviors.executeAnswersSearch = function() {

  // Initialize variables in DrupalUaAnswers object
  DrupalUaAnswers.$form = $('#answers-search-question-form');
  DrupalUaAnswers.$formProcessed = $('#answers-search-question-form.answers-processed');

  DrupalUaAnswers.googleSearchOnPageLoad();

  // Add handlers for ajaxSend and ajaxSuccess events
  $('#answers-search-question-form:not(.answers-processed)')
    .addClass('answers-processed')
    .ajaxSuccess(DrupalUaAnswers.onAjaxSuccess)
    .ajaxSend(DrupalUaAnswers.onAjaxSend);

  // Hide search results when user enters new query
  $('#edit-search-text', DrupalUaAnswers.$formProcessed).keypress(DrupalUaAnswers.onSearchFieldKeyPress);

  // Initialize pager
  $('#answers-search-pager a').click(DrupalUaAnswers.onPagerClick);

};