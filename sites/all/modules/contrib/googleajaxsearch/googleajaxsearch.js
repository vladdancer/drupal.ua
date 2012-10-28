
/**
 * @file
 * Javascript implementation of Google Ajax Search API
 */
 
google.load('search', '1');

function OnLoad() {
    var settings = Drupal.settings.gas;
    var blockCount = settings.block_count;
    var searchControls = new Array();
    var drawOptions = new Array();
    var searcherOptions = new Array();
    var deltas = settings.current_block;
    var firstBlockId = deltas[0];
//For all blocks, create searcher...    
//     For every delta, load settings for Google Ajax Search
    jQuery.each(deltas, function(iteration, delta){  
        var blockId = this; 
//     Id of a setting. Needed because of indexing of settings array -> indexing starts from delta of the first block        
        var blockSettings = settings[delta];
        searchControls[delta] = new google.search.SearchControl();

//Set searcher place  
        searcherOptions[delta] = new google.search.SearcherOptions();
        searcherOptions[delta].setExpandMode(eval(blockSettings.expansion_mode));
        if(blockSettings.results_place) {
//        If target place exists, show results in it. Otherwise show under textfield (like there's no place selected)
           
          if(document.getElementById(blockSettings.results_place)) {
            searcherOptions[delta].setRoot(document.getElementById(blockSettings.results_place));
          }
        }  
//End of set searcher place                                                                        
            
//If setting is on, turn on appropriate searcher type
//Set searcher type:
//      Set settings for searcher type Web
        if(blockSettings.search_options.web_search != 0) {
            var Web = new google.search.WebSearch();
            setLanguageAndDuplicateContent(blockSettings, Web);
            searchSetSiteRestriction(blockSettings, Web, "web");
            searchControls[delta].addSearcher(Web, searcherOptions[delta]);
        }
       
//      Set settings for searcher type Video  
        if(blockSettings.search_options.video_search != 0) {
            var Video = new google.search.VideoSearch();
            
            searchSetOrderBy(blockSettings, Video, "video");
            searchControls[delta].addSearcher(Video, searcherOptions[delta]);
        }
           
//      Set settings for searcher type News
        if(blockSettings.search_options.news_search != 0) {
            var News = new google.search.NewsSearch();
            
            searchSetSiteRestriction(blockSettings, News, "news");
            searchSetOrderBy(blockSettings, News, "news");
            setNewsTopic(blockSettings, News); 
            searchControls[delta].addSearcher(News, searcherOptions[delta]);
        }

//      Set settings for searcher type Image
        if(blockSettings.search_options.image_search != 0) {
            var Image = new google.search.ImageSearch();
            
            searchSetSiteRestriction(blockSettings, Image, "image");
            
            setImageRestriction(blockSettings.results_image_restrict_safesearch, Image);
            setImageRestriction(blockSettings.results_image_restrict_imagesize, Image);
            setImageRestriction(blockSettings.results_image_restrict_colorization, Image);
            setImageRestriction(blockSettings.results_image_restrict_colorfilter, Image);
            setImageRestriction(blockSettings.results_image_restrict_filetype, Image);
            setImageRestriction(blockSettings.results_image_restrict_imagetype, Image);
            
            searchControls[delta].addSearcher(Image, searcherOptions[delta]);
        }

//      Set settings for searcher type Blog
        if(blockSettings.search_options.blog_search != 0) {
            var Blog = new google.search.BlogSearch();      
            
            
            searchSetSiteRestriction(blockSettings, Blog, "blog");
            searchSetOrderBy(blockSettings, Blog, "blog");
            searchControls[delta].addSearcher(Blog, searcherOptions[delta]);
        }
//      Set settings for searcher type Book
        if(blockSettings.search_options.book_search != 0) {
            var Book = new google.search.BookSearch();
            
            setBookType(blockSettings, Book);    
            searchControls[delta].addSearcher(Book, searcherOptions[delta]);
        }
//      Set settings for searcher type Patent
        if(blockSettings.search_options.patent_search != 0) {
            var Patent = new google.search.PatentSearch();
            
            searchSetOrderBy(blockSettings, Patent, "patent");
            searchControls[delta].addSearcher(Patent, searcherOptions[delta]);
        }
//      Set settings for searcher type Local
        
        if(blockSettings.search_options.local_search != 0) {
        
            var Local = new google.search.LocalSearch();
            searchControls[delta].addSearcher(Local, searcherOptions[delta]);
        }

        
        
        drawOptions[delta] = new google.search.DrawOptions();
        
//  End of set searcher type


//   tell the searcher to display results inline or on tabs
        drawOptions[delta].setDrawMode(google.search.SearchControl[blockSettings.results_display]);
      
//   tell the searcher to display 4 or 8 results per page
        searchControls[delta].setResultSetSize(google.search.Search[blockSettings.results_number]);
      
//   place branding in branding placeholder if specified
        if (blockSettings.form_display == 1 &&  blockSettings.branding_place) {
            if (blockSettings.branding_orientation == "HORIZONTAL_BRANDING") {
                google.search.Search.getBranding(document.getElementById(blockSettings.branding_place), google.search.Search.HORIZONTAL_BRANDING);
            }  
            else {
                google.search.Search.getBranding(document.getElementById(blockSettings.branding_place), google.search.Search.VERTICAL_BRANDING);
            }
        }
        
      
//    set if the result link should be displayed in new window/frame etc...
        switch (blockSettings.target_place) {
            case "LINK_TARGET_BLANK":
                searchControls[delta].setLinkTarget(google.search.Search.LINK_TARGET_BLANK);
                break;
            case "LINK_TARGET_SELF":
                searchControls[delta].setLinkTarget(google.search.Search.LINK_TARGET_SELF);
                break;
            case "LINK_TARGET_TOP":
                searchControls[delta].setLinkTarget(google.search.Search.LINK_TARGET_TOP);
                break;
            case "LINK_TARGET_PARENT":
                searchControls[delta].setLinkTarget(google.search.Search.LINK_TARGET_PARENT);
                break;
        }
      
      
//         tell the searcher to draw itself and tell it where to attach
        searchControls[delta].draw(document.getElementById("searchcontrol-"+blockId), drawOptions[delta]);
      
//       if there is a keyword to initial search... execute the search with this keyword
        if (blockSettings.keywords) {
            searchControls[delta].execute(blockSettings.keywords);    
        }      
        if (blockSettings.form_display) {
             var form_display_settings = blockSettings.form_display;
             formVisibilitySet(form_display_settings, delta);
        }
      
    });
}

google.setOnLoadCallback(OnLoad);


// Helper functions
function setLanguageAndDuplicateContent(blockSettings, Web) {
    var code = blockSettings.results_web_language_restriction;
    var duplicate = blockSettings.results_web_duplicate_content_filter;
    
    if (code) {
        if  (duplicate == 1) {
            Web.setRestriction(google.search.WebSearch.RESTRICT_EXTENDED_ARGS, {"lr" : code, "filter" : "1"});    
        }
        else {
            Web.setRestriction(google.search.WebSearch.RESTRICT_EXTENDED_ARGS, {"lr" : code});      
        }
    }
    else if (duplicate == 1) {
        Web.setRestriction(google.search.WebSearch.RESTRICT_EXTENDED_ARGS, {"filter" : "1"});         
    }
}

function searchSetSiteRestriction(blockSettings, Web, option) {
    if (option == "web" && (blockSettings.results_web_site_restriction)) {
        Web.setSiteRestriction(blockSettings.results_web_site_restriction);
    }
    else if (option == "blog" && (blockSettings.results_blog_site_restriction)) {
        Web.setSiteRestriction(blockSettings.results_blog_site_restriction);
    }
    else if (option == "image" && (blockSettings.results_image_site_restriction)) {
        Web.setSiteRestriction(blockSettings.results_image_site_restriction);
    }
    else if (option == "news" && (blockSettings.results_news_site_restriction)) {
        Web.setSiteRestriction(blockSettings.results_news_site_restriction);
    }   
}

function setRestrict(blockSettings, Web) {
    var restrict = blockSettings.results_local_restrict_type;
    
    if (restrict) {
        Web.setRestriction(google.search.LocalSearch[restrict]);      
    }
} 

function setNewsTopic(blockSettings, News) {
    var topic = blockSettings.results_news_restrict_topic;
    
    if (topic) {
        Web.setRestriction(google.search.Search.RESTRICT_EXTENDED_ARGS, { "topic" : topic});
    }    
} 

function searchSetOrderBy(blockSettings, Web, option) {
    Web.setResultOrder(google.search.Search.ORDER_BY_DATE);
    
    if (option == "video" && (blockSettings.results_video_order == "by relevance")) {
        Web.setResultOrder(google.search.Search.ORDER_BY_RELEVANCE);
    }
    else if (option == "blog" && (blockSettings.results_blog_order == "by relevance")) {
        Web.setResultOrder(google.search.Search.ORDER_BY_RELEVANCE);
    }
    else if (option == "patent" && (blockSettings.results_patent_order == "by relevance")) {
        Web.setResultOrder(google.search.Search.ORDER_BY_RELEVANCE);
    }
    else if (option == "news" && (blockSettings.results_news_order == "by relevance")) {
        Web.setResultOrder(google.search.Search.ORDER_BY_RELEVANCE);
    }    
} 

function setBookType(blockSettings, Book) {
    var type = blockSettings.results_book_restrict_type;
    
    if (type == "TYPE_ALL_BOOKS") {
        Book.setRestriction(google.search.BookSearch.TYPE_ALL_BOOKS)
    }  
    else if (type == "TYPE_FULL_VIEW_BOOKS"){
       Book.setRestriction(google.search.BookSearch.TYPE_FULL_VIEW_BOOKS);
    }    
}

function setImageRestriction(option, Image) {
    option ? Image.setRestriction(google.search.ImageSearch[option]) : "";
}

function formVisibilitySet(form_display_settings, delta) {
    var visible = form_display_settings;
    
    if (visible == 1) {
        $("#searchcontrol-" + delta + " div.gsc-control form.gsc-search-box").addClass("hidden");
    }
}