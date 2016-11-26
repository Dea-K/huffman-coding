// File Name: huf_Deakyu.cpp
// Author	: Deakyu Lee
// Created	: 11/25/2016
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

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
	int getMinimum();
	void insert(int);
	void buildHeap(int*);
	void removeMin();
	void print();
	bool isEmpty();
private:
	int *data;
	int heapSize;
	int arraySize;

	int getLeftChildIndex(int);
	int getRightChildIndex(int);
	int getParentIndex(int);
	void shiftUp(int);
	void shiftDown(int);
	void printHeap(int*, int, int, int);
};

hufNode** readCount(string&, string);

#endif

int main()
{
	string fileName = "text.txt";
	string str = "";


	hufNode **chars = readCount(str, fileName);
	for (int i = 0; i < NUM_ALL_CHAR; i++)
		cout << chars[i]->ch << ": " << chars[i]->freq << endl;
	cout << str << endl;

	
	system("pause");
	return 0;
}

hufNode** readCount(string &str, string filename)
{
	ifstream indata;
	char ch;
	string temp = "";


	hufNode **tempN = new hufNode*[NUM_ALL_CHAR];
	for (int i = 0; i < NUM_ALL_CHAR; i++)
	{
		tempN[i] = new hufNode;
		tempN[i]->ch = (char)i;
		tempN[i]->freq = 0;
		tempN[i]->left = nullptr;
		tempN[i]->right = nullptr;
	}


	indata.open(filename);
	if (!indata)
	{
		cout << "Error opening the file..." << endl;
		return;
	}
	while (!indata.eof())
	{
		indata.get(ch);
		temp = temp + ch;
		tempN[(int)ch]->freq++;
	}
	str = temp.substr(0, temp.size() - 1);
	tempN[(int)ch]->freq--;
	indata.close();

	return tempN;
	delete[]tempN;
	for (int i = 0; i < NUM_ALL_CHAR; i++)
		delete tempN[i];
}

MinHeap::MinHeap(int maxSize)
{
	data = new int[maxSize];
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

int MinHeap::getMinimum()
{
	if (isEmpty())
		throw string("Heap is Empty...");
	else
		return data[0];
}

void MinHeap::shiftUp(int nodeIndex)
{
	int parentIndex, temp;
	if (nodeIndex != 0)
	{
		parentIndex = getParentIndex(nodeIndex);
		if (data[nodeIndex] < data[parentIndex])
		{
			temp = data[nodeIndex];
			data[nodeIndex] = data[parentIndex];
			data[parentIndex] = temp;
			shiftUp(parentIndex);
		}
	}
}

void MinHeap::insert(int value)
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
	int leftChildIndex, rightChildIndex, minIndex, temp;
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
		if (data[leftChildIndex] <= data[rightChildIndex])
			minIndex = leftChildIndex;
		else
			minIndex = rightChildIndex;
	}

	if (data[nodeIndex] > data[minIndex])
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

void MinHeap::print()
{
	printHeap(data, 0, heapSize - 1, 0);
}

void MinHeap::printHeap(int *heap, int root, int heapLast, int level)
{
	int child;
	int i;
	if (root <= heapLast)
	{
		child = (root * 2 + 1);
		printHeap(heap, child + 1, heapLast, level + 1);

		for (int i = 0; i < level; i++)
			cout << "     ";
		cout << setw(4) << heap[root] << endl;
		printHeap(heap, child, heapLast, level + 1);
	}
	return;
}

void MinHeap::buildHeap(int *arr)
{
	for (int i = 0; i < arraySize; i++)
	{
		insert(arr[i]);
	}
}