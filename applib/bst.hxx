//============================================================================
// Name        : BST implementation
// File Desc.  : Write detailed method implementations
// Author(s)   : Yusuf Pisan pisan@uw.edu, Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

// Included by bst.h (this is a header because of template usage...)
// INCLUDES (headers) SHOULD BE IN BST.H!!!

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
static int getHeight(const Node *n)
{
	//your code here

	return -2;
}

// Number of nodes in the BST.
int numberOfNodes() { return sizeHelper(Root); }

//also gets # of nodes in the BST.
int size() const { return sizeHelper(Root); }

// gets size recursively
int sizeHelper(Node *node) const
{
	//your code here
	
	return -1;
}

// true if item is in BST
bool contains(const key_t &key) const
{
	//your code here

	return false;
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void inOrderTraverse(void visit(const T &item)) const
{
	//your code here

	return;
}

// preorder traversal: root-left-right
void preOrderTraverse(void visit(const T &item)) const
{
	//your code here

	return;
}

// postorder traversal: left-right-root
void postOrderTraverse(void visit(const T &item)) const
{
	//your code here

	return;
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void rebalance()
{
	// your code here

	return;
}

//destructor fn
void clear()
{
	//your code here

	return;
}

void clearHelper(Node *curr)
{
	// your code here

	// recursive helper method (optional) for clear

	return;
}

// add a new item, return true if successful
// return false if the item is a duplicate
bool add(const T &Item) //default root
{
	//your code here

	return false;
}

bool rAdd(const T &Item, Node **n)
{
	// your code here

	// recursive helper method (optional) for add

	return false;
}

// remove item, return true if successful
bool remove(const T &Item)
{
	//your code here

	return false;
}

BST(const BST<T> &Bst)
{
	//your code here
}

void rCC(Node **copyThis, Node **newTree)
{
	//your code here
	
	// recursive helper method (optional) for copy constructor
	
	return;
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool operator==(const BST &other) const
{
	//your code here

	return false;
}

// not == to each other
bool operator!=(const BST &other) const
{
	// your code here

	return false; 
}
