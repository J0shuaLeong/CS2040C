#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"
using namespace std;


template <class T>
ListNode<T>::ListNode(T n)
{
	_item = n;
	_next = NULL;
}

template <class T>
void List<T>::insertHead(T n)
{
	ListNode<T> *aNewNode = new ListNode<T>(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

template <class T>
void List<T>::removeHead()
{
	if (_size > 0) {
		ListNode<T> *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

template <class T>
void List<T>::print(bool withNL) {

	ListNode<T> *temp = _head;
	while (temp) {
		cout << temp->_item;
		if (withNL)
			cout << endl;
		else
			cout << " ";
		temp = temp->_next;
	}
	cout << endl;
	  
}

template <class T>
bool List<T>::exist(T n) {

	// modify this
	ListNode<T>* temp = _head;
	while (temp)
	{
		if (temp->_item == n) //if item is found return true
		{
			return true;
		}
		temp = temp->_next; //else go to next node
	}
	return false; 
}

template <class T>
T List<T>::headItem()
{
	if (_size)
		return *_head;
}

template <class T>
T List<T>::extractMax()
{

	// if there are duplicates maximas in the list, return the leftmost one (the one closest to the _head)
	ListNode<T>* curr = _head; //pointer to the current node
	ListNode<T>* max = curr; //pointer to the current maximum item
	ListNode<T>* prev = _head; //keep track of previous node as we traverse the list
	ListNode<T>* prev_max = NULL; //a pointer to the node before the node containing max item
	T maxItem = curr->_item; //store max item
	while (curr) { //stop loop when reach the end of the list
		if (curr->_item > maxItem) { //if the current item is bigger than the max so far
			maxItem = curr->_item; //store new max 
			max = curr; //update the position of the node containing max
			prev_max = prev; //update position of previous node just before max
		}
		prev = curr; //shift the prev pointer to current node
		curr = curr->_next; //shift current pointer to next node
	}
	if (max == _head) { //if the max is in the head
		_head = _head->_next; //set next node as head
	}
	else {
		prev_max->_next = max->_next; //link the node before max to the node after max 
	}
	delete max; //delete the node containing max
	return maxItem;
}

template <class T>
void List<T>::reverseOp() {
	ListNode<T>* prev = NULL;
	ListNode<T>* curr = _head;
	ListNode<T>* next = NULL;
	while (curr)
	{
		next = curr->_next; //next node will point to current node
		curr->_next = prev; //current node point to previous node
		prev = curr; //move down the list
		curr = next;
	}
	_head = prev; //finally update new head
}



template <class T>
List<T>::~List()
{
	while (_head)
		removeHead();
};


#endif