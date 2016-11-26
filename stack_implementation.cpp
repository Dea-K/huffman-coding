//////////////////////////////////////////////////////////////////
/////////////  STACK	//////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#include "stack.h"
#include <iostream>
using namespace std;


Stack::Stack(int size)
{
	maxSize = size;
	count = 0;
	top = -1;
	data = new tableType[maxSize];
}

Stack::~Stack()
{
	delete[]data;
}

void Stack::push(tableType indata)
{
	if (count < maxSize)
	{
		count++;
		top++;
		data[top] = indata;
	}
	else
	{
		cout << "Stack is full..." << endl;
		return;
	}
}

void Stack::pop(tableType &outdata)
{
	if (count > 0)
	{
		count--;
		outdata = data[top];
		top--;
	}
	else
	{
		cout << "Stack is Empty..." << endl;
		return;
	}
}

void Stack::stackTop(tableType &outdata)
{
	if (count > 0)
	{
		outdata = data[top];
	}
	else
	{
		cout << "Stack is Empty..." << endl;
		return;
	}
}

bool Stack::isEmpty()
{
	return (count<1);
}

bool Stack::isFull()
{
	return (count>maxSize - 1);
}

int Stack::size()
{
	return count;
}

void Stack::printStack()
{
	cout << "My Stack is: " << endl;
	for (int i = size() - 1; i >-1; i--)
	{
		cout << data[i].ch << ":" << data[i].repSize << endl;
	}
	cout << endl;
}