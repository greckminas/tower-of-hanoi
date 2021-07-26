#ifndef STACK_H
#define STACK_H

struct node {
	int value;
	int step;
};

class Stack {
	int top;
	node list_stack[8];
	
public:
	Stack();
	bool push(int value);
	bool push(int value, int step);
	int pop();
	int peek(int n);
	int peek(int n, int* step);
	int count();
	void print();
};

#endif