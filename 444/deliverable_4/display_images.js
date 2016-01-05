function displayImagesLayer(data) {
  d3.select('#images_layer svg').remove();
  var svg = d3.select('#images_layer').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);

  var node = svg
    .selectAll('.node')
    .data(data);

  var g = node
    .enter()
    .append('g')
    .classed('node', true);

  g.each(function(d, i) { 
    d.index = i; 
  });

  //display the images
  var image = g.append("svg:image");
  image.attr("xlink:href", nodeImageLink);
  image.attr("x", posX);
  image.attr("y", posY);
  image.attr("width", itemWidth);
  image.attr("height", itemHeight);
  image.style("opacity", 0.75);

  image.on('mouseover', function(obj) {
    d3.select(this)
      .transition().duration(500)
      .attr("x", posXHoverZoom)
      .attr("y", posYHoverZoom)
      .attr("width", itemWidthHoverZoom)
      .attr("height", itemHeightHoverZoom)
      .style("opacity", 1.0);
      d3.event.stopPropagation();
  });
  image.on('mouseout', function(obj) {
    d3.select(this)
      .transition().duration(500)
      .attr("x", posX)
      .attr("y", posY)
      .attr("width", itemWidth)
      .attr("height", itemHeight)
      .style("opacity", 0.75);
      d3.event.stopPropagation();
  });
  g.on("click", function(obj) {
    selectedCell = obj.index;
    mapIsDrawn = false;
    zoomType = ZoomType.CELL_ONE_YEAR;

    displayAll();
    d3.event.stopPropagation();
  });

  d3.select("#images_layer")
  .style("width", width + "px")
  .style("height", height + "px");
}

function displayImagesCellLayer(data) {
  d3.select('#images_layer svg').remove();
  var svg = d3.select('#images_layer').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);

  var dots;
  if(selectedYear == -1) {
    dots = [];
  }
  else {
    dots = data[selectedCell][selectedYear];
  }

  if(dots.length == 0) return;

  var objFollowerCounts = dots.map(function(obj) {
    return obj.followCount;
  });
  var min = Math.min.apply(null, objFollowerCounts);
  var max = Math.max.apply(null, objFollowerCounts);
  var followerScale = 
    d3.scale.linear()
    .domain([min, max])
    .range([0.25, 1.0]);

  var objFavoriteCounts = dots.map(function(obj) {
    return obj.favoriteCount;
  });
  min = Math.min.apply(null, objFavoriteCounts);
  if(min == 0) min = 1;
  max = Math.max.apply(null, objFavoriteCounts);
  var favoriteScale = 
    d3.scale.log()
    .domain([min, max])
    .range(["#FF0000", "#00E833"]);

  var selectedCellCoords = {
    i: ((selectedCell)%10)+1,
    j: (Math.floor(selectedCell/10))+1
  }

  var selectedCellLatLng = {
    lng: (((selectedCellCoords.i-5)*36) - 18),
    lat: -1*(((selectedCellCoords.j-5)*18) - 9)
  }

  var limits = {
    left: selectedCellLatLng.lng - 18,
    top: selectedCellLatLng.lat + 9,
  }

  var length = {
    lng: width / 36,
    lat: height / 18
  }

  function geoX(obj, i) {
    var degFromLeft = Math.abs(limits.left - obj.geo.longtitude);
    var pxFromLeft = Math.floor(degFromLeft*length.lng);

    return pxFromLeft;
  }
  function geoY(obj, i) {
    var degFromTop = Math.abs(limits.top - obj.geo.latitude);
    var pxFromTop = Math.floor(degFromTop*length.lat);

    return pxFromTop;
  }
  function geoImage(obj, i) {
    return obj.downloadUrl;
  }
  function geoColor(obj) {
    return favoriteScale(obj.followCount);
  }
  function geoOpacity(obj) {
    return followerScale(obj.followCount);
  }

  var node = svg
    .selectAll('.node')
    .data(dots);

  var g = node
    .enter()
    .append('g')
    .classed('node', true);

  var dot = g.append("circle");
  dot.attr("r", "5px");
  dot.attr("cx", geoX);
  dot.attr("cy", geoY);
  dot.style("fill", geoColor);
  dot.style("opacity", geoOpacity);

  var representativeImage = pickImg(dots);
  var image = svg.append("svg:image");
  image.attr("xlink:href", representativeImage.downloadUrl);
  image.attr("x", geoX(representativeImage));
  image.attr("y", geoY(representativeImage));
  image.attr("width", itemWidth(representativeImage));
  image.attr("height", itemHeight(representativeImage));
  image.style("opacity", 0.75);
}

function posX(obj, i) {
return (obj.index%10) * (width / 10);
}
function posY(obj, i) {
return Math.floor(obj.index/10) * (height / 10) + (height / 50);
}
function itemWidth(obj) {
return (width / 10);
}
function itemHeight(obj) {
return (height / 10)*0.8;
}

function posXHoverZoom(obj) {
return (obj.index%10) * (width / 10) - itemWidthHoverZoom(obj)/2;
}
function posYHoverZoom(obj) {
return Math.floor(obj.index/10) * (height / 10) - itemHeightHoverZoom(obj)/2;
}
function itemWidthHoverZoom(obj) {
return itemWidth(obj)*4;
}
function itemHeightHoverZoom(obj) {
return itemHeight(obj)*4;
}

function nodeImageLink(obj) {
  if(zoomType == ZoomType.GLOBAL_ONE_YEAR) {
    var nodeImage = pickImg(obj[selectedYear]);
    if(nodeImage != null && nodeImage != undefined) {
      return nodeImage.downloadUrl;
    }
  }
  else {
    for(var i = 0; i < 26; i++) {
      var nodeImage = pickImg(obj[i]);
      if(nodeImage != null && nodeImage != undefined) {
        return nodeImage.downloadUrl;
      }
    }
  }
}