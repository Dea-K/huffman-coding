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
#include "stack.h"
#include "huf_minheap.h"
using namespace std;



hufNode** readCount(string&, string, char&);
void encodedFileMaker(tableType*, string);

#endif

int main()
{
	string fileName = "text.txt";
	string str = "";
	char notUsed = ' ';
	MinHeap hufHeap(NUM_ALL_CHAR);
	Stack S(100);

	hufNode **chars = readCount(str, fileName, notUsed);

	hufHeap.buildHeap(chars);
	//hufHeap.print();
	hufHeap.mergeNodes(notUsed);
	//hufHeap.print();
	int arr[NUM_ALL_CHAR], top = 0;
	hufHeap.traverse(hufHeap.getMinimum(), arr, top, S);
	

	// The following lines of code generate tableType array that stores the huffman table;
	int tableSize = S.size();
	tableType *hufTable = new tableType[tableSize];
	for (int i = 0; i < tableSize; i++)
		S.pop(hufTable[i]);
	for (int i = 0; i < tableSize; i++)
	{
		cout << hufTable[i].ch << ":";
		for (int j = 0; j < hufTable[i].repSize; j++)
			cout << hufTable[i].binRep[j];
		cout << endl;
	}
	
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

//void encodedFileMaker(tableType*, string)
//{
//
//}

