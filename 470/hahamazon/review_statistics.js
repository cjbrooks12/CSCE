var fs = require('fs');

// Main Function
//------------------------------------------------------------------------------
var main = function(){
  readFiles(__dirname + '/reviews/');
}

if (require.main === module) {
    main();
}

String.prototype.replaceAll = function(search, replacement) {
    var target = this;
    return target.split(search).join(replacement);
};

//Read files
//------------------------------------------------------------------------------

function readFiles(dirname, onFileContent, onError) {
  fs.readdir(dirname, function(err, filenames) {
    if (err) {
      return;
    }

    var histogram = {};
    var totalFiles = filenames.length;
    var filesRead = 0;

    filenames.forEach(function(filename) {
      fs.readFile(dirname + filename, 'utf-8', function(err, content) {
        if (err) {
          return;
        }

        var words = content.split(/\s+/);

        for(var i = 1; i < words.length; i++) {
          var word = words[i].replaceAll(/\W/, '');

          if(word.length > 4) {
            if(word in histogram) {
              histogram[word] = histogram[word] + 1;
            }
            else {
              histogram[word] = 1;
            }
          }
        }

        filesRead++;

        if(filesRead == totalFiles) {

          var sortedHistogram = Object.keys(histogram).map(function(key) {
            return {
              key: key,
              val: histogram[key]
            };
          });

          //sort smallest to largest
          // sortedHistogram.sort(function(a, b) {
          //   return b.val - a.val;
          // });

          //sort largest to smallest
          sortedHistogram.sort(function(a, b) {
            return a.val - b.val;
          });

          var totalWords = 0;
          for(var i = 1; i < sortedHistogram.length; i++) {
            totalWords += sortedHistogram[i].val;
          }

          console.log(JSON.stringify(sortedHistogram, null, 2));
          console.log('words in all reviews: ' + totalWords);

        }
      });
    });
  });
}