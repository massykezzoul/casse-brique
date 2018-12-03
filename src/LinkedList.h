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
	int len;
 public:
	LinkedList();
	LinkedList(T data);
	void Add(T data);
	bool RmAt(int i);
	bool Rm(T data);
	T Get(int i);
	T Get();
	int Lenght();
	void Print();
 private:
	void Rm(Node<T>* n);
};

#endif
