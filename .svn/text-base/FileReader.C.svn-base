/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#include "ctype.h"
#include "FileReader.h"


using namespace std;

FileReader::FileReader() {

}

bool FileReader::open(string filename) {
    this->input.open(filename.c_str());
    return this->input.is_open();
}

FileReader::~FileReader() {
    this->input.close();
}

vector<string> * FileReader::readLine() {
    return this->readLine(' ');
}

//void cleanString(vector<string> * cleanUp);
string cleanWord(string word);

vector<string> * FileReader::readLine(char delim) {
    string line;
    vector<string> * temp = 0;
    if (input.good()) {
        temp = new vector<string>;
        getline(input, line);
        stringstream stream(line);
        string word;
        while (getline(stream, word, delim)) {
            word = cleanWord(word);
            if (word.compare("") == 0)
                continue;
            temp->push_back(word);
        }

        //temp = split(line, delim);

        //  FIXED!!!
        //cleanString(temp);
    }
    return temp;
}


vector<string> * FileReader::readLine(stringstream * stm) {
    vector<string> *temp = new vector<string>;
    string word;
    while (getline(*stm, word, ' ')) {
        word = cleanWord(word);
        if (word.compare("") == 0)
            continue;
        temp->push_back(word);
    }
    return temp;
}

string cleanWord(string word) {
    stringstream temp;
    for (unsigned int i = 0; i < word.length(); i++) {
        unsigned int tempCharValue = word[i];
        if (tempCharValue < 256 && isalpha(tempCharValue)) {
            temp << (char) tempCharValue;
        }
    }
    return temp.str();
}

