#include <iostream>
#include "lab4_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (size == 0){
		return BinarySearchTree::TaskItem(-1, "N/A");
	}
	TaskItem* cur = root;
	while (cur->right != NULL){
		cur = cur->right;
	}
	return *cur;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (size == 0){
		return BinarySearchTree::TaskItem(-1, "N/A");
	}
	TaskItem* cur = root;
	while (cur->left != NULL){
		cur = cur->left;
	}
	return *cur;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	return get_node_depth(root);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	stack<BinarySearchTree::TaskItem *> s;
	// use a stack??
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	if (root == NULL){
		return false;
	}

	TaskItem* cur = root;
	while (cur != NULL){
		if (cur->priority == val.priority){
			return true;
		}

		else if (cur->priority > val.priority){
			cur = cur->left;
		}

		else if (cur->priority < val.priority){
			cur = cur->right;
		}
	}

	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if (n == NULL){
		return 0;
	}

	else{
		int ltree = get_node_depth(n->left);
		int rtree = get_node_depth(n->right);

		if (ltree > rtree){
			return (ltree + 1);
		}
		else{
			return (rtree + 1);
		}
	
	}
}



// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    if (root == NULL){
		root = new TaskItem(val);
		return true;
	}

	TaskItem* cur = root;
	while (cur != NULL){
		if (cur->priority == val.priority){
			return false;
		}

		else if (cur->priority > val.priority){
			cur = cur->left;	
		}

		else if (cur->priority < val.priority){
			cur = cur->right;
		}
	}

	cur = new TaskItem(val);
	return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    if (root == NULL){
		return false;
	}

	TaskItem* cur = root;
	while (cur != NULL){
		if (cur->priority == val.priority){
			if ((cur->left == NULL) && (cur->right == NULL)){
				cur
			}
		}

		else if (cur->priority > val.priority){
			cur = cur->left;
		}

		else if (cur->priority < val.priority){
			cur = cur->right;
		}
	}
	
	return false;
}
