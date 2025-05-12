#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	capacity = 10;
	elements = new TComp[capacity];
	next = new int[capacity];

	for (int i = 0; i < capacity - 1; i ++)
		next[i] = i+1;
	next[capacity - 1] = -1;
	firstEmpty = 0;
	head = -1;
	relation = r;
} // BC = WC = TC = THETA(capacity)

void SortedSet::resize() {
	int newCapacity = capacity * 2;
	TComp * newElems = new TComp[newCapacity];
	int * newNext = new int[newCapacity];

	for (int i = 0; i < capacity; i ++) {
		newElems[i] = elements[i];
		newNext[i] = next[i];
	}

	for (int i = capacity; i < newCapacity - 1; i ++)
		newNext[i] = i+1;
	newNext[newCapacity-1] = -1;

	delete[] elements;
	delete[] next;

	elements = newElems;
	next = newNext;

	firstEmpty = capacity;
	capacity = newCapacity;
} // BC = WC = TC = THETA(capacity)

int SortedSet::allocate() {
	if (firstEmpty == -1)
		resize();
	int newElem = firstEmpty;
	firstEmpty = next[firstEmpty];
	return newElem;
} // BC = THETA(1), WC = THETA(n), TC = THETA(1) AMORTIZED

void SortedSet::deallocate(int pos) {
	next[pos] = firstEmpty;
	firstEmpty = pos;
} // BC = WC = TC = THETA(1)

bool SortedSet::add(TComp elem) {
	int current = head;
	int prev = -1;

	while (current != -1 and relation(elements[current], elem)) {
		if (elements[current] == elem)
			return false;
		prev = current;
		current = next[current];
	}

	if (current != -1 and elements[current] == elem)
		return false;
	int newPos = allocate();
	elements[newPos] = elem;

	if (prev == -1) {
		next[newPos] = head;
		head = newPos;
	} else {
		next[newPos] = next[prev];
		next[prev] = newPos;
	}
	return true;
} // BC = THETA(1), WC = THETA(n), TC = O(n)


bool SortedSet::remove(TComp elem) {
    int current = head;
    int prev = -1;

    while (current != -1 && relation(elements[current], elem)) {
        if (elements[current] == elem) {
            if (prev == -1) {
                head = next[current];
            } else {
                next[prev] = next[current];
            }
            deallocate(current);
            return true;
        }

        prev = current;
        current = next[current];
    }

    if (current != -1 && elements[current] == elem) {
        if (prev == -1) {
            head = next[current];
        } else {
            next[prev] = next[current];
        }

        deallocate(current);
        return true;
    }

    return false;
} // BC = THETA(1), WC = THETA(n), TC = O(n)

bool SortedSet::search(TComp elem) const {
	int current = head;
    while (current != -1 && relation(elements[current], elem)) {
        if (elements[current] == elem)
            return true;

        current = next[current];
    }

    if (current != -1 && elements[current] == elem)
        return true;

    return false;
} // BC = THETA(1), WC = THETA(n), TC = O(n)


int SortedSet::size() const {
	int count = 0, current = head;
	while (current != -1) {
		count ++;
		current = next[current];
	}
	return count;
} // BC = WC = TC = THETA(n)



bool SortedSet::isEmpty() const {
	return head == -1;
} // BC = WC = TC = THETA(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
} // BC = WC = TC = THETA(1)


SortedSet::~SortedSet() {
	delete[] elements;
	delete[] next;
} // BC = WC = TC = THETA(1)

int SortedSet::difference(const SortedSet& s) {
	int removedCount = 0;
	SortedSetIterator it = s.iterator();

	while (it.valid()) {
		TComp elem = it.getCurrent();
		if (search(elem)) {
			remove(elem);
			removedCount++;
		}
		it.next();
	}

	return removedCount;
} // BC = THETA(m), WC = THETA(m * n), TC = O(m * n), where m = s.size(), n = this->size()
