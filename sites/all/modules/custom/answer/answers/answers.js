// $Id 

/*
 * @file
 * Contain reaction on flag's module links.
 */
Drupal.behaviors.answers = function (context) {
  var resolvedText = '<sup>[' + Drupal.t('resolved') + ']</sup>';

  if (typeof (Drupal.settings.pageTitleHtml) == 'undefined') {
    Drupal.settings.pageTitleHtml = $('#page-title').html();
  }

  if ($('div.answer.best-answer').length) {
    $('#page-title').html(Drupal.settings.pageTitleHtml + '&nbsp;' + resolvedText);
    $('#page-title').addClass('answered');
  }

  $('div.answer a.flag-link-toggle:not(.answers-processed)')
    .addClass('answers-processed')    
    .bind('flagGlobalAfterLinkUpdate', 
    function(event, data) {
        // Question title.
        var $pageTitle = $('#page-title');

        if (data.contentType == "comment" && data.flagName == "best_answer") {
          // Unflag best answer.
          if (data.flagStatus == "unflagged") {
            // Remove 'best-answer' class from comment wrapper.
            $('span.flag-best-answer-' + data.contentId)
              .parents('div.answer')
              .removeClass('best-answer');

            // Check for existing of comments with "Best Answer" flag.
            // If at least one exists - mark question title as "Resolved".
            if ($('div.answer.best-answer').length) {
                $pageTitle
                  .addClass('answered')
                  .html(Drupal.settings.pageTitleHtml + '&nbsp;' + resolvedText);
            }
            // If no best answer left - remove "Resolved" status from question title.
            else {
                $pageTitle
                  .removeClass('answered')
                  .html(Drupal.settings.pageTitleHtml);
            }
          }
          // If comment marked as best answer - Remove 'best-answer' class from comment wrapper,
          // and mark question title as "Resolved".
          else if (data.flagStatus == "flagged") {
            $('span.flag-best-answer-' + data.contentId)
              .parents('div.answer')
              .addClass('best-answer');
            $pageTitle
              .addClass('answered')
              .html(Drupal.settings.pageTitleHtml + '&nbsp;' + resolvedText);
          }
        }
    }
  );

  /**
   * Function was copied from flag.js because using
   * Drupal.flagLink.updateLink(); 
   * not works.
   * 
   * Helper function. Updates a link's HTML with a new one.
   *
   * @param element
   *   The <A> element.
   * @return
   *   The new link.
   */
  function updateLink(element, newHtml) {
    var $newLink = $(newHtml);

    // Initially hide the message so we can fade it in.
    $('.flag-message', $newLink).css('display', 'none');

    // Reattach the behavior to the new <A> element. This element
    // is either whithin the wrapper or it is the outer element itself.
    var $nucleus = $newLink.is('a') ? $newLink : $('a.flag', $newLink);
    $nucleus.addClass('flag-processed').click(flagClick);

    // Find the wrapper of the old link.
    var $wrapper = $(element).parents('.flag-wrapper:first');
    if ($wrapper.length == 0) {
      // If no ancestor wrapper was found, or if the 'flag-wrapper' class is
      // attached to the <a> element itself, then take the element itself.
      $wrapper = $(element);
    }
    // Replace the old link with the new one.
    $wrapper.after($newLink).remove();
    Drupal.attachBehaviors($newLink.get(0));

    $('.flag-message', $newLink).fadeIn();
    setTimeout(function(){ $('.flag-message', $newLink).fadeOut() }, 3000);
    return $newLink.get(0);
  }

  /**
   * Function was copied from flag.js because using
   * Drupal.flagLink.flagClick(); 
   * not works.
   *
   * A click handler that is attached to all <A class="flag"> elements.
   */
  function flagClick() {
    // 'this' won't point to the element when it's inside the ajax closures,
    // so we reference it using a variable.
    var element = this;

    // While waiting for a server response, the wrapper will have a
    // 'flag-waiting' class. Themers are thus able to style the link
    // differently, e.g., by displaying a throbber.
    var $wrapper = $(element).parents('.flag-wrapper');
    if ($wrapper.is('.flag-waiting')) {
      // Guard against double-clicks.
      return false;
    }
    $wrapper.addClass('flag-waiting');

    // Hide any other active messages.
    $('span.flag-message:visible').fadeOut();
    // Send POST request
    $.ajax({
      type: 'POST',
      url: element.href,
      data: { js: true },
      dataType: 'json',
      success: function (data) {
        if (data.status) {
          // Success.
          data.link = $wrapper.get(0);
          $.event.trigger('flagGlobalBeforeLinkUpdate', [data]);
          if (!data.preventDefault) { // A handler may cancel updating the link.
            data.link = updateLink(element, data.newLink);
          }
          $.event.trigger('flagGlobalAfterLinkUpdate', [data]);
        }
        else {
          // Failure.
          alert(data.errorMessage);
          $wrapper.removeClass('flag-waiting');
        }
      },
      error: function (xmlhttp) {
        alert('An HTTP error '+ xmlhttp.status +' occurred.\n'+ element.href);
        $wrapper.removeClass('flag-waiting');
      }
    });
    return false;
  }  
}
