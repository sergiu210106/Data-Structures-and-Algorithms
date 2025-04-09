
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
	head = nullptr;
	tail = nullptr;
	length = 0;
}

int IteratedList::size() const {
	return length;
} // BC = WC = TC = theta(1)

bool IteratedList::isEmpty() const {
	return length == 0;
} // BC = WC = TC = theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}// BC = WC = TC = theta(1)

TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid()) {
		throw std::exception();
	}

	return pos.getCurrent();
}// BC = WC = TC = theta(1)

TElem IteratedList::remove(ListIterator& pos) {
	if(!pos.valid()) {
		throw std::exception();
	}

	Node* toDelete = pos.current;
	TElem removedValue = toDelete->data;

	if (toDelete->prev != nullptr) {
		toDelete->prev->next = toDelete->next;
	} else {
		head = toDelete->next;
	}

	if (toDelete->next != nullptr) {
		toDelete->next->prev = toDelete->prev;
	} else {
		tail = toDelete->prev;
	}

	pos.next();
	delete toDelete;
	length --;

	return removedValue;
} // BC = WC = TC = theta(1)

ListIterator IteratedList::search(TElem e) const{
	ListIterator it = first();

	while (it.valid()) {
		if (it.current->data == e) {
			return it;
		}

		it.next();
	}

    ListIterator invalidIt(*this);
    invalidIt.current = nullptr;  
    return invalidIt;
} // BC = WC = TC = O(length)

TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid()) {
		throw std::exception();
	}
	TElem oldValue = pos.getCurrent();
	pos.current->data = e;
	return oldValue;
}// BC = WC = TC = theta(1)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid()) {
		throw std::exception();
	}

	Node* newNode = new Node {e, pos.current->next, pos.current};

	if (pos.current->next != nullptr) {
		pos.current->next->prev = newNode;
	} else {
		tail = newNode;
	}

	pos.current->next = newNode;
	pos.next(); 

	length++;
}// BC = WC = TC = theta(1)


void IteratedList::addToBeginning(TElem e) {
	Node* newNode = new Node{e, head, nullptr};

	if (head != nullptr) {
		head->prev = newNode;
	}
	head = newNode;

	if (tail == nullptr) {
		tail = newNode;
	}

	length++;
} // BC = WC = TC = theta(1)

void IteratedList::addToEnd(TElem e) {
	Node* next = new Node{e, nullptr, tail};

	if (tail!=nullptr) {
		tail->next = next;
	}

	tail = next;
	if (head == nullptr) {
		head = next;
	}

	length ++;
} // BC = WC = TC = theta(1)

IteratedList::~IteratedList() {
	Node* current = head;

	while (current != nullptr) {
		Node* toDelete = current;
		current = current->next;
		delete toDelete;
	}
} // BC = WC = TC = theta(1)
