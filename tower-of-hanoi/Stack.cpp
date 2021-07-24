#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack::Stack(){
	top = -1;
}

bool Stack::push(int value){
	//stack is overflow
	if(top == 8)
		return false; 

	//increase the top of stack
	top++;

	//set data of node
	list_stack[top].step = 0;
	list_stack[top].value = value;

	return true;
}

bool Stack::push(int value, int step){
	//stack is overflow
	if(top == 8)
		return false; 

	//increase the top of stack
	top++;

	//set data of node
	list_stack[top].step = step;
	list_stack[top].value = value;

	return true;
}

int Stack::pop(){
	int result = -1;

	//stack is underflow
	if(top == -1)
		return result;

	result = list_stack[top].value;

	//decrease the top of stack
	top--;

	return result;
}

int Stack::peek(int n){
	//0 = top
	int result = -1;
	
	//stack is empty
	if(top == -1)
		return result;

	//out of range
	if(top < n)
		return result;

	result = list_stack[top-n].value;
	return result;
}

int Stack::peek(int n, int* step){
	//0 = top
	int result = -1;
	
	//stack is empty
	if(top == -1)
		return result;

	//out of range
	if(top < n)
		return result;

	result = list_stack[top-n].value;
	*step = list_stack[top-n].step;
	return result;
}

int Stack::count(){
	int result = 0;
	
	//stack is empty
	if(top == -1)
		return result;

	result = top+1;

	return result;
}

void Stack::print(){
	//stack is empty
	if(top == -1)
		return;

	for(int i = 0; i < top; i++){
		printf("%d \n", list_stack[top].value);
	}
}