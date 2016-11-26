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

void readCount(hufNode**&, string&, string);
hufNode **buildInitial();

#endif

int main()
{
	hufNode **chars = buildInitial();
	string fileName = "text.txt";
	string str = "";


	readCount(chars, str, fileName);
	for (int i = 0; i < NUM_ALL_CHAR; i++)
		cout << chars[i]->ch << ": " << chars[i]->freq << endl;
	cout << str << endl;

	
	system("pause");
	return 0;
}

hufNode **buildInitial()
{
	hufNode **temp = new hufNode*[NUM_ALL_CHAR];
	for (int i = 0; i < NUM_ALL_CHAR; i++)
	{
		temp[i] = new hufNode;
		temp[i]->ch = (char)i;
		temp[i]->freq = 0;
		temp[i]->left = nullptr;
		temp[i]->right = nullptr;
	}
	return temp;
	delete[]temp;
	for (int i = 0; i < NUM_ALL_CHAR; i++)
		delete temp[i];
}

void readCount(hufNode **&Nodes, string &str, string filename)
{
	ifstream indata;
	char ch;
	string temp = "";
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
		Nodes[(int)ch]->freq++;
	}
	str = temp.substr(0, temp.size() - 1);
	Nodes[(int)ch]->freq--;
	indata.close();

}