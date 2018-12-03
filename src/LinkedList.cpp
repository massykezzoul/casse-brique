#include <iostream>
#include <sstream>

#include "LinkedList.h"

using namespace std;

template <typename T>
LinkedList<T>::LinkedList(): head(NULL), tail(NULL), len(0) {
}

template <typename T>
LinkedList<T>::LinkedList(T data): len(1) {
	head = (Node<T>*)malloc(sizeof(Node<T>));
	
	tail = head;
	
	head->next = NULL;
	head->prev = NULL;
	head->data = data;
}

template <typename T>
void LinkedList<T>::Add(T data) {
	Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>));

	newNode->prev = tail;
	newNode->next = NULL;
	newNode->data = data;
	if (tail) {
		tail->next = newNode;
		tail = newNode;
	}

	if (!head) {
		head = newNode;
	}
	if (!tail) {
		tail = newNode;
	}
	len++;
}

template <typename T>
void LinkedList<T>::Rm(Node<T>* n) {
	if (n == head)
		head = n->next;
	if (n == tail)
		tail = n->prev;
	if (n->prev)
		n->prev->next = n->next;
	if (n->next)
		n->next->prev = n->prev;
	free(n);
	len--;
}

template <typename T>
bool LinkedList<T>::RmAt(int i) {
	if (i > len - 1) {
		return false;
	}
	Node<T>* current = head;
	while (i > 0) {
		current = current->next;
		i--;
	}
	Rm(current);
}

template <typename T>
bool LinkedList<T>::Rm(T data) {
	Node<T>* current = head;
	while (current->next != NULL) {
		if (current->data == data) {
			Rm(current);
			return true;
		}
		current = current->next;
	}
	return false;
}

template <typename T>
T LinkedList<T>::Get (int i) {
	if (i > len - 1)
		return NULL;
	Node<T>* current = head;
	for (int nb = 0; nb < i; nb++) {
		current = current->next;
	}
	return current->data;
}

template <typename T>
T LinkedList<T>::Get () {
	if (head)
		return head->data;
	return NULL;
}

template <typename T>
int LinkedList<T>::Lenght () {
	return len;
}

template <typename T>
void LinkedList<T>::Print () {
	Node<T>* current = head;
	while (current) {
		std::cout << current->data << std::endl;
		current = current->next;
	}

}


/**************************************template classes*/
template class LinkedList<int>;
