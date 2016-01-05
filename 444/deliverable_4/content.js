var width = 1500;
var height = width/2;

var ZoomType = {
  WHOLE_DATASET: 1,
  GLOBAL_ONE_YEAR: 2,
  CELL_ONE_YEAR: 3,
};
var zoomType = ZoomType.WHOLE_DATASET;

var SearchType = {
  NONE: 1,
  SINGLE: 2,
  MULTI: 3,
};
var searchType = SearchType.NONE;
var singleSearchTerm;
var multiSearchTerms;

var mapIsDrawn = false;

var selectedYear = 24;
var selectedCell = -1;

var displayImages = true;
var displayCounts = true;

var year_sort;
var year_search;

function readFile(filename, i, j, callback) {
  d3.text(filename, function(err, content) {
    if (err) {
      cconsole.log('error reading file "' + filename + '"');
      callback([], i, j);
      return;
    }

    if(content.length == 0){
      callback([], i, j);
      return;
    }

    var lines = content.trim().split('\n');

    var dataArray = lines.map(function(line) {
      try {
        return JSON.parse(line);
      } catch (error) {
        console.warn("Cannot parse line: " + line);
      }
    });

    callback(dataArray, i, j);
  });
}

function loadData() {
  year_sort = Create3DArray(100);

  var dataLoaded = 0;
  selectedYear = 0;
  for(var i = 0; i < 10; i++) {
    for(var j = 0; j < 10; j++) {
      var fileName = 'outputs/data_' + i + '_' + j + '.json';
      readFile(fileName, i, j, function(dataArray, data_i, data_j) {
        dataLoaded++;

        //year sort
        for(var k=0; k<dataArray.length; k++){
          var year = parseInt(dataArray[k]["date"]["year"]);
          year = year-1990;
          //console.log(year);
          if(year >= 26){
            console.log("year error!");
            return;
          }
          window.year_sort[((9-data_j)*10) + data_i][year].push(dataArray[k]);
        }

        if(dataLoaded == 100) {
          updateSearchYear(-1);
          // displayAll();
        }
      });
    }
  }
}

function Create3DArray(rows) {
   var x = new Array(rows);
   for (var i = 0; i < rows; i++) {
      x[i] = new Array(26);
      for(var k=0;k<26;k++){
        x[i][k]= new Array();
      }
   }
   return x;
}

function updateSearchTerms(local_searchTerm) {
  var innerHtml = '';

  if(local_searchTerm.length == 0) {
    searchType = SearchType.NONE;
    d3.selectAll(".radio-inline").style("opacity", 0.0);

    innerHtml = 'none';
  }
  else if(local_searchTerm.indexOf(',') > -1) {
    searchType = SearchType.MULTI;
    d3.selectAll(".radio-inline").style("opacity", 1.0);
    multiSearchTerms = local_searchTerm.split(/\s*,\s*/);

    innerHtml += '<ul>';
    for(var i = 0; i < multiSearchTerms.length; i++) {
      innerHtml += '<li>' + multiSearchTerms[i] + '</li>';
    }
    innerHtml += '</ul>';
  }
  else {
    searchType = SearchType.SINGLE;
    d3.selectAll(".radio-inline").style("opacity", 0.0);
    singleSearchTerm = local_searchTerm;
    
    innerHtml += '<ul>';
    innerHtml += '<li>' + singleSearchTerm + '</li>';
    innerHtml += '</ul>';
  }

  d3.select("#selectedTags").html(innerHtml);
}

function performSearch() {
  if(searchType == SearchType.NONE) {
    displayAll();
    return;
  }
  else if(searchType == SearchType.SINGLE) {
    search_single_tags(function() {
      displayAll();
    });
  }
  else if(searchType == SearchType.MULTI) {
    var method = d3.select('input[name="and_or"]:checked').node().value;
    if(method === 'and') {
      search_multi_tags_and(function() {
        displayAll();
      });
    }
    else if(method === 'or') {
      search_multi_tags_or(function() {
        displayAll();
      });
    }
    else {
      displayAll();
    }
  }
}

function updateSearchYear(searchYear) {
  var innerHtml = "";

  selectedYear = searchYear;

  if(selectedYear == -1) {
    if(selectedCell == -1) {
      zoomType = ZoomType.WHOLE_DATASET;
    }
    else {
      zoomType = ZoomType.CELL_ONE_YEAR;
    }

    innerHtml += "1990+";
  }
  else {
    if(selectedCell == -1) {
      zoomType = ZoomType.GLOBAL_ONE_YEAR;
    }
    else {
      zoomType = ZoomType.CELL_ONE_YEAR;
    }

    innerHtml += "" + (1990 + searchYear);
  }

  displayAll();

  d3.select("#year_input_text").html(innerHtml);
}

function pickImg(imgArray){
  if(imgArray.length==0) return;
  var highest = imgArray[0];
  var highest_value = 1.5 *imgArray[0]["favoriteCount"] + 2.0 * imgArray[0]["followCount"];
  for(var i= 1; i < imgArray.length; i++){
    var popular_formula = 1.5 *imgArray[i]["favoriteCount"] + 2.0 * imgArray[i]["followCount"];
    if( popular_formula > highest_value ){
      highest = imgArray[i];
      highest_value = popular_formula;
    }
  }
  return highest;
}

function search_single_tags(callback){
  year_search = Create3DArray(100);
  for(var cell = 0; cell < 100; cell++) {
    for(var year = 0; year < 26; year++) {
      for(var image = 0; image < year_sort[cell][year].length; image++){
        for(var tag = 0; tag < year_sort[cell][year][image]["machineTags"].length; tag++){
          if(year_sort[cell][year][image]["machineTags"][tag].tag == singleSearchTerm){
            year_search[cell][year].push(year_sort[cell][year][image]);
            break;
          } 
        }
      }
    }
  }
  callback();
}

function search_multi_tags_and(callback){
  year_search = Create3DArray(100);
  console.log(multiSearchTerms);
  for(var cell = 0; cell < 100; cell++) {
    for(var year = 0; year < 26; year++) {
      for(var image = 0; image < window.year_sort[cell][year].length; image++){
        var flag = 0;
        for(var tag = 0; tag < window.year_sort[cell][year][image]["machineTags"].length; tag++){
          for(var n = 0; n < multiSearchTerms.length; n++){
            if(year_sort[cell][year][image]["machineTags"][tag].tag == multiSearchTerms[n]){
              flag++;
            }
          }
        }
        if(flag == multiSearchTerms.length){
          year_search[cell][year].push(year_sort[cell][year][image]);
          break;
        }
      }
    }
  }
  callback();
}

function search_multi_tags_or(callback){
  year_search = Create3DArray(100);
  for(var cell = 0; cell < 100; cell++) {
    for(var year = 0; year < 26; year++) {
      for(var image = 0; image < window.year_sort[cell][year].length; image++){
        var flag=0;
        for(var tag = 0; tag < window.year_sort[cell][year][image]["machineTags"].length; tag++){
          for(var n = 0; n < multiSearchTerms.length; n++){
            if(year_sort[cell][year][image]["machineTags"][tag].tag==multiSearchTerms[n]){
              year_search[cell][year].push(year_sort[cell][year][image]);
              break;
            }
          }
        }
      }
    }
  }
  callback();
}