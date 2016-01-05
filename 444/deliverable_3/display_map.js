function displayMap() {
  var projection = 
    d3.geo.equirectangular()
    .scale(width/6.25)
    .translate([width / 2, height / 2])
    .precision(.1);

  var path = 
    d3.geo.path()
    .projection(projection);

  var graticule = 
    d3.geo.graticule()
    .step([36, 18]); 

  var svg = 
    d3.select("#map_layer").append("svg")
    .attr("width", width)
    .attr("height", height);

  svg
    .append("path")
    .datum(graticule)
    .attr("class", "graticule")
    .attr("d", path);

  d3.json("world-50m.json", function(error, world) {
    if (error) throw error;

    svg.insert("path", ".graticule")
      .datum(topojson.feature(world, world.objects.land))
      .attr("class", "land")
      .attr("d", path);

    svg.insert("path", ".graticule")
      .datum(topojson.mesh(world, world.objects.countries, function(a, b) { return a !== b; }))
      .attr("class", "boundary")
      .attr("d", path);
  });
  d3.select("#map_layer")
  .style("width", width + "px")
  .style("height", height + "px");
}