#ifndef STACK_H
#define STACK_H

struct node {
	int value;
	node* prev;
};

class Stack {
	node* top;
	
public:
	Stack();
	bool push(int value);
	int pop();
	int peek(int n);
	int count();
	void print();
};

#endif