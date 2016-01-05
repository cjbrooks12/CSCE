function displayMapLayer() {
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

  d3.select('#map_layer svg').remove();
  var svg = d3.select('#map_layer').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);

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
  });
  
  mapIsDrawn = true;
}

function displayMapCellLayer() {
  var cellWidth = width / 10;
  var cellHeight = height / 10;

  var selectedCellCoords = {
    i: ((selectedCell)%10)+1,
    j: (Math.floor(selectedCell/10))+1
  }

  var selectedCellLatLng = {
    lng: ((selectedCellCoords.i-5)*36) - 18,
    lat: -1*(((selectedCellCoords.j-5)*18) - 9)
  }

  var projection = 
    d3.geo.equirectangular()
    .scale(width/0.625)
    .translate([width / 2, height / 2])
    .center([selectedCellLatLng.lng, selectedCellLatLng.lat])
    .precision(.1);

  var path = 
    d3.geo.path()
    .projection(projection);

  var graticule = 
    d3.geo.graticule()
    .step([3.6, 1.8]); 

  d3.select('#map_layer svg').remove();
  var svg = d3.select('#map_layer').append('svg');
  svg.attr('width', width);
  svg.attr('height', height);

  d3.json("world-50m.json", function(error, world) {
    if (error) throw error;

    svg.insert("path", ".graticule")
      .datum(topojson.feature(world, world.objects.land))
      .attr("class", "land")
      .attr("d", path);

    svg.insert("path", ".graticule")
      .datum(topojson.mesh(world, world.objects.countries, function(a, b) { return a !== b; }))
      .attr("class", "boundary")
      .attr("d", path)
      .style("stroke", "#888");
  });

  mapIsDrawn = true;
}