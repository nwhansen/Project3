/* 
 * File:   queue.h
 * Author: Ichigo
 *
 * Created on February 4, 2012, 3:23 PM
 */

#ifndef QUEUE_H
#define	QUEUE_H

template <class T>
class queue {
private:

    struct node {
        T *value;
        node * next;
    };
    int size;
    node * head;
    node * tail;

public:
    void Enqueue(T *item);
    T* Dequeue();
    int Size();
    ~queue();
    queue();
};

template <class T>
void queue<T>::Enqueue(T *item) {
    node * newNode = new node;
    newNode->next = 0;
    newNode->value = item;
    if (size <= 0) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
    return;
}

template<class T>
queue<T>::queue() {
    size = 0;
    head = 0;
    tail = 0;
}

template<class T>
queue<T>::~queue() {
    node * tempHead;
    while (head != 0) {
        tempHead = head;
        head = head->next;
        delete tempHead;
    }
}

template <class T>
T* queue<T>::Dequeue() {
    if (size <= 0) {
        return 0;
    }
    node * targetNode = head;
    head = head->next;
    if (head == 0) {
        tail = 0;
    }
    T *item = targetNode->value;
    delete targetNode;
    size--;

    return item;
}

template<class T>
int queue<T>::Size() {
    return size;
}


#endif	/* QUEUE_H */

