/* global pageData */

// Navigate between I Spy pages
//------------------------------------------------------------------------------
function pageForwardClick() {
  if(pageNumber < 5) goToPage((pageNumber + 1));
}

function pageBackwardClick() {
  if(pageNumber > 0) goToPage((pageNumber - 1));
}

function goToPage(nextPageNumber) {
  localStorage['iSpyPage'] = nextPageNumber;
  pageNumber = nextPageNumber;

  currentPageData = pageData[pageNumber];

  goToJournalPage(0);
  setLookingGlassSelected(false, false);

  var pageName = currentPageData.smallImage;
  var pageNameLarge = 'url(\'' + currentPageData.largeImage + '\') no-repeat';

  $("#iSpyPage").attr("src", pageName);
  $('.large').css('background', pageNameLarge);

  if(pageNumber == 0)
    $('#pageBackward').css('display', 'none');
  else
    $('#pageBackward').css('display', 'block');

  if(pageNumber == 5)
    $('#pageForward').css('display', 'none');
  else
    $('#pageForward').css('display', 'block');
}

//Initialize everything on the page, restoring the state of the last time it was opened
//------------------------------------------------------------------------------
$(document).ready(function() {
  //initialize values that will be stored in local storage
  if(localStorage['iSpyPage'] == undefined)
    localStorage['iSpyPage'] = 0;

  pageNumber = Number(localStorage['iSpyPage']);
  goToPage(pageNumber);

  $(document).keyup(function(e) {
      if (e.keyCode == 27) { // 'esc'
        setLookingGlassSelected(false, false);
      }
      else if(e.keyCode >= 49 && e.keyCode <= 54) { // numbers '1' thru '6' to navigate pages
        goToPage(e.keyCode - 49);
      }
  });

  trackMouseClicks();
  trackMouseMove();
});

//Deal with picking up and moving the looking glass, and clicking the image
//------------------------------------------------------------------------------
function clickImage(clickCoords) {
  setLookingGlassSelected(true, true);

  // create a jQuery event
  var e = $.Event('mousemove');

  // set coordinates
  e.pageX = clickCoords.x + $('.magnify').offset().left;
  e.pageY = clickCoords.y + $('.magnify').offset().top;

  // trigger event - must trigger on document
  $('.page_layout').trigger(e);

  setLookingGlassSelected(true, false);
}

function setLookingGlassSelected(isSelected, trackMousePosition) {
  if(isSelected == true) {
    if(trackMousePosition == true) {
      $("#looking_glass").removeClass("highlight-lg");
      $('#looking_glass').css("pointer-events", "none");

      lookingGlass_isSelected = true;
      goToJournalPage(0);
    }
    else {
      $("#looking_glass").addClass("highlight-lg");
      $('#looking_glass').css("pointer-events", "all");
      lookingGlass_isSelected = false;
    }
    $(".large").fadeIn(500);
  }
  else {
    $("#looking_glass").addClass("highlight-lg");
    $('#looking_glass').css("pointer-events", "all");

    lookingGlass_isSelected = false;
    goToJournalPage(0);
    $(".large").fadeOut(100);

    $("#looking_glass").animate({
      left: '0px',
      top: '435px'
    }, 500 );
  }
}

function trackMouseClicks() {
  $('.small').click(function(e) {

    //get coordinates of click relative to image
    var offset = $(this).offset();
    var clickCoords = {
      x: (e.pageX - offset.left),
      y: (e.pageY - offset.top)
    }

    //check to see if click is withing range of a found object
    for(var i = 0; i < currentPageData.foundObjects.length; i++) {
      var objectCoords = currentPageData.foundObjects[i].location;

      var dx = Math.abs(clickCoords.x - objectCoords.x);
      var dy = Math.abs(clickCoords.y - objectCoords.y);

      if(dx < 50 && dy < 50) {
        clickImage(objectCoords);
        goToJournalPage(i+1);
        break;
      }
    }
  });
}

function trackMouseMove() {
  $('.page_layout').mousemove(function(e){
    if(!lookingGlass_isSelected)
      return;

    var magnify_offset = $('.magnify').offset();

    //position of the mouse over the actual small image.
    //Offset the click even more to center the 'lens' over the mouse
    var mouse = {
      x: e.pageX - magnify_offset.left - 73,
      y: e.pageY - magnify_offset.top - 69
    }

    var large_ratio = {
      x: -1*((mouse.x / small_image.width) * large_image.width),
      y: -1*((mouse.y / small_image.height) * large_image.height)
    }

    var bgp = large_ratio.x + "px " + large_ratio.y + "px";

    //position the magnified image
    lastPos_lens.x = mouse.x;
    lastPos_lens.y = mouse.y;

    //position the looking glass image over the magnified image for the magnifying effect
    lastPos_glass.x = mouse.x + 130; //133
    lastPos_glass.y = mouse.y + 50; //54

    $(".large").css({left: lastPos_lens.x, top: lastPos_lens.y, backgroundPosition: bgp});
    $("#looking_glass").css({left: lastPos_glass.x, top: lastPos_glass.y});
	});
}

//Deal with advancing the journal pages
//------------------------------------------------------------------------------
function journalForwardClick() {
  if(journalPageNumber < 5) goToJournalPage((journalPageNumber + 1));
}

function journalBackwardClick() {
  if(journalPageNumber > 0) goToJournalPage((journalPageNumber - 1));
}

function goToJournalPage(nextJournalPageNumber) {
  journalPageNumber = nextJournalPageNumber;

  var currentFoundObject = currentPageData.foundObjects[journalPageNumber - 1];

  if(journalPageNumber == 0) {
    journalIsFoundObject = false;

    $('#journalBackward').fadeOut(100);
    if(currentPageData.foundObjects.length == 0) {
      $('#journalForward').fadeOut(100);
    }
    else {
      $('#journalForward').fadeIn(100);
    }

    $('.journal_title').css('color', 'black');
    $('.journal_title').text(currentPageData.title);
    $('.journal_content').html(currentPageData.journalText);
    $('.journal_content').css('color', 'black');
    $('.journal_page_number').text(journalPageNumber);
  }
  else {
    journalIsFoundObject = true;

    $('#journalBackward').fadeIn(100);

    if(journalPageNumber == (currentPageData.foundObjects.length))
      $('#journalForward').fadeOut(100);
    else
      $('#journalForward').fadeIn(100);

    $('.journal_title').css('color', '#BF1D00');
    $('.journal_title').text(currentFoundObject.title);
    $('.journal_content').css('color', '#BF1D00');
    $('.journal_content').html(currentFoundObject.journalText);
    $('.journal_page_number').text((journalPageNumber));
  }
}

//data members
//------------------------------------------------------------------------------
var pageNumber = 0;
var journalPageNumber = 0;

var journalIsFoundObject = false;

var currentPageData = null;

var lookingGlass_isSelected = false;
var small_image = {width: 675, height: 492};
var large_image = {width: 807, height: 588};

var lastPos_glass = {x: 0, y: 0};
var lastPos_lens = {x: 0, y: 0};