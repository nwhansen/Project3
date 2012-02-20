/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #2, cs3505, January 2012
 */

#ifndef BST_H
#define BST_H

#define TRACK_DEPTH	0

//#define NULL 0

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <deque> // Only included to assist in printing the DOT files used for visualization and debugging of the BST

using namespace std;

/// An implementation a a Binary Search Tree (BST).
/// This BST is templatized to accept any data type given.
/// No duplicates are allowed in this BST.

template <class T>
class BST
{
public:

	/// Creates a new BST
	BST();

	/// Creates a copy of an already existing BST
	BST(BST &copy);

	/// Creates a new BST from a provided collection
	/// Data should be in a somewhat randomized order before given to this constructor.
	/// Param - collection - the collection of data to add to the BST when created
	/// Param - collectionSize - the number of items in the collection
	BST(T **collection, int collectionSize);

	/// Deconstructs the BST
	~BST();

	/// Add an element to the BST
	/// If data does not yet exist in the BST, it will be added, otherwise no action is taken.
	/// Returns - true if the data was added to the BST, false otehrwise
	bool add(T *data);

	/// Adds an entire collection of elements to the BST
	/// Param - collection - the collection of data to add to the BST when created
	/// Param - collectionSize - the number of items in the collection
	/// Returns - true if any element was added to the BST, false otherwise
	bool addCollection(T **collection, int collectionSize);

	/// Removes the given data from the BST
	/// Param - data - the data to be removed
	/// Returns - true if the data existed and was removed, false otherwise
	bool remove(T *data);

	/// Checks to see if a given element exists in the BST
	/// Param - data - the data to search for in the BST
	/// Returns - true if the element exists in the BST, false otherwise
	bool contains(T *data);

	/// Clears all elements from the BST
	void clear();

	/// Gets the amount of elements contained in this BST
	/// Returns - int - the number of elements in the BST
	int getCount();

	/// Gets the items which are the closest relation to the provided data from the BST.
	/// If the given data exists, it will be included in the results, otherwise items which
	/// would have been in proximity to data will be in the results. There is no guarantee
	/// that results will contain ideal elements.
	/// Param - data - that data to get neighboring data of
	/// Param - qty - the desired (max) amount of results desired. No guarantee that qty number
	///  of results will be returned, only up to and including that number.
	/// Param - itemsFound - an array which the results can be stored in
	/// Returns - int - the number of results found.
	int getNeighboringData(T *data, int qty, T** itemsFound);

	/// Writes this BST into a Graphviz DOT format so that it can be viewed as a graph.
	/// Param - file - the path and name of the output file (generally should be given a .dot extension)
	void toDot(string file);

private:

	/// Internal node class for this BST
	/// Contains the data as well has left/right children and parent nodes
	class node
	{
	public:
		/// Creates a new node containing given data
		/// Param - data - the data which this node will contain.
		/// Param - parent - the parent node for this one
		node(T *data, node *parent);

		/// The left child of this node
		node *left;

		/// The right child of this node
		node *right;

		/// The parent of this node
		node *parent;

		/// The data contained in this node
		T *data;
	};

	/// The number of elements in this BST
	int count;

	/// The root node of this BST
	node *rootNode;

#if TRACK_DEPTH
	int depth;
#endif

	node* copyNode(node *nodeToCopy)
	{
		printfDebug("In copyNode and nodeToCopy is %ld", nodeToCopy);

		if (nodeToCopy == NULL)
		{
			return NULL;
		}

		node *returnVal = new node(nodeToCopy->data, nodeToCopy->parent);

		returnVal->left = copyNode(nodeToCopy->left);
		returnVal->right = copyNode(nodeToCopy->right);

		return returnVal;
	}

	node* findNode(node* workingNode, T *dataToFind)
	{
		while (workingNode != NULL)
		{
			if (*(workingNode->data) == *dataToFind)
			{
				return workingNode;
			}

			if (*(workingNode->data) < *dataToFind)
			{
				workingNode = workingNode->right;
			}
			else
			{
				workingNode = workingNode->left;
			}
		}

		return NULL;
	}

	node* getRightmostChild(node *parent)
	{
		node *workingNode = parent;

		while (workingNode->right != NULL)
		{
			workingNode = workingNode->right;
		}

		return workingNode;
	}

	node* getLeftmostChild(node *parent)
	{
		node *workingNode = parent;

		while (workingNode->left != NULL)
		{
			workingNode = workingNode->left;
		}

		return workingNode;
	}

	void deleteNode(node *nodeToDelete);
	void buildDotLines(node *currentNode, deque<string> *list);

};

template <class T>
BST<T>::BST()
{
	count = 0;

	rootNode = NULL;

#if TRACK_DEPTH
	depth = 0;
#endif
}

template <class T>
BST<T>::BST(BST &copy)
{
	count = copy.count;

	rootNode = copyNode(copy.rootNode);

#if TRACK_DEPTH
	depth = copy.depth;
#endif
}

template <class T>
BST<T>::BST(T **collection, int collectionSize)
{
	count = 0;

	rootNode = NULL;

	addCollection(collection, collectionSize);
}

template <class T>
BST<T>::~BST()
{
	deleteNode(rootNode);

	rootNode = NULL;

	count = 0; // Not needed but whatever

#if TRACK_DEPTH
	depth = 0; // Not needed but whatever
#endif
}

template <class T>
bool BST<T>::add(T *data)
{
	if (rootNode == NULL)
	{
		rootNode = new node(data, NULL);

		count++;

#if TRACK_DEPTH
		depth = 1;
#endif

		return true;
	}

#if TRACK_DEPTH
	int currentDepth = 1;
#endif

	node *workingNode = rootNode;

	while (workingNode != NULL)
	{
		// If the workingNode has the same data as what we are trying to insert (duplicate data), return false so the BST doesn't get any duplicate entries
		if (*(workingNode->data) == *data)
		{
			return false;
		}
		else if (*(workingNode->data) < *data)
		{
			if (workingNode->right == NULL)
			{
				workingNode->right = new node(data, workingNode);

				count++;

#if TRACK_DEPTH
				if (currentDepth > depth)
				{
					depth = currentDepth;
				}
#endif

				break;
			}
			else
			{
				workingNode = workingNode->right;

#if TRACK_DEPTH
				currentDepth++;
#endif
			}
		}
		else
		{
			if (workingNode->left == NULL)
			{
				workingNode->left = new node(data, workingNode);

				count++;

#if TRACK_DEPTH
				if (currentDepth > depth)
				{
					depth = currentDepth;
				}
#endif

				break;
			}
			else
			{
				workingNode = workingNode->left;

#if TRACK_DEPTH
				currentDepth++;
#endif
			}
		}
	}

	if (workingNode == NULL)
	{
		printf("workingNode is NULL in BST::add which shouldn't be possible");

		return false;
	}

	return true;
}

template <class T>
bool BST<T>::addCollection(T **collection, int collectionSize)
{
	bool changed = false;

	for (int i = 0; i < collectionSize; i++)
	{
		changed = add(collection[i]) || changed;
	}

	return changed;
}

template <class T>
bool BST<T>::remove(T *data)
{
	// searchflag remove causes a problem with depth that hasn't been resolved yet

	node *nodeToRemove = findNode(rootNode, data);

	if (nodeToRemove == NULL)
	{
		return false;
	}

	if (nodeToRemove->right != NULL)
	{
		node *workingNode = nodeToRemove->right;

		if (workingNode->left == NULL)
		{
			nodeToRemove->data = workingNode->data;

			workingNode->parent->right = workingNode->right;

			if (workingNode->right != NULL)
			{
				workingNode->right->parent = workingNode->parent;
			}

			delete workingNode;
		}
		else
		{
			while (workingNode != NULL)
			{
				if (workingNode->left == NULL)
				{
					nodeToRemove->data = workingNode->data;

					workingNode->parent->left = workingNode->right;

					if (workingNode->right != NULL)
					{
						workingNode->right->parent = workingNode->parent;
					}

					delete workingNode;

					break;
				}

				workingNode = workingNode->left;
			}
		}
	}
	else if (nodeToRemove->left != NULL)
	{
		node *workingNode = nodeToRemove->left;

		if (workingNode->right == NULL)
		{
			nodeToRemove->data = workingNode->data;

			workingNode->parent->left = workingNode->left;

			if (workingNode->left != NULL)
			{
				workingNode->left->parent = workingNode->parent;
			}

			delete workingNode;
		}
		else
		{
			while (workingNode != NULL)
			{
				if (workingNode->right == NULL)
				{
					nodeToRemove->data = workingNode->data;

					workingNode->parent->right = workingNode->left;

					if (workingNode->left != NULL)
					{
						workingNode->left->parent = workingNode->parent;
					}

					delete workingNode;

					break;
				}

				workingNode = workingNode->right;
			}
		}
	}
	else // This must have been a leaf node
	{
		node *parentNode = nodeToRemove->parent;

		if (parentNode != NULL)
		{
			if (parentNode->left == nodeToRemove)
			{
				parentNode->left = NULL;
			}
			else
			{
				parentNode->right = NULL;
			}
		}
		else // This must have been the root node
		{
			rootNode = NULL;
		}

		delete nodeToRemove;
	}

	return true;
}

template <class T>
bool BST<T>::contains(T *data)
{
	return (findNode(rootNode, data) != NULL);
}

template <class T>
void BST<T>::clear()
{
	// Bad practice?
	this->~BST();
}

template <class T>
int BST<T>::getCount()
{
	return count;
}

template <class T>
void BST<T>::deleteNode(node *nodeToDelete)
{
	if (nodeToDelete == NULL)
	{
		return;
	}

	deleteNode(nodeToDelete->left);
	deleteNode(nodeToDelete->right);

	nodeToDelete->left = NULL;
	nodeToDelete->right = NULL;

	delete nodeToDelete;
}

template <class T>
int BST<T>::getNeighboringData(T *dataToFind, int requestedQty, T** itemsFound)
{
	node *workingNode = rootNode;
	int foundQty = 0;

	while (workingNode != NULL)
	{
		if (*(workingNode->data) == *dataToFind)
		{
			break;
		}

		if (*(workingNode->data) < *dataToFind)
		{
			if (workingNode->right != NULL)
			{
				workingNode = workingNode->right;
			}
			else
			{
				break;
			}
		}
		else
		{
			if (workingNode->left != NULL)
			{
				workingNode = workingNode->left;
			}
			else
			{
				break;
			}
		}
	}

	// add the first node we stopped on
	if (foundQty < requestedQty)
	{
		itemsFound[foundQty++] = workingNode->data;
	}

	if (foundQty < requestedQty && workingNode->right != NULL)
	{
		itemsFound[foundQty++] = getLeftmostChild(workingNode->right)->data;
	}

	if (foundQty < requestedQty && workingNode->left != NULL)
	{
		itemsFound[foundQty++] = getRightmostChild(workingNode->left)->data;
	}

	if (foundQty < requestedQty && workingNode->parent != NULL)
	{
		itemsFound[foundQty++] = workingNode->parent->data;

		if (foundQty < requestedQty && workingNode->parent->right != NULL && workingNode->parent->right != workingNode)
		{
			itemsFound[foundQty++] = getLeftmostChild(workingNode->parent->right)->data;
		}

		if (foundQty < requestedQty && workingNode->parent->left != NULL && workingNode->parent->left != workingNode)
		{
			itemsFound[foundQty++] = getRightmostChild(workingNode->parent->left)->data;
		}
	}

	return foundQty;
}

template <class T>
BST<T>::node::node(T *data, node *parent)
{
	this->left = NULL;
	this->right = NULL;
	this->data = data;
	this->parent = parent;
}

#endif
