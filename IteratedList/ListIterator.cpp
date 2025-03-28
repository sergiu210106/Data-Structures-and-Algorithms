	#include "ListIterator.h"
	#include "IteratedList.h"
	#include <exception>

	ListIterator::ListIterator(const IteratedList& list) : list(list), current(list.head) {}

	void ListIterator::first() {
		current = list.head;
	}

	void ListIterator::next() {
		if (!valid()) {
			throw std::exception();
		}

		current = current->next;
	}

	bool ListIterator::valid() const {
		return current != nullptr;
	}

	TElem ListIterator::getCurrent() const {
		if (!valid()) {
			throw std::exception();
		}

		return current->data;
	}



