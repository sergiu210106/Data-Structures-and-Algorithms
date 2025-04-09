#pragma once
#include "IteratedList.h"

//DO NOT CHANGE THIS PART
class IteratedList;
typedef int TElem;

class ListIterator{
	friend class IteratedList;
private:
	Node* current;
	//DO NOT CHANGE THIS PART
	const IteratedList& list;
	ListIterator(const IteratedList& lista);
public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
	//changes the current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid  
	//throws an exception if the iterator is not valid when the operation is called  
	void previous();  
};


