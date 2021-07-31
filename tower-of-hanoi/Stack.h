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
	/* CONSTRUCTOR */
	Stack();

	/* PUSH AND POP */
	bool push(int value);
	bool push(int value, int step);
	int pop();

	/* PEEK */
	int peek(int n);
	int peek(int n, int* step);

	/* COUNT ELEMENT */
	int count();

	/* PRINT STACK */
	void print();
};

#endif