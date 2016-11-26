#include "stack.h"
#include "huf_minheap.h"
#include <iostream>
using namespace std;

MinHeap::MinHeap(int maxSize)
{
	data = new hufNode*[maxSize];
	heapSize = 0;
	arraySize = maxSize;
}

MinHeap::~MinHeap()
{
	delete[]data;
}

bool MinHeap::isEmpty()
{
	return (heapSize == 0);
}

int MinHeap::getLeftChildIndex(int nodeIndex)
{
	return (nodeIndex * 2) + 1;
}

int MinHeap::getRightChildIndex(int nodeIndex)
{
	return (nodeIndex * 2) + 2;
}

int MinHeap::getParentIndex(int nodeIndex)
{
	return (nodeIndex - 1) / 2;
}

hufNode* MinHeap::getMinimum()
{
	if (isEmpty())
		throw string("Heap is Empty...");
	else
		return data[0];
}

void MinHeap::shiftUp(int nodeIndex)
{
	int parentIndex;
	hufNode *temp;
	if (nodeIndex != 0)
	{
		parentIndex = getParentIndex(nodeIndex);
		if (data[nodeIndex]->freq < data[parentIndex]->freq)
		{
			temp = data[nodeIndex];
			data[nodeIndex] = data[parentIndex];
			data[parentIndex] = temp;
			shiftUp(parentIndex);
		}
	}
}

void MinHeap::insert(hufNode* value)
{
	if (heapSize == arraySize)
		throw string("Heap is Full...");
	else
	{
		heapSize++;
		data[heapSize - 1] = value;
		shiftUp(heapSize - 1);
	}
}

void MinHeap::shiftDown(int nodeIndex)
{
	int leftChildIndex, rightChildIndex, minIndex;
	hufNode *temp;
	leftChildIndex = getLeftChildIndex(nodeIndex);
	rightChildIndex = getRightChildIndex(nodeIndex);
	if (rightChildIndex >= heapSize)
	{
		if (leftChildIndex >= heapSize)
			return;
		else
			minIndex = leftChildIndex;
	}
	else
	{
		if (data[leftChildIndex]->freq <= data[rightChildIndex]->freq)
			minIndex = leftChildIndex;
		else
			minIndex = rightChildIndex;
	}

	if (data[nodeIndex]->freq > data[minIndex]->freq)
	{
		temp = data[nodeIndex];
		data[nodeIndex] = data[minIndex];
		data[minIndex] = temp;
		shiftDown(minIndex);
	}
}

void MinHeap::removeMin()
{
	if (isEmpty())
		throw string("Heap is Empty...");
	else
	{
		data[0] = data[heapSize - 1];
		heapSize--;
		if (heapSize > 0)
			shiftDown(0);
	}
}

void MinHeap::buildHeap(hufNode **arr)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (arr[i]->freq>0)
			insert(arr[i]);
	}
}

void MinHeap::print()
{
	while (!isEmpty())
	{
		cout << getMinimum()->ch << ":" << getMinimum()->freq << endl;
		removeMin();
	}

}

void MinHeap::mergeNodes(char notUsed)
{
	if (heapSize < 1)
		return;
	hufNode *newNode = new hufNode;
	newNode->ch = notUsed;

	newNode->left = getMinimum();
	removeMin();
	if (heapSize < 1)
	{
		newNode->right = nullptr;
		newNode->freq = newNode->left->freq;
		insert(newNode);
		return;
	}
	newNode->right = getMinimum();
	removeMin();

	newNode->freq = newNode->left->freq + newNode->right->freq;
	/*cout << newNode->left->ch << "+" << newNode->right->ch << " : " << newNode->freq << endl;
	system("pause");*/
	insert(newNode);
	mergeNodes(notUsed);

}

bool MinHeap::isLeaf(hufNode *walker)
{
	return ((walker->left == nullptr) && (walker->right == nullptr));
}

void MinHeap::traverse(hufNode *walker, int arr[], int top, Stack &S)
{
	if (walker->left != nullptr)
	{
		arr[top] = 0;
		traverse(walker->left, arr, top + 1, S);
	}

	if (walker->right != nullptr)
	{
		arr[top] = 1;
		traverse(walker->right, arr, top + 1, S);
	}
	if (isLeaf(walker))
	{
		/*cout << walker->ch << ":\t" << "freq:\t" << walker->freq << "\trep:\t";
		print(arr, top);*/


		tableType temp;
		temp.ch = walker->ch;
		temp.repSize = top;
		temp.binRep = new int[top];
		for (int i = 0; i < top; i++)
			temp.binRep[i] = arr[i];
		S.push(temp);
	}
}

void MinHeap::print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i];
	cout << endl;
}
