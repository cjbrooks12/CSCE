var fs = require("fs");

//Main method
//------------------------------------------------------------------------------
var main = function(){
  loadReviews();
}
if (require.main === module) {
  main();
}

//Data members
//------------------------------------------------------------------------------
var reviews = []
var uniqueReviews = [];

//Uniquify Reviews
//------------------------------------------------------------------------------

//loads all reviews into memory
function loadReviews() {
  var dir = __dirname + '/new_reviews/';
  fs.readdir(dir, function(err, filenames) {
    if (err) {
      return;
    }

    var totalFiles = filenames.length;
    var filesRead = 0;

    filenames.forEach(function(filename) {
      fs.readFile(dir + filename, 'utf-8', function(err, content) {
        if (err) throw err;
        reviews.push(JSON.parse(content));
        filesRead++;

        if(filesRead == totalFiles) {
          uniquifyReviews();
        }
      });
    });
  });
}

function uniquifyReviews() {
  console.log("number of reviews: " + reviews.length);

  for (var i = 0; i < reviews.length; i++) {
    console.log("checking review: " + reviews[i].name);
    if(uniqueReviews.length == 0) {
      uniqueReviews.push(reviews[i]);
    }
    else {
      var shouldAddToList = true;
      for(var j = 0; j < uniqueReviews.length; j++) {
        if(reviews[i].review === uniqueReviews[j].review) {
          shouldAddToList = false;
          break;
        }
      }

      if(shouldAddToList === true) {
        uniqueReviews.push(reviews[i]);
      }
    }
  }

  console.log("number of unique reviews: " + uniqueReviews.length);
  for (var i = 0; i < uniqueReviews.length; i++) {
    fs.writeFile(
      "new_unique_reviews/" + uniqueReviews[i].name + ".json",
      JSON.stringify(uniqueReviews[i]),
      function(err) {
        if(err) {
          return console.log(err);
        }
    });
  }
}


/*
{
  "url": "http://www.amazon.com/Zone-Tech-Laptop-Eating-Steering/dp/B00LFX3BKW/ref=pd_sbs_263_4/179-9597113-6890450?ie=UTF8&dpID=51gu166efrL&dpSrc=sims&preST=_AC_UL160_SR159%2C160_&refRID=19DEBF60BSJV1SP4ZB5M",
  "name":"3_16_84",
  "review":"Does not stay in place. Any movement causes it to fall. I didn't give one star only because it may work better on other wheels, but mine is average, with nothing unusual about it. Not good enough to keep, not worth the trouble to send back. I will say the plastic seems ok, but since it won't stay on I guess that doesn't matter",
  "upvotes":0,
  "downvotes":0,
  "productTitle":"Zone Tech Car Ipad Laptop/Eating Steering Wheel Desk",
  "imageUrl":"http://ecx.images-amazon.com/images/I/51gu166efrL._AC_UL160_SR159,160_.jpg"
}
*/