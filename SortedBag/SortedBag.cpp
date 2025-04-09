#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    ///time complexity: theta(1)
    this->rel = r;
    this->head = nullptr;
    this->count = 0;
}

void SortedBag::add(TComp e) {
    ///time complexity: O(n),theta(1) if the element is added at the beginning
    if (this->head == nullptr) {
        this->head = new SLLNode{ e, 1, nullptr };
        this->count++;
        return;
    }

    if (!this->rel(this->head->element, e)) {
        if (this->head->element == e) {
            this->head->frequency++;
            this->count++;
        }
        else {
            this->head = new SLLNode{ e, 1, this->head };
            this->count++; 
        }
        return;
    }

    SLLNode* current = this->head;
    SLLNode* previous = nullptr;

    while (current != nullptr && this->rel(current->element, e)) {
        if (current->element == e) {
            current->frequency++;
            this->count++; 
            return;
        }
        previous = current;
        current = current->next;
    }

    SLLNode* newNode = new SLLNode{ e, 1, current };
    previous->next = newNode;
    this->count++;
}
bool SortedBag::remove(TComp e) {
    ///time complexity: O(n)
    if (this->head == nullptr) {
        return false;
    }

    if (this->head->element == e) {
        if (this->head->frequency > 1) {
            this->head->frequency--;
            this->count--;
            return true;
        }
        else {
            SLLNode* toDelete = this->head;
            this->head = this->head->next;
            delete toDelete;
            this->count--;
            return true;
        }
    }

    SLLNode* current = this->head;
    SLLNode* previous = nullptr;

    while (current != nullptr && current->element != e) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    if (current->frequency > 1) {
        current->frequency--;
        this->count--;
    }
    else {
        previous->next = current->next;
        delete current;
        this->count--;
    }

    return true;
}


bool SortedBag::search(TComp elem) const {
    ///time: O(n), Best: Theta(1)
    SLLNode* current = this->head;

    while (current != nullptr && this->rel(current->element, elem)) {
        if (current->element == elem) {
            return true;
        }
        current = current->next;
    }

    if (current != nullptr && current->element == elem)
        return true;

    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    ///time: O(n), Best: Theta(1)
    SLLNode* current = this->head;

    while (current != nullptr && this->rel(current->element, elem)) {
        if (current->element == elem) {
            return current->frequency;
        }
        current = current->next;
    }

    if (current != nullptr && current->element == elem)
        return current->frequency;

    return 0;
}



int SortedBag::size() const {
    ///time complexity: theta(1)
    return this->count;
}


bool SortedBag::isEmpty() const {
    ///time complexity: theta(1)
    return this->head == nullptr;
}


SortedBagIterator SortedBag::iterator() const {
    ///time complexity: theta(1)
    return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
    ///time complexity: O(n)
    SLLNode* current = this->head;
    while (current != nullptr) {
        SLLNode* temp = current;
        current = current->next;
        delete temp;
    }
}