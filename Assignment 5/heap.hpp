#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
	if (index == 0) {
		return; //root
	}
	//if bigger than parent, swap until parent is bigger or is root
	while (_heap[index] > _heap[(index - 1) / 2]) {
		swap(_heap[index], _heap[(index - 1) / 2]);
		index = (index - 1) / 2;
		if (index == 0) {
			return;
		}
	}
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	int leftChild = index * 2 + 1;
	int rightChild = index * 2 + 2;
	int largerChildIndex = index;
	if (leftChild < _n && _heap[leftChild] > _heap[largerChildIndex]) { //if no right child
		largerChildIndex = leftChild; //index set to left child
	}
	if (rightChild < _n && _heap[rightChild] > _heap[largerChildIndex]) {
		//else compare left and right to see who bigger
		largerChildIndex = rightChild;
	}
	if (largerChildIndex != index) {
		swap(_heap[index], _heap[largerChildIndex]);
		index = largerChildIndex;
		_bubbleDown(index);
	}
}

template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item;
	_bubbleUp(_n);
	_n++;
}

template <class T>
T Heap<T>::extractMax() {
	if (_n == 0) {
		return T(); //empty heap
	}
	T max = _heap[0]; //root is max
	swap(_heap[0], _heap[_n - 1]);
	_n--;
	_bubbleDown(0);
	return max;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x) { // not a very good implementation, but just use this for now.
	int i;
	for (i = 0; i < _n; i++)
		if (_heap[i] == x)
			return i;

	return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to) {
	int targetIndex = _lookFor(from);
	if (targetIndex == -1) {
		return; //element not found
	}
	_heap[targetIndex] = to; //set index to new element
	_bubbleDown(targetIndex);
}


template <class T>
void Heap<T>::increaseKey(T from, T to) {
	int targetIndex = _lookFor(from);
	if (targetIndex == -1) {
		return; //element not found
	}
	_heap[targetIndex] = to; //set index to new element
	_bubbleUp(targetIndex); 
}

template <class T>
void Heap<T>::deleteItem(T x) {
	int index = _lookFor(x); //look for index of element to be deleted
	if (index == -1) { //element not in the heap
		return;
	}
	swap(_heap[index], _heap[_n - 1]); //swap the target element with the last element
	_n--; //decrease size of heap
	if (_heap[index] > _heap[(index - 1) / 2]) { //if current index greater than parent
		_bubbleUp(index);
	}
	else {
		_bubbleDown(index);
	}

}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}


#endif
