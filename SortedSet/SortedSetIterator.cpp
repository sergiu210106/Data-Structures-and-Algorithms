#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	current = multime.head;
} // BC = WC = TC = THETA(1)


void SortedSetIterator::first() {
	current = multime.head;
} // BC = WC = TC = THETA(1)


void SortedSetIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	current = multime.next[current];
} // BC = WC = TC = THETA(1)


TElem SortedSetIterator::getCurrent()
{
	if (!valid()) {
		throw std::exception();
	}
	return multime.elements[current];
} // BC = WC = TC = THETA(1)

bool SortedSetIterator::valid() const {
	return current != -1;
} // BC = WC = TC = THETA(1)

