#include "page_stats.h"

page_stats::page_stats()
{
	reset();
}

page_stats::~page_stats(){}
/** Getters **/
bool page_stats::getIsAmazon() {
	return this->isAmazon;
}

bool page_stats::getIsAmazonReviewPage() {
	return this->isAmazonReviewPage;
}

bool page_stats::getIsAmazonProductPage() {
	return this->isAmazonProductPage;
}

string page_stats::getURL() {
	return this->URL;
}

int page_stats::getTotalWordCount() {
	return this->totalWordCount;
}

int page_stats::getTotalMisspelledWordCount() {
	return this->totalMisspelledWordCount;
}

int page_stats::getTotalImageCount() {
	return this->totalImageCount;
}

int page_stats::getTotalKiloBytes() {
	return this->totalKiloBytes;
}

int page_stats::getTotalLinkCount() {
	return this->totalLinkCount;
}

int page_stats::getTotalInternalLinkCount() {
	return this->totalInternalLinkCount;
}

int page_stats::getTotalExternalLinkCount() {
	return this->totalExternalLinkCount;
}

/** Setters **/
void page_stats::setIsAmazon(bool isAmazon) {
	this->isAmazon = isAmazon;
}

void page_stats::setIsAmazonProductPage(bool isProductPage) {
	this->isAmazonProductPage = isProductPage;
}

void page_stats::setIsAmazonReviewPage(bool isReviewPage) {
	this->isAmazonReviewPage = isReviewPage;
}

void page_stats::setURL(string URL) {
	this->URL = URL;
}

void page_stats::setTotalWordCount(int wordCount) {
	this->totalWordCount = wordCount;
}

void page_stats::setTotalMisspelledWordCount(int misspellCount) {
	this->totalMisspelledWordCount = misspellCount;
}

void page_stats::setTotalImageCount(int imageCount) {
	this->totalImageCount = imageCount;
}

void page_stats::setTotalKiloBytes(int kiloByteCount) {
	this->totalKiloBytes = kiloByteCount;
}

void page_stats::setTotalLinkCount(int linkCount) {
	this->totalLinkCount = linkCount;
}

void page_stats::setTotalInternalLinkCount(int internalLinkCount) {
	this->totalInternalLinkCount = internalLinkCount;
}

void page_stats::setTotalExternalLinkCount(int externalLinkCount) {
	this->totalExternalLinkCount = externalLinkCount;
}

/** Amazon specific methods **/
int page_stats::getProductRating() {
	return this->productRating;
}

int page_stats::getRelatedProductCount() {
	return this->relatedProductCount;
}

int page_stats::getTotalReviewCount() {
	return this->totalReviewCount;
}
//int getTotalCommentorCount;
void page_stats::reset(){
	isAmazon = false;
	isAmazonProductPage = false;
	isAmazonReviewPage = false;
	URL = "";
	totalWordCount = 0;
	totalMisspelledWordCount = 0;
	totalImageCount = 0;
	totalKiloBytes = 0;
	totalLinkCount = 0;
	totalInternalLinkCount = 0;
	totalExternalLinkCount = 0;

	/** Amazon specific data members **/
	productRating = 0;
	relatedProductCount = 0;
	totalReviewCount = 0;
	//totalCommentorCount = 0;
}
