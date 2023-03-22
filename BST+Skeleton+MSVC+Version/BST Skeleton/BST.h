#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>*  _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	void _preOrderPrint(TreeNode<T>*);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>*);
	TreeNode<T>* _searchMin(TreeNode<T>*);
	void _destroySubTree(TreeNode<T>*);
	
	//my additions
	void _successor(TreeNode<T>*, T, T&);
	void _updateHeight(TreeNode<T>*);
	int _maxHeight(T, T);
	int _getHeight(TreeNode<T>*);
	int _getBalance(TreeNode<T>*);

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax();
	T searchMin();
	bool exist(T x);
	T successor(T);

};


template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++;
}


template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);


};


template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}


template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}


template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {


	if (current->_item > x)
	{
		if (current->_left)
			current->_left = _insert(current->_left, x);
		else
		{
			current->_left = new TreeNode<T>(x);
			_size++;
		}
	}
	else if (x > current->_item) {
		if (current->_right)
			current->_right = _insert(current->_right, x);
		else
		{
			current->_right = new TreeNode<T>(x);
			_size++;
		}
	}
	else 
		return current; // When the node already existed in the tree
	
	_updateHeight(current); //update height of ancestor node
	int balance = _getBalance(current); //get balance of ancestor node

	//case 1: out of balance, left heavy
	if (balance > 1) {
		//if current left is heavy right heavy, left rotate
		if (_getBalance(current->_left) < 0) 
			_leftRotation(current->_left);
		return _rightRotation(current);
	}

	//case 2: out of balance, right heavy
	if (balance < -1) {
		//if current right is left heavy, right rotate
		if (_getBalance(current->_right) > 0)
			_rightRotation(current->_right);
		return _leftRotation(current);
	}

	return current;

}

template <class T>
void BinarySearchTree<T>::_updateHeight(TreeNode<T>* current) {
	current->_height = _maxHeight(_getHeight(current->_left), _getHeight(current->_right)) + 1;
}

template <class T>
int BinarySearchTree<T>::_getHeight(TreeNode<T>* current) {
	if (current == NULL)
		return -1;
	return current->_height;
}

template <class T>
int BinarySearchTree<T>::_maxHeight(T x, T y) {
	return (x > y) ? x : y;
}

template <class T>
T BinarySearchTree<T>::searchMax() {
	TreeNode<T> *current = _searchMax(_root);
    T max = current->_item;
	return T(max);
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	while (current->_right != NULL) {
		current = current->_right;
	}
	return current;
}

template <class T>
T BinarySearchTree<T>::searchMin() {
	TreeNode<T>* current = _searchMin(_root);
	T min = current->_item;
	return T(min);
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	while (current->_left != NULL) {
		current = current->_left;
	}
	return current;
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
	TreeNode<T>* current = _root;
	while (current) {
		if (current->_item == x)
			return true;
		if (x < current->_item)
			current = current->_left;
		else
			current = current->_right;
	}
	return false;
}

template <class T>
T BinarySearchTree<T>::successor(T x)
{
	T succ = 0;
	_successor(_root, x, succ);
	return T(succ);
}

template <class T>
void BinarySearchTree<T>::_successor(TreeNode<T>* current, T x, T& succ) {
	//base case
	if (current == NULL) return;

	//if key is root, find the minimum item in its right child
	if (current->_item == x) {
		//Go to right child if there exist one
		if (current->_right) {
			TreeNode<T>* temp = current->_right;
			//Keep traversing left to get minimum item
			while (temp->_left) 
				temp = temp->_left;
			succ = temp->_item;
		}
	}
	//if key is smaller than current root, go left
	else if (current->_item > x) {
		succ = current->_item;
		_successor(current->_left, x, succ);
	}
	//else go right
	else
		_successor(current->_right, x, succ);
}

template <class T>
int BinarySearchTree<T>::_getBalance(TreeNode<T>* current) {
	if (current == NULL)
		return 0;
	return _getHeight(current->_left) - _getHeight(current->_right);
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
	TreeNode<T>* y = node->_right;
	TreeNode<T>* x = y->_left;

	//Rotate
	y->_left = node;
	node->_right = x;

	//update the new heights
	_updateHeight(node);
	_updateHeight(y);

	//Return new root
	return y;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
	TreeNode<T>* x = node->_left;
	TreeNode<T>* y = x->_right;

	//Rotate
	x->_right = node;
	node->_left = y;

	//update the new heights
	_updateHeight(node);
	_updateHeight(x);

	//Return new root
	return x;
}
