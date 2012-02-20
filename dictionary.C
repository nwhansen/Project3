/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#include <algorithm>

using namespace std;

#include "dictionary.h"
#include "FileReader.h"

dictionary::dictionary(string file_name) {
	FileReader reader;
	int total_words = 0;

	if (!reader.open(file_name)) {
		//throw some sort of error.
	}
	vector<string> * words;
	words = reader.readLine();
	while (words != 0) {
		for (unsigned int i = 0; i < words->size(); i++){
			string currentWord = words->at(i);
			// tolower code taken from http://stackoverflow.com/questions/313970/stl-string-to-lower-case
			transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
			dictionaryHashTable.put(currentWord, currentWord);
			total_words++;
		}
		delete words;
		words = reader.readLine();
	}

	//reader.close();// Needed?

	// searchflag should the BST be completely removed as it isn't needed for spell checking?
	int hashTableKeysCount = dictionaryHashTable.getSize();

	string **keys = new string*[hashTableKeysCount];

	dictionaryHashTable.getKeys(keys, hashTableKeysCount);

	for (int i = 0; i < hashTableKeysCount; i++)
	{
		bst.add(keys[i]);
	}

	delete [] keys;
}

dictionary::~dictionary()
{
	// Not needed because apparently C++ automatically calls the destructor for all objects in 'this' class before executing this desctructor code
	//dictionaryHashTable.~HashMap();
}

bool dictionary::spelled_correctly(string word) {
	return dictionaryHashTable.contains(word);
}


bool dictionary::best_matches(string word, vector<string> &list, int count) {
	
	// return true if word is spelled correctly as per Jim's API specification
	if(dictionaryHashTable.contains(word)) {
		return true;
	}

	vector<string> *oneWordIntoTwo = getMatchesBySplittingIntoTwo(&word, count);
	//vector<string> *vowelVariations; // NOT IMPLEMENTED
	vector<string> *twoTransposedChars = getMatchesFromTransposedCharPairs(&word, count);
	vector<string> *bstNeighbors = getMatchesFromBstNeighborWords(&word, count);
	//vector<string> *missingLetter; // NOT IMPLEMENTED

	int resultsCount = 0;

	// insert results from splitting into two valid words
	for(unsigned int i = 0; i < oneWordIntoTwo->size() && resultsCount < count; i++) {
		list.push_back(oneWordIntoTwo->at(i));
		resultsCount++;
	}

	// insert results from valid words formed by trasposing character pairs
	for(unsigned int i = 0; i < twoTransposedChars->size() && resultsCount < count; i++) {
		list.push_back(twoTransposedChars->at(i));
		resultsCount++;
	}

	// insert results from the BST's neighboring words in its data structure
	for(unsigned int i = 0; i < bstNeighbors->size() && resultsCount < count; i++) {
		list.push_back(bstNeighbors->at(i));
		resultsCount++;
	}

	delete oneWordIntoTwo;
	//delete vowelVariations;
	delete twoTransposedChars;
	delete bstNeighbors;
	//delete missingLetter;

	return false;
}

// Gets up to count results by splitting the provided word into two valid words.
// return vector* containing valid words from this analysis
vector<string>* dictionary::getMatchesBySplittingIntoTwo(string *word, int count) {
	vector<string> *resultsVector = new vector<string>();
	int resultsCount = 0;
	string firstWord;
	string secondWord;

	for(unsigned int i = 1; i < word->length() && resultsCount < count; i++) {
		firstWord = word->substr(0, i);
		secondWord = word->substr(i, word->length() - i);
		

		if(dictionaryHashTable.contains(firstWord) && dictionaryHashTable.contains(secondWord)) {
			resultsVector->push_back(firstWord + " " + secondWord); // should we also include "firstWord-secondWord"?
		}
	}

	return resultsVector;
}

// searchflag: needs thourough testing
// Gets up to count results from transposing each pair of inline chars 
// in the given word. Does not transpose the first or last char.
// return vector* containing valid words from this analysis
vector<string>* dictionary::getMatchesFromTransposedCharPairs(string *word, int count) {
	vector<string> *resultsVector = new vector<string>();
	int resultsCount = 0;
	string wordCopy;

	for(int i = (word->length() - 2); i > 1 && resultsCount < count; i--) {
		wordCopy = *word; // make copy of original word
		
		// swap pair of characters
		char temp = wordCopy[i];
		wordCopy[i] = wordCopy[i-1];
		wordCopy[i-1] = temp;

		if(dictionaryHashTable.contains(wordCopy)) {
			resultsVector->push_back(wordCopy);
		}
	}

	return resultsVector;
}

// Gets up to count results from replacing each vowel of the given word
// with all other vowels.
// return vector* containing valid words from this analysis
vector<string>* dictionary::getMatchesBasedOnVowels(string *word, int count) {
	string **results = new string*[count];
	vector<string> *resultsVector = new vector<string>();

	//searchflag: NOT IMPLEMENTED!!
	//code will go here

	for(int i = 0; i < count; i++) {
		resultsVector->push_back(*results[i]);
	}

	return resultsVector;
}

// Gets up to count results from querying the BST for neighbors of word in its data structure.
// These results are expected to result in words similar to the provided word, but not guaranteed
// to be closely related.
// return vector* with valid words from this query
vector<string>* dictionary::getMatchesFromBstNeighborWords(string *word, int count) {
	string **results = new string*[count]; // create empty container for possible results
	vector<string> *resultsVector = new vector<string>();

	int resultsCount = bst.getNeighboringData(word, count, results);

	for(int i = 0; i < resultsCount && i < count; i++) {
		resultsVector->push_back(*results[i]);
	}

	return resultsVector;
}
