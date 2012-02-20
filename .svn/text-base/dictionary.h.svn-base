/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#ifndef	DICTIONARY_H
#define	DICTIONARY_H

#include <vector>
#include <string>

#include "HashMap.h"
#include "BST.h"

using namespace std;

// Provides functionality to load a list of known correctly spelled words and use that list to:
//		Check if a word is contained in the dictionary (spelled correctly)
//		Suggest possible intended spellings for a misspelled word
class dictionary {
public:
	// Constructs a new dictionary using the specified file_name parameter as the path to the dictionary of known correct spelled words
	dictionary(string file_name);

	// Destructs the dictionary object
	~dictionary();

	// Returns true if the specified word parameter is also contained in the dictionary (spelled correctly)
	bool spelled_correctly(string word);

	// Attempts to find the best matches to the specified word using the words in the dictionary
	// It will add suggestions to the list vector parameter and attempt to add count words to the list
	// Note:  Even though the caller may ask for 5 (or whatever) words in count, the implementation might not supply that many
	//			The caller shouldn't assume that it will always get the count it asks for
	// Returns true if the specified word parameter is already spelled correctly
	bool best_matches(string word, vector<string> &list, int count = 5);

private:
	// Among the suite of methods employed to suggest possible words for the best_matches method
	// Attempts to provide suggestions by splitting the word parameter into two seperate words
	vector<string>* getMatchesBySplittingIntoTwo(string *word, int count);

	// Among the suite of methods employed to suggest possible words for the best_matches method
	// Attempts to provide suggestions by swapping two consective letters
	vector<string>* getMatchesFromTransposedCharPairs(string *word, int count);

	// Among the suite of methods employed to suggest possible words for the best_matches method
	// Attempts to provide suggestions by replacing vowels with other vowels (a common misspelling error is using an incorrect vowel)
	vector<string>* getMatchesBasedOnVowels(string *word, int count);

	// Among the suite of methods employed to suggest possible words for the best_matches method
	// Attempts to provide suggestions by using the BST to find 'neighboring' nodes to where the word parameter 'should' have appeared in the BST
	vector<string>* getMatchesFromBstNeighborWords(string *word, int count);

	// An implementation of the underlying dictionary data structure that employs a separate chaining hash table
	HashMap<string> dictionaryHashTable;

	// An implemenation of the underlying dictionary data structure that employs a BST (non-self balancing)
	BST<string> bst;
};

#endif	/* DICTIONARY_H */

