var scale;

function displayData(data) {
  displayGlobalTagSuggestions(data);
  var svg = d3.select('#visualization svg').remove();
  var svg = d3.select('#visualization').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);

  // create a log scale for converting following count to circle radius
  var objLengths = data.map(function(obj) {
    return obj[selectedYear].length;
  });
  var min = Math.min.apply(null, objLengths);
  if(min == 0) min = 1;
  var max = Math.max.apply(null, objLengths);
  scale = d3.scale.log().domain([min, max]).range([0, 128]);

  var node = svg
    .selectAll('.node')
    .data(data);

  var g = node
    .enter()
    .append('g')
    .classed('node', true);

  var tip = d3.tip()
    .attr('class', 'd3-tip')
    .offset([-10, 0])
    .html(tooltipHTML);

  svg.call(tip);

  g.each(function(d, i) { d.index = i; });

  //add rect to node
  var bg_rect = g.append('rect');
  bg_rect.attr('x', posX);
  bg_rect.attr('y', posY);
  bg_rect.attr("width", itemWidth);
  bg_rect.attr("height", itemHeight);
  bg_rect.style("opacity", 0.0);
  bg_rect.style('fill', rectBgColor);

  var image = g.append("svg:image");
  image.attr("xlink:href", nodeImageLink);
  image.attr("x", posX);
  image.attr("y", posY);
  image.attr("width", itemWidth);
  image.attr("height", itemHeight);
  image.style("opacity", 0.75);

  image.on('mouseover', function(obj) {
    tip.show(obj);
    var item = d3.select(this);
      item.transition().duration(500)
      .attr("x", posXHoverZoom)
      .attr("y", posYHoverZoom)
      .attr("width", itemWidthHoverZoom)
      .attr("height", itemHeightHoverZoom)
      .style("opacity", 1.0)
  });
  image.on('mouseout', function(obj) {
    tip.show(obj);
    d3.select(this)
      .transition().duration(500)
      .attr("x", posX)
      .attr("y", posY)
      .attr("width", itemWidth)
      .attr("height", itemHeight)
      .style("opacity", 0.75)
  });
  g.on("click", function(obj) {
    displayTagSuggestions(obj);
    d3.event.stopPropagation();
  });

  d3.select("#visualizaton")
  .style("width", width + "px")
  .style("height", height + "px");
  d3.select(".page_content")
  .style("width", width + "px")
  .style("height", height + "px");
}

function displayGlobalTagSuggestions(images) {
  createGlobalTagsHistogram(images[selectedYear], function(histogramObject, sortedHistogramArray) {
    var innerHtml = '<h4>Suggested Tags</h4>';
    innerHtml += '<ul>';
    var tagsCount = (sortedHistogramArray.length > displayedTagsCount) 
        ? displayedTagsCount
        : sortedHistogramArray.length;

    for(var i = 0; i < tagsCount; i++) {
      innerHtml += '<li><a href="">' + sortedHistogramArray[i][0] + ' (' + sortedHistogramArray[i][1] + ')</a></li>';
    }
    innerHtml += '<ul>';
    d3.select("#suggestions").html(innerHtml);
  });
}

function displayTagSuggestions(images) {
  createTagsHistogram(images[selectedYear], function(histogramObject, sortedHistogramArray) {
    var innerHtml = '<h4>Suggested Tags</h4>';
    innerHtml += '<ul>';
    var tagsCount = (sortedHistogramArray.length > displayedTagsCount) 
        ? displayedTagsCount
        : sortedHistogramArray.length;

    for(var i = 0; i < tagsCount; i++) {
      innerHtml += '<li><a href="">' + sortedHistogramArray[i][0] + ' (' + sortedHistogramArray[i][1] + ')</a></li>';
    }
    innerHtml += '<ul>';
    d3.select("#suggestions").html(innerHtml);
  });
}

function posX(obj, i) {
return (obj.index%10) * (width / 10);
}
function posY(obj, i) {
return Math.floor(obj.index/10) * (height / 10);
}
function itemWidth(obj) {
return (width / 10);
}
function itemHeight(obj) {
return (height / 10);
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

function itemText(obj, i) {
return '(' + (i%10) + ', ' + Math.floor(i/10) + ') ' + obj;
}
function tooltipHTML(obj) {
return "<strong>Count:</strong> <span>" + obj[selectedYear].length + "</span>"
}
function nodeImageLink(obj) {
  var nodeImage = obj[selectedYear][0];
  if(nodeImage != null && nodeImage != undefined) {
    return obj[selectedYear][0].downloadUrl;
  }
}
function rectBgColor(obj) {
  return "rgba(144, 195, 212, " + scale(obj[selectedYear].length) + ")";
}