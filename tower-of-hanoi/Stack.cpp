#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack::Stack(){
	top = NULL;
}

bool Stack::push(int value){
	node* newnode = (node*)malloc(sizeof(node));
	if(newnode == NULL)
		return false;

	newnode->value = value;
	newnode->prev = top;
	top = newnode;
	return true;
}

int Stack::pop(){
	int result = -1;

	if(top == NULL)
		return result;

	node* current = top;
	result = current->value;
	top = current->prev;

	free(current);

	return result;
}

int Stack::peek(int n){
	//0 = top
	int result = -1;
	
	if(top == NULL)
		return result;

	node* current = top;
	for(int i = 0; i < n; i++){
		if(current == NULL)
			return result;
		current = current->prev;
	}
	if(current == NULL)
		return result;

	result = current->value;
	return result;
}

int Stack::count(){
	int result = 0;
	node* current = top;

	while(current != NULL){
		result++;
		current = current->prev;
	}

	return result;
}

void Stack::print(){
	node* current = top;

	while(current != NULL){
		printf("%d \n", current->value);
		current = current->prev;
	}
}