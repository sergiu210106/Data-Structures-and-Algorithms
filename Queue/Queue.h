#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue
{
private:
	TElem* elements;
	int numberOfElements;
	int capacity;

	int front;
	int rear;
public:
	Queue();
	//resize function
	void resize();

	//pushes an element to the end of the queue
	void push(TElem e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//returns the minimum element from the Queue (assume that the elements are integer numbers)  
	//throws an exception if the Queue is empty   
	TElem minimum() ;  

	// assignment operator
	Queue& operator=(const Queue& other);

	// destructor
	~Queue();
};
