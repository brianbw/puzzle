

#include <iostream>
#include <string>
#include "linkedQueue.h"
#ifndef H_AVLTREE
#define H_AVLTREE

using namespace std; 

enum treeTraversalOptions { INORDER, INORDER2, PREORDER, POSTORDER, LEVELORDER, NONE};

template <class myType>
struct nodeType
{
	myType keyValue;			// value of this node
	int	nodeHeight;				// height of this node
	nodeType<myType> *left;		// node to the left of this node
	nodeType<myType> *right;	// node to the right of this node
};

template <class myType>
class avlTree
{
	public:
		avlTree();															// constructor
		~avlTree();															// destructor

		void destroyTree();													// deallocate all nodes
		int countNodes() const;												// count number of nodes
		int height() const;													// count height of tree
		bool search(myType) const;											// search for node
		void printTree(treeTraversalOptions) const;							// print all nodes
		void insert(myType);												// insert a node
		void deleteNode(myType);											// delete a node
		bool isPrefix(string) const;										// search for substring of node

	private:
		nodeType<myType> *root;												// root of tree (base)
		void destroyTree(nodeType<myType> *);								// deallocate all nodes (priv)
		int countNodes(nodeType<myType> *) const;							// count number of nodes (priv)
		int height(nodeType<myType> *) const;								// count height of tree (priv)
		nodeType<myType> *search(myType, nodeType<myType> *) const; 		// search for node (priv)
		void printTree(nodeType<myType> *, treeTraversalOptions) const;		// print all nodes (priv)
		void printLevelOrder() const;										// print bfs (priv)
		nodeType<myType> *insert(myType, nodeType<myType> *);				// insert a node (priv)
		nodeType<myType> *rightRotate(nodeType<myType> *);					// right rotate tree (priv)
		nodeType<myType> *leftRotate(nodeType<myType> *);					// left rotate tree (priv)
		int getBalance(nodeType<myType> *) const;							// get balance factor of tree (priv)
		nodeType<myType> *deleteNode(myType, nodeType<myType> *);			// delete a node (priv)
		nodeType<myType> *minValueNode(nodeType<myType> *) const;			// get smallest valued node
};

// initialize tree to empty state
template <class myType>
avlTree<myType>::avlTree()
{
	root = NULL;					// no nodes
}

// delete tree by calling destroyTree
template <class myType>
avlTree<myType>::~avlTree()
{
	destroyTree(root);				// deallocate all nodes
	root = NULL;					// no nodes
}

// delete tree (call private)
template <class myType>
void avlTree<myType>::destroyTree()
{
	destroyTree(root);				// deallocate all nodes
	root = NULL;					// no nodes
}

// delete tree, deallocate memory
template <class myType>
void avlTree<myType>::destroyTree(nodeType<myType> *tree)
{
	if (tree != NULL)				// if there is a node
	{
		destroyTree(tree->left);	// destroy right node (recur)
		destroyTree(tree->right);	// destroy left node (recur)
		delete tree;				// deallocate node
	}

	tree = NULL;					// no nodes
}

// return total count of nodes in tree (call private)
template <class myType>
int avlTree<myType>::countNodes() const
{
	return countNodes(root);							// count number of nodes in tree
}

// recursively return total counts of nodes in tree
template <class myType>
int avlTree<myType>::countNodes(nodeType<myType> *tree) const
{
	if (tree != NULL)									// if there is a node
	{
		int count = 1;									// 1st count 

		if (tree->left != NULL)							// count left subtree (recur)
			count = count + countNodes(tree->left);		// running sum of left

		if (tree->right != NULL)						// count right subtree (recur)
			count = count + countNodes(tree->right);	// running sum of right

		return count; 									// final count
	}

	else 												// if there is no node
		return 0;										// count is 0 
}

// return max height of tree (call private)
template <class myType>
int avlTree<myType>::height() const
{
	return height(root);								// count height of node (tallest subtree)
}

// recursively return max height of tree
template <class myType>
int avlTree<myType>::height(nodeType<myType> *tree) const
{
	int lh, rh;											// left height, right height
	if (tree == NULL)									// if there is no node
		return 0;										// tree's height is 0

	lh = height(tree->left);							// recursively get height of left tree
	rh = height(tree->right);							// recursively get height of right tree

	if (lh > rh) 										// if left height is taller
		return (lh + 1);								// return left

	else 												// if right height is taller
		return (rh + 1);								// return right
}

// determine if passed node key is in tree (call private)
// if node is found -> true, false otherwise
template <class myType>
bool avlTree<myType>::search(myType key) const
{
	nodeType<myType> *temp = search(key, root);			// search for a node in tree

	if (temp == NULL)									// if node is empty
		return false;									// search fail, key is not in tree

	return true;										// else, found
}

// recursively search tree for passed node key
template <class myType>
nodeType<myType> *avlTree<myType>::search(myType key, nodeType<myType> *tree) const
{
	if (tree != NULL)									// if there is a node
	{
		if (key < tree->keyValue)						// is key less than middle (recur)
			return search(key, tree->left);				// traverse left (lower)
		else if (key > tree->keyValue)					// or is key more than middle (recur)
			return search(key, tree->right);			// traverse right (higher)
	}

	return tree;										// if there is no node / if node is found
} 

// print tree in order passed (call private)
template <class myType>
void avlTree<myType>::printTree(treeTraversalOptions userChoice) const
{
	printTree(root, userChoice);						// print all nodes' values from tree
	cout << endl;
}

// recursively print tree in specified order
// uses printLevelOrder when LEVELORDER is specified
template <class myType>
void avlTree<myType>::printTree(nodeType<myType> *tree, treeTraversalOptions userChoice) const
{	
	switch(userChoice)
	{
		case INORDER:									// print LPR
		{
			if (tree == NULL)							// if there is no node	
				return;									// dont print

			printTree(tree->left, userChoice);			// LEFT 
			cout << "  " << tree->keyValue;				// PARENT
			printTree(tree->right, userChoice);			// RIGHT
		}
		break; 

		case INORDER2:									// print LPR (for wordPuzzle b/c endl)
		{
			if (tree == NULL)							// if there is no node	
				return;									// dont print

			printTree(tree->left, userChoice);			// LEFT 
			cout << "  " << tree->keyValue << endl;		// PARENT
			printTree(tree->right, userChoice);			// RIGHT
		}
		break; 

		case PREORDER:									// print PLR
		{	
			if (tree == NULL)							// if there is no node
				return;									// dont print

			cout << "  " << tree->keyValue;				// PARENT
			printTree(tree->left, userChoice);			// LEFT 
			printTree(tree->right, userChoice);			// RIGHT	

		}
		break;

		case POSTORDER:									// print LRP
		{
			if (tree == NULL)							// if there is no node		
				return;									// dont print

			printTree(tree->left, userChoice);			// LEFT 
			printTree(tree->right, userChoice);			// RIGHT
			cout << "  " << tree->keyValue;				// PARENT
		}
		break; 

		case LEVELORDER:								// BFS
		{
			printLevelOrder();							// print based on level
		}
		break; 

		case NONE:										// no printing occurs
			break; 
	}

}

// print tree in level order by doing breadth first traversal (BFS) 
// uses linked queue
template <class myType>
void avlTree<myType>::printLevelOrder() const
{
	linkedQueue<nodeType<myType> *> bfsQueue;			// create queue via linkedQueue template class
	bfsQueue.initializeQueue();							// intialize to new and empty queue
	nodeType<myType> *temp = root;						// copy node to start 
	while (temp != NULL)								// loop forever if there is node to print
	{
		cout << "  " << temp->keyValue;					// print node's value

		if (temp->left != NULL)							// enqueue left child if exists
			bfsQueue.addItem(temp->left);

		if (temp->right != NULL)						// enqueue right child if exists
			bfsQueue.addItem(temp->right);

		if (bfsQueue.isEmptyQueue())					// check if queue is empty 
			break;										// to determine exit

		else 											// queue has items
		{
			temp = bfsQueue.front();					// copy first item
			bfsQueue.deleteItem();						// remove item from stack
		}	
	} 
}

// insert passed key value into tree (call private)
template <class myType>
void avlTree<myType>::insert(myType key)
{
	if (!search(key))														// if key is not already in tree							
		root = insert(key, root);											// attempt to insert
}

// insert passed key value to tree, if already in, don't insert
template <class myType>
nodeType<myType> *avlTree<myType>::insert(myType key, nodeType<myType> *tree)
{
	if (tree == NULL)														// if tree does not exist
	{
		nodeType<myType> *temp = new nodeType<myType>;						// allocate memory
		temp->keyValue = key;												// key is first item
		temp->left = NULL;													// only node so no left
		temp->right = NULL;													// no right either
		temp->nodeHeight = 1;												// 1 node = 1 height
		tree = temp;														// copy to root/base
		return tree;														// insertion complete
	}

	if (key < tree->keyValue)												// if key is smaller
		tree->left = insert(key, tree->left);								// traverse left (recur)

	else if (key > tree->keyValue)											// if key is bigger
		tree->right = insert(key, tree->right);								// traverse right (recur)

	else																	// key = node value
		return tree;														// cannot insert same value

	tree->nodeHeight = max(height(tree->left), height(tree->right)) + 1;	// update height
	int balance = getBalance(tree);											// get balance factor

	if (balance > 1 && key < tree->left->keyValue)							// left left case
		return rightRotate(tree);	

	if (balance < -1 && key > tree->right->keyValue)						// right right case
		return leftRotate(tree);

	if (balance > 1 && key > tree->left->keyValue)							// left right case
	{
		tree->left = leftRotate(tree->left);
		return rightRotate(tree);
	}

	if (balance < -1 && key < tree->right->keyValue)						// right left case
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}

	return tree;														
}

// delete passed key value from tree (call private)
template <class myType>
void avlTree<myType>::deleteNode(myType key)
{
	if (search (key))														// if key in tree
		root = deleteNode(key, root);										// attempt to delete
}

// delete passed key value from tree (if it exists)
// uses leftRotate(), rightRotate(), getBalance(), minValueNode()
template <class myType>
nodeType<myType> *avlTree<myType>::deleteNode(myType key, nodeType<myType> *tree)
{
	if (tree == NULL)														// if node does not exist
		return tree;														// nothing to delete

	if (key < tree->keyValue)												// if key is smaller
		tree->left = deleteNode(key, tree->left);							// traverse left (recur)

	else if (key > tree->keyValue)											// if key is bigger
		tree->right = deleteNode(key, tree->right);							// traverse right (recur)
	
	else 																	// tree == key (base case)
	{
		if (tree->left == NULL)												// none or right child only
		{
			nodeType<myType> *temp = tree->right;							// copy right node							
			delete tree;													// deallocate old node
			return temp;													// right node is new node
		}

		else if (tree->right == NULL)										// none or left child only
		{				
			nodeType<myType> *temp = tree->left;							// copy left node
			delete tree;													// deallocate old node
			return temp;													// right node is new node
		}

		nodeType<myType> *temp = minValueNode(tree->right);					// node has 2 children
		tree->keyValue = temp->keyValue;									// smallest child in right subtree
		tree->right = deleteNode(temp->keyValue, tree->right);				// overwrite parent w/ smallest right
	}

	if (tree == NULL)														// if empty after 1 delete														
		return tree;														// no rebalancing needed											

	tree->nodeHeight = max(height(tree->left), height(tree->right)) + 1;	// update height
	int balance = getBalance(tree);											// get balance factor

	if (balance > 1 && getBalance(tree->left) >= 0)							// left left case
		return rightRotate(tree);

	if (balance < -1 && getBalance(tree->right) <= 0)						// right right case
		return leftRotate(tree);

	if (balance > 1 &&  getBalance(tree->left) < 0)							// left right case
	{
		tree->left = leftRotate(tree->left);
		return rightRotate(tree);
	}

	if (balance < -1 && getBalance(tree->right) > 0)						// right left case
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}

	return tree;
}

// determine if passed prefix is in tree
template <class myType>
bool avlTree<myType>::isPrefix(string prefix) const
{
	nodeType<myType> *temp = root;
	string sTemp = "";
	while (temp != NULL)														// traverse whole tree
	{
		sTemp = temp->keyValue;													// copy node value
		//cout << "sTemp: " << sTemp << endl;
		//cout << "prefix: " << prefix << endl;
		//cout << "temp->keyValue:" << sTemp.substr(0, prefix.length()) << endl;
		//cout << "temp->keyValue(orig): " << temp->keyValue << endl;

		if (prefix > sTemp.substr(0, prefix.length()))							// if higher than mid
 			temp = temp->right;													// traverse right (iter)

		else if (prefix < sTemp.substr(0, prefix.length()))						// if lower than mid
			temp = temp->left;													// traverse left (iter)

		else 								
		{	
			sTemp == "";							
			return true;														// substring found	
		}
	} 		

	return false;																// prefix not in tree
}

// perform right tree rotation operation
template <class myType>
nodeType<myType> *avlTree<myType>::rightRotate(nodeType<myType> *tree)
{
	nodeType<myType> *tempL = tree->left;										// new = og's left
	nodeType<myType> *tempR = tempL->right;										// new2 = new's right

	tempL->right = tree;														// new's right = og
	tree->left = tempR;															// og's left = new2

	tree->nodeHeight = max(height(tree->left), height(tree->right)) + 1;		// update og's height
	tempL->nodeHeight = max(height(tempL->left), height(tempL->right)) + 1;		// update new's height

	return tempL;																// new is new og
}

// perform left tree rotation operation 
template <class myType>
nodeType<myType> *avlTree<myType>::leftRotate(nodeType<myType> *tree)
{
	nodeType<myType> *tempR = tree->right;										// new = og's right
	nodeType<myType> *tempL = tempR->left;										// new2 = new's left

	tempR->left = tree;															// new's right = og 
	tree->right = tempL;														// og's right = new2

	tree->nodeHeight = max(height(tree->left), height(tree->right)) + 1;		// update og's height 
	tempR->nodeHeight = max(height(tempR->left), height(tempR->right)) + 1;		// update new's height

	return tempR;																// new is new og
}

// return the balance factor 
// (left subtree height - right subtree height) of passed node
template <class myType>
int avlTree<myType>::getBalance(nodeType<myType> *tree) const
{
	if (tree == NULL)															// if tree is empty
		return 0;																// balance is 0
	return height(tree->left) - height(tree->right);							// else, b.f. = lh - rh
}

// search tree from passed node and return node with min key value
// non recursive, follow the left tree branch 
template <class myType>
nodeType<myType> *avlTree<myType>::minValueNode(nodeType<myType> *tree) const
{
	nodeType<myType> *temp = tree;												// copy node
	while (temp->left != NULL)													// traverse to extreme left
		temp = temp->left;							

	return temp;																// smallest node found
}		

#endif 
