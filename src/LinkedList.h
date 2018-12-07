/********************************************************
*  File : LinkedList.h
*  Description : A LinkedList implementation, should be
*  used to store references and pointer as it uses the
*  NULL value
*
*  Author : Romain Fournier romain.fournier.095@gmail.com
*  4/12/2018
*/

#ifndef __LinkedList
#define __LinkedList

using namespace std;

template <typename T>
struct Node {
	Node* next;
	Node* prev;
	T data;
};

template <typename T>
class LinkedList {
 private:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* current;
	int len;
 public:
	LinkedList();
	LinkedList(T data);
	void Add(T data);
	bool RmAt(int i);
	bool Rm(T data);
	T Get(int i);
	int Lenght();
	void Print();
	T Pull();
	void ResetPull();
 private:
	void Rm(Node<T>* n);
};

#endif
