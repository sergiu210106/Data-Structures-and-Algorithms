#include "SortedMultiMap.h"
#include <cmath> 
#include <stdexcept>
#include "SMMIterator.h"

SortedMultiMap::SortedMultiMap(Relation r) {
    capacity = 13;
    SMMsize = 0;
    rel = r;
    loadFactorTreshold = 0.7f;

    table = new Node [capacity];
    nextFree = new int [capacity];
    firstEmpty = 0;

    for (int i = 0; i < capacity; i ++) {
        table[i].key = NULL_TVALUE;
        table[i].next = -1;
        table[i].values = nullptr;
        table[i].vcapacity = 0;
        table[i].vsize = 0;
        nextFree[i] = i+1;
    }

    nextFree[capacity - 1] = -1;
} // BC = WC = TC = Theta(capacity) ~ Theta(1)

int SortedMultiMap::hashFunction(TKey key) const {
    return std::abs(key) % capacity;
} // BC = WC = TC = Theta(1)

void SortedMultiMap::resizeAndRehash() {
    int oldCapacity = capacity;
    Node * oldTable = table;

    capacity *= 2;
    table = new Node [capacity];
    
    delete[] nextFree;
    nextFree = new int [capacity];
    firstEmpty = 0;

    for (int i = 0; i < capacity; i ++) {
        table[i].key = NULL_TVALUE;
        table[i].next = -1;
        table[i].values = nullptr;
        table[i].vcapacity = 0;
        table[i].vsize = 0;

        nextFree[i] = i+1;
    }

    nextFree[capacity - 1] = -1;

    this->SMMsize = 0;

    for (int i = 0; i < oldCapacity; i ++) {
        if (oldTable[i].key != NULL_TVALUE) {
            for (int j = 0; j < oldTable[i].vsize; j ++) {
                add(oldTable[i].key, oldTable[i].values[j]);
            }
            delete[] oldTable[i].values;
        }
    }

    delete[] oldTable;
} // BC = WC = TC = Theta(n)

void SortedMultiMap::add(TKey c, TValue v) {
    if ((float) (SMMsize + 1) / capacity > loadFactorTreshold) {
        resizeAndRehash();
    }

    int pos = hashFunction(c);

    if (table[pos].key == NULL_TVALUE) {
        table[pos].key = c;
        table[pos].values = new TValue[2];
        table[pos].vcapacity = 2;
        table[pos].vsize = 1;
        table[pos].values[0] = v;
        table[pos].next = -1;
    } else {
        int current = pos;
        int prev = -1;

        while (current != -1 and table[current].key != c) {
            prev = current;
            current = table[current].next;
        }  

        if (current != -1) {
            if (table[current].vsize == table[current].vcapacity) {
                table[current].vcapacity *= 2;

                TValue * newValues = new TValue[table[current].vcapacity];

                for (int i = 0; i < table[current].vsize; i ++) {
                    newValues[i] = table[current].values[i];
                }

                delete[] table[current].values;
                table[current].values = newValues;
            }
            table[current].values[table[current].vsize++] = v;
        } else {
            int newPos = firstEmpty;

            if (newPos == -1) {
                throw std::runtime_error("Hashtable full, cannot resolve collision");
            }

            firstEmpty = nextFree[firstEmpty];

            table[newPos].key = c;
            table[newPos].values = new TValue[2];
            table[newPos].next = -1;
            table[newPos].vcapacity = 2;
            table[newPos].vsize = 1;

            table[newPos].values[0] = v;

            int curr = pos;
            int prev = -1;

            while (curr != -1 and rel(table[curr].key, c)) {
                prev = curr;
                curr = table[curr].next;
            }

            if (prev == -1) {
                table[newPos].next = pos;
                std::swap(table[newPos], table[pos]);

                nextFree[newPos] = firstEmpty;
                firstEmpty = newPos;
            } else {
                table[newPos].next = table[prev].next;
                table[prev].next = newPos;
            }
        }
    }

    SMMsize ++;
} // WC = Theta(capacity), BC = Theta(1), TC = O(capacity)

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> result;
    int pos = hashFunction(c);

    int current = pos;

    while (current != -1) {
        if (table[current].key == c) {
            for (int i = 0; i < table[current].vsize; i++) {
                result.push_back(table[current].values[i]);
            }
            break;
        }

        if (!rel(table[current].key, c))
            break;

        current = table[current].next;
    }

    return result;
}  // WC = Theta(capacity), BC = Theta(1+k), TC = O(capacity), where k is the number of values associated with c


bool SortedMultiMap::remove(TKey c, TValue v) {
    int pos = hashFunction(c);

    int current = pos;
    int prev = -1;

    while (current != -1) {
        if (table[current].key == c) {
            for (int i = 0; i < table[current].vsize; i ++) {
                if (table[current].values[i] == v) {
                    for (int j = i; j < table[current].vsize; j ++) {
                        table[current].values[j] = table[current].values[j+1];
                    }
                    table[current].vsize --;
                    SMMsize --;

                    if (table[current].vsize == 0) {
                        delete[] table[current].values;
                        table[current].values = nullptr;
                        table[current].vcapacity = 0;
                        table[current].key = NULL_TVALUE;

                        if (prev != -1) {
                            table[prev].next = table[current].next;
                        }

                        table[current].next = -1;
                        nextFree[current] = firstEmpty;
                        firstEmpty = current;
                    }

                    return true;
                }
            }

            return false;
        }

        if (!rel(table[current].key, c)) break;

        prev = current;
        current = table[current].next;
    }

    return false;
} // WC = Theta(capacity), BC = Theta(1), TC = Theta(1) amortized


int SortedMultiMap::size() const {
    return SMMsize;
} // BC = WC = TC = Theta(1)

bool SortedMultiMap::isEmpty() const {
    return SMMsize == 0;
}// BC = WC = TC = Theta(1)

SortedMultiMap::~SortedMultiMap() {
    for (int i = 0; i < capacity; ++i) {
        delete[] table[i].values;
    }
    delete[] table;
    delete[] nextFree;
}// BC = WC = TC = Theta(capacity)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}// BC = WC = TC = Theta(1)