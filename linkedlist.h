#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

template <class T>
class LinkedList;

template <class T>
class ListNode {
    T *data;
    ListNode *next;
    ListNode(T *d, ListNode<T> *n);
    ~ListNode();
    friend class LinkedList<T>;
}; // ListNode class template

template <class T>
class LinkedList
{
    ListNode<T> *head;
public:
    LinkedList();
    ~LinkedList();
    const T* operator[] (int index)const;
    T* operator[] (int index);
    LinkedList& operator+= (T *data);
    LinkedList& operator= (const LinkedList &linkedList);
}; // LinkedList class template

#include "linkedlist.cpp"

#endif	/* LINKEDLIST_H */

