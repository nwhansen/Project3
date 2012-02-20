/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#ifndef	HASHMAP_H
#define	HASHMAP_H

#include <vector>

#include "locale"
#include "LinkedHashEntry.h"

// Default capacity to allocate the hashmap to unless otherwise specified
const int DEFAULT_MAP_SIZE = 200000;

// A templatized implemenation of a separate chaining hash map
// Note:  This implemenation makes a copy of the V object on insertion so any object can be deleted after insertion without affecting the hash map
template<class V>
class HashMap {
private:
	// The underlying data structure to contain the elements
	// This is separate chaining hash table so any conflicts are resolved by adding the conflicting elements to the same linked list
    LinkedHashEntry<V> **table;

	// The total capacity of the hash map (the number of elements in the table variable)
    int capacity;

	// The number elements in the hash map
    int size;

	// Doubles the size of the table array, re-hashes all elements in the old array, and adds them to the new array
	// This reduces the average lenght of the individual linked lists in the table
    void resize(){
		// Compute the size of the new array (double the size of the old/current array)
        int temp_capacity = capacity*2;

		// Create a new table to hold the data
        LinkedHashEntry<V> ** temp;
        temp = new LinkedHashEntry<V>*[temp_capacity];

		// Zero out the pointers in the new table
        for(int i =0; i < temp_capacity; i++){
            temp[i] = 0;
        }
        
		// Go through all of the linked lists in the old/current array
        for (int i = 0; i < capacity; i++)
			// If a linked list has been created at this table index...
            if (table[i] != 0) {
				// We need to take all elements in the current linked list, re-hash them and add them to the new array
                LinkedHashEntry<V> *prevEntry = 0;
                LinkedHashEntry<V> *current = table[i];
                LinkedHashEntry<V> *temp_current;
				// Step through all of the elements one by one in the current linked list
                while (current != 0) {
                    prevEntry = current;
                    current = current->getNext();
                    prevEntry->setNext(0);
					// Re hash the current element
                    unsigned int pos = (hash(prevEntry->getKey()) % temp_capacity);
					// Insert the re-hashed current element into the new array
                    if(temp[pos] == 0){
                        temp[pos] = prevEntry;
                    } else{
                        temp_current = temp[pos];
                        while(temp_current->getNext() != 0){
                            temp_current = temp_current->getNext();
                        }
                        temp_current->setNext(prevEntry);
                    }
                }
            }
        
		// We have created a new array, copied all of the elements from the old array into the new
		// The old array is now longer needed.  Free it now
        delete[] table;
        
		// Set our internal data structure to the newly created larger array
        table = temp;
    }
    
    
    
public:

	// Computes the hash for a string
	// As all keys in the hash map are strings, we can compute the hash for the key and use that for the object as a whole
    unsigned int hash(string key) {
		// use the std library to compute the hash from key
        locale loc; // the "C" locale

        const collate<char>& coll = use_facet<collate<char> >(loc);
        return coll.hash(key.data(), key.data() + key.length());

    }

	// Constructs a new hash map using the DEFAULT_MAP_SIZE define as the initial capacity
    HashMap() {
		// Set capacity to the size we are going to allocate for our array
        capacity = DEFAULT_MAP_SIZE;

		// Since we have no elements in the brand new table, set size to 0
        size = 0;

		// Allocate the array that will hold the linked lists
        table = new LinkedHashEntry<V>*[capacity];

		// Initialize all pointers in the new array to null
        for (int i = 0; i < capacity; i++)
            table[i] = 0;
    }
    
	// Constructs a new hash map using the specified initial_size parameter as the initial capacity
    HashMap(int initial_size) {
		// Consider making a private init function that will do all this so both constructors can share the same code

		// Set capacity to the size we are going to allocate for our array
        capacity = initial_size;

		// Since we have no elements in the brand new table, set size to 0
        size = 0;

		// Allocate the array that will hold the linked lists
        table = new LinkedHashEntry<V>*[capacity];

		// Initialize all pointers in the new array to null
        for (int i = 0; i < capacity; i++)
            table[i] = 0;
    }

	// Gets a copy of the value for the specified key
    V GetValue(string key) {
		// Create an empty V object to return in case the specified key parameter isn't in the hash map
        V empty;

		// Compute the hash for the object we wish to return
        unsigned int pos = (hash(key) % capacity);

		// If there is no linked list located at that hash, clearly the item doesn't exist in the hash map
        if (table[pos] == 0)
			// so just return our empty object
            return empty;
		// Otherwise, we need to look for the object in the linked list we found
        else {
			// Start at the beginning of the linked list and check each element to see if its the one we are looking for
            LinkedHashEntry<V> *entry = table[pos];

			// While the current element isn't what we want and we have a next element, set it to our current element
            while (entry != 0 && entry->getKey() != key)
                entry = entry->getNext();
			// If entry is null, that means that we went to the end of our linked list and didn't find what we were looking for
            if (entry == 0)
				// so just return our empty object
                return empty;
            else
				// If entry isn't null, entry must be pointing to the object we were seeking.  Return that object now
                return entry->getValue();
        }
    }

    void put(string key, V value) {
        unsigned int pos = (hash(key) % capacity);
        if (table[pos] == 0)
            table[pos] = new LinkedHashEntry<V > (key, value);
        else {
            LinkedHashEntry<V> *entry = table[pos];
            while (entry->getNext() != 0)
                entry = entry->getNext();
            if (entry->getKey() == key)
                entry->setValue(value);
            else
                entry->setNext(new LinkedHashEntry<V > (key, value));
        }
        size++;
        if(size /(double)capacity >= 2){
            this->resize();
        }
    }

    void remove(string key) {
        unsigned int pos = (hash(key) % capacity);
        if (table[pos] != 0) {
            LinkedHashEntry<V> *prevEntry = 0;
            LinkedHashEntry<V> *entry = table[pos];
            while (entry->getNext() != 0 && entry->getKey() != key) {
                prevEntry = entry;
                entry = entry->getNext();
            }
            if (entry->getKey() == key) {
                if (prevEntry == 0) {
                    LinkedHashEntry<V> *nextEntry = entry->getNext();
                    delete entry;
                    table[pos] = nextEntry;
                } else {
                    LinkedHashEntry<V> *next = entry->getNext();
                    delete entry;
                    prevEntry->setNext(next);
                }
            }
        }
    }

    ~HashMap() {
		//int numberOfNodes = 0;
		//int longestChainLength = 0;
		//int currentChainLength = 0;
        for (int i = 0; i < capacity; i++)
            if (table[i] != 0) {
				//numberOfNodes++;
				//currentChainLength = 0;
                LinkedHashEntry<V> *prevEntry = 0;
                LinkedHashEntry<V> *current = table[i];
                while (current != 0) {
					//currentChainLength++;
                    prevEntry = current;
                    current = current->getNext();
                    delete prevEntry;
                }
				//if (currentChainLength > longestChainLength)
				//{
				//	longestChainLength = currentChainLength;
				//}
            }
		if (table != NULL)
		{
			delete[] table;
		}
		table = NULL;
		capacity = 0;
    }

    vector<V> getValues() {

        vector<V> list;
        for (int i = 0; i < capacity; i++)
            if (table[i] != 0) {
                LinkedHashEntry<V> *current = table[i];
                while (current != 0) {
                    list.push_back(current->getValue());
                    current = current->getNext();
                }
            }
        return list;
    }
    
    vector<string> getKeys(){
        vector<string> list;
        for (int i = 0; i < capacity; i++)
            if (table[i] != 0) {
                LinkedHashEntry<V> *current = table[i];
                while (current != 0) {
                    list.push_back(current->getKey());
                    current = current->getNext();
                }
            }
        return list;
    }

	bool getKeys(string **output, int outputCapacity)
	{
		if (outputCapacity < size)
		{
			return false;
		}

		int addedKeys = 0;

		for (int i = 0; i < capacity; i++)
		{
			if (table[i] != 0)
			{
				LinkedHashEntry<V> *current = table[i];

				while (current != 0)
				{
					// This should never happen so long as our size member variable is correct
					if (addedKeys >= outputCapacity)
					{
						return false;
					}

					output[addedKeys++] = &(current->key);

					current = current->getNext();
				}
			}
		}

		return true;
	}
    
    bool contains(string key){
        unsigned int pos = (hash(key) % capacity);
        if (table[pos] != 0) {
	  //LinkedHashEntry<V> *prevEntry = 0;
            LinkedHashEntry<V> *entry = table[pos];
            while (entry->getNext() != 0 && entry->getKey() != key) {
	      //prevEntry = entry;
                entry = entry->getNext();
            }
            if (entry->getKey() == key) {
                return true;
            }
        }
        return false;
    }
    
	string* GetKeyPtr(string key){
        string * empty = 0;
        unsigned int pos = (hash(key) % capacity);
        if (table[pos] == 0)
            return empty;
        else {
            LinkedHashEntry<V> *entry = table[pos];
            while (entry != 0 && entry->getKey() != key)
                entry = entry->getNext();
            if (entry == 0)
                return empty;
            else
                return &(entry->key);
        }
    }

    V* GetValuePtr(string key){
        V * empty = 0;
        unsigned int pos = (hash(key) % capacity);
        if (table[pos] == 0)
            return empty;
        else {
            LinkedHashEntry<V> *entry = table[pos];
            while (entry != 0 && entry->getKey() != key)
                entry = entry->getNext();
            if (entry == 0)
                return empty;
            else
                empty = &(entry->value);
                return empty;
        }
    }

	int getSize()
	{
		return size;
	}
};

#endif	/* HASHMAP_H */

