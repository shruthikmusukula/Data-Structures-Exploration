 /**
 * Dictionary BST example usage
 *
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>, Eric Huber
 */

#include <string>
#include <iostream>
#include <vector>

#include "bst.h"

 int main() {

  // First, we'll fill a vector with some values matching each index, which
  // will be the actual external memory that our tree refers to with the
  // references in each tree node.

  // This is so that we have an existing value to reference with each tree
  // entry in our dictionary. The lecture video shows literal values being
  // passed to insert() directly, but some compiler versions don't support
  // storing references to temporary literal values. In general, it's a good
  // idea to only store references to memory that you have guaranteed will be
  // valid for some duration of the code; in this case, we can ensure that
  // the vector of actual data items will stay in scope for the rest of the
  // main function, as long as our tree will exist.

  // Another important thing to remember here: If you insert more items into
  // a std::vector after you begin recording references or pointers to its
  // contents, then those references and pointers may be invalidated due to
  // a resize and reallocation of the vector. So in practice, you may not
  // want to store references to external storage in this way, but instead
  // allow your data structure to directly store contents within itself in
  // a way that can be managed at all times throughout any updates. (If you
  // want to be able to do fast swaps inside of your data structure without
  // copying large pieces of data, as the reference-based design allows, but
  // you also want to have a robust and reusable structure that protects its
  // contents, then there are advanced ways to design your structure to
  // maintain both the organizational structure, like the tree hierarchy, as
  // well as the backing storage, together. Or, you can use "smart" pointer
  // types from recent versions of C++ that can move memory ownership around
  // without making copies or leaking memory. However, that's beyond the
  // scope of the current course sequence.)

  // Initialize a vector 100 elements long, filled with 0 values
  const int V_SIZE = 100;
  std::vector<int> v(V_SIZE, 0);
  // Reassign each item to hold a value matching its index
  for (int i=0; i<V_SIZE; i++) {
    v[i] = i;
  }

  // Let's create an inner scoping block here to restrict the lifetime of our
  // tree to be shorter than that of the ints and strings, since the tree
  // will directly reference those items. This way, the ints and strings will
  // be destroyed only after the tree has already gone out of scope at the
  // end, so the tree will be destroyed before the objects that it refers to.
  {
    BinarySearchTree<int> t;

    // Let's enable conversion from bool to strings "true" and "false"
    // for the std::cout stream. This is just to show that the empty()
    // member function is working.
    std::cout << std::boolalpha;
    std::cout << "BST empty at the beginning? " << t.empty() << std::endl;

    std::cout << "Inserting items..." << std::endl;

    // Note that we insert items here by reference to the actual items in the
    // vector "v" where they reside. The [] indexing operator for std::vector
    // returns a reference.
    t.insert(v[37]);
    t.insert(v[19]);
    t.insert(v[51]);
    t.insert(v[55]);
    t.insert(v[4]);
    t.insert(v[11]);
    t.insert(v[20]);
    t.insert(v[2]);

    // When we call find and remove below, we don't need to use v[] and we
    // can specify a number just by a literal value. That's because our
    // member functions are designed to find a key that matches the argument
    // by value equivalence, not by memory identity.

    std::cout << "Dictionary empty after insertions? " << t.empty() << std::endl;

    std::cout << "Current tree contents in order:" << std::endl;
    t.printInOrder();
    std::cout << std::endl;

    std::cout << "Using find to show that 51 has been inserted:" << std::endl;
    std::cout << "t.find(51): " << t.find(51) << std::endl;

    std::cout << "Trying to remove some items:" << std::endl;
    std::cout << "t.remove(11): " << t.remove(11) << " (zero child remove)" << std::endl;
    std::cout << "t.remove(51): " << t.remove(51) << " (one child remove)" << std::endl;
    std::cout << "t.remove(19): " << t.remove(19) << " (two child remove)" << std::endl;

    std::cout << "Current tree contents in order:" << std::endl;
    t.printInOrder();
    std::cout << std::endl;

    // The following "find" query throws an exception when the item is not
    // found, as shown in lecture. Here's a little example of exception
    // handling using the "try...catch" syntax. (If we didn't use this to
    // catch the exception, then the program would just crash to the terminal
    // and display the exception error message there.)
    try {
      std::cout << "Attempting to find a non-existent item, 51: " << std::endl;
      std::cout << "t.find(51): " << t.find(51) << std::endl;
    }
    catch (const std::runtime_error& e) {
      std::cout << "\nCaught exception with error message: " << e.what() << std::endl;
    }

    // Another example
    try {
      std::cout << "Attempting to remove a non-existent item, 99: " << std::endl;
      std::cout << "t.remove(99): " << t.remove(99) << std::endl;
    }
    catch (const std::runtime_error& e) {
      std::cout << "\nCaught exception with error message: " << e.what() << std::endl;
    }
  }

  // Show that the program exited without crashing. If you try other
  // experiments in the code block above, you may find that they throw
  // uncaught exceptions from our class functions and crash to the terminal.
  std::cout << "Exiting program normally." << std::endl;

  return 0;
}
