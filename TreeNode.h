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

    TreeNode()
	{
		data = 0;
		left = 0;
		right = 0;
		height = 0;
		balanceFactor = 0;
	}
    TreeNode(int item, TreeNode * lptr, TreeNode * rptr);
    TreeNode::TreeNode(int data, int bf, TreeNode * lptr, TreeNode * rptr);
    ~TreeNode();

    // access methods
    TreeNode* Left() const;
    TreeNode* Right() const;
    int getData() const;
    int getBalFac() const;
    int getHeight() const;
};

// small methods like these I make inline to avoid linking errors and because
// I'm not going to write a separate *.cpp file for them
/*inline TreeNode() {
	data = 0;
	left = 0;
	right = 0;
	height = 0;
	balanceFactor = 0;
}*/

inline TreeNode::TreeNode(int data, TreeNode * lptr=0, TreeNode * rptr=0) {
  this -> data  = data;
  left  = lptr;
  right = rptr;
  height = 0;
  balanceFactor = 0;
}

inline TreeNode::TreeNode(int data, int bf, TreeNode * lptr=0, TreeNode * rptr=0) {
  this -> data  = data;
  left  = lptr;
  right = rptr;
  height = 0;
  balanceFactor = bf;
}

inline TreeNode::~TreeNode() {
  data  = 0;
  left  = 0;
  right = 0;
  height = 0;
  balanceFactor = 0;
}

inline TreeNode* TreeNode::Left() const {
  return left;
}

inline TreeNode* TreeNode::Right() const {
  return right;
}

inline int TreeNode::getData() const {
  return data;
}

inline int TreeNode::getBalFac() const {
  return balanceFactor;
}

inline int TreeNode::getHeight() const {
  return height;
}

#endif
