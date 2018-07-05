# Installation Instructions

First, you must install the necessary dependencies:
```
npm install
```

Then, you can run the scripts as outlined below.

### Amazon Crawler

Start the crawler with the following command:
```
node amazon-items.js <url> <tag>
```
where `<url>` is the URL of the Amazon product you wish to scrape and `<tag>` is
a tag to be appended to the beginning of the filenames for that run of the crawler.

This script takes a single product on Amazon as an argument, then extracts the
URLs of related items so that they can be queued to be parsed later. It also
extracts the text of reviews for that item so that we can use them for classification.

### Application
Our project code is currently on Heroku, available at [hahamazon.herokuapp.com](hahamazon.herokuapp.com).

For the checkpoint, we have gathered and indexed about 5000 reviews from various
items on Amazon, such as the Banana Slicer, a horse mask, or a jar of uranium ore.
We then indexed every review and ran a Naive Bayes classifier on it to determine
if the individual review was funny or not, trained with a set of hand-picked funny
reviews. The code running at the above URL will get a random review from the list
and serve it up as JSON, and should contain a property of 'classification', indicating
that the Naive Bayes classifier determined the review to be funny or not.

For additional information about our classifier, we have several other routes set
up as well:

[hahamazon.herokuapp.com](hahamazon.herokuapp.com) gets a random review and shows
the data calculated from running the Naive Bayes classifier on it.
[hahamazon.herokuapp.com/funnyIndex](hahamazon.herokuapp.com/funnyIndex) shows the
statistics of the training for the 'funny' reviews.
[hahamazon.herokuapp.com/boringIndex](hahamazon.herokuapp.com/boringIndex) shows the
statistics of the training for the 'boring', or not funny, reviews.

In the next checkpoint, we will be adding an additional step after preprocessing
to give the users more control over which reviews they find funny, using something
like a simple collaborative filtering process. In the UI, a user can vote whether
a they think a particular review is funny or not, and reviews that are voted
highly will be given preference over poorly voted items, so that over time we will
learn which reviews users think are funny.

Alternatively, if you wish to run the code yourself, follow the steps below:

1) Install packages from NPM:

``` npm install ```

2) Gather reviews from Amazon:

``` ./get_reviews ```

or

``` node amazon-items.js <url> <tag> ```

3) Run server

``` node server.js ```
