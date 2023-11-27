#include "bst.h"
#include <algorithm>
#include <cassert>



// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
template<class Node>
int BST<Node>::getHeight(const Node *n) {
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
int BST<Node>::numberOfNodes() const { return sizeHelper(root); }

// gets size recursively
int BST<Node>::sizeHelper(Node *node) const {
  if (node == nullptr) {
    return 0;
  }
  return sizeHelper(node->left) + 1 + sizeHelper(node->right);
}




// true if item is in BST
bool BST<Node>::contains(const key_type &key) const {
  Node *curr;
  curr = root;
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
void BST::inorder(void visit(const value_type &item)) const {
  if (!empty()) {
    Node *curr = root;
    stack<Node *> order;
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
void BST::preorder(void visit(const value_type &item)) const {
  if (!empty()) {
    Node *curr = root;
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
void BST::postorder(void visit(const value_type &item)) const {
  if (!empty()) {
    Node *curr = root;
    stack<Node *> order;
    stack<Node *> order2;
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
void BST::rebalance() {
  if (root != nullptr) {
    vector<Node *> nodes;
    nodesInVector(root, nodes);
    uint64_t size = nodes.size();
    uint64_t mid = size / 2;
    root = nodes[mid];
    // use queue to hold nodes and what their low and high are
    queue<pair<Node *, pair<int, int>>> assign;
    assign.push({root, {0, mid - 1}});
    assign.push({root, {mid + 1, size - 1}});
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


void BST::clear()
{
    clearHelper(this.root);
    this.root = nullptr;
}

void BST::clearHelper(Node *curr) {
  if (curr != nullptr) {
    clearHelper(curr->left);
    clearHelper(curr->right);
    delete curr;
  }
}


// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BST::operator==(const BST &other) const {
  if (empty() && other.empty()) {
    return true;
  }
  if (empty() || other.empty()) {
    return false;
  }
  queue<Node *> currTree;
  queue<Node *> otherTree;
  currTree.push(root);
  otherTree.push(other.root);
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
bool BST::operator!=(const BST &other) const { return !(*this == other); }