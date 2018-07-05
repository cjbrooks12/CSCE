var jsdom = require('jsdom');
var fs = require('fs');
var request = require('request');
var TotalItems = 30;
var tag;

// Main Function
//------------------------------------------------------------------------------
var main = function(){
    if(process.argv.length != 4) {
        console.log("run command: node amazon-items.js <url of amazon product> <tag to append to filenames>");
        return;
    }
    tag = process.argv[3];
    loadAmazonProduct(process.argv[2], TotalItems);
}

if (require.main === module) {
    main();
}

//load amazon product
//------------------------------------------------------------------------------
function loadAmazonProduct(amazonBaseUrl, productIndex) {
    var request = require('request');
    request({uri: amazonBaseUrl}, function(err, response, body) {
        if(err) {
            console.log(JSON.stringify(err));
            return;
        }
        jsdom.env({
            html: body,
            scripts: ['http://code.jquery.com/jquery-1.6.min.js'],
            done: function(err, window){
                if(err) {
                    console.log("Error loading webpage");
                    return;
                }

                parseReviews(window, amazonBaseUrl, productIndex);
                getRelatedProducts(window, amazonBaseUrl, productIndex);
            }
        });
    });
}

//Get the text of the reviews for this product
//------------------------------------------------------------------------------
function parseReviews(window, amazonBaseUrl, productIndex) {
	// console.log("parse review baseUrl = " + amazonBaseUrl)
    var $ = window.jQuery;
    var link = $("#revSum a.a-nowrap");
    var linkUrl = link.attr('href');
    var collectedData = {
        productTitle: $("#productTitle").text(),
        imageUrl: $("#landingImage").attr("src")
    };
    console.log("parse review = " + JSON.stringify(collectedData));

	if(linkUrl) {
		for(var i = 1; i < 10; i++) {
		    saveReviews(amazonBaseUrl, collectedData, linkUrl, i, productIndex);
		}
	}
}

function saveReviews(amazonBaseUrl, collectedData, linkUrl, i, productIndex) {
    var linkPage = linkUrl.replace("cm_cr_dp_see_all_summary", "cm_cr_getr_d_paging_btm_" + i);

    request({uri: linkPage}, function(err, response, body) {
        if(err) {
            console.log(err);
            return;
        }

        jsdom.env({
            html: body,
            scripts: ['http://code.jquery.com/jquery-1.6.min.js'],
            done: function(err, window){
                if(err) {
                    console.log(err);
                    return;
                }

                var $ = window.jQuery;
                var reviews = $(".review-text");
				//10 items per page, changed multiplier to 10, in lieu of scalability
                var reviewsIndex = (i*10);
                reviews.each(function(index) {
                    var fileContent = {};
                    fileContent.url = amazonBaseUrl;
                    fileContent.name = tag + "_" + productIndex + "_" + reviewsIndex;
                    fileContent.review = $(this).text().replace(/\s+/, ' ').trim();
                    fileContent.upvotes = 0;
                    fileContent.downvotes = 0;
                    fileContent.productTitle = collectedData.productTitle;
                    fileContent.imageUrl = collectedData.imageUrl;

                    fs.writeFile(
                        "new_reviews/" + fileContent.name + ".json",
                        JSON.stringify(fileContent),
                        function(err) {
                            if(err) {
                                return console.log(err);
                            }
                    });
                    reviewsIndex++;
                });
            }
        });
    });
}

//Get 'Customers Who Viewed This Item Also Viewed' item URLs
//------------------------------------------------------------------------------
function getRelatedProducts(window, amazonBaseUrl, productIndex) {
    var $ = window.jQuery;

    //'Customers Who Viewed This Item Also Viewed'
    var relatedProducts = $("#session-similarities_feature_div li a");
    if(relatedProducts.length > 0) {
		relatedProducts.each(function(index) {
		    var relatedUrl = "http://www.amazon.com" + $(this).attr('href');

            if(!(relatedUrl.indexOf('product-reviews') > -1)) {
                if(TotalItems > 1) {
                    TotalItems = TotalItems - 1;
                    loadAmazonProduct(relatedUrl, TotalItems);
                }
            }
    	});
	}
}
