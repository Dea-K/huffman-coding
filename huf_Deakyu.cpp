// File Name: huf_Deakyu.cpp
// Author	: Deakyu Lee
// Created	: 11/25/2016
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
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