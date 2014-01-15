#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class TemplateDoublyLinkedList; // class declaration

// list node
template <typename T>
class DListNode {
private: T obj;
    DListNode *prev, *next;
    friend class TemplateDoublyLinkedList<T>;
public:
    DListNode(T e=T(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
    T getElem() const { return obj; }
    DListNode<T>* getNext() const { return next; }
    DListNode<T>* getPrev() const { return prev; }
}   ;

// doubly linked list
template <typename T>
class TemplateDoublyLinkedList {
protected: DListNode<T> header, trailer;
public:
    TemplateDoublyLinkedList() : header(), trailer() // constructor
    { header.next = &trailer; trailer.prev = &header; }
    TemplateDoublyLinkedList(TemplateDoublyLinkedList& dll); // copy constructor
    ~TemplateDoublyLinkedList(); // destructor
    TemplateDoublyLinkedList& operator=(TemplateDoublyLinkedList& dll); // assignment operator
    // return the pointer to the first node
    DListNode<T>* getFirst() const { return header.next; }
    // return the pointer to the trailer
    DListNode<T>* getAfterLast() { return &trailer; }
    // inserting an object at its proper location in the linked list
    void insert(const T& newobj);
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
template <typename T>
ostream& operator<<(ostream& out, TemplateDoublyLinkedList<T>& dll);

// extend range_error from <stdexcept>
struct EmptyDLinkedListException: std::range_error {
    explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
// copy constructor
template <typename T>
TemplateDoublyLinkedList<T>::TemplateDoublyLinkedList(TemplateDoublyLinkedList& dll)
{
    // Initialize the list
    header=T();
    trailer=T();
    header.next = &trailer; trailer.prev = &header;
    // Copy from dll
    /* Complete this function */
    DListNode<T> *node = dll.header.next;
    
    while (node != &dll.trailer) {
        insertLast(node->getElem());
        node = node->next;
    }
    
}
// assignment operator
template <typename T>
TemplateDoublyLinkedList<T>& TemplateDoublyLinkedList<T>::operator=(TemplateDoublyLinkedList& dll)
{
    // Delete the whole list
    /* Complete this function */
    header=0;
    trailer=0;
    header.next = &trailer; trailer.prev = &header;
    
    TemplateDoublyLinkedList temporary(dll);
    //header = temporary.header;
    //trailer = temporary.trailer;
    DListNode<T> *node = temporary.header.next;
    while (node != &temporary.trailer) {
        insertLast(node->getElem());
        node = node->next;
    }
    return *this;
}
// insert the object to the first of the linked list
template <typename T>
void TemplateDoublyLinkedList<T>::insertFirst(T newobj)
{
    DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert the object to the first of the linked list
template <typename T>
void TemplateDoublyLinkedList<T>::insert(const T& newobj)
{
    DListNode<T>* newNode = new DListNode<T>(newobj);
    DListNode<T>* iterNode = getFirst();

    while (iterNode != getAfterLast()) {                // Loop through list of nodes
        if (newNode->getElem()((iterNode->getElem()))) {              // Break if this node is less than another, Record(Record)
            newNode->prev = iterNode->prev;
            iterNode->prev->next = newNode;
            newNode->next = iterNode;
            iterNode->prev = newNode;
            break;
        }
        iterNode = iterNode->next;                      // Move the iterating node forward
    }
    if (iterNode == getAfterLast()) {
        insertLast(newNode->getElem());
    }
}

// insert the object to the last of the linked list
template <typename T>
void TemplateDoublyLinkedList<T>::insertLast(T newobj)
{
    DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}
// remove the first object of the list
template <typename T>
T TemplateDoublyLinkedList<T>::removeFirst()
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
template <typename T>
T TemplateDoublyLinkedList<T>::removeLast()
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
template <typename T>
TemplateDoublyLinkedList<T>::~TemplateDoublyLinkedList()
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
template <typename T>
T TemplateDoublyLinkedList<T>::first() const
{
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    return header.next->obj;
}
// return the last object
template <typename T>
T TemplateDoublyLinkedList<T>::last() const
{
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    return trailer.prev->obj;
}
// return the list length
template <typename T>
int TemplateDoublyLinkedListLength(TemplateDoublyLinkedList<T>& dll) {
    DListNode<T> *current = dll.getFirst();
    int count = 0;
    while(current != dll.getAfterLast()) {
        count++;
        current = current->getNext(); //iterate
    }
    return count;
}
// output operator
template <typename T>
ostream& operator<<(ostream& out, TemplateDoublyLinkedList<T>& dll) {
    
    /* Complete this function */
    DListNode<T> *node = dll.getFirst();
    //DListNode *ptr = dll.getAfterLast();
    while (node != dll.getAfterLast()) {
        out << node->getElem() << " ";
        node = node->getNext();
    }
    return out;
}