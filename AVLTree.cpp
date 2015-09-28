/*******************************************************************************
* AVLTree.cpp
*
* author: Joshua Hawkins
* date created: 2015
* last updated: 9/28/2015
*
* This file implements the methods of the AVLTree class
*******************************************************************************/


#include "AVLTree.h"

using std::cout;
using std::endl;
AVLTree::AVLTree() {
  size = 0;
  root = 0;
}

AVLTree::AVLTree(TreeNode* node) {
  size = 1;
  root = node;
}

AVLTree::~AVLTree() {
  size = 0;
  ClearTree(root);
}

int AVLTree::getSize() {
  return size;
}


TreeNode* AVLTree::getRoot() {
  return root;
}

int AVLTree::getHeight(TreeNode* node) {
  if(node == 0) {
    return -1;
  }

  return node->height;

}

void AVLTree::setHeight(TreeNode*& node) {
	// updates a node's height and balance factor. don't forget that any node
	// in a tree is the root of a subtree
  node->height = std::max(getHeight(node->left),getHeight(node->right)) + 1;
  node->balanceFactor = (getHeight(node->left) - getHeight(node->right));
}

bool AVLTree::IsFull() const {
  TreeNode* temp;
  try {
    temp = new TreeNode();
    delete temp;
    return false;
  }
  catch(std::bad_alloc) {
    return true;
  }
}

bool AVLTree::IsEmpty() const {
  return (root == 0);
}


void AVLTree::PrintTree(TreeNode* node) {
  if(node != 0) {
	PrintTree(node->left);
    std::cout << node->data << " ";
    PrintTree(node->right);
  }
}

void AVLTree::ClearTree(TreeNode*& node) {
  if(node != 0) {
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
  }
}

bool AVLTree::Find(TreeNode* node, int& item) {

  // return false if the tree is empty or if item is not in the tree
  if(node == 0) {
    return false;
  }
	// otherwise traverse the tree
  if(item < node->data) {
    return Find(node->left,item);
  }
  else if(item > node->data) {
    return Find(node->right,item);
  }
  else {
    item = node->data;
    return node->data == item;
  }

}

bool AVLTree::Find(TreeNode* node, int& item, TreeNode*& target) {

  // return false if the tree is empty or if item is not in the tree
  if(node == 0) {
    return false;
  }
	// otherwise traverse the tree
  if(item < node->data) {
    return Find(node->left,item,target);
  }
  else if(item > node->data) {
    return Find(node->right,item,target);
  }
  else {
    target = node;  // returns the node via reference variable
    item = node->data;
    return node->data == item;
  }

}

void AVLTree::Insert(int item) {
  if(IsFull()) {
    throw TreeFullException();
  }

  try{
    Insert(root,item);
    size += 1;
  }
  catch(DuplicateItemException) {
    throw;
  }

}

void AVLTree::Insert(TreeNode*& node, int item) {
	// identical to the Insert in Bst but you need to
	// decide if this method will update the height
	// of a node and its balance factor
	// this method throws a DuplicateItemException

	if (node == 0) {
		node = new TreeNode(item);		// create and add the new node
	}
	else if (item == node->data) {
		throw DuplicateItemException(item);
	}
	else if (item < node->data) {
		Insert(node->left, item);			// search left subtree
	}
	else {
		Insert(node->right, item);			// search right subtree
	}

	// Now update balance factor.
	setHeight(node);

	// Check if the subtree is unbalanced as we unwind the recursion
	if (node->balanceFactor > 1 || node->balanceFactor < -1){
		BalanceTree(node); // Balance the tree where the node is unbalanced
	}
}


void AVLTree::Delete(int item) {
  if(root == 0) {
    throw TreeEmptyException();
  }
  else{
    try{
      Delete(root, item);
      size -= 1;
    }
    catch(ItemNotFoundException) {
      throw;
    }
  }
}

void AVLTree::Delete(TreeNode*& node, int item) {
	// identical to the Delete in Bst but you need to
	// decide if this method will update the height
	// of a node and its balance factor
	// this method throws a ItemNotFoundException
	if (node == 0) {
		throw ItemNotFoundException(item);
	}
	else if (item == node->data) {
		// Delete the node.
		DeleteNode(node); // Is this correct syntax?
	}
	else if (item < node->data) {
		Delete(node->left, item);

		// Unwind recursion; update height
		setHeight(node);
		// Check if the subtree is unbalanced as we unwind the recursion
		if (node->balanceFactor > 1 || node->balanceFactor < -1){
			BalanceTree(node); // Balance the tree where the node is unbalanced
		}
	}
	else if (item > node->data) {
		Delete(node->right, item);

		// Unwind recursion; update height
		setHeight(node);
		// Check if the subtree is unbalanced as we unwind the recursion
		if (node->balanceFactor > 1 || node->balanceFactor < -1){
			BalanceTree(node); // Balance the tree where the node is unbalanced
		}
	}


}

void AVLTree::DeleteNode(TreeNode*& node){
	TreeNode *rnode, *dnode;
	// identical to the DeleteNode in Bst but you need to
	// decide if this method will update the height
	// of a node and its balance factor
	bool isroot = false;
	if (node == this->root){
		isroot = true;
	}

	if (node->left != 0 && node->right != 0){
		// If both children exist, 2nd degree deletion.
		dnode = node;	// Node to delete
		rnode = node;	// Node to replace with
		TreeNode* temp;
		temp = node->left;

		// Find the replacement node
		rnode = dnode->left; // Will not be 0, dnode has 2 children
		while (rnode->right != 0){
			temp = rnode; // Temp will be rnode's parent
			rnode = rnode->right;
			temp->height--;	// Decrease height for each node once
		}

		// Check for children under final rnode
		if (rnode != temp){
			// Move child pointers
			if (rnode->left != 0){
				temp->right = rnode->left; // Set any possible left children of rnode to it's parent's right child node.
				rnode->left = 0;
			}
			else{
				temp->right = 0;
			}
		}


		// Account for dnode children next
		if (dnode->left != 0 && dnode->left != rnode){
			rnode->left = dnode->left;
		}
		if (dnode->right != 0){	// Should never be equal to rnode anyway
			rnode->right = dnode->right;
		}

		// Find parent node of dnode
		temp = this->root;
		if (!isroot){
			while (!(temp->left == dnode || temp->right == dnode)){
				if (temp->data > dnode->data){
					if (temp->left != dnode){
						temp = temp->left;
					}
				}
				else if (temp->data < dnode->data){
					if (temp->right != dnode){
						temp = temp->right;
					}
				}
			}	// Temp is now the parent of dnode
		}

		// Set temp to point past dnode
		if (temp->left == dnode){
			temp->left = rnode;
		}
		else if (temp->right == dnode){
			temp->right = rnode;
		}

		// Check if root was deleted
		if (isroot){
			this->root = rnode; // Update root node.
		}

		setHeight(rnode);
		// Clear up memeory
		delete dnode;
	}
	else if (node->left != 0 && node->right != 0){
		// Node has no children
		delete node;
	}
	else if (node->left == 0){
		// Left child does not exist, single degree deletion.
		TreeNode* temp = node;
		node = node->right;
		delete temp;
	}
	else if (node->right == 0){
		// Right child does not exist, single degree deletion.
		TreeNode* temp = node;
		node = node->left;
		delete temp;
	}

}

void AVLTree::BalanceTree(TreeNode*& node) {
	// checks the balance factor of a node and determines what
	// type of rotation needs to be executed (basically calls a
	// rotation function).  Don't forget that you also need to
	// check for cases that require a double rotation.

	if (node->getBalFac() > 0){ // node is left-heavy
		if (node->left->getBalFac() >= 0){ // sub-tree is also left heavy
			// Single right rotation
			RightSingleRotate(node);
		}
		else if (node->left->getBalFac() < 0){ // sub-tree is right heavy instead
			// Double rotation. right then left
			LeftRightRotate(node);
		}
	}

	else if (node->getBalFac() < 0){ // node is right-heavy
		if (node->right->getBalFac() <= 0){ // sub-tree is also right heavy
			LeftSingleRotate(node);
		}
		else if (node->right->getBalFac() > 0){ // sub-tree is left heavy instead
			// Double rotation. left then right
			RightLeftRotate(node);
		}
	}
}


void AVLTree::LeftSingleRotate(TreeNode*& node) {
	// rotates a right heavy subtree left.  You will have to decide
	// if this method updates the height and balance factor of the
	// nodes involved.

	// std::cout << "Left single rotate detected." << std::endl;
	TreeNode* parent = getRoot();
	bool isRoot = false;

	if (parent == node){
		isRoot = true;
	}
	else{// if unbalanced node is not root
		while (parent->right != node && parent->left != node){
			if (node->getData() > parent->getData()){
				parent = parent->right;
			}
			else if (node->getData() < parent->getData()){
				parent = parent->left;
			}
		}
	}

	// Actual swap
	TreeNode * mid = node->right; // Assign right-subtree to mid

	node->right = mid->left;
	mid->left = node;
	node = mid;

	// Update root
	if (isRoot){
		root = mid;
	}
	if (!isRoot){ // This section may or may not belong
		if (parent->right == node){
			parent->right = mid;
		}
		else if (parent->left == node){
			parent->left = mid;
		}
	}



	// Update balance factors
	mid->balanceFactor = 0;
	mid->left->balanceFactor = 0;
	setHeight(mid->left);
	setHeight(mid);

	// Debug print tree
	//PrintTree(root);
	// std::cout << "Root's right child is: " << root->right->getData() << std::endl;
	// std::cout << "Root's left child is: " << root->left->getData() << " height:" << root->left->getHeight() << std::endl;
}

void AVLTree::RightSingleRotate(TreeNode*& node) {
	// rotates a left heavy subtree right  You will have to decide
	// if this method updates the height and balance factor of the
	// nodes involved.


	// std::cout << "Right single rotate detected." << std::endl;
	TreeNode* parent = getRoot();
	bool isRoot = false;

	if (parent == node){
		isRoot = true;
	}
	else{// if unbalanced node is not root
		while (parent->left != node && parent->right != node){
			if (node->getData() > parent->getData()){
				parent = parent->right;
			}
			else if (node->getData() < parent->getData()){
				parent = parent->left;
			}
		}
	}

	// Actual swap
	TreeNode * mid = node->left; // Assign left-subtree to mid

	node->left = mid->right;
	mid->right = node;
	node = mid;

	// Update root
	if (isRoot){
		root = mid;
	}
	if (!isRoot){ // This section may or may not belong
		if (parent->right == node){
			parent->right = mid;
		}
		else if (parent->left == node){
			parent->left = mid;
		}
	}



	// Update balance factors
	mid->balanceFactor = 0;
	mid->right->balanceFactor = 0;
	setHeight(mid->right);
	setHeight(mid);

	// Debug print tree
	//PrintTree(root);
}

void AVLTree::LeftRightRotate(TreeNode*& node) {
	// executes a double rotation of a left heavy tree with a right heavy subtree
	// the subtree is rotated left first and then the tree is rotated right
	// You will have to decide if this method updates the height and balance
	// factor of the nodes involved.

	// cout << "Double rotate detected -> Left, Right" << endl;
	LeftSingleRotate(node->left);
	RightSingleRotate(node);
}

void AVLTree::RightLeftRotate(TreeNode*& node) {
	// executes a double rotation of a right heavy tree with a left heavy subtree
	// the subtree is rotated right first and then the tree is rotated left
	// You will have to decide if this method updates the height and balance
	// factor of the nodes involved.

	// cout << "Double rotate detected -> Right, Left" << endl;
	RightSingleRotate(node->right);
	LeftSingleRotate(node);
}
