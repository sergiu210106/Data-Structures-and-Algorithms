#include "Stack.h"
#include <exception>
#include <stdexcept>

using namespace std;


Stack::Stack() {
	capacity = 1000;
	numberOfElements = 0;

	elems = new TElem[capacity];
}


void Stack::push(TElem e) {
	if (numberOfElements == capacity) {
		int newCapacity = capacity * 2;
		TElem* newElements = new TElem[newCapacity];

		for (int i = 0; i < numberOfElements; i ++) {
			newElements[i] = elems[i];
		}

		delete[] elems;
		elems = newElements;
		capacity = newCapacity;
	}

	elems[numberOfElements++] = e;
}

TElem Stack::top() const {
	if (numberOfElements == 0) {
		throw invalid_argument("Stack is empty");
	}

	return elems[numberOfElements - 1];
}

TElem Stack::pop() {
	if (numberOfElements == 0) {
		throw invalid_argument("Stack is empty");
	}

	TElem temp = elems[numberOfElements - 1];
	numberOfElements --;
	return temp;
}


bool Stack::isEmpty() const {
	
	return (numberOfElements == 0);
}

Stack::~Stack() {
	delete[] elems;
	elems = nullptr;
}