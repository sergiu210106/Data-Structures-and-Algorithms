#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
    capacity = 10;
    elements = new TElem[capacity];
    next = new int[capacity];
    head = -1;
    firstEmpty = 0;

    for (int i = 0; i < capacity - 1; i++) {
        next[i] = i + 1;
    }
    next[capacity - 1] = -1; // Last free spot
}

void MultiMap::add(TKey c, TValue v) {
    if (firstEmpty == -1) {
        // No free space, need to resize
        int newCapacity = capacity * 2;
        TElem* newElements = new TElem[newCapacity];
        int* newNext = new int[newCapacity];

        for (int i = 0; i < capacity; i++) {
            newElements[i] = elements[i];
            newNext[i] = next[i];
        }

        for (int i = capacity; i < newCapacity - 1; i++) {
            newNext[i] = i + 1;
        }
        newNext[newCapacity - 1] = -1;

        firstEmpty = capacity;
        capacity = newCapacity;

        delete[] elements;
        delete[] next;

        elements = newElements;
        next = newNext;
    }

    int newPos = firstEmpty;
    firstEmpty = next[firstEmpty];

    elements[newPos] = make_pair(c, v);
    next[newPos] = head;
    head = newPos;
}

bool MultiMap::remove(TKey c, TValue v) {
    int current = head;
    int previous = -1;

    while (current != -1) {
        if (elements[current].first == c && elements[current].second == v) {
            if (previous == -1) {
                // Removing head
                head = next[current];
            } else {
                next[previous] = next[current];
            }
            // Free the node
            next[current] = firstEmpty;
            firstEmpty = current;
            return true;
        }
        previous = current;
        current = next[current];
    }
    return false;
}

vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> values;
    int current = head;
    while (current != -1) {
        if (elements[current].first == c) {
            values.push_back(elements[current].second);
        }
        current = next[current];
    }
    return values;
}

int MultiMap::size() const {
    int count = 0;
    int current = head;
    while (current != -1) {
        count++;
        current = next[current];
    }
    return count;
}

bool MultiMap::isEmpty() const {
    return head == -1;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
    delete[] elements;
    delete[] next;
}


