/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#ifndef LINKEDHASHENTRY_H
#define	LINKEDHASHENTRY_H

#include <string>

using namespace std;

template <class V>
class LinkedHashEntry {
private:

public:

    string key;
    V value;
    LinkedHashEntry *next;

    LinkedHashEntry(string key, V value) {
        this->key = key;
        this->value = value;
        this->next = 0;
    }

    string getKey() {
        return key;
    }

    V getValue() {
        return value;
    }

    void setValue(V value) {
        this->value = value;
    }

    LinkedHashEntry *getNext() {
        return next;
    }

    void setNext(LinkedHashEntry *next) {
        this->next = next;
    }
};

#endif	/* LINKEDHASHENTRY_H */

