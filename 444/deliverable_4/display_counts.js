function displayImageCountsLayer(data) {
  d3.select('#counts_layer svg').remove();
  var svg = d3.select('#counts_layer').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);

  var objLengths = data.map(function(obj) {
    if(selectedYear == -1) {
      var count = 0;
      for(var i = 0; i < obj.length; i++) {
        count += obj[i].length;
      }
      obj.count = count;
      return count;
    }
    else {
      obj.count = obj[selectedYear].length;
      return obj[selectedYear].length;
    }
  });
  var min = Math.min.apply(null, objLengths);
  if(min == 0) min = 1;
  var max = Math.max.apply(null, objLengths);
  var colorScale = 
    d3.scale.log()
    .domain([min, max])
    .range(["#FF0000", "#00E833"]);

  var followerScale = 
    d3.scale.log()
    .domain([1, 100])
    .range([0.25, 1.0]);

  function posX(obj, i) {
  return (obj.index%10) * (width / 10);
  }
  function posY(obj, i) {
  return Math.floor(obj.index/10) * (height / 10);
  }
  function textX(obj, i) {
  return (obj.index%10) * (width / 10) + (width / 50);
  }
  function textY(obj, i) {
  return Math.floor(obj.index/10) * (height / 10) + (height / 100);
  }
  function countText(obj) {
  return obj.count;
  }
  function radius(user) {
    return (width / 100);
  }
  function itemWidth(user) {
    return (width / 10);
  }
  function itemHeight(user) {
    return (height / 10) / 5;
  }
  function countColor(obj) {
    return colorScale(obj.count);
  }
  function countOpacity(obj) {
    var thisobj = nodeImageObj(obj);
    if(thisobj == undefined) return 0.25;
    else return followerScale(thisobj.followCount);
  }

  var node = svg
    .selectAll('.node')
    .data(data);

  var g = node
    .enter()
    .append('g')
    .classed('node', true);

  var circle = g.append('rect');
  circle.attr('x', posX);
  circle.attr('y', posY);
  circle.attr('width', itemWidth);
  circle.attr('height', itemHeight);
  circle.style("fill", countColor);
  circle.style("opacity", countOpacity);

  var text = g.append("text");
  text.attr('font-family', 'Helvetica');
  text.attr('font-size', '9pt');
  text.attr('text-anchor', 'middle');
  text.attr('dominant-baseline', 'middle');
  text.attr('x', textX);
  text.attr('y', textY);
  text.text(countText);

  d3.select("#visualizaton")
  .style("width", width + "px")
  .style("height", height + "px");
}

function displayImageCountsCellLayer(data) {
  d3.select('#counts_layer svg').remove();
  var svg = d3.select('#counts_layer').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);
}

function nodeImageObj(obj) {
  if(zoomType == ZoomType.GLOBAL_ONE_YEAR) {
    var nodeImage = pickImg(obj[selectedYear]);
    if(nodeImage != null && nodeImage != undefined) {
      return nodeImage;
    }
  }
  else {
    for(var i = 0; i < 26; i++) {
      var nodeImage = pickImg(obj[i]);
      if(nodeImage != null && nodeImage != undefined) {
        return nodeImage;
      }
    }
  }
}