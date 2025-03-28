#include "Stack.h"
#include <exception>
#include <stdexcept>

using namespace std;


Stack::Stack() {
	capacity = 1000;
	numberOfElements = 0;

	elems = new TElem[capacity];
} // BC = WC = TC = theta(1)


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
} // BC = theta(1), WC = theta(numberOfElements), TC = theta(numberOfElements)

TElem Stack::top() const {
	if (numberOfElements == 0) {
		throw invalid_argument("Stack is empty");
	}

	return elems[numberOfElements - 1];
} // BC = WC = TC = theta(1)

TElem Stack::pop() {
	if (numberOfElements == 0) {
		throw invalid_argument("Stack is empty");
	}

	TElem temp = elems[numberOfElements - 1];
	numberOfElements --;
	return temp;
} // BC = WC = TC = theta(1)


bool Stack::isEmpty() const {
	return (numberOfElements == 0);
} // BC = WC = TC = theta(1)

Stack::~Stack() {
	delete[] elems;
	elems = nullptr;
} // BC = WC = TC = theta(1)