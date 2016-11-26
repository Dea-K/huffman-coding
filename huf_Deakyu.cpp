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
	hufNode* getMinimum();
	void insert(hufNode*);
	void buildHeap(hufNode**);
	void removeMin();
	bool isEmpty();
	void print();
	void mergeNodes(char);
	void traverse(hufNode *, int[], int);
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

hufNode** readCount(string&, string, char&);

#endif

int main()
{
	string fileName = "test.txt";
	string str = "";
	char notUsed = ' ';
	MinHeap hufHeap(NUM_ALL_CHAR);

	hufNode **chars = readCount(str, fileName, notUsed);

	hufHeap.buildHeap(chars);
	//hufHeap.print();
	hufHeap.mergeNodes(notUsed);
	//hufHeap.print();
	int arr[NUM_ALL_CHAR], top = 0;
	hufHeap.traverse(hufHeap.getMinimum(), arr, top);

	
	system("pause");
	return 0;
}

hufNode** readCount(string &str, string filename, char &notUsed)
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
		exit(1);
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

	for (int i = 0; i < NUM_ALL_CHAR; i++)
	{
		if (tempN[i]->freq == 0)
		{
			notUsed = tempN[i]->ch;
			break;
		}
	}

	return tempN;
	delete[]tempN;
}

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

void MinHeap::traverse(hufNode *walker, int arr[], int top)
{
	if (walker->left != nullptr)
	{
		arr[top] = 0;
		traverse(walker->left, arr, top + 1);
	}

	if (walker->right != nullptr)
	{
		arr[top] = 1;
		traverse(walker->right, arr, top+1);
	}
	if (isLeaf(walker))
	{
		cout << walker->ch << ": ";
		print(arr, top);
	}
}

void MinHeap::print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i];
	cout << endl;
}