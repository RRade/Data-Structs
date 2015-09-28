/*******************************************************************************
* Bst.cpp
*
* author: Joshua Hawkins
* date created: 2015
* last updated: 9/28/2015
*
* This files implements the methods of the Bst class
*******************************************************************************/

#include "TreeNode.h"
#include "Bst.h"
#include <iostream>
using std::cout;
using std::endl;

Bst::Bst() {
  size = 0;
  root = 0;
}

Bst::Bst(TreeNode* node) {
  size = 1;
  root = node;
}

Bst::~Bst() {
  size = 0;
  ClearTree(root);
}

int Bst::getSize() {
  return size;
}


TreeNode* Bst::getRoot() {
  return root;
}

bool Bst::IsFull() const {
	// the method attempts to allocate memory for a tree node
	// and returns false if the allocation was successful. if a
	// std::bad_alloc exception was thrown, true is returned
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

bool Bst::IsEmpty() const {
  return (root == 0);
}


void Bst::PrintTree(TreeNode* node) {
	// executes and in-order traversal of the tree where
	// the visit opration is a cout of the node data
  if(node != 0) {
    PrintTree(node->left);
    std::cout << node->data << " ";
    PrintTree(node->right);
  }
}

void Bst::ClearTree(TreeNode*& node) {
	// uses a post-order traversal to remove all nodes in the tree
  if(node != 0) {
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
  }
}

bool Bst::Find(TreeNode* node, int& item) {

  // return false if the tree is empty of if item is not in the tree
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

bool Bst::Find(TreeNode* node, int& item, TreeNode*& target) {

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


void Bst::Insert(int item) {
	// checks for a full tree and then calls the recursive
	// Insert method. Throws the exception thrown by
	// Insert(TreeNode*& node, int item) and also TreeFullException
  if(IsFull()) {
    throw TreeFullException();
  }

  try{
    Insert(root,item);		// recursive function call
    size += 1;
  }
  catch(DuplicateItemException) {
    throw;		// throw the exception thrown by Insert(TreeNode*& node, int item)
  }

}

void Bst::Insert(TreeNode*& node, int item) {
	// a recursive method that traverses the tree and adds a new
	// node to the tree when the correct position is found
	// throws a DuplicateItemException
  if(node == 0) {
    node = new TreeNode(item);		// create and add the new node
	/*std::cout << "Item added to tree" << std::endl;
	std::cout << node->getData() << ", at " << node << std::endl;
	*/
  }
  else if(item == node->data) {
    throw DuplicateItemException(item);
  }
  else if(item < node->data) {
    Insert(node->left,item);			// search left subtree
  }
  else {
    Insert(node->right,item);			// search right subtree
  }
}

void Bst::Delete(int item) {
	// checks for an empty tree and then calls the recursive
	// Delete method. Throws a TreeEmptyException if the tree
	// is empty and also throws the exception thrown by
	// Delete(TreeNode*& node, int item)
  if(root == 0) {
    throw TreeEmptyException();
  }
  else{
    try{
      Delete(root, item);			// recursive function call
      size -= 1;							// decrement size when done
    }
    catch(ItemNotFoundException) {
      throw;		// throw the exception thrown by Delete(TreeNode*& node, int item)
    }
  }
}

void Bst::Delete(TreeNode*& node, int item) {
	// a recursive method that traverses the tree and calls DeleteNode to
	// remove the node found from the tree.
	// throws an ItemNotFoundException
  if(node == 0) {
    throw ItemNotFoundException(item);
  }
  else if (item == node->data) {
	  // Delete the node.
	  DeleteNode(node);
  }
  else if (item < node->data) {
	  Delete(node->left, item);
  }
  else if (item > node->data) {
	  Delete(node->right, item);
  }
}

void Bst::DeleteNode(TreeNode*& node) {
	// this method executes a degree 0/1 and degree 2 deletion
	// degree 0/1: test for a NULL child. if NULL, attach the other
	//						 child to the this nodes parent
	// degree 2: keep track of the node to delete, search the left subtree
	// 					 for a replacment node, update data then delete the replacment
	//           node
	TreeNode *rnode, *dnode;		// rnode is used for degree 2 deletion

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
				//std::cout << "temp->right:" << temp->right << " data:" << temp->right->getData() << std::endl;
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
				//cout << "While" << endl;
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

		// dnode = rnode; // Actual replacement of node

		// Check if root was deleted
		if (isroot){
			this->root = rnode; // Update root node.
		}

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
