#include <string>

using namespace std;

#include "../curl/curl.h"

#include "curl_tests.h"
#include "../html_helpers.h"


// Test method for curl.  Delete it when tests are complete.  Taken from http://www.learning2.eng.utah.edu/mod/page/view.php?id=308
size_t curl_easy_test1_callback(void *ptr, size_t numberOfElements, size_t bytesPerElement, void *userdata)
{
	// use buffer as reference so we can use nice . syntax below
	string *buffer = (string*)userdata;

	// debug info
	//printf("In curl write callback function. numberOfElements: %d  bytesPerElement: %d  userdata %p\n", (unsigned int)numberOfElements, (unsigned int)bytesPerElement, userdata);

	// save current state
	buffer->append((char*)ptr, numberOfElements * bytesPerElement);

	// Return the total number of bytes processed
	return numberOfElements * bytesPerElement;
}

bool curl_easy_test1()
{
	CURL *curl;
	//CURLcode res;

	string buffer;
	curl = curl_easy_init();

	if (curl)
	{
		const char *rootURL = "http://www.amazon.com";

		// Set it to download the rootURL
		curl_easy_setopt(curl, CURLOPT_URL, rootURL);

		// Set the callback function to send data to as write_function
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_easy_test1_callback);

		// Set the buffer to put temp data into as buffer
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "cs3505_NullPointerExceptionBot");

		// Execute the request
		/*res = */curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		printf("Read %ul bytes from %s\n", buffer.size(), rootURL);

		// If we reach here, everything has gone good and we should return true
		return true;
	}
	else
	{
		printf("Failed to initialize curl\n");
	}

	// If we reach here, something went wrong.  Return false
	return false;
}

// Test method for curl.  Delete it when tests are complete.  Taken from http://www.learning2.eng.utah.edu/mod/page/view.php?id=308
size_t curl_relative_path_test1_callback(void *ptr, size_t numberOfElements, size_t bytesPerElement, void *userdata)
{
	// use buffer as reference so we can use nice . syntax below
	string *buffer = (string*)userdata;

	// debug info
	//printf("In curl write callback function. numberOfElements: %d  bytesPerElement: %d  userdata %p\n", (unsigned int)numberOfElements, (unsigned int)bytesPerElement, userdata);

	// save current state
	buffer->append((char*)ptr, numberOfElements * bytesPerElement);

	// Return the total number of bytes processed
	return numberOfElements * bytesPerElement;
}

bool curl_relative_path_test1()
{
	CURL *curl;
	CURLcode res;

	string buffer;

	curl = curl_easy_init();

	if (curl)
	{
		const char *rootURL = "http://thedarkbeginnings.com/about/comics/../../";

		// Set it to download the rootURL
		curl_easy_setopt(curl, CURLOPT_URL, rootURL);

		// Set the callback function to send data to as write_function
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_easy_test1_callback);

		// Set the buffer to put temp data into as buffer
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "cs3505_NullPointerExceptionBot");

		// Execute the request
		/*res = */curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		printf("Read %ul bytes from %s\n", buffer.size(), rootURL);

		// If we reach here, everything has gone good and we should return true
		return true;
	}
	else
	{
		printf("Failed to initialize curl\n");
	}

	// If we reach here, something went wrong.  Return false
	return false;
}

// Test method for curl.  Delete it when tests are complete.  Taken from http://www.learning2.eng.utah.edu/mod/page/view.php?id=308
size_t curl_amazon_product_page_test1_callback(void *ptr, size_t numberOfElements, size_t bytesPerElement, void *userdata)
{
	// use buffer as reference so we can use nice . syntax below
	string *buffer = (string*)userdata;

	// debug info
	//printf("In curl write callback function. numberOfElements: %d  bytesPerElement: %d  userdata %p\n", (unsigned int)numberOfElements, (unsigned int)bytesPerElement, userdata);

	// save current state
	buffer->append((char*)ptr, numberOfElements * bytesPerElement);

	// Return the total number of bytes processed
	return numberOfElements * bytesPerElement;
}

bool curl_amazon_product_page_test1()
{
	CURL *curl;
	CURLcode res;

	string buffer;

	curl = curl_easy_init();

	if (curl)
	{
		//const char *rootURL = "http://atr.eng.utah.edu/~nathan/ps3?URL=http://www.amazon.com/review/R1LJSIRSGRQ03X/ref=cm_cr_pr_perm?ie=UTF8&ASIN=B0051VVOB2&nodeID=&tag=&linkCode=";
		string rootURL = html_helpers::getDomParserServerURL("http://www.amazon.com/review/R1LJSIRSGRQ03X/ref=cm_cr_pr_perm?ie=UTF8&ASIN=B0051VVOB2&nodeID=&tag=&linkCode=");
		// Set it to download the rootURL
		curl_easy_setopt(curl, CURLOPT_URL, rootURL.c_str());

		// Set the callback function to send data to as write_function
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_amazon_product_page_test1_callback);

		// Set the buffer to put temp data into as buffer
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "cs3505_NullPointerExceptionBot");

		// Execute the request
		/*res = */curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		printf("Read %ul bytes from %s\n", buffer.size(), rootURL);

		// If we reach here, everything has gone good and we should return true
		return true;
	}
	else
	{
		printf("Failed to initialize curl\n");
	}

	// If we reach here, something went wrong.  Return false
	return false;
}
