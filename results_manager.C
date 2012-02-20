/*
 * Created for CS 3505 Spring 2012
 * Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
 * 
 * Implemenation of the results_manager class.
 * For more information, see results_manager.h header comment
 */

#include "results_manager.h"

// Default constructor
results_manager::results_manager()
{
	reset();
}

// Destructor
results_manager::~results_manager()
{
}

void results_manager::reset()
{
	totalPagesCount = 0;
	totalLinkCount = 0;
	totalInternalLinkCount = 0;
	totalExternalLinkCount = 0;
	totalImageCount = 0;
	totalWordCount = 0;
	totalMispelledWordCount = 0;
	totalKiloBytesOfPages = 0;

	/* Amazon specific data/methods:
	 *******************************/

	totalAmazonProductPagesCount = 0;
	toalAmazonProductRatings = 0;
	totalAmazonRelatedProductsCount = 0;
	totalAmazonReviewsCount = 0;
	totalAmazonReviewWordCount = 0;
	totalAmazonReviewMisspelledWordCount = 0;
	totalAmazonReviewCommentsCount = 0; // p2

	// searchflag - need to be able to reset this!
	//reviewers;
}

void results_manager::submitPageStats(page_handler_args *args)
{
	// TODO Make this threadsafe!!!!

	//unused page_stats variables:
	// string URL;
	this->totalPagesCount++;

	this->totalWordCount += args->pageStats.getTotalWordCount();
	this->totalMispelledWordCount += args->pageStats.getTotalMisspelledWordCount();
	this->totalImageCount += args->pageStats.getTotalImageCount();
	this->totalKiloBytesOfPages += args->pageStats.getTotalKiloBytes();
	this->totalLinkCount += args->pageStats.getTotalLinkCount();
	this->totalInternalLinkCount += args->pageStats.getTotalInternalLinkCount();
	this->totalExternalLinkCount += args->pageStats.getTotalExternalLinkCount();

	if(args->pageStats.getIsAmazon())
	{
		if(args->pageStats.getIsAmazonProductPage())
		{
			this->totalAmazonProductPagesCount++;
			this->toalAmazonProductRatings += args->pageStats.getProductRating();
			this->totalAmazonRelatedProductsCount += args->pageStats.getRelatedProductCount();
		}
		else if(args->pageStats.getIsAmazonReviewPage())
		{
			this->totalAmazonReviewsCount++;
			this->totalAmazonReviewsCount += args->pageStats.getTotalReviewCount();
			this->totalAmazonReviewWordCount += args->productReviewer.getTotalWordCount();
			this->totalAmazonReviewMisspelledWordCount += args->productReviewer.getMisspelledCount();
			updateReviewer(&(args->productReviewer));
		}
	}
	
		
	
}

void results_manager::updateReviewer(reviewer *theReviewer)
{
	// TODO Make this threadsafe!!!!

	reviewer *existingReviewer = reviewers.GetValuePtr(theReviewer->getID());

	if (existingReviewer != 0)
	{
		existingReviewer->update(theReviewer);
	}
	else
	{
		reviewer newReviewer = *theReviewer;

		reviewers.put(newReviewer.getID(), newReviewer);
	}
}

//void results_manager::updateCommenters(vector<commenter*> *commenters) // p2
//{
//	// TODO Make this threadsafe!!!!
//}


/*** GETTERS ***/

// General page data getters
unsigned int results_manager::getTotalPagesCount(){return totalPagesCount;}
unsigned int results_manager::getTotalLinkCount(){return totalLinkCount;}
unsigned int results_manager::getTotalInternalLinkCount(){return totalInternalLinkCount;}
unsigned int results_manager::getTotalExternalLinkCount(){return totalExternalLinkCount;}
unsigned int results_manager::getTotalImageCount(){return totalImageCount;}
unsigned long results_manager::getTotalWordCount(){return totalWordCount;}
unsigned int results_manager::getTotalMispelledWordCount(){return totalMispelledWordCount;}
unsigned int results_manager::getTotalKiloBytesOfPages(){return totalKiloBytesOfPages;}

// Amazon page data getters
unsigned int results_manager::getTotalAmazonProductPagesCount(){return totalAmazonProductPagesCount;}
unsigned int results_manager::getTotalAmazonRelatedProductsCount(){return totalAmazonProductPagesCount;}
unsigned int results_manager::getTotalAmazonReviewsCount(){return totalAmazonProductPagesCount;}

// A number of get methods to extract interesting data ratios
// searchflag should there be methods for these, or should it be up to the results printer
// to decide how and what to compute based on the counts from above?
double results_manager::getAverageLinksPerPage(){return totalLinkCount/totalPagesCount;} // links/pages
double results_manager::getAverageInternalLinksPerPage(){return totalInternalLinkCount/totalPagesCount;} // intetnalinks/pages
double results_manager::getAverageExternalLinksPerPage(){return totalExternalLinkCount/totalPagesCount;} // externalLinks/pages
double results_manager::getAverageWordsPerImage(){return totalWordCount/totalImageCount;} // words/images
double results_manager::getAverageWordsPerPage(){return totalWordCount/totalPagesCount;} // words/pages
double results_manager::getAverageImagesPerPage(){return totalImageCount/totalPagesCount;} // images/pages
double results_manager::getAverageMisspelledWordsPerPage(){return totalMispelledWordCount/totalPagesCount;} // misspelledWords/pages
double results_manager::getAverageKilobytesPerPage(){return totalKiloBytesOfPages/totalPagesCount;} // kilobytes/pages
double results_manager::getAverageLinksPerImage(){return totalLinkCount/totalImageCount;} // links/images
double results_manager::getAverageLinksPerWord(){return totalLinkCount/totalWordCount;} // links/words
double results_manager::getAverageWordsPerMisspelledWord(){return totalWordCount/totalMispelledWordCount;} // totalWords/misspelledWords
double results_manager::getAverageInternalLinksPerExternalLink(){return totalInternalLinkCount/totalExternalLinkCount;} // internalLinks/externalLinks

// A number of get methods to extract interesting data ratios from Amazon
double results_manager::getAmazonAverageProductRating(){return toalAmazonProductRatings/totalAmazonProductPagesCount;}
double results_manager::getAmazonAverageRelatedProductsPerProduct(){return totalAmazonRelatedProductsCount/totalAmazonProductPagesCount;}
double results_manager::getAmazonAverageReviewsPerProduct(){return totalAmazonReviewsCount/totalAmazonProductPagesCount;}
double results_manager::getAmazonAverageProductPagesPerNonProductPage(){return totalAmazonProductPagesCount/totalPagesCount;}
double results_manager::getAmazonReviewMisspellingsPercent(){return totalAmazonReviewMisspelledWordCount/totalAmazonReviewWordCount;}
double results_manager::getAmazonAverageReviewMisspelledWordsPerReview(){return totalAmazonReviewMisspelledWordCount/totalAmazonReviewsCount;}
double results_manager::getAmazonAverageReviewWordsPerReview(){return totalAmazonReviewWordCount/totalAmazonReviewsCount;}
