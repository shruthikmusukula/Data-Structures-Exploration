/**
 * BinarySearchTree BST auxiliary definitions.
 * 
 * @author
 *   Shruthik Musukula <srm14@illinois.edu>
 */

#pragma once

#include "bst.h"

template <typename D>
const D& BinarySearchTree<D>::find(const D& value) {
  TreeNode*& node = _find(value, head_);
  if (node == nullptr) { throw std::runtime_error("error: key not found"); }
  return node->data;
}

template <typename D>
typename BinarySearchTree<D>::TreeNode*& BinarySearchTree<D>::_find(
    const D& value, TreeNode*& cur) const {
  if (cur == nullptr) { return cur; }
  else if (value == cur->data) { return cur; }
  else if (value < cur->data) { return _find(value, cur->left); }
  else { return _find(value, cur->right); }

}

/**
* insert()
* Inserts `data` into the BinarySearchTree.
*/
template <typename D>
void BinarySearchTree<D>::insert(const D& data) {
  TreeNode *& node = _find(data, head_);
  if (node) { throw std::runtime_error("error: insert() used on an existing data value"); }
  node = new TreeNode(data);
}

/**
* remove()
* Removes `key` from the BinarySearchTree. Returns the associated data.
*/
template <typename D>
const D& BinarySearchTree<D>::remove(const D& value) {
  TreeNode*& node = _find(value, head_);
  if (!node) { throw std::runtime_error("error: remove() used on non-existent key"); }
  return _remove(node);
}

template <typename D>
const D& BinarySearchTree<D>::_remove(TreeNode*& node) {

  if (!node) { throw std::runtime_error("error: _remove() used on non-existent key"); }


  // Zero child remove:
  if (node->left == nullptr && node->right == nullptr) {
    const D& data = node->data;
    delete node;
    node = nullptr;
    return data;
  }
  // One-child (left) remove
  else if (node->left != nullptr && node->right == nullptr) {
    const D& data = node->data;
    TreeNode* temp = node;
    node = node->left;
    delete temp;
    return data;
  }
  // One-child (right) remove
  else if (node->left == nullptr && node->right != nullptr) {
    const D& data = node->data;
    TreeNode* temp = node;
    node = node->right;
    delete temp;
    return data;
  }
  // Two-child remove
  else {
    // Find the IOP (in-order predecessor) of the current node.
    TreeNode*& iop = _iop_of(node);
    if (!iop) {
      throw std::runtime_error("error in two-child remove: IOP not found");
    }

    // Swap the node to remove and the IOP.
    //  To make things easier, _swap_nodes will return
    //  a pointer, by reference, that is the updated pointer in the tree
    //  that is now pointing to the same node we gave as the first argument,
    //  so we can do more work on that node afterwards.)
    TreeNode*& moved_node = _swap_nodes(node, iop);

    return _remove(moved_node);
  }
}

template <typename D>
typename BinarySearchTree<D>::TreeNode*& BinarySearchTree<D>::_iop_of(
  TreeNode*& cur) const {

  if (!cur) {
    return cur;
  }
  
  if (!(cur->left)) {
    return cur->left;
  }

  return _rightmost_of(cur->left);
}

template <typename D>
typename BinarySearchTree<D>::TreeNode*& BinarySearchTree<D>::_rightmost_of(
  TreeNode*& cur) const {
  if (!cur) return cur;
  if (!(cur->right)) return cur;
  return _rightmost_of(cur->right);
}

template <typename D>
typename BinarySearchTree<D>::TreeNode*& BinarySearchTree<D>::_swap_nodes(
  TreeNode*& node1, TreeNode*& node2) {
  TreeNode* orig_node1 = node1;
  TreeNode* orig_node2 = node2;

  if (node1->left == node2) {
    std::swap(node1->right, node2->right);

    // Now we have to deal with the left child pointers, and it's
    // complicated. We need to be very careful about the order of changes.
    // The easiest way to see how this works is draw a diagram of the
    // original nodes and pointers, and see how the pointers have to be
    // redirected.

    // Make "node1" take its leftmost grandchild as its left child.
    // The next line also affects the actual "node2" pointer, implicitly,
    // so we won't try to use the "node2" pointer after this; it will no
    // longer point to the original "node2" node that we would expect from
    // the naming.
    node1->left = orig_node2->left;
    // Now the original node2 needs to take the original node1 as its left
    // child.
    orig_node2->left = node1;
    // Now the actual node1 pointer should point to the object that was
    // the original node2.
    node1 = orig_node2;

    // The node position swap is done, but the node1 and node2 arguments
    // themselves haven't been swapped! We can't do that in this case.

    // This is the actual pointer in the tree that is now pointing to what
    // was our original node1 object, so return it by reference.
    return node1->left;
  }
  else if (node1->right == node2) {
    std::swap(node1->left, node2->left);
    node1->right = orig_node2->right;
    orig_node2->right = node1;
    node1 = orig_node2;
    return node1->right;
  }
  else if (node2->left == node1) {
    std::swap(node2->right, node1->right);
    node2->left = orig_node1->left;
    orig_node1->left = node2;
    node2 = orig_node1;
    return node2->left;
  }
  else if (node2->right == node1) {
    std::swap(node2->left, node1->left);
    node2->right = orig_node1->right;
    orig_node1->right = node2;
    node2 = orig_node1;
    return node2->right;
  }
  else {
    // If the two nodes aren't adjacent in the tree, it's a lot easier.
    // We can swap their child pointers and swap their main pointers,
    // and it just works. (Again, the easiest way to see this is true is
    // to draw a picture of the pointer connections between the nodes.)

    std::swap(node1->left, node2->left);
    std::swap(node1->right, node2->right);
    std::swap(node1, node2);

    // This is the actual pointer in the tree that is now pointing to what
    // was our original node1 object, so return it by reference.
    return node2;
  }

  // For future reference, here are some debugging output statements that
  // might be helpful if trouble arises:

  // std::cerr << "\nAfter swap: [" << node1->key << " , " << node1->data
  //   << " ] [ " << node2->key << " , " << node2->data << " ] " << std::endl;
  // std::cerr << "\nn1: " << node1 << " n2: " << node2
  //   << "\n n1l: " << node1->left << " n1r: " << node1->right
  //   << "\n n2l: " << node2->left << " n2r: " << node2->right << std::endl;

}


