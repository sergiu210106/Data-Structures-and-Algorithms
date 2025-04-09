#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    ///time complexity: theta(1)
    this->currentNode = b.head;
    this->currentFrequency = 1;
}

TComp SortedBagIterator::getCurrent() {
    ///time complexity: theta(1)
    if (!valid()) {
        throw exception();
    }
    return this->currentNode->element;
}

bool SortedBagIterator::valid() {
    ///time complexity: theta(1)
    return this->currentNode != nullptr;
}

void SortedBagIterator::next() {
    ///time complexity: theta(1)
    if (!valid()) {
        throw exception();
    }
    if (this->currentFrequency < this->currentNode->frequency) {
        this->currentFrequency++;
    }
    else {
        this->currentNode = this->currentNode->next;
        this->currentFrequency = 1;
    }
}

void SortedBagIterator::first() {
    ///time complexity: theta(1)
    this->currentNode = this->bag.head;
    this->currentFrequency = 1;
}
