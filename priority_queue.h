/**
 * Written by Nate Anderson and Eric Olson
 * Written for CS 3505 Univerity of Utah Spring 2012 Semester
 * Declaration and implemenation of the templatized priority_queue class
 * Elements with lower weights are insterted at the beginning of the queue
 */

#ifdef USING_VS
#pragma once // eliminates unnecessary warning about headers
#endif

// Because this is a template class, the implementation must be in the same file as the header
// Not sure if the standard is to put header stuff info cpp file or to put cpp stuff into h file

#ifndef PRIORITY_QUEUE_H  // Ensure it doesn't get included (and thus defined) more than once
#define PRIORITY_QUEUE_H

#define DECLARE_NULL
#ifdef DECLARE_NULL
#define NULL 0  // Didn't think this was needed but kept erring out without it so we added it
#endif

#include <numeric>
using namespace std;

// The class is templatized.  This allows us to create a strongly-typed priority queue using generic code
template <class T>
class priority_queue
{
public:

	// Constructs a new, empty queue max queue
	priority_queue();

	// constructs a new max or min queue
	// true = max queue, false = min queue
	priority_queue(bool isMaxQueue);

	// constructs a new truncated max queue
	// The queue size will be limited to maxQueueSize, though items can still be added
	// which, if they qualify to be added will cause the current last item to be removed.
	priority_queue(unsigned int maxQueueSize);

	// Constructs a new truncated max or min queue (see notes above otehr constructors)
	priority_queue(bool isMaxQueue, unsigned int maxQueueSize);

	// Destructor
	~priority_queue();

	// Returns - The number of elements in this queue
	int getCount();

	// Adds a new element to the queue
	// Param weight - The weight of the data being inserted.  Lower valued weights are placed at the beginning of the queue
	// Param data - The data to be inserted into the queue.  Nodes use simple pointer copy.  The data itself it not replicated.
	//				This means that if the calling method destroys the data located at the pointer location, the data in the 
	//				newly added node is also destroyed
	void enqueue(int weight, T *data);

	// Removes and returns a pointer to the data associated with the first node in the queue (NULL if the queue was empty)
	// Returns - See method description comment
	T* dequeue();

	// Returns - A pointer to the data associated with the first node in the queue (NULL if the queue was empty)
	T* peek();

	// Removes the node associated with the specified data
	// Param data - The data to remove from the queue
	// Returns - data if data was in the queue, NULL otherwise
	T* remove(T* data);

	// Udates the weight of an element in the queue to a new weight.
	// Param weight - The weight of the data being updated.
	// Param data - The data to whose weight will be updated in the queue.
	void updateWeight(int weight, T *data);

	// Sets the node count to 0 and the head node to NULL (the same thing the constructor does)
	// Note:  The data contained in the queue is not freed but the nodes in the queue are deleted
	void clear();


private:

	// Nested node class
	class node
	{
	public:

		// Constructs a new node with the specified data
		node(int weight, node *previous, node *next, T *data);

		// The weight of this node.  Our implementation places lower weighted nodes at the beginning of the queue
		int weight;

		// A pointer to the node that appears before 'this' node in the queue
		node *previous;

		// A pointer to the node that appears after 'this' node in the queue
		node *next;

		// A pointer to the data that this node represents.
		// Note:	because it is a pointer, if other code has a pointer to the same object,
		//			it is possible for this object to be manipulated outside of this class
		T *data;
	};

	// The number of nodes in this queue
	int count;

	// A pointer to the first node in the queue
	// Because our queue is implemented using the linked list approach, this is the only data we need to keep track of specifically in this class
	// The other nodes will be tracked using the previous and next pointers inside the node class itself
	node *head;

	node *tail;

	unsigned int maxQueueSize;

	int smallestWeightInQueue;
	int largestWeightInQueue;

	bool isMaxQueue;

	// initial member data
	void init();

	// sets the current largest and smallest weight variables in the queue
	void setSmallestLargestQueueWeights();
};

// Sets count to 0 and head to NULL
template <class T>
priority_queue<T>::priority_queue()
{
	init();
}

template <class T>
priority_queue<T>::priority_queue(bool isMaxQueue)
{
	init();

	this->isMaxQueue = isMaxQueue;
}

template <class T>
priority_queue<T>::priority_queue(unsigned int maxQueueSize)
{
	init();

	this->maxQueueSize = maxQueueSize;
}

template <class T>
priority_queue<T>::priority_queue(bool isMaxQueue, unsigned int maxQueueSize)
{
	init();

	this->isMaxQueue = isMaxQueue;
	this->maxQueueSize = maxQueueSize;
}

template <class T>
priority_queue<T>::~priority_queue()
{
	// no data to clean up
}

template <class T>
void priority_queue<T>::init()
{
	count = 0;

	head = NULL;
	tail = NULL;

	maxSizeLimit = -1;

	setSmallestLargestQueueWeights();

	maxQueue = true;
}

template <class T>
void priority_queue<T>::setSmallestLargestQueueWeights()
{
	if(head == NULL)
	{
		smallestWeightInQueue numeric_limits<int>::max();
		largestWeightInQueue numeric_limits<int>::min();
	}
	else
	{
		if(isMaxQueue)
		{
			smallestWeightInQueue = tail->weight;
			largestWeightInQueue = head->weight;
		}
		else
		{
			smallestWeightInQueue = head->weight;
			largestWeightInQueue = tail->weight;
		}
	}
}

// Returns - The number of elements in this queue
template <class T>
int priority_queue<T>::getCount()
{
	return count;
}

// Adds a new element to the queue
// Param weight - The weight of the data being inserted.  Lower valued weights are placed at the beginning of the queue
// Param data - The data to be inserted into the queue.  Nodes use simple pointer copy.  The data itself it not replicated.
//				This means that if the calling method destroys the data located at the pointer location, the data in the 
//				newly added node is also destroyed
// When inserting a node at the beginning:
//	Ensure that the head pointer gets set to the new node
//	Ensure that the previous head (if any) node gets its previous node pointer set to the new head node
//	Ensure that the new node gets its previous pointer NULLed and its next pointer set to what the previous head node was (if any)
// When inserting a node at the end:
//	Ensure that the previously last node gets its next pointer updated to the new node
//	Ensure that the new node gets its previous pointer set to the previously last node in queue and its next pointer NULLed
// When inserting a node in the middle:
//	Ensure that the node before the new node gets its next pointer updated to be the new node
//	Ensure that the node after the new node gets its previous pointer updated to be the new node
//	Ensure that the new node gets its previous and next pointers set appropriately

template <class T>
void priority_queue<T>::enqueue(int weight, T *data)
{
	if(maxQueueSize >= 0)
	{
		if(count >= maxQueueSize)
		{
			if((isMaxQueue && weight <= smallestWeightInQueue) || (!isMaxQueue && weight >= largestWeightInQueue))
			{
				// queue is at capacity and new data did not qualify to be entered
				return;
			}

			// removes the current tail to make sure that there is now room to add the new data
			tail = tail->previous;
			delete tail->next;
			tail->next = NULL;

			count--;
		}
	}

	if (head == NULL)
	{
		head = new priority_queue<T>::node(weight, NULL, NULL, data);
		tail = head;
	}
	else
	{
		node* currentWorkingNode = head;
		node* previousWorkingNode = currentWorkingNode;

		while (currentWorkingNode != NULL)
		{
			previousWorkingNode = currentWorkingNode;

			if ((isMaxQueue && weight >= currentWorkingNode->weight) || (!isMaxQueue && weight <= currentWorkingNode->weight))
			{
				priority_queue<T>::node *newNode = new priority_queue<T>::node(weight, currentWorkingNode->previous, currentWorkingNode, data);

				if (currentWorkingNode->previous == NULL)
				{
					head = newNode;
				}
				else
				{
					currentWorkingNode->previous->next = newNode;
				}

				count++;

				currentWorkingNode->previous = newNode;

				return;
			}

			currentWorkingNode = currentWorkingNode->next;
		}

		// If we reach this point, the new node belongs at the end of the priority queue
		// previousWorkingNode should be pointing to the tail at this point
		priority_queue<T>::node *newNode = new priority_queue<T>::node(weight, previousWorkingNode, NULL, data);

		previousWorkingNode->next = newNode;

		tail = newNode;
	}

	setSmallestLargestQueueWeights();

	count++;
}

// Removes and returns a pointer to the data associated with the first node in the queue (NULL if the queue was empty)
// Returns - See method description comment
template <class T>
T* priority_queue<T>::dequeue()
{
	if (head == NULL)
	{
		return NULL;
	}

	priority_queue<T>::node *oldHead = head;
	T* returnVal = head->data;

	head = head->next;

	if (head != NULL)
	{
		head->previous = NULL;
	}
	else
	{
		// must be the last node in the queue, so tail should also be null
		tail = NULL;
	}

	setSmallestLargestQueueWeights();

	count--;

	delete oldHead;

	return returnVal;
}

// Returns - A pointer to the data associated with the first node in the queue (NULL if the queue was empty)
template <class T>
T* priority_queue<T>::peek()
{
	return NULL;
}

// Removes the node associated with the specified data
// Param data - The data to remove from the queue
// Returns - data if data was in the queue, NULL otherwise
template <class T>
T* priority_queue<T>::remove(T* data)
{
	node *workingNode = head;

	while (workingNode != NULL)
	{
		if (workingNode->data == data)
		{
			// [ ]-[ ]-[X]-[ ]-[ ]
			if(workingNode->previous != NULL && workingNode->next != NULL)
			{
				workingNode->previous->next = workingNode->next;
				workingNode->next->previous = workingNode->previous;
			}
			// [ ]-[ ]-[ ]-[ ]-[X]
			else if(workingNode->previous != NULL && workingNode->next == NULL)
			{
				tail = tail->previous;
				tail->next = NULL;
			}
			// [X]-[ ]-[ ]-[ ]-[ ]
			else if(workingNode->previous == NULL && workingNode->next != NULL) // if we get in here it must be the head node with more in the queue
			{
				head = workingNode->next;
				head->previous = NULL;
			}
			// [X]
			else // if we get in here it must be the head node with no more items in the queue
			{
				head = NULL;
				tail = NULL;
			}

			setSmallestLargestQueueWeights();

			count--;

			delete workingNode;

			return data;
		}

		workingNode = workingNode->next;
	}

	// If we reach here, the specified node must not have been in the queue.  Return NULL per the method contract
	return NULL;
}

// Updates the weight of the node associated with the specified data
// Param weight - The weight of the data being updated.
// Param data - The data to whose weight will be updated in the queue.
//
// NOTE: This feature is not compatible with truncating the queue to a maximum size!
//
template <class T>
void priority_queue<T>::updateWeight(int weight, T *data)
{
	node *workingNode = head;

	while (workingNode != NULL && workingNode->data != data)
	{
		workingNode = workingNode->next;
	}

	if(workingNode == NULL)
	{
		return;
	}

	workingNode->weight = weight;

	while(workingNode->next != NULL && workingNode->weight > workingNode->next->weight)
	{
		node *nextNode = workingNode->next;

		if(workingNode->previous != NULL)
		{
			workingNode->previous->next = nextNode;
		}

		if(nextNode->next != NULL)
		{
			nextNode->next->previous = workingNode;
		}

		nextNode->previous = workingNode->previous;
		workingNode->next = nextNode->next;
		workingNode->previous = nextNode;
		nextNode->next = workingNode;
	}

	while(workingNode->previous != NULL && workingNode->weight < workingNode->previous->weight)
	{
		node *previousNode = workingNode->previous;

		if(workingNode->next != NULL)
		{
			workingNode->next->previous = previousNode;
		}

		if(previousNode->previous != NULL)
		{
			previousNode->previous->next = workingNode;
		}

		previousNode->next = workingNode->next;
		workingNode->previous = previousNode->previous;
		workingNode->next = previousNode;
		previousNode->previous = workingNode;
	}

	if(workingNode->previous == NULL)
	{
		head = workingNode;
	}
}

// Sets the node count to 0 and the head node to NULL (the same thing the constructor does)
// Note:  The data contained in the queue is not freed but the nodes in the queue are deleted
template <class T>
void priority_queue<T>::clear()
{
	count = 0;

	while (head != NULL)
	{
		node* tempNext = head->next;

		delete head;

		head = tempNext;
	}
	this->tail->
	tail = NULL;

	setSmallestLargestQueueWeights();
}

// Constructs a new node with the specified data
template <class T>
priority_queue<T>::node::node(int weight, node *previous, node *next, T *data)
{
	this->weight = weight;
	this->previous = previous;
	this->next = next;
	this->data = data;
}

#endif
