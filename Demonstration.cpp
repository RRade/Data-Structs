/*******************************************************************************
* AVLTree.cpp
*
* author: Joshua Hawkins
* date created: 2015
* last updated: 9/28/2015
*
* This file provides a demonstration of the capabilities of the BST and AVL
* tree classes.
*******************************************************************************/

//#include "Bst.h"
#include "TreeNode.h"
#include "Exceptions.h"
//#include "Bst.cpp"
//#include "AVLTree.h"
//#include "AVLTree.cpp"
#include "SetAVL.cpp"
#include "SetBst.cpp"
#include <random>
#include <vector>

using namespace std;

void originalTreeTest(){
	/***************************************************************************
	NOTE: THIS IS A DEPRECATED FUNCTION. LEFT AS AN ARTIFACT; MEANT ONLY FOR USE
	IN EXAMPLE AND EXPANSION. Feel free to edit this function to test whatever
	features or algorithms desired. The other functions in this file serve to
	fully demonstrate what the BST and AVL trees are designed for.
	***************************************************************************/
	// Create the BST
	TreeNode* root = new TreeNode();
	Bst* tree = new Bst(root);

	// Build the BST
	tree->Insert(17);
	tree->Insert(7);
	tree->Insert(12);
	tree->Insert(25);
	tree->Insert(23);
	tree->Insert(24);

	// Display the BST
	cout << "Tree after original insertions:" << endl;
	tree->PrintTree(root);
	cout << endl << endl;

	// Remove parts from BST
	tree->Delete(7); // Single degree deletion
	cout << "Tree after removing 7:" << endl;
	root = tree->getRoot();
	tree->PrintTree(root);
	cout << endl << endl;

	// Remove 0 from root
	tree->Delete(0);
	root = tree->getRoot();
	cout << endl;
	cout << "Tree after remoivng 0 (root):" << endl;
	tree->PrintTree(root);
	cout << endl << endl;

	// Delete the BST
	delete tree;

	// Make a new tree for 2 degree deletion testing
	TreeNode* newroot = new TreeNode();
	Bst* newtree = new Bst(newroot);
	// Build new tree
	newtree->Insert(3);
	newtree->Insert(2);
	newtree->Insert(4);
	newtree->Insert(-3);
	newtree->Insert(-4);
	newtree->Insert(-2);
	// Print new tree
	cout << "NEW TREE: for use in 2-degree deletion testing" << endl;
	newtree->PrintTree(newroot);
	//Delete 0 for 2-degree deletion test
	newtree->Delete(0);
	newroot = newtree->getRoot();
	cout << "== newroot:" << newroot << " data:" << newroot->getData() << endl;
	cout << endl << endl << "New Tree after deleting 0 (2-degree): " << endl;
	newtree->PrintTree(newroot);
	cout << endl;
}

void properBSTTest(){
	// Build the tree
	cout << "Proper Binary Search Tree Test." << endl;
	TreeNode * root = new TreeNode(22);	// 1 is the data at root
	Bst * tree = new Bst(root);

	for (int i = 1; i < 11; i++){
		try{
			switch (i){
			case 0: {tree->Insert(22); break; }
			case 1: {tree->Insert(15);	break; }
			case 2: {tree->Insert(45);	break; }
			case 3: {tree->Insert(13);	break; }
			case 4: {tree->Insert(20);
				tree->PrintTree(root);	break; }
			case 5:{tree->Delete(45);
					tree->PrintTree(root);	break;}
			case 6:{tree->Insert(33);		break;}
			case 7:{tree->Insert(14);		break;}
			case 8:{tree->Insert(30);
					tree->PrintTree(root);	break;}
			case 9:{tree->Delete(15);
					tree->PrintTree(root);	break;}
			case 10:{tree->Delete(33);
					tree->PrintTree(root);	break;}

			}
		}
		catch (DuplicateItemException){
			cout << "Error: Item already exists." << endl;
		}
		catch (ItemNotFoundException){
			cout << "Error: Item not found in tree." << endl;
		}
		catch (TreeFullException){
			cout << "Error: The tree is full." << endl;
		}
		catch (TreeEmptyException){
			cout << "Error: The tree is empty." << endl;
		}
		root = tree->getRoot();
		//tree->PrintTree(root);
		cout << endl;
	}
	cout << endl << "BST Testing complete." << endl << endl;
}

void properAVLTest(){
	// Build a basic AVL tree
	TreeNode * root = new TreeNode(22);
	AVLTree * tree = new AVLTree(root);

	// Begin testing
	for (int i = -1; i < 11; i++){
		try{
			switch (i){
			case -1: {
						 tree->Insert(15);
						 break; }
			case 0: {
						tree->Insert(50);
						break; }
			case 1: {
						tree->Insert(12);
						break; }
			case 2: {
						tree->Insert(45);
						break; }
			case 3:{
					   tree->Insert(60);
					   break; }
			case 4: {
						tree->Insert(55);
						break; }
			case 5: {
						tree->Insert(67);
						cout << endl;
						tree->PrintTree(tree->getRoot());
						break; }
			case 6: {
						tree->Insert(11);
						cout << endl;
						tree->PrintTree(tree->getRoot());
						break; }
			case 7: {
						tree->Insert(63);
						cout << endl;
						tree->PrintTree(tree->getRoot());
						break;
			}
			case 8: {
						tree->Insert(47);
						cout << endl;
						tree->PrintTree(tree->getRoot());
						break;
			}
			case 9: {
						tree->Delete(60);
						cout << endl;
						tree->PrintTree(tree->getRoot());
						break;
			}
			case 10: {
						tree->Insert(48);
						tree->PrintTree(tree->getRoot());
						break;
			}
			}
		}
		catch (DuplicateItemException){
			cout << "Error: Item already exists." << endl;
		}
		catch (ItemNotFoundException){
			cout << "Error: Item not found in tree." << endl;
		}
		catch (TreeFullException){
			cout << "Error: The tree is full." << endl;
		}
		catch (TreeEmptyException){
			cout << "Error: The tree is empty." << endl;
		}
	}

	root = tree->getRoot();
	cout << endl;


}

void properSetTest(){
	// Create all local variables
	SetBst * setbst = new SetBst();
	SetAVL * setavl = new SetAVL();
	vector<int> all_added_items;		// Lists all items in sets
	TreeNode * b_begin;
	TreeNode * a_begin;
	TreeNode * b_end;
	TreeNode * a_end;
	TreeNode * temp = 0;				// For iteration
	int n = 0;							// Number of nodes to test
	int item = 0;						// Item that may be added
	int size = 0;						// How many items exist
	//int counter = 0;
	int steps = 0;						// For use in path length
	vector<int> b_totalsteps;
	vector<int> a_totalsteps;
	int b_sumsteps = 0;
	int a_sumsteps = 0;
	float b_avgsteps = 0.00;
	float a_avgsteps = 0.00;
	float delta = 0.00;

	// Which test should we run? 1 or 2
	int testID = 1;						// Change this value to decide which test to run

	// Prompt how large set is
	while (n <= 0){
		cout << "How many nodes to test? ";
		cin >> n;
	}

	// Generate tree array and get beginning pointer
	b_begin = setbst->begin();
	a_begin = setavl->begin();
	b_end = setbst->end();
	a_end = setavl->end();
	TreeNode* newend;

	// Generate set of that size
	while (size < n){
		item = rand();// % n*(n - 1); // items exist from 0 to n^2-n, allowing for some spreading. However, this creates a pattern in output.
		setbst->Insert(item);
		setavl->Insert(item);

		//Check if a new node was appended
		newend = setbst->end();
		if (b_end != newend){
			all_added_items.push_back(item);
			b_end = newend;
			size++;
		}
	}

	// Update tree array and get beginning pointer
	b_begin = setbst->begin();
	a_begin = setavl->begin();
	b_end = setbst->end();
	a_end = setavl->end();

	if (testID == 1){
		// Calculate average number of steps for Test 1 (items do exist)
		for (int i = 0; i < all_added_items.size(); i++){
			// BST
			setbst->PathLength(all_added_items[i], steps);
			b_totalsteps.push_back(steps);
			steps = 0;	// Reset to prepare for AVL

			// AVL
			setavl->PathLength(all_added_items[i], steps);
			a_totalsteps.push_back(steps);
			steps = 0;	// Reset to prepare for BST

			b_sumsteps += b_totalsteps[i];
			a_sumsteps += a_totalsteps[i];
		}
	}
	else if (testID == 2){
		// Calculate average number of steps for Test 2 (items may or may not exist)
		// Generate step vector
		for (int i = 0; i < size; i++){
			int random = rand();
			// BST
			setbst->PathLength(random, steps);
			b_totalsteps.push_back(steps);
			steps = 0;	// Reset to prepare for AVL

			// AVL
			setavl->PathLength(random, steps);
			a_totalsteps.push_back(steps);
			steps = 0;	// Reset to prepare for BST

			b_sumsteps += b_totalsteps[i];
			a_sumsteps += a_totalsteps[i];
		}
	}

	// Complete calculations
	b_avgsteps = (float)b_sumsteps / (float)b_totalsteps.size();
	a_avgsteps = (float)a_sumsteps / (float)a_totalsteps.size();
	delta = b_avgsteps - a_avgsteps;

	// Display output
	cout << "Average number of steps to find item in BST: " << b_avgsteps << endl;
	cout << "Average number of steps to find item in AVL: " << a_avgsteps << endl;
	cout << "Delta (Bst - AVLTree): " << delta << endl;


	// Try iterating through the array
	/*
	cout << "Begin:" << b_begin << endl;
	cout << "End:" << b_end << endl << endl;
	for (int i = 0; temp != b_end && i<size; i++){
		temp = &b_begin[i];
		cout << temp << " " << temp->getData() << " i:" << i << endl;
	}
	cout << b_end << " - end" << endl;
	*/
}

int main()
{
	// Old tree test, artifact. Left for example and expansion
	// originalTreeTest();

	// Test exception handling
	properBSTTest();

	// Test AVL
	properAVLTest();

	// Test Set Classes
	properSetTest();

	// Exit the program
	return 0;
}
