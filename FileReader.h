/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#ifndef	FILEREADER_H
#define	FILEREADER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// A class that provides methods for reading lines of words from an input file

class FileReader {
public:
    // Default constructor
    FileReader();
    // Opens the specified filename path for reading
    // Returns true if the file opened successfully and is ready for reading operations
    bool open(string text);
    // Default destructor
    virtual ~FileReader();
    // Reads the next line from the input file and breaks it up into individual words using the space character as the delimiter
    vector<string> * readLine();
    //This will always return a vector to the heap. Therefore you must always delete the vector when done
    //This is static method as it has no notion of what this object is. Keep calling this until it returns nothing.
    static vector<string> * readLine(stringstream *stm);
    // Reads the next line from the input file and breaks it up into individual words using the specified delim parameter character as the delimiter
    vector<string> * readLine(char delim);

private:
    // An input file stream to the underlying data source
    ifstream input;
};

#endif	/* FILEREADER_H */
