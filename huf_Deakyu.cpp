// File Name: huf_Deakyu.cpp
// Author	: Deakyu Lee
// Created	: 11/25/2016
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <bitset>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "stack.h"
#include "huf_minheap.h"
using namespace std;



hufNode** readCount(string&, string, char&);
void encodedFileMaker(tableType*, int, string, string);

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
	int arr[NUM_ALL_CHAR];
	int top = 0;
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

	encodedFileMaker(hufTable, tableSize, fileName, "result.txt");
	
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

	cout << "initial file's size: " << str.size() << endl;
	return tempN;
	delete[]tempN;
}

void encodedFileMaker(tableType* hufTable, int tableSize, string filename, string encodedfile)
{
	ifstream inD;
	inD.open(filename);
	if (!inD)
	{
		cout << "Error opening the file..." << endl;
		return;
	}

	char ch = ' ';
	string result = "";
	string temp = "";
	bitset<100> outbit[100];
	while (!inD.eof())
	{
		inD.get(ch);
		for (int i = 0; i < tableSize; i++)
		{
			if (hufTable[i].ch == ch)
			{
				for (int j = 0; j < hufTable[i].repSize; j++)
				{
					result += (char)hufTable[i].binRep[j] + '0';
					outbit[i][j] = hufTable[i].binRep[j];
				}
				break;
			}
		}
		//result += " ";
	}
	inD.close();

	ofstream outD("result.bin", ios::binary);
	for (int i = 0; i < tableSize; i++)
		for (int j = 0; j < hufTable[i].repSize; j++)
			outD << outbit[i][j];
	outD.close();

	cout << "result's file size: " << result.size() << endl;



	/*ifstream bitD("result.bin", ios::binary);
	char tmp = ' ';
	string stemp = "";
	for (int i = 0; i < tableSize; i++)
	{
		for (int j = 0; j < hufTable[i].repSize; j++)
		{
			bitD.get(tmp);
			stemp += tmp;
		}
	}
	bitD.close();
	cout << "stemp: " << stemp << endl;*/
}

