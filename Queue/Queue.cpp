#include "Queue.h"
#include <exception>
#include <iostream>
#include <exception>
using namespace std;


Queue::Queue() {
	capacity = 1000;
	numberOfElements = 0;

	elements = new int[capacity];
} // BC = WC = TC = theta(1)


void Queue::push(TElem elem) {
	if (numberOfElements == capacity) {
		int newCapacity = capacity * 2;

		TElem* newElements = new TElem[newCapacity];
		for (int i = 0; i < numberOfElements; i ++) {
			newElements[i] = elements[i];
		}

		delete[] elements;
		elements = newElements;
		capacity = newCapacity;
	}

	elements[numberOfElements++] = elem; 
} // BC = theta(1), WC = theta(numberOfElements), TC = theta(numberOfElements)


TElem Queue::top() const {
	if (numberOfElements == 0) {
		throw invalid_argument("The queue is empty!");
	}

	return elements[0];
} // BC = WC = TC = theta(1)

TElem Queue::pop() {
	if (numberOfElements == 0) {
		throw invalid_argument("The queue is empty!");
	}

	TElem temp = elements[0];
	for (int i = 0; i < numberOfElements - 1; i ++) {
		elements[i] = elements[i+1];
	}

	numberOfElements --;
	return temp;
}// BC = WC = TC = theta(numberOfElements)

bool Queue::isEmpty() const {
	return (numberOfElements == 0);
} // BC = WC = TC = theta(1)


Queue::~Queue() {
	delete[] elements;
	elements = nullptr;
} // BC = WC = TC = theta(1)

