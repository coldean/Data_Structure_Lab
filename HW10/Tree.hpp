#ifndef __TREE_H__
#define __TREE_H__

#include "TreeNode.hpp"

#define NONE 0
#define LEFT 1
#define RIGHT 2

class Tree {
  public:
    Tree();
    Tree(int data);

    void insert(int data);
    void display();
    void search(int data);
    void remove(int data);

  private:
    void display(TreeNode *curNode);
    void search(TreeNode *curNode, int data);
    void remove(TreeNode *beforeNode, TreeNode *curNode, int data, int flag);
    TreeNode *remove_max_left(TreeNode *beforeNode, TreeNode *curNode, TreeNode* newNode);

    TreeNode *rootnode;
};
#endif
