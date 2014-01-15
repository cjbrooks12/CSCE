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
  DoublyLinkedList<T>(DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList<T>& operator=(DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  DListNode<T> *getAfterLast() { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
};
// output operator
template <typename T> ostream& operator<<(ostream& out, DoublyLinkedList<T>& dll);

//DoublyLInkedList.cpp
//-----------------------------------------------------------------------------
// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
// copy constructor
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>& dll) //O(n)
{
  // Initialize the list
  header=T();
  trailer=T();
  header.next = &trailer; trailer.prev = &header;
  
  //Copy from dll
  DListNode<T>* p=dll.getFirst();
  while (p!=dll.getAfterLast()) { //O(n)
    DListNode<T> *newNode = new DListNode<T>(p->getElem(), trailer.prev,&trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
    
	p=p->getNext();
  }  
}
// assignment operator
template <typename T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>& dll) //O(n)
{
  // Delete the whole list
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) { //O(n)
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
  
  // Copy from dll
  DListNode<T>* p=dll.getFirst();
  while (p!=dll.getAfterLast()) { //O(n)
    DListNode<T> *newNode = new DListNode<T>(p->getElem(), trailer.prev,&trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
    
	p=p->getNext();
  }  
}
// insert the object to the first of the linked list
template <typename T> void DoublyLinkedList<T>::insertFirst(T newobj) //O(1)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}
// insert the object to the last of the linked list
template <typename T> void DoublyLinkedList<T>::insertLast(T newobj) //O(1)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
// remove the first object of the list
template <typename T> T DoublyLinkedList<T>::removeFirst() //O(1)
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
template <typename T> T DoublyLinkedList<T>::removeLast() //O(1)
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
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() //O(n)
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) { //O(n)
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}
// return the first object
template <typename T> T DoublyLinkedList<T>::first() const //O(1)
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}
// return the last object
template <typename T> T DoublyLinkedList<T>::last() const //O(1)
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}
// return the list length
template <typename T> int DoublyLinkedListLength(DoublyLinkedList<T>& dll) { //O(n)
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) { //O(n)
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}
// output operator
template <typename T> ostream& operator<<(ostream& out, DoublyLinkedList<T>& dll) { //O(n)
  
  DListNode<T>* p=dll.getFirst();
  while (p!=dll.getAfterLast()) { //O(n)
    out << p->getElem() << ", ";
    p=p->getNext();
  }
  out << endl;
  
  return out;
}
