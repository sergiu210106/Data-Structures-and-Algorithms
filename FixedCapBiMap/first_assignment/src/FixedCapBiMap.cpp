#include "../include/FixedCapBiMap.h"
#include "../include/FixedCapBiMapIterator.h"
#include <exception>

using namespace std;
class FixedCapBiMapIterator;
FixedCapBiMap::FixedCapBiMap(int capacity) {
	if(capacity <= 0){
		throw exception();
	}

	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->mapSize == this->capacity){
		throw exception();
	}
	int count = 0;
	int index = 0;
	while(count < 2 and index < this->mapSize){
		if (this->elements[index].first == c){
			count ++;
		}
		index ++;
	}

	if (count == 2) {
		return false;
	}

	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;
	this->mapSize++;
	return true;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;
	int nrFound = 0;
	int index = 0;
	while (nrFound < 2 and index < this->mapSize){
		if (this->elements[index].first == c) {
			if (nrFound == 0) {
				result.first = this->elements[index].second;
				nrFound ++;
			} else {
				result.second = this->elements[index].second;
				nrFound++;
			}			
		}
		index ++;
	}
	return result;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	int index = 0;
	while (index < this->mapSize) {
		if (this->elements[index].first == c and this->elements[index].second == v){
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize --;
			return true;
		}
		index ++;
	}
	return false;
}


int FixedCapBiMap::size() const {
	return this->mapSize;
}

bool FixedCapBiMap::isEmpty() const{
	return this->mapSize == 0;
}

bool FixedCapBiMap::isFull() const {
	return this->mapSize == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



