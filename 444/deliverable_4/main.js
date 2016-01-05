function main() {
  width = window.innerWidth;
  height = window.innerWidth / 2;
  loadData();

  d3.selectAll(".radio-inline").style("opacity", 0.0);
  d3.select("#search_input").on("input", function() {
    updateSearchTerms(this.value.trim());
  });
  d3.select("#year_input").on("input", function() {
    updateSearchYear(+this.value);
  });
  d3.select(".back_button").on("click", function() {
    zoomType = ZoomType.WHOLE_DATASET;
    mapIsDrawn = false;
    selectedYear = -1;
    selectedCell = -1;
    displayAll();
  });
  d3.select("#tag_search_button").on("click", function() {
    performSearch();
  });
  d3.select("#show_images_checkbox").on("change", function() {
    if(this.checked) {
      d3.select("#images_layer")
        .transition().duration(500)
        .style("opacity", 1.0);
      displayImages = true;
      displayAll();
    }
    else {
      d3.select("#images_layer")
        .transition().duration(500)
        .style("opacity", 0.0);
      displayImages = false;
      displayAll();
    }
  });
  d3.select("#show_counts_checkbox").on("change", function() {
    if(this.checked) {
      d3.select("#counts_layer")
        .transition().duration(500)
        .style("opacity", 1.0);
      displayCounts = true;
      displayAll();
    }
    else {
      d3.select("#counts_layer")
        .transition().duration(500)
        .style("opacity", 0.0);
      displayCounts = false;
      displayAll();
    }
  });
}

function pageResized() {
  mapIsDrawn = false
  width = window.innerWidth;
  height = window.innerWidth / 2;
  d3.selectAll("svg").remove();
  displayAll();
  updateSearchYear(selectedYear);
}

main();
