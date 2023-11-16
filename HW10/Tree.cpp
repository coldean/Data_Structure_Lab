#include "Tree.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <stddef.h>

Tree::Tree() { this->rootnode = NULL; }
Tree::Tree(int data) {
	TreeNode* node = new TreeNode(data);
	this->rootnode = node;
}
void Tree::insert(int data) {
	TreeNode* node = new TreeNode(data);
	TreeNode* cursor = this->rootnode;
	if (cursor == NULL) {
		this->rootnode = node;
		return;
	}
	while (1) {
		int value = cursor->getData();
		if (value < data) {
			if (cursor->getRight() == NULL) {
				cursor->setRight(node);
				break;
			}
			else {
				cursor = cursor->getRight();
			}
		}
		else {
			if (cursor->getLeft() == NULL) {
				cursor->setLeft(node);
				break;
			}
			else {
				cursor = cursor->getLeft();
			}
		}
	}
	return;
}
void Tree::display() {
	display(this->rootnode);
	return;
}

void Tree::display(TreeNode* curNode) {
	if (curNode == NULL)
		return;
	display(curNode->getLeft());
	std::cout << " ";
	std::cout << curNode->getData();
	display(curNode->getRight());
	return;
}

void Tree::search(int data) {
	search(this->rootnode, data);
	return;
}
void Tree::search(TreeNode* curNode, int data) {
	if (curNode == NULL) {
		std::cout << "\n" << data << " search failed!\n";
		return;
	}

	if (curNode->getData() == data) {
		std::cout << "\n" << data << " search success!\n";
		return;
	}
	else if (curNode->getData() < data) {
		std::cout << " " << curNode->getData();
		search(curNode->getRight(), data);
	}
	else {
		std::cout << " " << curNode->getData();
		search(curNode->getLeft(), data);
	}
}
void Tree::remove(int data) {
	remove(NULL, this->rootnode, data, NONE);
	return;
}
void Tree::remove(TreeNode* beforeNode, TreeNode* curNode, int data, int flag) {
	if (curNode == NULL) {
		std::cout << "\n" << data << " remove failed!\n";
		return;
	}

	if (curNode->getData() == data) {
		if (curNode->getLeft() != NULL) {
			TreeNode* oldNode = new TreeNode();
			TreeNode* newNode = curNode;
			TreeNode* tempNode = new TreeNode();

			oldNode->setLeft(curNode->getLeft());
			oldNode->setRight(curNode->getRight());

			tempNode->setData(curNode->getData());
			tempNode->setLeft(curNode->getLeft());
			tempNode->setRight(curNode->getRight());

			tempNode = remove_max_left(tempNode, curNode->getLeft(), newNode);
			tempNode->setLeft(oldNode->getLeft());
			tempNode->setRight(oldNode->getRight());

			if (beforeNode != NULL) {
				if (flag == LEFT)
					beforeNode->setLeft(tempNode);
				else
					beforeNode->setRight(tempNode);
				delete oldNode;
			}
			else {
				this->rootnode = tempNode;
				delete curNode;
			}
		}
		else if (curNode->getRight() != NULL && curNode->getLeft() == NULL) {
			TreeNode* oldNode = curNode;
			curNode = curNode->getRight();

			if (flag == LEFT)
				beforeNode->setLeft(curNode);
			else
				beforeNode->setRight(curNode);

			delete oldNode;
		}
		else {
			if (flag == LEFT)
				beforeNode->setLeft(NULL);
			else
				beforeNode->setRight(NULL);

			delete curNode;
		}
		std::cout << "\n" << data << " remove success!\n";
		return;
	}
	else if (curNode->getData() < data) {
		remove(curNode, curNode->getRight(), data, RIGHT);
	}
	else {
		remove(curNode, curNode->getLeft(), data, LEFT);
	}
}
TreeNode* Tree::remove_max_left(TreeNode* beforeNode, TreeNode* curNode, TreeNode* newNode) {
	if (curNode->getRight() == NULL) {
		if (curNode->getLeft() == NULL) {
			newNode->setData(curNode->getData());
			newNode->setLeft(curNode->getLeft());
			newNode->setRight(curNode->getRight());
			delete curNode;
			beforeNode->setRight(NULL);
			return newNode;
		}
		else {
			beforeNode->setRight(curNode->getLeft());
			return curNode;
		}

	}
	else {
		return remove_max_left(curNode, curNode->getRight(), newNode);
	}
}
