	#include "ListIterator.h"
	#include "IteratedList.h"
	#include <exception>

	ListIterator::ListIterator(const IteratedList& list) : list(list), current(list.head) {}

	void ListIterator::first() {
		current = list.head;
	}// BC = WC = TC = theta(1)

	void ListIterator::next() {
		if (!valid()) {
			throw std::exception();
		}

		current = current->next;
	}// BC = WC = TC = theta(1)

	void ListIterator::previous() {
		if (!valid()) {
			throw std::exception();
		} 
		current = current->prev;
	}

	bool ListIterator::valid() const {
		return current != nullptr;
	}// BC = WC = TC = theta(1)

	TElem ListIterator::getCurrent() const {
		if (!valid()) {
			throw std::exception();
		}

		return current->data;
	}// BC = WC = TC = theta(1)



