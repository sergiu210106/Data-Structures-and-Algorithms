#include "ShortTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <assert.h>

bool r2(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}


void testAll() { 
	int vverif[5];
	int iverif;
	TComp e;

	SortedSet s1(r2);
	assert(s1.add(5) == true);
	assert(s1.add(1) == true);
	assert(s1.add(10) == true);
	SortedSetIterator it1 = s1.iterator();
	it1.first();
	e = it1.getCurrent();
	iverif = 0;
	vverif[iverif++] = e;
	it1.next();
	while (it1.valid()) {
		assert(r2(e, it1.getCurrent()));
		e = it1.getCurrent();
		vverif[iverif++] = e;
		it1.next();
	}
	assert((vverif[0] == 1) && (vverif[1] == 5) && (vverif[2] == 10));


	SortedSet s(r2);
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	assert(s.add(5) == true);
	assert(s.add(1) == true);
	assert(s.add(10) == true);
	assert(s.add(7) == true);
	assert(s.add(1) == false);
	assert(s.add(10) == false);
	assert(s.add(-3) == true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);

	SortedSetIterator it = s.iterator();
	iverif = 0;
	it.first();
	e = it.getCurrent();
	vverif[iverif++] = e;
	it.next();
	while (it.valid()) {
		assert(r2(e, it.getCurrent()));
		e = it.getCurrent();
		vverif[iverif++] = e;
		it.next();
	}
	assert((vverif[0] == -3) && (vverif[1] == 5) && (vverif[2] == 7) && (vverif[3] == 10));

	// TEST DIFFERENCE
	SortedSet s_diff(r2);
	s_diff.add(1);
	s_diff.add(2);
	s_diff.add(3);
	s_diff.add(4);
	s_diff.add(5);

	SortedSet s2_diff(r2);
	s2_diff.add(3);
	s2_diff.add(4);
	s2_diff.add(10);  // Not in s_diff

	int removed = s_diff.difference(s2_diff);
	assert(removed == 2); // 3 and 4 should be removed

	assert(s_diff.search(1) == true);
	assert(s_diff.search(2) == true);
	assert(s_diff.search(3) == false); // removed
	assert(s_diff.search(4) == false); // removed
	assert(s_diff.search(5) == true);
	assert(s_diff.search(10) == false); // was never in s_diff
	assert(s_diff.size() == 3);
}

