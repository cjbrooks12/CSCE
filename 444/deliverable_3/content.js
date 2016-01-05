var width = 1500;
var height = width/2;
var displayedTagsCount = 10;
var selectedYear = 24;
var searchTerm;

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
  window.year_sort = Create3DArray(100);

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
          updateSearchYear(0);
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

//given an array of images, construct a histogram of all the machine tags throughout the set.
//When we have created this histogram, sort it, then return it in the callback function. 
function createTagsHistogram(images, callback) {
  var histogram = {};

  //iterate through all images and all machineTags on those images
  //create a histogram by making the tags keys in a JS object.
  for(var i = 0; i < images.length; i++) {
    for(var j = 0; j < images[i].machineTags.length; j++) {
      var key = images[i].machineTags[j].tag;
      if (key in histogram)
        histogram[key]++;
      else
        histogram[key] = 1;
    }
  }

  var sortedTags = [];
  for (var tag in histogram) {
    sortedTags.push([tag, histogram[tag]])
  }
  sortedTags.sort(function(a, b) {return b[1] - a[1]})

  callback(histogram, sortedTags);
}

function createGlobalTagsHistogram(imageArrays, callback) {
  var histogram = {};

  //iterate through all images and all machineTags on those images
  //create a histogram by making the tags keys in a JS object.
  for(var k = 0; k < imageArrays.length; k++) {
    var images = imageArrays[k];
    for(var i = 0; i < images.length; i++) {
      for(var j = 0; j < images[i].machineTags.length; j++) {
        var key = images[i].machineTags[j].tag;
        if (key in histogram)
          histogram[key]++;
        else
          histogram[key] = 1;
      }
    }
  }

  var sortedTags = [];
  for (var tag in histogram) {
    sortedTags.push([tag, histogram[tag]])
  }
  sortedTags.sort(function(a, b) {return b[1] - a[1]})

  callback(histogram, sortedTags);
}

function search_single_tags(tag){
  var year_search = Create3DArray(100); 
  for (var i = 0; i < 10; i++){   
    
    for(var j = 0; j < 10; j++){
      
      for(var k =0 ; k < 26; k++){
          
        for(var z=0; z < window.year_sort[((9-j)*10) + i][k].length; z++){
          
          for(var v=0; v < window.year_sort[((9-j)*10) + i][k][z]["machineTags"].length; v++){
            var flag= new Array();
            
            if(year_sort[((9-j)*10) + i][k][z]["machineTags"][v].tag==tag){
              year_search[((9-j)*10) + i][k].push(year_sort[((9-j)*10) + i][k][z]);
              var output = i+" : "+j+" : "+k;
              break;
            } 
          }
        }
      }
    }
  }
  return year_search;
}

function updateSearchTerms(local_searchTerm) {
  searchTerm = local_searchTerm;

  var innerHtml = '<h4>Search Terms</h4>';
  var multipleTerms = [];

  if(searchTerm.indexOf(',') > -1) {
    d3.selectAll(".radio-inline").style("opacity", 1.0);
    multipleTerms = searchTerm.split(',');
    innerHtml += '<ul>';

    for(var i = 0; i < multipleTerms.length; i++) {
      innerHtml += '<li>' + multipleTerms[i] + '</li>';
    }

    innerHtml += '</ul>';
  }
  else {
    d3.selectAll(".radio-inline").style("opacity", 0.0);

    innerHtml += searchTerm;
  }

  d3.select("#suggestions").html(innerHtml);
}

function search() {
  console.log("search button hit");
  updateSearchYear(selectedYear);
}

function updateSearchYear(searchYear) {
  var innerHtml = "Searching for ";

  selectedYear = searchYear;

  if(searchTerm != undefined && searchTerm.length > 0){
    innerHtml += "'" + searchTerm + "' in " + (1990 + searchYear);
    displayData(search_single_tags(searchTerm));
  }
  else {
    innerHtml += "all images in " + (1990 + searchYear) + ", " + searchTerm;
    displayData(year_sort);
  }

  d3.select("#year_input_text").html(innerHtml);
}

