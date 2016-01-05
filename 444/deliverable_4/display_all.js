function displayAll() {

  console.log("zoomType=" + zoomType);
  d3.select(".page_content")
  .style("width", width + "px")
  .style("height", height + "px");
  d3.select("#clickable_layer")
  .style("width", width + "px")
  .style("height", height + "px");

  var imageSet;
  if(searchType == SearchType.NONE) {
    imageSet = year_sort;
  }
  else {
    imageSet = year_search;
  }

  if(zoomType == ZoomType.CELL_ONE_YEAR) {
    d3.select(".back_button").style("opacity", 1.0);
  }
  else {
    d3.select(".back_button").style("opacity", 0.0);
  }

  //draw the base map layer
  if(!mapIsDrawn) {
    if(selectedCell == -1) {
      console.log("Drawing full world map");
      displayMapLayer();
    }
    else {
      console.log("Drawing map cell at " + selectedCell);
      displayMapCellLayer();
    }
  }

  //draw the images layer
  if(displayImages) {
    if(zoomType == ZoomType.CELL_ONE_YEAR) {
      displayImagesCellLayer(imageSet);
    }
    else{
      displayImagesLayer(imageSet);
    }
  }

  if(displayCounts) {
    if(zoomType == ZoomType.WHOLE_DATASET) {
      console.log("displaying counts for whole dataset");
      displayImageCountsLayer(imageSet);
    }
    else if(zoomType == ZoomType.GLOBAL_ONE_YEAR) {
      console.log("displaying counts for global one year");
      displayImageCountsLayer(imageSet);
    }
    else if(zoomType == ZoomType.CELL_ONE_YEAR) {
      console.log("displaying counts for one cell in one year");
      displayImageCountsCellLayer(imageSet);
    }
  }

  //display appropriate histogram as a word cloud
  if(zoomType == ZoomType.WHOLE_DATASET) {
    getWholeDatasetTags(imageSet, function(histogram) {
      displayWordCloud(histogram);
    });
  }
  else if(zoomType == ZoomType.GLOBAL_ONE_YEAR) {
    getGlobalOneYearTags(imageSet[selectedYear], function(histogram) {
      displayWordCloud(histogram);
    });
  }
  else if(zoomType == ZoomType.CELL_ONE_YEAR) {
    getCellOneYearTags(imageSet[selectedCell][selectedYear], function(histogram) {
      displayWordCloud(histogram);
    });
  }
}