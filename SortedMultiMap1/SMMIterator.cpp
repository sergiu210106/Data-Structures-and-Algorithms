#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	stackCapacity = 100;
	stack = new int[stackCapacity];
	stackSize = 0;
	first();
}

void SMMIterator::first(){
	stackSize = 0;
	currentNode = map.root;

	while(currentNode != -1) {
		if (stackSize == stackCapacity) {
			int * newStack = new int[stackCapacity * 2];
			for (int i = 0; i < stackCapacity; i ++) {
				newStack[i] = stack[i];
			}
			delete[] stack;
			stack = newStack;
			stackCapacity *= 2;
		}

		stack[stackSize++] = currentNode;
		currentNode = map.nodes[currentNode].left;
	}

	if (stackSize > 0) {
		currentNode = stack[--stackSize];
	} else {
		currentNode = -1;
	}
}

void SMMIterator::next(){
	if (!valid()) {
		throw exception();
	}

	int rightChild = map.nodes[currentNode].right;

	while (rightChild != -1) {
		if (stackSize == stackCapacity) {
			int * newStack = new int[stackCapacity * 2];
			for (int i = 0; i < stackCapacity; i ++) {
				newStack[i] = stack[i];
			}
			delete[] stack;
			stack = newStack;
			stackCapacity *= 2;
		}

		stack[stackSize++] = rightChild;
		rightChild = map.nodes[rightChild].left;
	}

	if (stackSize > 0) {
		currentNode = stack[--stackSize];
	} else {
		currentNode = -1;
	}
}

bool SMMIterator::valid() const {
	return currentNode != -1;
}

TElem SMMIterator::getCurrent() const {
	if (!valid()) {
		throw exception();
	}

	return map.nodes[currentNode].elem;
}


