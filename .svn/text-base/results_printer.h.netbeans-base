/*
 * Created for CS 3505 Spring 2012
 * Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
 * 
 * Class for printing the results of the crawler
 * Most likely will only implement HTML printing to a file but could implement other methods for writing the data
 */

#ifndef RESULTS_PRINTER
#define RESULTS_PRINTER

#include "program_options.h"
#include "results_manager.h"

// Class for printing the results of the crawler
class results_printer
{
public:

	// Constructs an object with the specified options and results data structures
	results_printer(program_options * const options, results_manager * const results);

	// Default destructor
	~results_printer();

	// Writes and HTML file to the output file specified in the results member variable using the options specified in the options memeber variable
	void writeHtmlFile();

private:

	// An unchangeable pointer to the options to use to write the data
	program_options * const myOptions;

	// An unchangeable pointer to the results to write
	results_manager * const myResultsManager;

	// Helper methods for writting HTML files
	void writeHtmlHeader();
	void writeHtmlPageStats();
	void writeHtmlProductStats();
	void writeHtmlReviewersStats();
	void writeHtmlCommentersStats();
	void writeHtmlFooter();

};

#endif
