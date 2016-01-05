function main() {
  width = window.innerWidth;
  height = window.innerWidth / 2;
  displayMap();
  loadData();

  d3.selectAll(".radio-inline").style("opacity", 0.0);
  d3.select("#search_input").on("input", function() {
    updateSearchTerms(this.value);
  });
  d3.select("#year_input").on("input", function() {
    updateSearchYear(+this.value);
  });
}

function pageResized() {
  width = window.innerWidth;
  height = window.innerWidth / 2;
  d3.selectAll("svg").remove();
  displayMap();
  updateSearchYear(selectedYear);
}

main();
