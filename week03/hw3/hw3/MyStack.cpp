#include"MyStack.h"
#include"Coordinate.h"

using namespace std;

template <class T>
MyStack<T>::MyStack(){
    head=NULL;
    size=0;
}

template <class T>
MyStack<T>::~MyStack(){}

template <class T>
void MyStack<T>::push(T& v){
    class Node *in=new Node(v,head);
    head=in;
    size++;
}

template <class T>
void MyStack<T>::pop(){
    head=head->next;
    size--;
}

template <class T>
T& MyStack<T>::top(){
    return head->value;
}

template <class T>
size_t MyStack<T>::getSize() const{
    return size;
}

template <class T>
bool MyStack<T>::empty() const{
    return size==0?1:0;
}

template <class T>
MyStack<T>::Node::Node(T& v, Node* n):value(v){
    next=n;
}

template class MyStack < char >;
template class MyStack < Coordinate >;
