/*
* Created for CS 3505 Spring 2012
* Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
* 
* Class for maintaining user-specified command line arguments
* It is expected that a single object of this type will be created,
*   populated from command line arguments, and passed to what ever method might need it
*/

#include <string>

using namespace std;

// The default maximum number of threads this crawler is allowed to spawn
#define DEFAULT_MAX_THREADS 1

// The default maximum number of URLs this crawler is allowed to crawl (-1 means unlimited)
#define DEFAULT_URLS_TO_CRAWL_COUNT -1

#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H

// Encapsulates all user-defineable settings for one execution of the program

class program_options {
public:

	// Default constructor
	program_options(int argc, char **argv);

	// Default destructor
	~program_options();

	// Get functions for variables
	bool getDisplayPageStats();
	bool getDisplayReviewerStats();
	bool getDisplayCommenterStats();

	bool getCrawlExternalDomains();

	bool getAllowUserToStopCrawler();

	bool getHasInitialURLBeenSet();
	bool getHasDictionaryPathBeenSet();
	bool getHasOutputFilenameBeenSet();

	int getMaxURLsToCrawlPerCrawler();
	int getMaxThreadsToSpawnPerCrawler();

	const string getInitialURL();
	string getInitialURLBase();

	string getDictionaryFilename();

	string getOutputFilename();

	// Set functions for variables
	void setDisplayPageStats(bool newValue);
	void setDisplayReviewerStats(bool newValue);
	void setDisplayCommenterStats(bool newValue);

	void setCrawlExternalDomains(bool newValue);

	void setAllowUserToStopCrawler(bool newValue);

	// If newValue is -1, the crawler won't stop based on URLs crawled (ie crawls unlimited URLs)
	void setMaxURLsToCrawlPerCrawler(int newValue);

	// newValue is capped to DEFAULT_MAX_THREADS
	void setMaxThreadsToSpawnPerCrawler(unsigned int newValue);

	void setInitialURL(string URL);

	void setDictionaryFilename(string dictionaryFilePath);

	void setOutputFilename(string outputFilePath);

private:

	/**
	* Processes the command line arugments
	*/
	void process(int argc, char **argv);

	/**
	* General features on the page stats
	* Enabled by default. 
	* Turn off by --display-off
	*/
	bool displayPageStats;

	/**
	* Display advanced features on the reviewers.
	* --display-review
	*/
	bool displayReviewerStats;

	/**
	* Should the results printer display advanced features on the Commenter stats
	* --display-commenter
	*/
	bool displayCommenterStats; // P2

	/**
	* Do we allow external domains?
	* Set by --ex-domain
	*/
	bool crawlExternalDomains;

	/**
	* Always true for now.
	*/
	bool allowUserToStopCrawler;

	/**
	* ... 
	*/
	bool hasInitialURLBeenSet;

	/**
	* Redundant variable.
	*/
	bool hasDictionaryPathBeenSet;

	/**
	* Redundant variable.
	*/
	bool hasOutputFilenameBeenSet;

	/**
	* Max number
	* This well be set by --set-max-urls 
	*/
	int maxURLsToCrawlPerCrawler;

	/**
	* Max number of threads to fork.
	* set by -threads
	* or --threads
	*/
	int maxThreadsToSpawnPerCrawler;

	/**
	* Defines how many top X words from the crawler we should display.
	* set by the -count or --count param
	*/
	int topWords;

	/**
	* Defines the top X misspelled words from the crawler we should display.
	* set by -miss or --miss
	*/
	int missedWords;

	/**
	* The initial url
	*/
	string initialURL;

	/**
	* The base domain
	* -domain
	* --domain
	*/
	string initialURLBase;

	/**
	* Dictionary file name.
	* set by the --dictionary command
	*/
	string dictionaryFilename;

	/**
	* Output Destination For the Results Manager
	* --output-file
	*/
	string outputFilename;

};

#endif
