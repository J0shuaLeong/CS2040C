#pragma once
#include <math.h>

#include <iostream>


using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
    if (index == 0) return; //root
    while (_heap[index] > _heap[(index-1)/2]) { // index > parent. bubble up the index
        _swap(index, (index-1)/2);
        index = (index-1)/2; // Set index to the parent
        if (index == 0) break;
    }
}

template <class T>
void Heap<T>::_swap(int x, int y) {
    T temp;
    temp = _heap[x];
    _heap[x] = _heap[y];
    _heap[y] = temp;
}
             
template <class T>
void Heap<T>::_bubbleDown(int index) {
    while ((index*2+1) < _n) {// There is children (left node in range)
        int biggerChildIdx;
        if ((index*2+2) >= _n) {// Right child of out range
            biggerChildIdx = index*2+1; // Set bigger child to left index
        }
        else { //Compare both left child and right child
            biggerChildIdx = _heap[index*2+1] > _heap[index*2+2] ? index*2+1: index*2+2;
        }
        if (_heap[index] < _heap[biggerChildIdx]) { //Bubble down
            _swap(index, biggerChildIdx);
            index = biggerChildIdx;
        }
        index = biggerChildIdx;
    }
}

template <class T>
void Heap<T>::insert(T item) {
    _heap[_n] = item; //Add item to array
    _bubbleUp(_n);
    _n++; // Increase the item count
}

template <class T>
T Heap<T>::extractMax() {
    if (_n== 0) return T(); // No elements
    T max = _heap[0];
    _swap(0, _n-1);
    _n--; // Need to update before bubbling down. Bubbledown uses _n
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
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x) return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
    int index = _lookFor(from);
    if (index == -1) return;
    else {
        _heap[index] = to;
    }
    _bubbleDown(index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
    int index = _lookFor(from);
    if (index == -1) return;
    else {
        _heap[index] = to;
    }
    _bubbleUp(index);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
    int deleteIndex = _lookFor(x);
    if (deleteIndex == -1) return; // cannot find
    int lastIndex = _n -1;
    _swap(deleteIndex, lastIndex);
    _n--;
    if (_heap[deleteIndex] > _heap[(deleteIndex-1)/2]) { // Index > parent
        _bubbleUp(deleteIndex);
    }
    else _bubbleDown(deleteIndex);
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
