/*
* Created for CS 3505 Spring 2012
* Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
* 
* Implementation of the progam_options class.
* For more information, see program_options.h header comment
*/

#ifdef VS
#define DEFAULT_DICTIONARY_PATH "../../Files/tinyDictionary"
#define DEFAULT_OUTPUT_FILE_PATH "Output/testOutput.html"
#else
#define DEFAULT_DICTIONARY_PATH "Files/tinyDictionary"
#define DEFAULT_OUTPUT_FILE_PATH "Output/testOutput.html"
#endif

#include <iostream>

using namespace std;

#include "program_options.h"
#include "html_helpers.h"

program_options::program_options(int argc, char **argv) {
	// Set default values in case the command line arguments don't specify a particular option
	this->displayPageStats = true;
	this->displayReviewerStats = true;
	this->displayCommenterStats = false; // Because this is phase 2, default it to false

	this->crawlExternalDomains = false;

	this->allowUserToStopCrawler = true;

	this->hasInitialURLBeenSet = false;
	this->hasDictionaryPathBeenSet = false;
	this->hasOutputFilenameBeenSet = false;
	this->maxThreadsToSpawnPerCrawler = 1;
	this->maxURLsToCrawlPerCrawler = -1;
	this->initialURL = "";
	this->initialURLBase = "";

	this->dictionaryFilename = "";

	this->outputFilename = "";

	this->maxURLsToCrawlPerCrawler = DEFAULT_URLS_TO_CRAWL_COUNT;
	this->maxThreadsToSpawnPerCrawler = DEFAULT_MAX_THREADS;
	//Defaults have been set process the actual parameters. And change as needed.
	//this->process(argc, argv);
	// searchflag set options using the argv here

	// Temp code that should be removed once the code is using argv properly
	//setInitialURL("http://www.amazon.com/review/R1LJSIRSGRQ03X/ref=cm_cr_pr_perm?ie=UTF8&ASIN=B0051VVOB2&nodeID=&tag=&linkCode=");
	setInitialURL("http://www.randomabs.com");
	setDictionaryFilename(DEFAULT_DICTIONARY_PATH);
	setOutputFilename(DEFAULT_OUTPUT_FILE_PATH);
}

void program_options::process(int argc, char **argv) {
	//Try to get the domain.
	//The first is worthless it is the exceutable
	if (argc == 1) {
		//DIE!
		cout << "Missing critical argument! Please refer to readme for exact syntax." << endl;
		cout << "basic syntax is: crawler \"url\" --domain \"domain\"" << endl;
		return;
	}
	int argPos = 1;
	this->initialURL = string(argv[argPos]);

	for (; argPos < argc; argPos++) {
		string cmd(argv[argPos]);
		//Handle no argument arguments

		// <editor-fold defaultstate="collapsed" desc="No args args">
		if (cmd.compare("--ex-domains") == 0) {
			this->crawlExternalDomains = true;
			continue;
		} else if (cmd.compare("--display-review") == 0) {
			this->displayReviewerStats = true;
			continue;
		} else if (cmd.compare("--display-commenter") == 0) {
			//Unsupported
			cout << "Unsupported at this time sorry." << endl;
			this->displayCommenterStats = false;
			continue;
		} else if (cmd.compare("--display-off") == 0) {
			this->displayPageStats = false;
			continue;
		}
		// </editor-fold>

		// <editor-fold defaultstate="collapsed" desc="Multi arg args">
		//All of the commands that take another param.
		if ((argPos + 1) < (argc)) {
			if (cmd.compare("--dictionary") == 0) {
				if (!this->hasDictionaryPathBeenSet) {
					this->setDictionaryFilename(argv[++argPos]);
				}
			} else if (cmd.compare("--output-file") == 0) {
				if (!this->hasOutputFilenameBeenSet) {
					this->setOutputFilename(argv[++argPos]);
				}
			} else if (cmd.compare("-threads") == 0 || cmd.compare("--threads") == 0) {
				if (this->maxThreadsToSpawnPerCrawler == 1) {
					string arg(argv[++argPos]);
					int size = atoi(arg.c_str());
					if (size <= 0) {
						size = 1;
					}
					this->maxThreadsToSpawnPerCrawler = size;
				}
			} else if (cmd.compare("-domain") == 0 || cmd.compare("--domain") == 0) {
				if(this->getInitialURLBase().compare("") == 0){
					this->initialURLBase = string(argv[++argPos]);
				}
			} else if (cmd.compare("-count") == 0 || cmd.compare("--count") == 0) {
				if (this->topWords == 100) {
					string arg(argv[++argPos]);
					int size = atoi(arg.c_str());
					if (size <= 0) {
						size = 100;
					}
					this->topWords = size;
				}
			} else if (cmd.compare("-miss") == 0 || cmd.compare("--miss") == 0) {
				if (this->missedWords == 100) {
					string arg(argv[++argPos]);
					int size = atoi(arg.c_str());
					if (size <= 0) {
						size = 100;
					}
					this->missedWords = size;
				}
			} else if (cmd.compare("--set-max-urls") == 0) {
				if (this->maxURLsToCrawlPerCrawler == -1) {
					string arg(argv[++argPos]);
					int size = atoi(arg.c_str());
					if (size <= 0) {
						size = -1;
					}
					this->maxURLsToCrawlPerCrawler = size;
				}
			}
			// </editor-fold>

		}
	}
	// Temp code that should be removed once the code is using argv properly
	//setInitialURL("http://www.amazon.com/review/R1LJSIRSGRQ03X/ref=cm_cr_pr_perm?ie=UTF8&ASIN=B0051VVOB2&nodeID=&tag=&linkCode=");
	//setInitialURL("http://www.amazon.com");
	setInitialURL("http://www.randomabs.com");
	setDictionaryFilename(DEFAULT_DICTIONARY_PATH);
	setOutputFilename(DEFAULT_OUTPUT_FILE_PATH);
}

// <editor-fold defaultstate="collapsed" desc="Getters and setters">

program_options::~program_options() {
	// No memory has been allocated so no real destruction is needed here
}

bool program_options::getDisplayPageStats() {
	return displayPageStats;
}

bool program_options::getDisplayReviewerStats() {
	return displayReviewerStats;
}

bool program_options::getDisplayCommenterStats() {
	return displayCommenterStats;
}

bool program_options::getCrawlExternalDomains() {
	return crawlExternalDomains;
}

bool program_options::getAllowUserToStopCrawler() {
	return allowUserToStopCrawler;
}

bool program_options::getHasInitialURLBeenSet() {
	return hasInitialURLBeenSet;
}

bool program_options::getHasDictionaryPathBeenSet() {
	return hasDictionaryPathBeenSet;
}

bool program_options::getHasOutputFilenameBeenSet() {
	return hasOutputFilenameBeenSet;
}

int program_options::getMaxURLsToCrawlPerCrawler() {
	return maxURLsToCrawlPerCrawler;
}

int program_options::getMaxThreadsToSpawnPerCrawler() {
	return maxThreadsToSpawnPerCrawler;
}

const string program_options::getInitialURL() {
	return initialURL;
}

string program_options::getInitialURLBase() {
	return initialURLBase;
}

string program_options::getDictionaryFilename() {
	return dictionaryFilename;
}

string program_options::getOutputFilename() {
	return outputFilename;
}

void program_options::setDisplayPageStats(bool newValue) {
	displayPageStats = newValue;
}

void program_options::setDisplayReviewerStats(bool newValue) {
	displayReviewerStats = newValue;
}

void program_options::setDisplayCommenterStats(bool newValue) {
	// Because this is phase 2, don't expect this flag to do anything yet
	displayCommenterStats = newValue;
}

void program_options::setCrawlExternalDomains(bool newValue) {
	crawlExternalDomains = newValue;
}

void program_options::setAllowUserToStopCrawler(bool newValue) {
	allowUserToStopCrawler = newValue;
}

void program_options::setMaxURLsToCrawlPerCrawler(int newValue) {
	// If newValue is -1, the crawler won't stop based on URLs crawled (ie crawls unlimited URLs)
	maxURLsToCrawlPerCrawler = newValue;
}

void program_options::setMaxThreadsToSpawnPerCrawler(unsigned int newValue) {
	// newValue is capped to DEFAULT_MAX_THREADS
	if (newValue > DEFAULT_MAX_THREADS) {
		newValue = DEFAULT_MAX_THREADS;
	}

	maxThreadsToSpawnPerCrawler = newValue;
}

void program_options::setInitialURL(string URL) {
	initialURL = URL;

	initialURLBase = html_helpers::getBaseURL(initialURL);

	hasInitialURLBeenSet = true;
}

void program_options::setDictionaryFilename(string dictionaryFilePath) {
	dictionaryFilename = dictionaryFilePath;

	hasDictionaryPathBeenSet = true;
}

void program_options::setOutputFilename(string outputFilePath) {
	outputFilename = outputFilePath;

	hasOutputFilenameBeenSet = true;
}// </editor-fold>
