#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;

void Queue::resize() {
	int newCapacity = capacity * 2;
	TElem * newElems = new TElem[newCapacity];

	for (int i = 0; i < length; i ++) {
		newElems[i] = elems[(head + i) % capacity];
	}

	delete[] elems;
	elems = newElems;

	capacity = newCapacity;
	head = 0;
	tail = length;
}

Queue::Queue() {
	capacity = 100;
	length = 0;

	head = 0;
	tail = 0;

	elems = new TElem[capacity];
}


void Queue::push(TElem elem) {
	if (length == capacity) {
		resize();
	}

	elems[tail] = elem;
	tail = (tail + 1) % capacity;
	length++;
}


TElem Queue::top() const {
	if (length == 0) 
		throw exception();

	return elems[head];
}

TElem Queue::pop() {
	if (length == 0) {
		throw exception();
	}

	TElem temp = elems[head];
	head = (head+1) % capacity;
	length --;
	return temp;
}

bool Queue::isEmpty() const {
	return (length == 0);
}


Queue::~Queue() {
	delete[] elems;
}

