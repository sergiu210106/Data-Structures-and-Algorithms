#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
#include <functional>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	capacity = 10;
	nodes = new Node[capacity];

	for (int i = 0; i < capacity; i ++) {
		nodes[i].left = nodes[i].right = -1;
	}

	root = -1;
	firstFree = 0;
	length = 0;
	rel = r;
}

int SortedMultiMap::allocate() {
	if (firstFree == capacity) {
		int newCapacity = capacity * 2;
		Node * newNodes = new Node [newCapacity];

		for (int i = 0; i < capacity; i ++) {
			newNodes[i] = nodes[i];
		}

		for (int i = capacity; i < capacity * 2; i ++) {
			newNodes[i].left = newNodes[i].right = -1;
		}

		delete[] nodes;
		nodes = newNodes;
		capacity = newCapacity;
	}

	return firstFree++;
}

void SortedMultiMap::add(TKey c, TValue v) {
	int newNode = allocate();

	nodes[newNode].elem = make_pair(c,v);
	nodes[newNode].left = nodes[newNode].right = -1;

	if (root == -1) {
		root = newNode;
	} else {
		int current = root;

		while (true) {
			if (rel(c, nodes[current].elem.first)) {
				if (nodes[current].left == -1) {
					nodes[current].left = newNode;
					break;
				}

				current = nodes[current].left;
			} else {
				if (nodes[current].right == -1) {
					nodes[current].right = newNode;
					break;
				}

				current = nodes[current].right;
			}
		}
	}

	length ++;
}
void SortedMultiMap::inorderSearch(int node, TKey c, vector<TValue> & result) const {
	if (node == -1) {
		return;
	}

	inorderSearch(nodes[node].left, c, result);

	if (nodes[node].elem.first == c) {
		result.push_back(nodes[node].elem.second);
	}

	inorderSearch(nodes[node].right, c, result);
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> res;

	inorderSearch(root, c, res);

	return res;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	int parent = -1;
	int current = root;

	while (current != -1 and !(nodes[current].elem.first == c and nodes[current].elem.second == v)) {
		parent = current;

		if (rel(c, nodes[current].elem.first)) {
			current = nodes[current].left;
		} else {
			current = nodes[current].right;
		}
	}
	
	if (current == -1) {
		return false;
	}

	// case 1 : leaf
	if (nodes[current].left == -1 and nodes[current].right == -1) {
		if (current == root) {
			root = -1;
		} else if (nodes[parent].left == current) {
			nodes[parent].left = -1;
		} else {
			nodes[parent].right = -1;
		}
	}

	// case 2 : one child
	else if (nodes[current].left == -1 or nodes[current].right == -1) {
		int child = (nodes[current].left == -1) ? nodes[current].right : nodes[current].left;

		if (current == root) {
			root = child;
		} else if (nodes[parent].left == current) {
			nodes[parent].left = child;
		} else {
			nodes[parent].right = child;
		}
	}

	// case 3 : two children
	else {
		int succParent = current;
		int succ = nodes[current].right;

		while (nodes[succ].left != -1) {
			succParent = succ;
			succ = nodes[succ].left;
		}

		nodes[current].elem = nodes[succ].elem;

		if (nodes[succParent].left == succ) {
			nodes[succParent].left = nodes[succ].right;
		} else {
			nodes[succParent].right = nodes[succ].right;
		}
	}

	length --;
	return true;
}


int SortedMultiMap::size() const {
	return length;
}

bool SortedMultiMap::isEmpty() const {
	return (length == 0);
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	delete[] nodes;
}
