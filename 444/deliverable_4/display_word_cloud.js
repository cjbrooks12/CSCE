function displayWordCloud(fullTagsList) {
  var tagCloudWidth = d3.select("#word_cloud").node().getBoundingClientRect().width;

  var limit = (fullTagsList.length >= 35) ? 35 : fullTagsList.length;
  var tags = [];
  var min = 1000000; 
  var max = 0;

  for(var i = 0; i < limit; i++) {
    if(fullTagsList[i][0] == "outdoor"){
      continue;
    }

    var count = fullTagsList[i][1];
    if(count < min) min = count;
    if(count > max) max = count;
    tags.push({text: fullTagsList[i][0], size: 25, count: count});
  }

  var colorScaler = d3.scale.log().domain([min, max]).range([0, 256]);
  var sizeScaler = d3.scale.linear().domain([min, max]).range([15, 35]);

  d3.layout.cloud().size([tagCloudWidth, 240])
      .words(tags)
      .rotate(function() { return ~~(Math.random() * 2) * 90; })
      .font("Impact")
      .fontSize(size)
      .on("end", draw)
      .start();

  function color(d, i) {
    var scaledCount = colorScaler(d.count);
    var R = Math.floor(scaledCount*0.605);
    var G = Math.floor(scaledCount*0.398);
    var B = Math.floor(scaledCount*0.398);

    var RGB = "rgb(" + R + ", " + G + ", " + B + ")";

    return RGB;
  }
  function colorFull(d, i) {
    return "rgb(175, 125, 125)";
  }
  function size(d, i) {
    return Math.floor(sizeScaler(d.count));;
  }

  function draw(words) {
    d3.select("#word_cloud svg").remove();
      d3.select("#word_cloud").append("svg")
        .attr("width", tagCloudWidth)
        .attr("height", 240)
      .append("g")
        .attr("transform", "translate(" + tagCloudWidth/2 + ",120)")
      .selectAll("text")
        .data(words)
      .enter().append("text")
        .style("font-size", function(d) { return d.size + "px"; })
        .style("font-family", "Impact")
        .style("fill", color)
        .attr("text-anchor", "middle")
        .attr("transform", function(d) {
          return "translate(" + [d.x, d.y] + ")rotate(" + d.rotate + ")";
        })
        .text(function(d) { return d.text; })
        .on('mouseover', function(obj) {
          d3.select(this)
            .transition().duration(100)
            .style("fill", colorFull)
            .style("cursor", "pointer");
            d3.event.stopPropagation();
        })
        .on('mouseout', function(obj) {
          d3.select(this)
            .transition().duration(100)
            .style("fill", color)
            .style("cursor", "default");
            d3.event.stopPropagation();
        })
        .on("click", function(obj) {
          var input = d3.select("#search_input");
          var inputValue = input.property("value");
          console.log("value=" + inputValue + " tag=" + obj.text);

          if(inputValue == undefined || inputValue.length == 0) {
            input.property("value", obj.text);
            updateSearchTerms(input.property("value"));
          }
          else {
            input.property("value", inputValue + ", " + obj.text);
            updateSearchTerms(input.property("value"));
          }
          
          d3.event.stopPropagation();
        });
  }
}

//given an array of images (i.e. a cell), construct a histogram of all the machine tags throughout the set.
//When we have created this histogram, sort it, then return it in the callback function. 
function getCellOneYearTags(images, callback) {
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

  callback(sortedTags);
}

//given all arrays of images in the world for a given year, construct a histogram of all 
//the machine tags throughout the set. When we have created this histogram, sort it, 
//then return it in the callback function. 
function getGlobalOneYearTags(imageArrays, callback) {
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

  callback(sortedTags);
}

//given all arrays of images in the world for a all years, construct a histogram of all 
//the machine tags throughout the set. When we have created this histogram, sort it, 
//then return it in the callback function. 
function getWholeDatasetTags(imageArrays, callback) {
  var histogram = {};

  //iterate through all images and all machineTags on those images
  //create a histogram by making the tags keys in a JS object.
  for(var year = 0; year < 26; year++) {
    for(var k = 0; k < imageArrays[year].length; k++) {
      var images = imageArrays[year][k];
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
  }

  var sortedTags = [];
  for (var tag in histogram) {
    sortedTags.push([tag, histogram[tag]])
  }
  sortedTags.sort(function(a, b) {return b[1] - a[1]})

  callback(sortedTags);
}