//included by bst.h (this is a header because of template usage...)
#include <algorithm>
#include <iostream>
#include <stack>
//#include <cassert>

//using namespace std;

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
//template <class T>
int getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  int left = getHeight(n->left);
  int right = getHeight(n->right);
  if (left > right) {
    return left + 1;
  }
  return right + 1;
}




// Number of nodes in BST
//template <class T>
int numberOfNodes() { return sizeHelper(Root); }

// gets size recursively
//template <class T>
int sizeHelper(Node *node) const {
  if (node == nullptr) {
    return 0;
  }
  return sizeHelper(node->left) + 1 + sizeHelper(node->right);
}




// true if item is in BST
//template <class T>
bool contains(const key_type &key) const {
  Node *curr;
  curr = Root;
  while (curr != nullptr && curr->data.first != key) {
    if (curr->data.first <= key) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }
  return curr != nullptr;
}


// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
//template <class T>
void inOrderTraverse(void visit(const value_type &item)) const {
  if (! isEmpty()) {
    Node *curr = Root;
    std::stack<Node *> order(10,vector<Node *>(10));
    while (!order.empty() || curr != nullptr) {
      while (curr != nullptr) {
        order.push(curr);
        curr = curr->left;
      }
      curr = order.top();
      order.pop();
      visit(curr->data);
      curr = curr->right;
    }
  }
}


// preorder traversal: root-left-right
//review vlaue_type...? may not be right thing...
//template <class T>
void preOrderTraverse(void visit(const value_type &item)) const {
  if (!isEmpty()) {
    Node *curr = Root;
    stack<Node *> order;
    order.push(curr);
    while (!order.empty()) {
      curr = order.top();
      visit(curr->data);
      order.pop();
      if (curr->right != nullptr) {
        order.push(curr->right);
      }
      if (curr->left != nullptr) {
        order.push(curr->left);
      }
    }
  }
}



// postorder traversal: left-right-root
//template <class T>
void postOrderTraverse(void visit(const value_type &item)) const {
  if (!isEmpty()) {
    Node *curr = Root;
    std::stack<Node *> order;
    std::stack<Node *> order2;
    order.push(curr);
    while (!order.empty()) {
      curr = order.top();
      order.pop();
      order2.push(curr);
      if (curr->left != nullptr) {
        order.push(curr->left);
      }
      if (curr->right != nullptr) {
        order.push(curr->right);
      }
    }
    while (!order2.empty()) {
      curr = order2.top();
      order2.pop();
      visit(curr->data);
    }
  }
}


// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
//template <class T>
void rebalance() {
  if (Root != nullptr) {
    vector<Node *> nodes;
    nodesInVector(Root, nodes);
    uint64_t size = nodes.size();
    uint64_t mid = size / 2;
    Root = nodes[mid];
    // use queue to hold nodes and what their low and high are
    queue<pair<Node *, pair<int, int>>> assign;
    assign.push({Root, {0, mid - 1}});
    assign.push({Root, {mid + 1, size - 1}});
    while (!assign.empty()) {
      pair<Node *, pair<int, int>> pairCurr = assign.front();
      assign.pop();
      Node *curr;
      curr = pairCurr.first;
      int start = pairCurr.second.first;
      int end = pairCurr.second.second;
      if (start <= end && curr != nullptr) {
        int newMid = (start + end) / 2;
        Node *childCurr = nodes[newMid];
        if (curr->data.first > childCurr->data.first) {
          curr->left = childCurr;
        } else {
          curr->right = childCurr;
        }
        assign.push({childCurr, {start, newMid - 1}});
        assign.push({childCurr, {newMid + 1, end}});
      }
    }
  }
}


//template <class T>
void clear()
{
    clearHelper(this.Root);
    this.Root = nullptr;
}

//template <class T>
void clearHelper(Node *curr) {
  if (curr != nullptr) {
    clearHelper(curr->left);
    clearHelper(curr->right);
    delete curr;
  }
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
//template <class T>
bool operator==(const BST &other) const {
  if (isEmpty() && other.isEmpty()) {
    return true;
  }
  if (isEmpty() || other.isEmpty()) {
    return false;
  }
  queue<Node *> currTree;
  queue<Node *> otherTree;
  currTree.push(Root);
  otherTree.push(other.Root);
  while (!currTree.empty() && !otherTree.empty()) {
    Node *currTreeTemp = currTree.front();
    currTree.pop();
    Node *otherTreeTemp = otherTree.front();
    otherTree.pop();
    if (currTreeTemp == nullptr && otherTreeTemp == nullptr) {
      continue;
    }
    if (currTreeTemp == nullptr || otherTreeTemp == nullptr) {
      return false;
    }
    if (currTreeTemp->data.first != otherTreeTemp->data.first ||
        currTreeTemp->data.second != otherTreeTemp->data.second) {
      return false;
    }
    currTree.push(currTreeTemp->left);
    currTree.push(currTreeTemp->right);
    otherTree.push(otherTreeTemp->left);
    otherTree.push(otherTreeTemp->right);
  }
  return this->size() == other.size();
}

// not == to each other
//template <class T>
bool operator!=(const BST &other) const { return !(*this == other); }

// template<class T>
// bool BST<Node>::operator!=(const BST &other) const { return !(*this == other); }