// Author : Romain Fournier romain.fournier.095@gmail.com
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "LinkedList.h"
#include "Body.h"

using namespace std;

//*****CONSTRUCTORS

/* Creates an empty list
*/
template <typename T>
LinkedList<T>::LinkedList(): head(NULL), tail(NULL), current(NULL), len(0) {
}

/* Creates a list of lenght 1
*/
template <typename T>
LinkedList<T>::LinkedList(T* data): len(1) {
	head = (Node<T>*)malloc(sizeof(Node<T>));
	tail = head;
	current = head;

	head->next = NULL;
	head->prev = NULL;
	head->data = data;
}

//*****METHODS

/* Adds an element to the end of the list.
*/
template <typename T>
void LinkedList<T>::Add(T* data) {
	Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>));

	newNode->prev = tail;
	newNode->next = NULL;
	newNode->data = data;
	if (tail) {
		tail->next = newNode;
		tail = newNode;
	}

	if (len == 0) {
		head = newNode;
		tail = newNode;
		current = newNode;
	}
	len++;
}

/* Private : Removes the node n from the list
*/
template <typename T>
void LinkedList<T>::Rm(Node<T>* n) {
	if (n == current) { //Moves the <current> pointer forward (backwards if n is the tail)
		if (n == tail)
			current = n->prev;
		else
			current = n->next;
	}
	if (n == head) //New head
		head = n->next;
	if (n == tail) //New tail
		tail = n->prev;

	//Removes n from the list
	if (n->prev)
		n->prev->next = n->next;
	if (n->next)
		n->next->prev = n->prev;

	free(n);
	len--;
}

/* Removes the data at the location i
 * Returns true if an element has been deleted
*/
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
	return true;
}

/* Removes the first instance of T, if it exists
 * Returns true if an element has been deleted
*/
template <typename T>
bool LinkedList<T>::Rm(T* data) {
	Node<T>* current = head;
	while (current != NULL) {
		if (current->data == data) {
			Rm(current);
			return true;
		}
		current = current->next;
	}
	return false;
}

/* Gets the data at the location i
 * /!\ slow if you need more than one element
 * if you need a sequence of all elements, use Pull() instead !
*/
template <typename T>
T* LinkedList<T>::Get (int i) {
	if (i > len - 1)
		return NULL;
	Node<T>* current = head;
	for (int nb = 0; nb < i; nb++) {
		current = current->next;
	}
	return current->data;
}

/* Returns the length of the list
*/
template <typename T>
int LinkedList<T>::Lenght () {
	return len;
}

/* Prints the list
*/
template <typename T>
void LinkedList<T>::Print () {
	Node<T>* c = head;
	std::cout << "Length: " << len << "  {";
	while (c) {
		if (c == current) {
			std::cout << "*";
		}
		std::cout << c->data;
		c = c->next;
		if (c)
			std::cout << ", ";
	}
	std::cout << "}" << std::endl;
}

/* Behaves like a pile, get the data of the current element,
 * then sets the current element as current->next.
 * Used to get all elements sequentially as it is WAY FASTER
 * /!\ Use this instead of Get(i) if you need all elements !!
*/
template <typename T>
T* LinkedList<T>::Pull () {
	if (current == NULL)
		return NULL;
	T* ans = current->data;
	current = current->next;
	return ans;
}

/* Sets the pointer <current> as head
*/
template <typename T>
void LinkedList<T>::ResetPull () {
	current = head;
}


//*****TEMPLATE CLASSES
template class LinkedList<int>;
template class LinkedList<Body>;
