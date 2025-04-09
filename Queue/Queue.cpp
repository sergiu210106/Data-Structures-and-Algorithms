#include "Queue.h"
#include <exception>
#include <iostream>
#include <exception>
using namespace std;


Queue::Queue() {
	capacity = 1000;
	numberOfElements = 0;

	front = 0;
	rear = -1;

	elements = new TElem[capacity];
} // BC = WC = TC = theta(1)

void Queue::resize() {
	int newCapacity = capacity * 2;
	TElem * newElements = new TElem[newCapacity];

	for (int i = 0; i < numberOfElements; i ++) {
		newElements[i] = elements[(front+i) % capacity];
	}

	delete[] elements;
	elements = newElements;
	capacity = newCapacity;
	front = 0;
	rear = numberOfElements - 1;
}

void Queue::push(TElem elem) {
	if (numberOfElements == capacity) {
		resize();
	}
	rear = (rear+1) % capacity;
	elements[rear] = elem;
	numberOfElements++; 
} // BC = theta(1), WC = theta(numberOfElements), TC = theta(numberOfElements)


TElem Queue::pop() {
	if (isEmpty()) {
		throw invalid_argument("The queue is empty!");
	}

	TElem temp = elements[front];
	front = (front+1) % capacity;
	numberOfElements --;
	return temp;
} // BC = WC = TC = theta(1)

TElem Queue::top() const {
	if (numberOfElements == 0) {
		throw invalid_argument("The queue is empty!");
	}

	return elements[front];
}// BC = WC = TC = theta(1)

bool Queue::isEmpty() const {
	return (numberOfElements == 0);
} // BC = WC = TC = theta(1)


TElem Queue::minimum() {
	if (this->isEmpty()){
		throw invalid_argument("Queue is empty!");
	}

	Queue newq = Queue();
	
	TElem min = this->pop();
	newq.push(min);
	while (!this->isEmpty()) {
		TElem current = this->pop();
		if (current < min) 
			min = current;
		
		newq.push(current);
	}

	while(!newq.isEmpty()) {
		TElem current = newq.pop();
		this->push(current);
	}

	return min;
} // BC = WC = TC = theta(numberOfElements)

Queue& Queue::operator=(const Queue& other) {
	if (this != &other) {
		delete[] elements;
		capacity = other.capacity;
		numberOfElements = other.numberOfElements;
		front = other.front;
		rear = other.rear;
		elements = new TElem[capacity];

		for (int i = 0; i < capacity; i ++)
			elements[i] = other.elements[i];
	}
	
	return *this;
} // BC = WC = TC = theta(numberOfElements)

Queue::~Queue() {
	delete[] elements;
	elements = nullptr;
} // BC = WC = TC = theta(1)

