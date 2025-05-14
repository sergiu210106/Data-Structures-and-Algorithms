#include "SMMIterator.h"
#include <algorithm>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    for (int i = 0; i < map.capacity; i ++) {
        if (map.table[i].key != NULL_TVALUE) {
            Pair p;

            p.key = map.table[i].key;
            for (int j = 0; j < map.table[i].vsize; j ++) {
                p.values.push_back(map.table[i].values[j]);
            }

            pairs.push_back(p);
        }
    }

    std::sort(pairs.begin(), pairs.end(), [this](const Pair& a, const Pair& b) {
        return map.rel(a.key, b.key);
    });

    first();
} // BC = TC = WC = Theta(n + k log k)

void SMMIterator::first() {
    currentPair = 0;
    currentValue = 0;
    advanceToValid();
} // WC = theta(k), BC = theta(1), TC = theta(1) amortized

void SMMIterator::next() {
    if (!valid()) 
        throw std::exception();
    currentValue++;
    if (currentValue >= pairs[currentPair].values.size()) {
        currentPair++;
        currentValue = 0;
    }
    advanceToValid();
} // WC = theta(k), BC = theta(1), TC = theta(1)

void SMMIterator::advanceKSteps(int k) {
    if (k <= 0) {
        throw std::exception();
    }

    while (k--) 
        next();
} // WC = theta(steps * keys), BC = theta(steps), TC = theta(steps)

bool SMMIterator::valid() const {
    return currentPair < pairs.size();
} // BC = WC = TC = theta(1)

TElem SMMIterator::getCurrent() const {
    if (!valid()) 
        throw std::exception();
    return {pairs[currentPair].key, pairs[currentPair].values[currentValue]};
} // BC = WC = TC = theta(1) 

void SMMIterator::advanceToValid() {
    while (currentPair < pairs.size() && currentValue >= pairs[currentPair].values.size()) {
        currentPair ++;
        currentValue = 0;
    }
} // BC = theta(1), WC = theta(keys), TC = theta(keys)
