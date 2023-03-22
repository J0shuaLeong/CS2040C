#include <iostream>
#include "simpleIntLinkedList.h"
using namespace std;

ListNode::ListNode(int n)
{
	_item = n;
	_next = NULL;
}

void List::insertHead(int n)
{
	ListNode *aNewNode = new ListNode(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

void List::removeHead()
{
	if (_size > 0) {
		ListNode *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

void List::print() {

	cout << endl; // modify this
}

bool List::exist(int n) {

	return 0; // modify this
}

int List::headItem()
{
	return 0; // modify this
}

List::~List()
{
	while (_size != 0)
		removeHead();
};

