/*
 * Created for CS 3505 Spring 2012
 * Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
 * 
 * Static helper class for various html string manipulations, checks, anything else useful
 */

#ifndef HTML_HELPERS_H
#define HTML_HELPERS_H

#include <string>
#include <sstream>

using namespace std;

// Static helper class for various html string manipulations, checks, anything else useful
// Note:  Even though this class is conceptually static, C++ doesn't have static classes
class html_helpers
{
public:

	static bool isValidURL(string URL);

	// Gets the site root of the specified URL
	static string getBaseURL(string URL);

	// Returns true if the specified URL is a relative URL path
	static bool isRelativeURL(string URL);

	// Returns true if both URLs have the same base URL
	static bool hasSameBaseURL(string URL1, string URL2);

	// Returns true if the first URL is within the domain of the second
	static bool isWithinDomain(string subjectURL, string controlURL);

	// Removes all characters after the # in the URL (as long as the # isn't in the query string)
	static string stripHashTag(string URL);

	// Returns the full URL of the potentially partial URL in reference to the relative URL
	static string getFullURL(string relativeURL, string referenceURL);

	static int graphIdUniqueTag;

	// Returns the necessary script and HTML to generate a chart generated from Google Charts API.
	// Restricting this to two pieces of data was for simplicity in visualizing ratio data.
	// Note: In order for this to render, the following must be included in the head of the including page:
	//
	// <script type="text/javascript" src="https://www.google.com/jsapi"></script>
	//
	// param - chartType - the type of chart to generate ("Pie", "Bar" or "Column")
	// param - title - the title of the chart
	// param - label1 - the label for the first data to be charted
	// param - label2 - the label for the second data to be charted
	// param - data1 - the first data to be charted
	// param - data2 - the second data to be charted
	// param - [legendPos] - where the graph legend should go ("right", "top", "bottom", "none")
	static string getTwoElementChartHTML(string chartType, string title, string label1, string label2, int data1, int data2, string legendPos = "right");

	// Returns the URL to the server that is handling the DOM parsing of the href URL
	static string getDomParserServerURL(string href);
};

#endif
