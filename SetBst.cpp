/*******************************************************************************
* SetBst.cpp
*
* author: Joshua Hawkins
* date created: 2015
* last updated: 9/28/2015
*
* This files implements the methods of the SetBst class
*******************************************************************************/

#include "SetBst.h"
#include "Bst.h"
#include "Bst.cpp"

SetBst::SetBst() {
	tree = new Bst();
	treeArray = 0;
	arraySize = 0;
}

void SetBst::genTreeArray() {
	// dynamically allocates space for an array the size of the tree + 1
	// and uses the recursive function genTreeArray(TreeNode* node, int& position)
	// to populate it
  int position = 0;		// used to index the array
	if(treeArray != 0) {
		delete [] treeArray;
	}
	treeArray = new TreeNode[tree->getSize()+1];	// create an array to fit all nodes
	treeArray[tree->getSize()] = 0;								// set the last element to NULL
	arraySize = tree->getSize();
	genTreeArray(tree->getRoot(),position);
}

void SetBst::genTreeArray(TreeNode* node, int& position) {
	// executes a inorder traversal where the visit part stores the node pointed
	// to by TreeNode* node into the position location of the array
	if (node != 0){
		genTreeArray(node->Left(), position);
		treeArray[position++] = *node;
		genTreeArray(node->Right(), position);
	}
}

TreeNode* SetBst::Find(int item) const {
	TreeNode *node;
	bool found = false;
	// uses the Find method of Bst to locate and return a TreeNode pointer

	found = tree->Find(tree->getRoot(), item, node);
	return node;
}

void SetBst::Insert(int item) {
	// inserts an item into the Bst, must handle a TreeFullException and
	// DuplicateItemException. hint: print out the associated message

	try{
		tree->Insert(item);
	}
	catch (DuplicateItemException) {
		cout << "Error: This item already exists in the binary search tree. Unable to insert duplicate." << endl;
	}
	catch (TreeFullException){
		cout << "Error: The binary search tree is full. Unable to insert node." << endl;
	}

}

void SetBst::Delete(int item) {
	// deletes an item from the Bst, must handle a TreeEmptyException and
	// ItemNotFoundException. hint: print out the associated message

	try{
		tree->Delete(item);
	}
	catch (TreeEmptyException){
		cout << "Error: The tree is empty. Unable to delete node." << endl;
	}
	catch (ItemNotFoundException){
		cout << "Error: Item not found in tree. Unable to delete item." << endl;
	}
}

void SetBst::Clear() {
	// clears the tree and deletes the tree array
	//tree->ClearTree(tree->getRoot());
	delete tree;

	if (treeArray != 0) {
		delete[] treeArray;
	}
}

TreeNode* SetBst::begin()  {
	// checks to see if the size of the array and the size of the tree differ.
	// if they do, or if array is empty, a new array is generated and a TreeNode
	// pointer to the first element in the array is returned
	if (tree->getSize() != arraySize || arraySize == 0){
		genTreeArray();
	}

	return & treeArray[0];
}

TreeNode* SetBst::end()  {
	// checks to see if the size of the array and the size of the tree differ.
	// if they do, or if array is empty, a new array is generated and a TreeNode
	// pointer to the last element in the array is returned
	if (tree->getSize() != arraySize || arraySize == 0){
		genTreeArray();
	}

	return & treeArray[arraySize]; // Check logic for off-by-one error
}

void SetBst::PathLength(int item, int &steps) {
	// used to calculate the number of steps it takes to find item
	// since steps is a reference, its value will be accumulated each
	// call of the recursive PathLength method.  This method assumes that
	// steps has been initialized
	PathLength(tree->getRoot(),item,steps);
}

void SetBst::PathLength(TreeNode* node, int item, int &steps) {
	// used to calculate the number of steps it takes to find item
	// steps is increamented each recursive call  this method
	// traverses the tree similarly to the Find method  of Bst.
	// steps does not get modified if the node is NULL or
	// if the nodes data is item

	if (node == 0) {
		return;
	}
	// otherwise traverse the tree
	if (item < node->getData()) {
		steps++;
		PathLength(node->Left(), item, steps);
	}
	else if (item > node->getData()) {
		steps++;
		PathLength(node->Right(), item, steps);
	}
	else {
		return;
	}
}
