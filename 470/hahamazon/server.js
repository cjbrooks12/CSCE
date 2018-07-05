//setup server and global variables
//------------------------------------------------------------------------------
var express = require('express');
var fs = require("fs");
var bodyParser = require('body-parser');

var app = express();

app.set('port', (process.env.PORT || 5000));

app.use(express.static(__dirname + '/public'));
app.use('/scripts', express.static(__dirname + '/node_modules'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));

app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');

//data to be used in the algorithm
//------------------------------------------------------------------------------
var reviews = [];
var funnyIndex = {count: {}, frequency: {}, totalCount: 0};
var boringIndex = {count: {}, frequency: {}, totalCount: 0};
var idf = {};

//HTTP server methods
//------------------------------------------------------------------------------
function startServer() {
  app.get('/', function(request, response) {
    var review = reviews[Math.floor(Math.random()*reviews.length)];
    while(review.classification != "funny") {
        review = reviews[Math.floor(Math.random()*reviews.length)];
    }
    if(review) {
      response.render('home', {data: review});
     }
    else {
      response.send("error getting review");
    }
  });
  app.get('/funnyIndex', function(request, response) {
    response.json(funnyIndex);
  });
  app.get('/boringIndex', function(request, response) {
    response.json(boringIndex);
  });
  app.get('/p/:tagId', function(request, response){
    var review;
    for (var i  = 0; i < reviews.length; i++) {
      if(reviews[i].name == request.params.tagId) {
        review = reviews[i];
      }
    }

    if(review)
      response.render('home',{data: review})
    else
      response.send("cannot find review with tagId=" + request.params.tagId);
  })
  app.get('/p/:tagId/json', function(request, response){
    var review;
    for (var i  = 0; i < reviews.length; i++) {
      if(reviews[i].name == request.params.tagId) {
        review = reviews[i];
      }
    }

    if(review)
      response.json(review);
    else
      response.send("cannot find review with tagId=" + request.params.tagId);
  })
  app.post('/upvote', function(request, response) {
    if(request.body.review_name) {
      console.log("upvoting " + request.body.review_name);
      var review;
      for (var i  = 0; i < reviews.length; i++) {
        if(reviews[i].name == request.body.review_name) {
          review = reviews[i];
        }
      }

      if(review) {
        review.upvotes++;
        if(review.funnyCount * review.upvotes > review.boringCount * review.downvotes) {
          review.classification = "funny";
        }
        else {
          review.classification = "boring";
        }
        response.send("POSTed to /upvote");
      }
      else {
        response.send("cannot find review with review_name=" + request.body.review_name);
      }
    }
    else {
      response.send("must send a review_name to update");
    }
  });
  app.post('/downvote', function(request, response) {
    if(request.body.review_name) {
      console.log("downvoting " + request.body.review_name);
      var review;
      for (var i  = 0; i < reviews.length; i++) {
        if(reviews[i].name == request.body.review_name) {
          review = reviews[i];
        }
      }

      if(review) {
        review.downvotes++;
        if(review.funnyCount * review.upvotes > review.boringCount * review.downvotes) {
          review.classification = "funny";
        }
        else {
          review.classification = "boring";
        }
        response.send("POSTed to /downvote");
      }
      else {
        response.send("cannot find review with review_name=" + request.body.review_name);
      }
    }
    else {
      response.send("must send a review_name to update");
    }
  });

  app.get('/similar', function(request, response) {
    if(request.query.review_name) {
      console.log("getting similar review to " + request.query.review_name);
      var review;
      for (var i  = 0; i < reviews.length; i++) {
        if(reviews[i].name == request.query.review_name) {
          review = reviews[i];
          break;
        }
      }

      if(review) {
        rank_tf_idf(review, function(similarReview) {
          response.render('home',{data: similarReview})
        })
      }
      else {
        response.send("cannot find review with review_name=" + request.query.review_name);
      }
    }
    else {
      response.send("must send a review_name to update");
    }
  });

  app.listen(app.get('port'), function() {
    console.log('Node app is running on port', app.get('port'));
  });
}

//core algorithm
//------------------------------------------------------------------------------
trainClassifier(function() {
  indexReviews(function() {
    startServer();
  });
});

//Train Naive Bayes classifier
//------------------------------------------------------------------------------
function trainClassifier(callback) {
  var trainedCount = 0;

  //train the 'funny' class
  var funnyDir = __dirname + '/funnyReviews/';
  fs.readdir(funnyDir, function(err, filenames) {
    if (err) {
      return;
    }

    var totalFiles = filenames.length;
    var filesRead = 0;

    filenames.forEach(function(filename) {
      fs.readFile(funnyDir + filename, 'utf-8', function(err, content) {
        if (err) throw err;

        var words = content.split(/\s+/);
        for(var i = 1; i < words.length; i++) {
          var word = words[i].replace(/\W/, '');
          if(word in funnyIndex.count) {
            funnyIndex.count[word]++;
          }
          else {
            funnyIndex.count[word] = 1;
          }
          funnyIndex.totalCount++;
        }

        filesRead++;
        if(filesRead == totalFiles) {
          console.log("Finished training 'funny' classifier");
          trainedCount++;
          if(trainedCount == 2) {
            calculateClassFrequencies(callback);
          }
        }
      });
    });
  });

  //train the 'boring' class
  var boringDir = __dirname + '/boringReviews/';
  fs.readdir(boringDir, function(err, filenames) {
    if (err) {
      return;
    }

    var totalFiles = filenames.length;
    var filesRead = 0;

    filenames.forEach(function(filename) {
      fs.readFile(boringDir + filename, 'utf-8', function(err, content) {
        if (err) throw err;

        var words = content.split(/\s+/);
        for(var i = 1; i < words.length; i++) {
          var word = words[i].replace(/\W/, '');
          if(word in boringIndex.count) {
            boringIndex.count[word]++;
          }
          else {
            boringIndex.count[word] = 1;
          }
          boringIndex.totalCount++;
        }

        filesRead++;
        if(filesRead == totalFiles) {
          console.log("Finished training 'boring' classifier");
          trainedCount++;
          if(trainedCount == 2) {
            calculateClassFrequencies(callback);
          }
        }
      });
    });
  });
}

function calculateClassFrequencies(callback) {
  console.log("calculating class frequencies");
  var totalWordCount = 0;
  for(var key in funnyIndex.count) {
    totalWordCount = totalWordCount + funnyIndex.count[key];
  }
  for(var key in boringIndex.count) {
    totalWordCount = totalWordCount + boringIndex.count[key];
  }

  for (var key in funnyIndex.count) {
    if (funnyIndex.count.hasOwnProperty(key)) {
      funnyIndex.frequency[key] = funnyIndex.count[key] / totalWordCount;
    }
  }

  for (var key in boringIndex.count) {
    if (boringIndex.count.hasOwnProperty(key)) {
      boringIndex.frequency[key] = boringIndex.count[key] / totalWordCount;
    }
  }

  callback();
}

function indexReviews(callback) {
  console.log("indexing reviews");

  var dirname = __dirname + '/new_unique_reviews/';
  fs.readdir(dirname, function(err, filenames) {
    if (err) {
      return;
    }

    var totalFiles = filenames.length;
    var filesRead = 0;
    var errorFiles = 0;

    filenames.forEach(function(filename) {
      fs.readFile(dirname + filename, 'utf-8', function(err, content) {
        if (err) throw err;

        try {
          var review = JSON.parse(content);
          naiveBayes(review);
          tf(review);
          reviews.push(review);
        }
        catch(err2) {
          errorFiles++;
          console.log(err2);
        }

        filesRead++;
        if(filesRead == totalFiles) {
          for(var i = 0; i < reviews.length; i++) {
            tf_idf(reviews[i]);
          }

          console.log("Finished reading reviews, should be starting the server. totalFiles=" + totalFiles + ", errorFiles=" + errorFiles);
            callback();
        }
      });
    });
  });
}

//Classify a review using our trained Naive Bayes classifier
//------------------------------------------------------------------------------
function naiveBayes(review) {
  //we have an equal amount of training data by word count for each class, so class
  //probability for each is 50%, meaning we can safely ignore that term in the
  //final calculation.
  var funnyCount = 0.0;
  var boringCount = 0.0;

  var reviewIndex = {};

  //get the word count of a particualr review
  var words = review.review.split(/\s+/);
  for(var i = 1; i < words.length; i++) {
    var word = words[i].replace(/\W/, '');
    if(word in reviewIndex) {
      reviewIndex[word]++;
    }
    else {
      reviewIndex[word] = 1;
    }
  }

  var reviewTotalWordCount = 0;
  for(var key in reviewIndex) {
    reviewTotalWordCount = reviewTotalWordCount + reviewIndex[key];
  }

  for (var key in reviewIndex) {
    var reviewFrequency =  reviewIndex[key] / reviewTotalWordCount;

    var funnyAddition = reviewFrequency * funnyIndex.frequency[key];
    var boringAddition = reviewFrequency * boringIndex.frequency[key];

    if(!isNaN(funnyAddition))
      funnyCount += funnyAddition;

    if(!isNaN(boringAddition))
      boringCount += boringAddition;
  }

  if(funnyCount > boringCount) {
    review.classification = 'funny';
  }
  else{
    review.classification = 'boring';
  }

  review.funnyCount = funnyCount;
  review.boringCount = boringCount;
  review.difference = Math.floor((review.funnyCount / review.boringCount) * 100)-100;

  if(review.classification === "funny") {
    review.upvotes = Math.ceil(review.difference * (3.0/4.0));
    review.downvotes = Math.ceil(review.difference * (1.0/4.0));
  }
  else {
    review.upvotes = Math.ceil(review.difference * (1.0/3.0));
    review.upvotes = Math.ceil(review.difference * (2.0/3.0));
  }
}

function tf(review) {
  review.reviewIndex = {};

  //get the term frequency for a particular review
  var words = review.review.split(/\s+/);
  for(var i = 1; i < words.length; i++) {
    var word = words[i].replace(/\W/, '');
    if(word in review.reviewIndex) {
      review.reviewIndex[word]++;
    }
    else {
      review.reviewIndex[word] = 1;
    }
  }

  //update the IDF vector from the words in this review
  for (var key in review.reviewIndex) {
    if(key in idf) {
      idf[key]++;
    }
    else {
      idf[key] = 1;
    }
  }
}

function tf_idf(review) {
  review.tf_idf = {};

  for (var key in review.reviewIndex) {
    var key_tf = 1 + Math.log10(review.reviewIndex[key]);
    var key_idf = Math.log10(reviews.length / idf[key]);

    review.tf_idf[key] = {
      raw_tf: review.reviewIndex[key],
      raw_df: idf[key],
      tf: key_tf,
      idf: key_idf,
      tf_idf: key_tf*key_idf
    }
  }
}

function rank_tf_idf(queryReview, callback) {

  var cosineRanking = [];

  for (var i  = 0; i < reviews.length; i++) {
    var cos = rankCosine(queryReview, reviews[i]);

    if(cos < 1) {
      cosineRanking.push({
        name: reviews[i].name,
        cosine: cos
      });
    }
  }

  cosineRanking.sort(function(a, b) {
    return b.cosine - a.cosine;
  });

  var randomSimilarReviewIndex = Math.floor(Math.random()*5);
  var randomSimilarReviewName = cosineRanking[randomSimilarReviewIndex].name;
  for (var i  = 0; i < reviews.length; i++) {
    if(reviews[i].name == randomSimilarReviewName) {
      callback(reviews[i]);
      return;
    }
  }
}

function rankCosine(queryReview, docReview) {
  var magQ = vectorMagnitude(queryReview);
  var magD = vectorMagnitude(docReview);
  var dotProduct = vectorDotProduct(queryReview, docReview);

  return dotProduct / (magD * magQ);
}

function vectorMagnitude(review) {
  var sum = 0;

  for (var key in review.tf_idf) {
    sum += review.tf_idf[key].tf_idf * review.tf_idf[key].tf_idf;
  }

  return Math.sqrt(sum);
}

function vectorDotProduct(queryReview, docReview) {
  var sum = 0;

  for (var key in queryReview.tf_idf) {
    if(key in docReview.tf_idf) {
      sum += queryReview.tf_idf[key].tf_idf * docReview.tf_idf[key].tf_idf;
    }
  }

  return sum;
}