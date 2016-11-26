#ifndef HUFHEAP_H
#define HUFHEAP_H
#include "stack.h"
const int NUM_ALL_CHAR = 255;

struct hufNode
{
	char ch;
	int freq;
	hufNode *left;
	hufNode *right;
};


class MinHeap
{
public:
	MinHeap(int);
	~MinHeap();
	hufNode* getMinimum();
	void insert(hufNode*);
	void buildHeap(hufNode**);
	void removeMin();
	bool isEmpty();
	void print();
	void mergeNodes(char);
	void traverse(hufNode *, int[], int, Stack&);
	void print(int[], int);
private:
	hufNode **data;
	int heapSize;
	int arraySize;

	int getLeftChildIndex(int);
	int getRightChildIndex(int);
	int getParentIndex(int);
	void shiftUp(int);
	void shiftDown(int);
	bool isLeaf(hufNode*);
};
#endif