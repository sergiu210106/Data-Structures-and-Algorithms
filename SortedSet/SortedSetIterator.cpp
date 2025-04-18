#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	current = multime.head;
}


void SortedSetIterator::first() {
	current = multime.head;
}


void SortedSetIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	current = multime.next[current];
}


TElem SortedSetIterator::getCurrent()
{
	if (!valid()) {
		throw std::exception();
	}
	return multime.elements[current];
}

bool SortedSetIterator::valid() const {
	return current != -1;
}

