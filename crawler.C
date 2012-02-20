#include "crawler.h"

// Constructor.
// Sets the maximum threads that the crawler will spawn to the specified maxThreads
// Sets the maximum number of URLs to crawl to the specified urlsToCrawl (-1 means unlimited)

crawler::crawler(program_options * const theOptions, dictionary * const theDictionary, results_manager * const theResultsManager)
: myOptions(theOptions), myDictionary(theDictionary), myResultsManager(theResultsManager) {
	this->crawledURLCount = 0;
	this->runningThreadCount = 0;
	this->shouldStopCrawling = false;
	this->timeLinkLastServed = 0;
}

// Default destructor

crawler::~crawler() {
	//searchflag possible list of threads to clean up???
}

// Starts the crawler at the initial URL

void crawler::startCrawler() {
	vector<string> initialURL;

	initialURL.push_back(myOptions->getInitialURL());

	addLinks(&initialURL, NULL);
}

// Adds the URLs contained in the linksToAdd parameter to the list of links to crawl if the URL is new (not already visited or queued)

void crawler::addLinks(vector<string> *linksToAdd, page_handler_args *args) {
	int linksToAddCount = linksToAdd->size();
	string nextLink;
	vector<string> validUrls;
	int internalDomainCount = 0;
	
	//Remove invalid links
	for (int i = 0; i < linksToAddCount; i++) {
		string currLink = linksToAdd->at(i);
		bool isInternal = html_helpers::isWithinDomain(currLink, this->myOptions->getInitialURLBase());
		if (isInternal)
		{
			internalDomainCount++;
		}
		if (html_helpers::isValidURL(currLink) &&
				(this->myOptions->getCrawlExternalDomains() || isInternal)) {
			validUrls.push_back(currLink);
		}
	}
	linksToAddCount = validUrls.size();
	//Lock data structure here
	int linksAddedCount = 0;
	for (int i = 0; i < linksToAddCount; i++) {
		nextLink = validUrls[i];

		if (!crawledURLs.contains(nextLink)) {
			crawledURLs.put(nextLink, 0);
			queuedURLs.Enqueue(crawledURLs.GetKeyPtr(nextLink));
			linksAddedCount++;
		}
	}

	if (args != 0)
	{
		args->pageStats.setTotalExternalLinkCount(linksToAdd->size() - internalDomainCount);
		args->pageStats.setTotalInternalLinkCount(internalDomainCount);
	}

	//Here we test info
	cout << "Added " << linksAddedCount << " out of " << linksToAddCount << " link(s) to the queue." << endl;
	if(linksToAddCount > linksAddedCount)
	{
		cout << "(the rest were duplicates or previously visited)" << endl;
	}

	int discardedLinkCount = linksToAdd->size() - linksToAddCount;
	if(discardedLinkCount > 0)
	{
		cout << "There was " << discardedLinkCount << " link(s) discarded (invalid or not in the same domain if enforced)" << endl;
	}

	int maxThreadsSpawnable = myOptions->getMaxThreadsToSpawnPerCrawler();
	int queuedURLCount = queuedURLs.Size();

	cout << "There are now " << queuedURLCount << " link(s) left to process." << endl;

	cout << endl;

	// remove lock

	//Read lock

	// If we still have more URLs to process and haven't reached our thread cap, spawn a new thread
	while ((runningThreadCount == 0 && queuedURLCount > 0) ||
			(runningThreadCount < maxThreadsSpawnable && queuedURLCount > 1)) {
		// We are going be creating a new thread that will use up URL.  Decrement the count now
		queuedURLCount--;

		// Spawn new thread here
		page_handler_args *newArgs = new page_handler_args();
		
		string * url = this->getNextLink();
		if(url == NULL){
			//This should never happen.  Add some kind of error message here.
		}
		//Convert this to the other method >.> for only 1 page request per second.
		newArgs->URL = *(url);
		
		//newArgs->URL = *queuedURLs.Dequeue();
		cout << "Forking a thread" << endl;
		page_handler *newPageHandler = new page_handler(this, myDictionary, &crawler::pageHandlerCallback);
		//increment the thread count to prevent infinite thread creation
		runningThreadCount++;
		//TODO: add the actual threading later
		newPageHandler->start(newArgs);
	}
}

// Returns the number of URLs that have been crawled since this crawler was started

int crawler::getLinksCrawledCount() {
	return crawledURLCount;
}


// Returns the next URL that should be crawled

string* crawler::getNextLink() {
	if (shouldStopCrawling) {
		return NULL;
	}

	string *nextLink = queuedURLs.Dequeue();

	if (nextLink == NULL) {
		return NULL;
	}

	if (time(NULL) == timeLinkLastServed)
	{
#ifdef VS
		Sleep(1000);
#else
		usleep(1000000);
#endif
	}

	timeLinkLastServed = time(NULL);

	crawledURLCount++;
	return nextLink;
}

// Notifies the crawler to finish crawling current URLs and not start any new ones

void crawler::stopCrawling() {
	shouldStopCrawling = true;
}

// Gets a bool indicating if the crawler has been asked to stop crawling

bool crawler::getShouldStopCrawling() {
	return shouldStopCrawling;
}

// Gets whether or not the crawler has completed the assigned task
// This will only return true if one or more of the following conditions are true:
//		It was asked to stop (by calling stopCrawling) AND all pages currently being processed has finished
//		It has crawled the maximum number of pages as specified by the maxURLsToCrawlCount member variable
//		It has run out of pages to crawl

bool crawler::isDoneCrawling() {
	// searchflag not yet written
	// before we can return true, we must make sure that all threads have finished processing their current page
	return shouldStopCrawling;
}


// The callback for the page handler object to invoke when it has completed processing a URL

page_handler_args * crawler::pageHandlerCallback(void * obj, page_handler *pageHandler) {
	//TODO: Thread safe here some how.
	crawler * me = (crawler*) obj;
	//Get the args that will contain all of the information found and the links to visit.
	page_handler_args * results = pageHandler->getArgs();

	me->addLinks(&results->links, results);

	//TODO: Need to invoke the add pagestats to the results manager.
	me->myResultsManager->submitPageStats(results);

	//cout << "Examined " << results->URL << endl;
	//Now to see if we can take out a new url.
	string * nextUrl = me->getNextLink();
	if (nextUrl == NULL) {
		//Time to clean up our object mess.
		//Thread will die soon
		me->runningThreadCount--; //TODO: thread safe this sooner or later
		if (me->runningThreadCount == 0) {
			me->shouldStopCrawling = true;
		}
		delete results;
		return NULL;
	}
	results->reset();
	results->URL = *nextUrl;
	return results;
}
