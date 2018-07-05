

function main() {
  displayMap();
  var data = [];

  for(var i = 0; i < 100; i++) {
    data[i] = 0;
  }
  // displayData(data);

  var dataLoaded = 0;
  for(var i = 0; i < 10; i++) {
    for(var j = 0; j < 10; j++) {
      var fileName = 'outputs/data_' + i + '_' + j + '.json';
      readFile(fileName, i, j, function(dataArray, data_i, data_j) {
        data[((9-data_j)*10) + data_i] = dataArray;
        dataLoaded++;

        if(dataLoaded == 100) {
          console.log('displaying data and map');
          displayData(data);
        }
      });
    }
  }
}

main();

