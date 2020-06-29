//
//  Stack.cpp
//  CS300_HW1
//
//  Created by selçuk yılmaz on 2/29/20.
//  Copyright © 2020 selçuk yılmaz. All rights reserved.
//

#include "Stack.hpp"
#include <iostream>


template <class Object>
Stack<Object>::Stack(){
    topOfStack = NULL;
}

template <class Object>
bool Stack<Object>::isFull() const{
    return false;
}

template <class Object>
bool Stack<Object>::isEmpty( ) const{
    return topOfStack == NULL;
}

template <class Object>
const Object & Stack<Object>::top( ) const{
    if (isEmpty())
        throw ("Stack is empty");
    return topOfStack->element;

}
template <class Object>
void Stack<Object>::push(const Object & x){

    topOfStack = new ListNode(x, topOfStack);

}
template <class Object>
void Stack<Object>::pop(){

if (isEmpty())
    throw ("Stack is empty");

topOfStack = topOfStack -> next;

}

template <class Object>
Object Stack<Object>::topAndPop(){
    Object topItem = top();
    pop();
    return topItem;

}


template <class Object>
void Stack<Object>::makeEmpty(){
    while (!isEmpty())
        pop();
}

template <class Object>
const Stack<Object> & Stack<Object>::operator=( const Stack<Object> & rhs ){

if (this != &rhs){

    makeEmpty();

    if (rhs.isEmpty())
        return *this;

    ListNode *rptr = rhs.topOfStack;
    ListNode *ptr = new ListNode( rptr->element );
    topOfStack = ptr;
    for (rptr = rptr->next; rptr != NULL; rptr = rptr->next)
        ptr = ptr->next = new ListNode( rptr->element );

    }
    return *this;

}

template <class Object>
Stack<Object>::Stack(const Stack<Object> & rhs){

topOfStack = NULL;

*this = rhs; // deep copy

}


template <class Object>
Stack<Object>::~Stack(){

makeEmpty();

}
