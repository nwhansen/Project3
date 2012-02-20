/*
* Created for CS 3505 Spring 2012
* Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
* 
* Class for maintaining the statistics of a single URL page.
*/

#ifndef PAGE_STATS_H
#define PAGE_STATS_H

#include <string>

using namespace std;

// Class for maintaining the statistics of a single URL page

class page_stats {
public:

	page_stats();

	~page_stats();
	/** Getters **/
	bool getIsAmazon();

	bool getIsAmazonProductPage();

	bool getIsAmazonReviewPage();

	string getURL();

	int getTotalWordCount() ;

	int getTotalMisspelledWordCount() ;

	int getTotalImageCount();

	int getTotalKiloBytes();

	int getTotalLinkCount();

	int getTotalInternalLinkCount();

	int getTotalExternalLinkCount();

	/** Setters **/
	void setIsAmazon(bool isAmazon);

	void setIsAmazonProductPage(bool isProductPage);

	void setIsAmazonReviewPage(bool isReviewPage);

	void setURL(string URL);

	void setTotalWordCount(int wordCount) ;

	void setTotalMisspelledWordCount(int misspellCount) ;

	void setTotalImageCount(int imageCount) ;

	void setTotalKiloBytes(int kiloByteCount);

	void setTotalLinkCount(int linkCount) ;

	void setTotalInternalLinkCount(int internalLinkCount) ;

	void setTotalExternalLinkCount(int externalLinkCount) ;

	/** Amazon specific methods **/
	int getProductRating() ;

	int getRelatedProductCount();

	int getTotalReviewCount();
	//int getTotalCommentorCount;
	void reset();

	//FILL IN
private:

	bool isAmazon;
	bool isAmazonProductPage;
	bool isAmazonReviewPage;
	string URL;
	int totalWordCount;
	int totalMisspelledWordCount;
	int totalImageCount;
	int totalKiloBytes;
	int totalLinkCount;
	int totalInternalLinkCount;
	int totalExternalLinkCount;


	/** Amazon specific data members **/
	int productRating;
	int relatedProductCount;
	int totalReviewCount;
	//int totalCommentorCount;

};

#endif
