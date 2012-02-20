/*
 * Created for CS 3505 Spring 2012
 * Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
 * 
 * Class for maintaining and coallescing the results from possilby multiple page_handler objects simultaneously.
 */

#ifndef RESULTS_MANAGER_H
#define RESULTS_MANAGER_H

#include <vector>

#include "HashMap.h"
#include "page_handler_args.h"
#include "reviewer.h"
#include "commenter.h"

// Class for maintaining and coallescing the results from possilby multiple page_handler objects simultaneously
class results_manager
{

public:

	/* General public data/methods:
	 ******************************/

	// Default constructor
	results_manager();

	// Destructor
	~results_manager();

	// Resets all values in results_manager to default values
	void reset();

	// Collects the page_stats object of data collected from a single URL
	void submitPageStats(page_handler_args *args);

	// TODO Unsigned int to doubles due to adverage methods?

	// A number of get methods to extract data totals
	unsigned int getTotalPagesCount();
	unsigned int getTotalLinkCount();
	unsigned int getTotalInternalLinkCount();
	unsigned int getTotalExternalLinkCount();
	unsigned int getTotalImageCount();
	unsigned long getTotalWordCount();
	unsigned int getTotalMispelledWordCount();
	unsigned int getTotalKiloBytesOfPages();

	// A number of get methods to extract interesting data ratios
	// searchflag should there be methods for these, or should it be up to the results printer
	// to decide how and what to compute based on the counts from above?
	double getAverageLinksPerPage(); // links/pages
	double getAverageInternalLinksPerPage(); // intetnalinks/pages
	double getAverageExternalLinksPerPage(); // externalLinks/pages
	double getAverageWordsPerImage(); // words/images
	double getAverageWordsPerPage(); // words/pages
	double getAverageImagesPerPage(); // images/pages
	double getAverageMisspelledWordsPerPage(); // misspelledWords/pages
	double getAverageKilobytesPerPage(); // kilobytes/pages
	double getAverageLinksPerImage(); // links/images
	double getAverageLinksPerWord(); // links/words
	double getAverageWordsPerMisspelledWord(); // totalWords/misspelledWords
	double getAverageInternalLinksPerExternalLink(); // internalLinks/externalLinks

	/* Amazon.com specific public data/methods:
	 ******************************************/

	// Updates all reviewers in this results manager from the given list of reviewers.
	// If the reviewer already exists, their information will be updated. If they do
	// not yet exist, they will be added.
	void updateReviewer(reviewer *theReviewer);

	// Updates all reviewers in this results manager from the given list of reviewers.
	// If the reviewer already exists, their information will be updated. If they do
	// not yet exist, they will be added.
	//void updateCommenters(vector<commenter*> *commenters); // p2

	// A number of get methods to extract Amazon data totals
	unsigned int getTotalAmazonProductPagesCount();
	unsigned int getToalAmazonProductRatingsCount();
	unsigned int getTotalAmazonRelatedProductsCount();
	unsigned int getTotalAmazonReviewsCount();

	// A number of get methods to extract interesting Amazon data ratios
	double getAmazonAverageProductRating();
	double getAmazonAverageRelatedProductsPerProduct();
	double getAmazonAverageReviewsPerProduct();
	double getAmazonAverageProductPagesPerNonProductPage();
	double getAmazonReviewMisspellingsPercent();
	double getAmazonAverageReviewMisspelledWordsPerReview();
	double getAmazonAverageReviewWordsPerReview();

	//searchflag need average misspelled words per review. this will require page_stats to be modified.

private:

	/* General private data/methods:
	 *******************************/

	unsigned int totalPagesCount;
	unsigned int totalLinkCount;
	unsigned int totalInternalLinkCount;
	unsigned int totalExternalLinkCount;
	unsigned int totalImageCount;
	unsigned long totalWordCount;
	unsigned int totalMispelledWordCount;
	unsigned int totalKiloBytesOfPages;

	/* Amazon specific data/methods:
	 *******************************/

	unsigned int totalAmazonProductPagesCount;
	unsigned int toalAmazonProductRatings;
	unsigned int totalAmazonRelatedProductsCount;
	unsigned int totalAmazonReviewsCount;
	unsigned int totalAmazonReviewWordCount;
	unsigned int totalAmazonReviewMisspelledWordCount;
	unsigned int totalAmazonReviewCommentsCount; // p2

	HashMap<reviewer> reviewers;
	//HashMap<commenter*> commenters;

};

#endif
