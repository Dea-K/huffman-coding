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


// reads the file and creates initial nodes
hufNode** readCount(string&, string, char&);
// returns a string resulted from the encoded file (encoding process included)
string encodedFileMaker(tableType*, int, string, string);
string decodedBinRep(string);
int binaryToDecimal(string);
string decBinRet(int);
#endif

int main()
{
	string fileName = "test.txt";
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

	string binStringFromFile = encodedFileMaker(hufTable, tableSize, fileName, "result.txt");
	cout << "Resulting string from encoded file: " << endl
		<< binStringFromFile << endl;

	cout << decodedBinRep(binStringFromFile) << endl;

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

string encodedFileMaker(tableType* hufTable, int tableSize, string filename, string encodedfile)
{
	ifstream inD;
	inD.open(filename);
	if (!inD)
	{
		cout << "Error opening the file..." << endl;
		exit(1);
	}

	char ch = ' ';
	string result = "";
	while (!inD.eof())
	{
		inD.get(ch);
		for (int i = 0; i < tableSize; i++)
		{
			if (hufTable[i].ch == ch)
			{
				for (int j = 0; j < hufTable[i].repSize; j++)
					result += (char)hufTable[i].binRep[j] + '0';
				break;
			}
		}
	}
	inD.close();
	int tempSize = (result.size() / 8) + 1;
	string *temp = new string[tempSize];
	int *decRep = new int[tempSize];
	char *charRep = new char[tempSize];
	string codedResult = "";
	for (int i = 0; i < result.size(); i++)
	{
		temp[i / 8] += result[i];
	}
	cout << "temp: " << endl;
	for (int i = 0; i < tempSize; i++)
		cout << temp[i] << " ";
	cout << endl;

	for (int i = 0; i < tempSize; i++)
	{
		decRep[i] = binaryToDecimal(temp[i]);
		charRep[i] = (char)decRep[i];
		codedResult += charRep[i];
	}

	/*ofstream outD;
	outD.open(encodedfile);
	outD << codedResult;
	outD.close();*/

	return codedResult;
}

string decodedBinRep(string encodedResult)
{
	int sizeEnResult = encodedResult.size();
	string *temp = new string[sizeEnResult];
	int *intTemp = new int[sizeEnResult];
	string decodedResult = "";
	for (int i = 0; i < sizeEnResult; i++)
	{
		intTemp[i] = (int)encodedResult[i];
		bitset<8> tempBit(intTemp[i]);
		temp[i] = tempBit.to_string();
		decodedResult += temp[i];
		decodedResult += char(32);
	}
	return decodedResult;
}

int binaryToDecimal(string binNumber)
{
	// Write a function that converts a binary number to its decimal equivalent. The functinos takes
	// one string parameter representing a binary number and returns its decimal representation as an
	// integer

	int leng = binNumber.length();	// holds the length of the binary number string
	int backwardIndex;				// holds the backward index of the binary number
	int poweredNum[50];				// holds the number to multiply for each binary number (2^0, 2^1, etc.)
	int numberToMul[50];			// holds the binary number to be multiplied by the powered number(1, 0)
	int decimalRep = 0;				// holds the binary representation of a decimal number

	backwardIndex = leng;

	int count = 0;

	while (count < leng)
	{
		// this line takes the number equivalent of char '1' or '0' and subtract '0' to make it actual '1's and '0's
		numberToMul[count] = int(binNumber[backwardIndex - 1]) - '0';

		// index counting
		backwardIndex--;
		count++;
	}

	count = 0;		// reset the counter

	while (count <leng)
	{
		poweredNum[count] = pow(2, count);
		count++;
	}

	count = 0;		// reset the counter

	while (count <leng)
	{
		decimalRep += numberToMul[count] * poweredNum[count];
		count++;
	}

	return decimalRep;

}

string decBinRet(int quotient)
{
	if (quotient == 0)
		return "";
	else
	{
		char bin = static_cast<char>(quotient % 2) + '0';
		return decBinRet(quotient / 2) + bin;
	}
}