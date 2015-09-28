/*******************************************************************************
* Bst.h
*
* author: Joshua Hawkins
* date created: 2015
* last updated: 9/28/2015
*
* This class defines a binary search tree.  This tree is not a balanced AVL
* tree.  Operations performed on this tree are recursive.  The implementation
* of these operations can be found in Bst.cpp.
*
* Variable descriptions:
*   root: the root of the tree
*
*   size: the number of nodes in the tree
*******************************************************************************/

#ifndef BST_H
#define BST_H

#include <iostream>
#include <new>		// for the std::bad_alloc exception

#include "TreeNode.h"
#include "Exceptions.h"

// in a real production environment, this class would be a generic class that
// uses templates
class Bst {
  private:
    TreeNode* root;
    int size;				// the number of nodes in the tree


  public:

    Bst();
    Bst(TreeNode* node);
    ~Bst();

    int getSize();
    TreeNode* getRoot();

    bool IsFull() const;
    bool IsEmpty() const;

    bool Find(TreeNode* node, int& item);
    bool Find(TreeNode* node, int& item, TreeNode*& target);
    void Insert(int item);  // throws TreeFullException and DuplicateItemException
    void Insert(TreeNode*& node, int item); // throws DuplicateItemException
    void Delete(int item);  // throws ItemNotFoundException
    void Delete(TreeNode*& node, int item); // throws an ItemNotFoundException
    void DeleteNode(TreeNode*& node);

    void ClearTree(TreeNode*& node);	// deletes all nodes in the tree
    void PrintTree(TreeNode* node);		// print all the nodes in the tree

};

#endif
