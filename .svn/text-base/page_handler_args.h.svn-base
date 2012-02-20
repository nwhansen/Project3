#pragma once

#include <string>
#include <vector>

using namespace std;

#include "page_stats.h"
#include "reviewer.h"
#include "commenter.h"

struct page_handler_args {
    
    // Used to report if a successfull attempt download the page.
    bool Success;
    // Used to report if the page was successfull in processing the page
    bool Complete;
    // Error Code - The code that represents the type of error encountered. 
    // 0 - No errors Present with Page Handler.
    // 404 - Page not found
    // 10 - Unable to initialize curl
    // 301 - Page Redirected. May indicate duplication of URLs
    // 8 - There was an error retriving the processed content from server.
    int ErrorCode;
    // Maintains the overall statistics on the current page.
    // When this page handler gets a new page to handle, pageStats should be cleared.
    page_stats pageStats;

    // Keeps a cummulative list of all unique links found on the current page
    // When this page handler gets a new page to handle, links should be cleared.
    vector<string> links;

    // Keeps a cummulative list of all unique reviewers found on the current review page (if it is an Amazon.com review page).
    // When this page handler gets a new page to handle, reviewers should be cleared.
    reviewer productReviewer; //need to create the reviewer class

    // Keeps a cummulative list of all unique commenters found on the current review page (if it is an Amazon.com review page).
    // When this page handler gets a new page to handle, commenters should be cleared.
    vector<commenter> commenters; //need to create the commenter class

    // The URL to processes
    string URL;

    void reset() {
        this->commenters.clear();
        this->links.clear();
        this->pageStats.reset();
        this->productReviewer.reset();
        this->URL = "";
    }
};
