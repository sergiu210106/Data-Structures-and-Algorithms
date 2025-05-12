
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
	head = nullptr;
}

int IteratedList::size() const {
	Node * current = head;

	int cnt = 0;
	while (current) {
		cnt ++;

		current = current->next;
	}

	return cnt;
}

bool IteratedList::isEmpty() const {
	return head == nullptr;
}

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

TElem IteratedList::getElement(ListIterator pos) const {
	return pos.getCurrent();
}

TElem IteratedList::remove(ListIterator& pos) {
	if (!pos.valid()) {
		throw std::exception();
	}
	Node * current = head;
	Node * nodeToRemove = pos.current;	

	TElem removedValue = nodeToRemove->data;

	if (nodeToRemove == head) {
		head = head->next;

		pos.current = head;

		delete nodeToRemove;
		removed

	}

	Node * prev = head;


}

ListIterator IteratedList::search(TElem e) const{
	//TODO - Implementation
	return ListIterator(*this);	
}

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    //TODO - Implementation
	return NULL_TELEM;
}

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    //TODO - Implementation
}

void IteratedList::addToEnd(TElem e) {
	//TODO - Implementation
}

IteratedList::~IteratedList() {
	//TODO - Implementation
}
