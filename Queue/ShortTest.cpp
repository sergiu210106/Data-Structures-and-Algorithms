#include "ShortTest.h"
#include "Queue.h"
#include <assert.h>
#include <stdexcept>
#include <iostream>
void testAll() { 
	Queue q;
	assert(q.isEmpty() == true);
	try {
		TElem minVal = q.minimum();
	} catch(const std::invalid_argument& e) {
		assert(true);
	}
	q.push(5);
	q.push(1);

	TElem minVal = q.minimum();
	assert (minVal == 1);

	q.push(10);
	assert(q.isEmpty() == false);
	assert(q.top() == 5);
	assert(q.pop() == 5);
	assert(q.top() == 1);
	assert(q.pop() == 1);
	assert(q.top() == 10);
	assert(q.pop() == 10);
	assert(q.isEmpty() == true);
}