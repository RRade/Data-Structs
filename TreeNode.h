/*******************************************************************************
* TreeNode.h
*
* author: Rikk Anderson
* date created: 2015
* last updated: 9/28/2015
*
* This class defines and implements a node for binary trees.  It is a friend
* class of the binary search tree class Bst and AVLTree. There are no methods
* that modify the data of this node.  The data can only be modified by Bst and
* AVLTree.  The balancefactor and height attributes are only needed my AVLTree.
*******************************************************************************/


#ifndef TREENODE_H
#define TREENODE_H


// in a real production environment, this class should be a generic class that
// uses templates
class TreeNode {
  friend class Bst;  // friend because only Bst or AVLTree will uses this class
  friend class AVLTree;

  private:
    TreeNode* left;
    TreeNode* right;
    int height; 				// AVL only: the height of the subtree the node is a root of
    int balanceFactor;  // AVL only: height(left_subtree) - height(right_subtree)
    int data;

  public:

    TreeNode() {
		data = 0;
		left = 0;
		right = 0;
		height = 0;
		balanceFactor = 0;
	}
    TreeNode(int data, TreeNode * lptr, TreeNode * rptr) {
      this -> data  = data;
      left  = lptr;
      right = rptr;
      height = 0;
      balanceFactor = 0;
    }
    TreeNode(int data, int bf, TreeNode * lptr, TreeNode * rptr) {
      this -> data  = data;
      left  = lptr;
      right = rptr;
      height = 0;
      balanceFactor = bf;
    }
    ~TreeNode() {
      data  = 0;
      left  = 0;
      right = 0;
      height = 0;
      balanceFactor = 0;
    }

    // access methods
    TreeNode* Left() const {
      return left;
    }
    TreeNode* Right() const {
      return right;
    }
    int getData() const {
      return data;
    }
    int getBalFac() const {
      return balanceFactor;
    }
    int getHeight() const {
      return height;
    }
};

#endif
