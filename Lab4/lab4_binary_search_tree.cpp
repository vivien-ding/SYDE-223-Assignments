//Written by Vivien (Zhaowei) Ding & Christina Lim 
//Student numbers: 20654920 & 20724130

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
	return get_node_depth(root)-1;
}

void BinarySearchTree::print_help(BinarySearchTree::TaskItem *t) const{
	if (t == NULL){
		cout << "NULL" <<endl;
	}
	else{
		cout << t->priority << " " << t-> description << endl;
		print_help(t->left);
		print_help(t->right);
	}
}


// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	// use a stack?? 
	cout << "PRINTING TREE" << endl;
	print_help(root);
	cout << "END TREE" << endl;
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
		size++;
		return true;
	}

	TaskItem* parent = NULL;
	TaskItem* cur = root;

	while (cur != NULL){
		parent = cur;
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

	if (parent->priority < val.priority){
		parent->right = cur;
	}
	else{
		parent->left = cur;
	}

	size++;
	
	return true;
}


 

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    if (root == NULL){
		return false;
	}

	if (val == *root){
		
		TaskItem* temp = root;
		//no subtrees
		if(root->left == NULL && root->right == NULL){
			delete root;
			root = NULL;
		}
		//no right subtree
		else if(root->left == NULL && root->right != NULL){
			root = root->right;
			delete temp;

		}
		//no left subtree
		else if (root->left != NULL && root->right == NULL){
			root = root->left;
			delete temp;
		}
		//2 subtrees
		else{
			TaskItem* successor_parent = root;
			TaskItem* successor = root->right;

			while(successor->left != NULL){
				successor_parent = successor;
				successor = successor->left;
			}
			
			root->priority = successor->priority;
			root->description = successor->description;

			//special case
			if(*successor_parent == *root){
				root->right = successor->right;
			}
			else{
				successor_parent->left = successor->right;
			}

			delete successor;
				
		}
		size--;
		return true;
	}

	TaskItem* cur = root;
	TaskItem* target;

	while (cur != NULL){
		if (cur->left != NULL && *(cur->left) == val){
			target = cur->left;
			break;
		}
		else if ( cur->right != NULL && *(cur->right) == val){
			target = cur->right;
			break;
		}
		else if (cur->priority > val.priority){
			cur = cur->left;
		}

		else if (cur->priority < val.priority){
			cur = cur->right;
		}
		else{
			return false;
		}
	}

	//case0: did not find target
	if (cur == NULL){
		return false;
	}

	//case1: target is leaf node
	if(target->right == NULL && target->left == NULL){

		if (cur->right!= NULL && *(cur->right) == *target){
			cur->right = NULL;
		}
		else{
			cur->left = NULL;
		}

		delete target;
		size--;
		return true;
	}


	//case2.0: target  only has left subtree
	else if(target->right == NULL && target->left != NULL){
		if (*cur->right == *target){
			cur->right = target->left;

		}
		else{
			cur->left = target->left;
		}
		delete target;
		size--;
		return true;
	}

	//case2.1: target  only has right subtree
	else if(target->left == NULL && target->right != NULL){
		if (*cur->right == *target){
			cur->right = target->right;

		}
		else{
			cur->left = target->right;
		}
		delete target;
		size--;
		return true;
	}

	//case3: target has both sides
	else if (target->left != NULL && target->right != NULL){
		
		TaskItem* successor_parent = target;
		TaskItem* successor = target->right;

		while(successor->left != NULL){
			successor_parent = successor;
			successor = successor->left;
		}
		
		target->priority = successor->priority;
		target->description = successor->description;

		//special case
		if(*successor_parent == *target){
			target->right = successor->right;
		}
		else{
			successor_parent->left = successor->right;
		}

		delete successor;
		successor = NULL;
		size--;

		return true;
	}
	

	
	return false;
}
