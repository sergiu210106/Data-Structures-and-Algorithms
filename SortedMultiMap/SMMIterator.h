#pragma once

#include "SortedMultiMap.h"
#include <vector>

class SMMIterator {
    friend class SortedMultiMap;
private:
    const SortedMultiMap& map;

    struct Pair {
        TKey key;
        std::vector<TValue> values;
    };

    std::vector<Pair> pairs;
    int currentPair;
    int currentValue;

    SMMIterator(const SortedMultiMap& map);
    void advanceToValid();

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
    void advanceKSteps(int k);

};