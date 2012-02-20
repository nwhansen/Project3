/*
 * Created for CS 3505 Spring 2012
 * Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
 * 
 * Implementation of the results_printer class.
 * For more information, see results_printer.h header comment
 */

#include "results_printer.h"

// Constructs an object with the specified options and results data structures

results_printer::results_printer(program_options * const options, results_manager * const resultsManager)
: myOptions(options), myResultsManager(resultsManager) {
}

// Default destructor

results_printer::~results_printer() {
}

// Writes and HTML file to the output file specified in the results member variable using the options specified in the options memeber variable

void results_printer::writeHtmlFile() {
    //Ok do we even write anything?
    if(!this->myOptions->getDisplayPageStats()){
        //Do nothing.
        return;
    }
}
