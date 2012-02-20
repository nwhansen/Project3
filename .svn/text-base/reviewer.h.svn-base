/*
 * Created for CS 3505 Spring 2012
 * Written by: Nate Anderson, Cody Foltz, Nathan Hansen, Eric Olson
 * 
 * Class for maintaining the information on an indivudual reviewer
 */

#ifndef REVIEWER_H
#define REVIEWER_H

#include <string>
using namespace std;


/* reviewer object will keep track of the number of posts,
*  total words, total misspelled words, total helpful ratings, and total unhelpful ratings for this userID.
*  Object is used specifically for customer reviews inconjuction with the product pages on the amazon domain.
*/
class reviewer
{
public:

	/* Creates a new reviewer object that will keep track of the number of posts,
	*  total words, total misspelled words, total helpful ratings, and total unhelpful ratings for this userID.
	*/
	reviewer(string id, int posts, int misspelled_word_count, int total_word_count, int total_helpful_count, int total_nonhelpful_count );

	reviewer();
	reviewer(const reviewer &otherReviewer);
	~reviewer();

	/* Takes the totals passed and adds them to the total counts already present in this object.
	*  
	*/ 
	void update(int posts, int misspelled_word_count, int total_word_count, int total_helpful_count, int total_nonhelpful_count );
	
	/* Takes the totals passed and adds them to the total counts already present in this object.
	*  Makes the assumtion that you are incrementing the number of posts by one.
	*/ 
	void update(int misspelled_word_count, int total_word_count, int total_helpful_count, int total_nonhelpful_count );
	
	/* Takes the totals passed and adds them to the total counts already present in this object.
	*  Makes the assumtion that you are incrementing the number of posts by one.
	*/ 
	void update(reviewer * second_review );

	/* Returns the userID for this reviewer.
	*/
	string getID();

	/* Returns the number of posts for this reviewer.
	*/
	int getPostCount();
	
	/* Returns the number of misspelled words for this reviewer.
	*/
	int getMisspelledCount();
	
	/* Returns the number of total words used by this reviewer.
	*/
	int getTotalWordCount();
		
	/* Returns the number of times this reviewer received positive feedback for their review.
	*/
	int getTotalHelpfulCount();
		
	/* Returns the number of times this reviewer received negative feedback for their review.
	*/
	int getTotalNonHelpfulCount();

	/* Resets all member variables to their default value
	*/
	void reset();

private:

	string id;
	int posts;
	int misspelled_word_count;
	int total_word_count;
	int total_helpful_count;
	int total_nonhelpful_count;

};

#endif
