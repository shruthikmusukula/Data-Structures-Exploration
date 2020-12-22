/**
 * C++ BST (binary search tree) example.
 * 
 * @author
 *   Shruthik Musukula <srm14@illinois.edu>
 */

#pragma once

// We include <stdexcept> so we can throw std::runtime_error in some cases.
#include <stdexcept>
// We include <utility> for the std::swap function
#include <utility>
// We'll add a "printInOrder" function to help us inspect the results.
// This will require std::cout from <iostream>.
#include <iostream>

template <typename D>
class BinarySearchTree {
  public:
    BinarySearchTree() : head_(nullptr) { }

    const D& find(const D& value);
    void insert(const D& value);
    const D& remove(const D& value);

  private:
    class TreeNode {
    public:
        const D& data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const D& data)
          : data(data), left(nullptr), right(nullptr) { }
    };

    TreeNode *head_;
    TreeNode*& _find(const D& value, TreeNode*& cur) const;
    const D& _remove(TreeNode*& node);
    // _remove relies on the following three functions.
    TreeNode*& _iop_of(TreeNode*& cur) const;
    TreeNode*& _rightmost_of(TreeNode*& cur) const;
    TreeNode*& _swap_nodes(TreeNode*& node1, TreeNode*& node2);
  
  public:
    bool empty() const {
      return !head_;
    }

  private:
    void _printInOrder(TreeNode* node) {
      // Base case: if node is nullptr, then print a space and return.
      if (!node) {
        std::cout << " ";
        return;
      }
      else {
        // Recurse left:
        _printInOrder(node->left);
        // Print this node:
        std::cout << "[" << node->data << "]";
        // Recurse right:
        _printInOrder(node->right);
      }
    }

  public:

    void printInOrder() {
      _printInOrder(head_);
    }

    // clear_tree: Remove the head item until the tree is empty.
    void clear_tree() {
      while (head_) {
        // As long as the head pointer isn't null, we can just look at
        // what the key is and call remove based on that.
        remove(head_->data);
      }
    }

    ~BinarySearchTree() {
      clear_tree();
    }

};

#include "bst.hpp"

