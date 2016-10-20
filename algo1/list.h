/** Алгоритмическая сложность печати как по времени, так и по памяти O(n) */
#pragma once
#include <stdlib.h>
#include <iostream>
#include <stack>

#define ERROR_MEMORY_ALLOCATION 1

template<typename T>
struct node
{
	T value;
	node<T>* next;
};

template<typename T>
class list{
	node<T>* _first;
	node<T>* _last;
public:
	list();
	~list();
	int add(T);				/** Adds  new node. */
	void reverse_print() const;	/** Prints the list in reverse order. */
};

template<typename T>
list<T>::list() {
	_first = NULL;
	_last = NULL;
}

template<typename T>
list<T>::~list() {
	if(_first == NULL) {
		return;
	}
	auto t = _first;
	while(t) {
		auto next = t->next;
		free(t);
		t = next;
	}
}

template<typename T>
int list<T>::add(T value) {
	node<T>* new_node = (node<T>*) malloc(sizeof(void*));	// Creating new node.
	if(new_node == NULL) {
		return ERROR_MEMORY_ALLOCATION;
	}
	new_node->value = value;
	new_node->next = NULL;
	if(_first != NULL){										// If list isn't empty, just add the new node to the end.
		_last->next = new_node;
		_last = new_node;
		return 0;
	}
	_first = new_node;				// Else new node is first and last in the list.
	_last = new_node;
	return 0;		
}

template<typename T>
void list<T>::reverse_print() const {
	std::stack<T> st;
	auto t = _first;
	while(t) {
		st.push(t->value);
		t = t->next;
	}
	while(!st.empty()) {
		std::cout<<st.top()<<std::endl;
		st.pop();
	}
}
