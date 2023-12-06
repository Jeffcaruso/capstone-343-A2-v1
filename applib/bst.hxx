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
	if (n == nullptr)
	{
		return 0;
	}
	int left = getHeight(n->Left);
	int right = getHeight(n->Right);
	if (left > right)
	{
		return left + 1;
	}
	return right + 1;
}

// Number of nodes in BST
int numberOfNodes() { return sizeHelper(Root); }

int size() const
{
	return numberOfNodes();
}

// gets size recursively
int sizeHelper(Node *node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return sizeHelper(node->Left) + 1 + sizeHelper(node->Right);
}

// true if item is in BST
bool contains(const key_t &key) const
{
	Node *curr;
	curr = Root;
	while (curr != nullptr && curr->data.first != key)
	{
		if (curr->data.first <= key)
		{
			curr = curr->right;
		}
		else
		{
			curr = curr->left;
		}
	}
	return curr != nullptr;
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void inOrderTraverse(void visit(const T &item)) const
{
	if (!isEmpty())
	{
		Node *curr = Root;
		std::stack<Node *> order;
		while (!order.empty() || curr != nullptr)
		{
			while (curr != nullptr)
			{
				order.push(curr);
				curr = curr->Left;
			}
			curr = order.top();
			order.pop();
			visit(curr->Data);
			curr = curr->Right;
		}
	}
}

// preorder traversal: root-left-right
void preOrderTraverse(void visit(const T &item)) const
{
	if (!isEmpty())
	{
		Node *curr = Root;
		std::stack<Node *> order;
		order.push(curr);
		while (!order.empty())
		{
			curr = order.top();
			visit(curr->Data);
			order.pop();
			if (curr->Right != nullptr)
			{
				order.push(curr->Right);
			}
			if (curr->Left != nullptr)
			{
				order.push(curr->Left);
			}
		}
	}
}

// postorder traversal: left-right-root
void postOrderTraverse(void visit(const T &item)) const
{
	if (!isEmpty())
	{
		Node *curr = Root;
		std::stack<Node *> order;
		std::stack<Node *> order2;
		order.push(curr);
		while (!order.empty())
		{
			curr = order.top();
			order.pop();
			order2.push(curr);
			if (curr->Left != nullptr)
			{
				order.push(curr->Left);
			}
			if (curr->Right != nullptr)
			{
				order.push(curr->Right);
			}
		}
		while (!order2.empty())
		{
			curr = order2.top();
			order2.pop();
			visit(curr->Data);
		}
	}
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void rebalance()
{
	if (Root != nullptr)
	{
		vector<Node *> nodes;
		nodesInVector(Root, nodes);
		uint64_t size = nodes.size();
		uint64_t mid = size / 2;
		Root = nodes[mid];
		// use queue to hold nodes and what their low and high are
		queue<pair<Node *, pair<int, int>>> assign;
		assign.push({Root, {0, mid - 1}});
		assign.push({Root, {mid + 1, size - 1}});
		while (!assign.empty())
		{
			pair<Node *, pair<int, int>> pairCurr = assign.front();
			assign.pop();
			Node *curr;
			curr = pairCurr.first;
			int start = pairCurr.second.first;
			int end = pairCurr.second.second;
			if (start <= end && curr != nullptr)
			{
				int newMid = (start + end) / 2;
				Node *childCurr = nodes[newMid];
				if (curr->data.first > childCurr->data.first)
				{
					curr->left = childCurr;
				}
				else
				{
					curr->right = childCurr;
				}
				assign.push({childCurr, {start, newMid - 1}});
				assign.push({childCurr, {newMid + 1, end}});
			}
		}
	}
}

void clear()
{
	if(Root)
	{
		clearHelper(Root);
	}
}

void clearHelper(Node *curr)
{
	if(curr != nullptr)
	{
		clearHelper(curr->Left);
		clearHelper(curr->Right);
		delete curr;
		curr = nullptr;
	}
}

// add a new item, return true if successful
// return false if the item is a duplicate
bool add(const T &Item) //default root
{
	bool setRoot = false;
	if(Root == nullptr)
	{
		setRoot = true;
	}
	Node *n = Root;

	bool ok = rAdd(Item, &n);

	//if Root was initially unset.
	if(setRoot)
	{
		Root = n;
	}

	//return if it was added successfully. expect true.
	return ok;
}

bool rAdd(const T &Item, Node **n)
{
	if ((*n) == nullptr)
	{
		Node *nn = new Node(Item);
		(*n) = nn;
		return true;
	}
	else
	{
		if (Item < (*n)->Data)
		{
			// go left
			return rAdd(Item, &((*n)->Left));
		}
		else
		{
			// go right
			return rAdd(Item, &((*n)->Right));
		}
	}
	return false;
}

// remove item, return true if successful
bool remove(const T &Item)
{
	if (Root->Data == Item) {
 
        // Insert the first node, if root is NULL.
		Root = Node(Item);
        return true;
    }
	else
	{
		//Actual BST insert...
		return false;
	}
}

BST(const BST<T> &Bst)
{
	//gather Root (Node *)
	Node *copyThis = Bst.Root;

	Node *newTree;

	rCC(&copyThis, &newTree);

	//saving the root
	Root = newTree;
}

void rCC(Node **copyThis, Node **newTree)
{
	if(copyThis == nullptr)
	{
		newTree = nullptr;
		return;
	}

	//Create node
	(*newTree) = new Node((*copyThis)->Data);
	
	//shouldn't really need these if blocks, but just in case that is what is causing the problem
	if((*copyThis)->Left != nullptr)
	{
		rCC(&((*copyThis)->Left), &((*newTree)->Left));
	}
	if((*copyThis)->Right != nullptr)
	{
		rCC(&((*copyThis)->Right), &((*newTree)->Right));
	}
	
	return;
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool operator==(const BST &other) const
{
	if (isEmpty() && other.isEmpty())
	{
		return true;
	}
	if (isEmpty() || other.isEmpty())
	{
		return false;
	}
	queue<Node *> currTree;
	queue<Node *> otherTree;
	currTree.push(Root);
	otherTree.push(other.Root);
	while (!currTree.empty() && !otherTree.empty())
	{
		Node *currTreeTemp = currTree.front();
		currTree.pop();
		Node *otherTreeTemp = otherTree.front();
		otherTree.pop();
		if (currTreeTemp == nullptr && otherTreeTemp == nullptr)
		{
			continue;
		}
		if (currTreeTemp == nullptr || otherTreeTemp == nullptr)
		{
			return false;
		}
		if (currTreeTemp->Data != otherTreeTemp->Data ||
			currTreeTemp->Data != otherTreeTemp->Data )
		{
			return false;
		}
		currTree.push(currTreeTemp->Left);
		currTree.push(currTreeTemp->Right);
		otherTree.push(otherTreeTemp->Left);
		otherTree.push(otherTreeTemp->Right);
	}
	return this->size() == other.size();
}

// not == to each other
bool operator!=(const BST &other) const { return !(*this == other); }
