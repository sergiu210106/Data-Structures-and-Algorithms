#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

using namespace std;

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	first();
}

TElem MultiMapIterator::getCurrent() const {
	if (!valid())
		throw exception();
	return col.elements[current];
}

bool MultiMapIterator::valid() const {
	return current != -1;
}

void MultiMapIterator::next() {
	if (!valid())
		throw exception();
	current = col.next[current];
}

void MultiMapIterator::first() {
	current = col.head;
}

