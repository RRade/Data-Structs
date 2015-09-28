/*******************************************************************************
* AVLTree.h
*
* author: Rikk Anderson
* date created: 2015
* last updated: 9/28/2015
*
* This class defines a balanced AVL tree.  Operations performed on this tree are
* recursive.  The implementation of these operations can be found in AVLTree.cpp.
*
* Variable descriptions:
*   root: the root of the tree
*
*   size: the number of nodes in the tree
*
*   The below constants are used for checking the balance factors of a node
*
*   LEFTHEAVY  = 1;
*   RIGHTHEAVY = -1;
*   BALANCED   = 0;
*
*   The formula uesed to calculate the balance factors is the following
*   (based off of the current CSE2383 textbook):
*
*       balanceFactor = height(left_subtree) - height(right_subtree)
*
*   anything outside of the range [-1,0,1] is an unbalanced subtree
*
*   Note: other Data Strcuture books state that the balance factor is:
*
*       balanceFactor = height(right_subtree) - height(left_subtree)
*
*   Where:
*     LEFTHEAVY  = -1;
*     RIGHTHEAVY = 1;
*     BALANCED   = 0;

*******************************************************************************/


#ifndef AVLTREE_H
#define AVLTREE_H


#include <iostream>
#include <algorithm>	// used for max
#include <new>				// used for std::bad_alloc

#include "TreeNode.h"
#include "Exceptions.h"

class AVLTree {
  private:
    TreeNode* root;
    int size;
    static const int LEFTHEAVY  = 1;  // can be used for checking balance factors
    static const int RIGHTHEAVY = -1;
    static const int BALANCED   = 0;


  public:
    AVLTree();
    AVLTree(TreeNode* node);
    ~AVLTree();

    int getSize();
    int getHeight(TreeNode* node);
    void setHeight(TreeNode*& node);
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

    void BalanceTree(TreeNode*& node);
    void LeftSingleRotate(TreeNode*& node);   // rotates a right heavy subtree left
    void RightSingleRotate(TreeNode*& node);  // rotates a left heavy subtree right
    void LeftRightRotate(TreeNode*& node);    // rotates a subtree left then right
    void RightLeftRotate(TreeNode*& node);    // rotates a subtree right then left


    void ClearTree(TreeNode*& node);
    void PrintTree(TreeNode* node);
};





#endif
