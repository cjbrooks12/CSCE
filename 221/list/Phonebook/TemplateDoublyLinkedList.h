#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;

//DoublyLinkedList.h
//-----------------------------------------------------------------------------
template <typename T> class DoublyLinkedList; // class declaration

// list node
template <typename T> class DListNode {
private: T obj;
  DListNode *prev, *next;
  friend class DoublyLinkedList<T>;
public:
  DListNode(T e = T(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
  T getElem() const { return obj; }
  DListNode<T> * getNext() const { return next; }
  DListNode<T> * getPrev() const { return prev; }
};

// doubly linked list
template <typename T> class DoublyLinkedList {
protected: DListNode<T> header, trailer;
public:
  DoublyLinkedList<T>() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList<T>(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T>  *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  DListNode<T> const *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insert(T& obj);
};
// output operator
template <typename T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

//DoublyLinkedList.cpp
//-----------------------------------------------------------------------------
// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
// copy constructor
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  header=T();
  trailer=T();
  header.next = &trailer; trailer.prev = &header;
  
  // Copy from dll
  DListNode<T>* p=dll.getFirst();
  while (p!=dll.getAfterLast()) {
    DListNode<T> *newNode = new DListNode<T>(p->getElem(), trailer.prev,&trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
    
	p=p->getNext();
  }  
}
// assignment operator
template <typename T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  // Delete the whole list
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
  
  // Copy from dll
  DListNode<T>* p=dll.getFirst();
  while (p!=dll.getAfterLast()) {
    DListNode<T> *newNode = new DListNode<T>(p->getElem(), trailer.prev,&trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
    
	p=p->getNext();
  }  
}
// insert the object to the first of the linked list
template <typename T> void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
template <typename T> void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
// remove the first object of the list
template <typename T> T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}
// remove the last object of the list
template <typename T> T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}
// destructor
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
template <typename T> T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
template <typename T> T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
template <typename T> int DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
template <typename T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) { 
  DListNode<T>* p=dll.getFirst();
  while (p!=dll.getAfterLast()) {
    out << p->getElem() << endl;
    p=p->getNext();
  }
  
  return out;
}


//I could not figure out how to get this insert function working correctly. Ideally, an insert would
//	look at an element and if the element to be inserted was less, it would move to the next, and 
// 	repeat until it was not less, and it would get inserted there. With this logic, the running time 
// 	of an insertion would be O(n) with a best case scenario of Big-Theta(1).
template <typename T> void DoublyLinkedList<T>::insert (T& obj) {
	DListNode<T>* p = trailer.getPrev();
	//DListNode<T> *newNode;
	
	//get length of current list
	DListNode<T> *current = getFirst();
	int count = 0;
	while(current != getAfterLast()) {
		count++;
		current = current->getNext(); //iterate
	}
	
	if(count < 1) {
			DListNode<T> *newNode = new DListNode<T>(obj, &header, header.next);
			header.next->prev = newNode;
			header.next = newNode;
	}
	else {
		for(int i = 0; i <= count; ++i) {
			if(obj(p->getElem())) {
				p = p->prev;
			}
			else {
				DListNode<T> *newNode = new DListNode<T>(obj, p->prev, p);
				p->prev->next = newNode;
				p->prev = newNode;
				break;
			}
		}
	}
	
}
