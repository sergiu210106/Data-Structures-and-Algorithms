#include "Stack.h"
#include <exception>


using namespace std;

void Stack::resize() {
	int newCapacity = capacity * 2;
	TElem* newElems = new TElem[newCapacity];

	for (int i = 0; i < length; i ++)
		newElems[i] = elems[i];

	delete[] elems;
	elems = newElems;
	capacity = newCapacity;
}

Stack::Stack() {
	capacity = 100;
	length = 0;
	elems = new TElem[capacity];	
}


void Stack::push(TElem e) {
	if (length == capacity)
		resize();

	elems[length++] = e;
}

TElem Stack::top() const {
	if (length == 0)
		throw exception();

	return elems[length - 1];
}

TElem Stack::pop() {
	if (length == 0)
	throw exception();

	TElem temp = elems[length - 1];
	length --;
	return temp;
}


bool Stack::isEmpty() const {
	return (length == 0);
}

Stack::~Stack() {
	delete[] elems;
}