// @todo : update this to have the standard top of file description

// Included by bst.h (this is a header because of template usage...)
// INCLUDES SHOULD BE IN BST.H!!!

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
// template <class T>
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
// template <class T>
int numberOfNodes() { return sizeHelper(Root); }

// gets size recursively
// template <class T>
int sizeHelper(Node *node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return sizeHelper(node->Left) + 1 + sizeHelper(node->Right);
}

// true if item is in BST
// template <class T>
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
// template <class T>

// maybe key is ok, b/c this is using visit on the data...
//  used to be (const value_type &item)
void inOrderTraverse(void visit(const key_t &item)) const
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
			visit(curr->data);
			curr = curr->Right;
		}
	}
}

// preorder traversal: root-left-right
// review vlaue_type...? may not be right thing...
// template <class T>
void preOrderTraverse(void visit(const key_t &item)) const
{
	if (!isEmpty())
	{
		Node *curr = Root;
		std::stack<Node *> order;
		order.push(curr);
		while (!order.empty())
		{
			curr = order.top();
			visit(curr->data);
			order.pop();
			if (curr->right != nullptr)
			{
				order.push(curr->Right);
			}
			if (curr->left != nullptr)
			{
				order.push(curr->Left);
			}
		}
	}
}

// postorder traversal: left-right-root
// template <class T>
void postOrderTraverse(void visit(const key_t &item)) const
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
				order.push(curr->left);
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
// template <class T>
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

// template <class T>
void clear()
{
	clearHelper(this->Root);
	this->Root = nullptr;
}

// template <class T>
void clearHelper(Node *curr)
{
	if (curr != nullptr)
	{
		clearHelper(curr->Left);
		clearHelper(curr->Right);
		delete curr;
	}
}


///////////////////////////////////////////////////////////NOTE: probably doesn't work properly yet.
// add a new item, return true if successful
// return false if the item is a duplicate
// Note T is value to insert...
bool add(const T &Item)
{
    if (!this->Root) {
 
        // Insert the first node, if root is NULL.
		this.Root = Node(Item);
        return true;
    }
	else
	{
		//Actual BST insert...
		return false;
	}
 
    // // Insert data.
    // if (value > Item->data) {
    //     // Insert right node data, if the 'value'
    //     // to be inserted is greater than 'root' node data.
 
    //     // Process right nodes.
    //     Item->right = Insert(Item->right, value);
    // }
    // else if (value < Item->data) {
    //     // Insert left node data, if the 'value'
    //     // to be inserted is smaller than 'root' node data.
 
    //     // Process left nodes.
    //     Item->left = Insert(Item->left, value);
    // }
 
    // return true;
}

// remove item, return true if successful
bool remove(const T &Item)
{
	if (!this->Root->Data == Item) {
 
        // Insert the first node, if root is NULL.
		this.Root = Node(Item);
        return true;
    }
	else
	{
		//Actual BST insert...
		return false;
	}
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
// template <class T>
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
		if (currTreeTemp->data.first != otherTreeTemp->data.first ||
			currTreeTemp->data.second != otherTreeTemp->data.second)
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
// template <class T>
bool operator!=(const BST &other) const { return !(*this == other); }

// template<class T>
// bool BST<Node>::operator!=(const BST &other) const { return !(*this == other); }