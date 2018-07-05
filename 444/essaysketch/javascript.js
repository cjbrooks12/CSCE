function goToPage(pageNumber) {
  localStorage['iSpyPage'] = pageNumber;

  document.getElementById('iSpyPage').src = 'page_' + pageNumber + '.png';
  var pageBackwardButton = document.getElementById('pageBackward');
  var pageForwardButton = document.getElementById('pageForward');

  if(pageNumber == 0) {
    pageBackwardButton.style.display = 'none';
    pageForwardButton.style.display = 'block';
  }
  else if(pageNumber == 5) {
    pageBackwardButton.style.display = 'block';
    pageForwardButton.style.display = 'none';
  }
  else {
    pageBackwardButton.style.display = 'block';
    pageForwardButton.style.display = 'block';
  }
}

function pageForwardClick() {
  var pageNumber = Number(localStorage['iSpyPage']);
  if(pageNumber < 5) goToPage((pageNumber + 1));
}

function pageBackwardClick() {
  var pageNumber = Number(localStorage['iSpyPage']);
  if(pageNumber > 0) goToPage((pageNumber - 1));
}





//Initialize everything on the page, restoring the state of the
function initializePage() {
  //initialize values that will be stored in local or session storage
  if(localStorage['iSpyPage'] == undefined)
    localStorage['iSpyPage'] = 1;

  if(localStorage['journal_hasArrows'] == undefined)
    localStorage['journal_hasArrows'] = true;
  if(localStorage['journal_hasTitle'] == undefined)
    localStorage['journal_hasTitle'] = true;
  if(sessionStorage['journal_page'] == undefined)
    sessionStorage['journal_page'] = 1;

  if(sessionStorage['lookingGlass_isSelected'] == undefined)
    sessionStorage['lookingGlass_isSelected'] = false;

  //Initialize the I Spy page that will be shown
  //I Spy pages are maintained across browser sessions
  var pageNumber = Number(localStorage['iSpyPage']);
  goToPage(pageNumber);

  //Initialize the journal page appropriate for that I Spy Page
  //Journal pages are reset every browser session
}