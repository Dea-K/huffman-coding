#ifndef STACK_H
#define STACK_H

struct tableType
{
	char ch;
	int *binRep;
	int repSize;
};


class Stack
{
private:
	tableType *data;
	int maxSize;
	int top;
	int count;
public:
	Stack(int);
	~Stack();
	bool isEmpty();
	bool isFull();
	void push(tableType);
	void pop(tableType&);
	void stackTop(tableType&);
	void printStack();
	int size();
};

#endif