//
//  Stack.hpp
//  CS300_HW1
//
//  Created by selçuk yılmaz on 2/29/20.
//  Copyright © 2020 selçuk yılmaz. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>

#include <iostream>
using namespace std;

template <class Object>
class Stack{
public:
Stack();
Stack(const Stack & rhs);
~Stack();
    
bool isEmpty() const;
bool isFull() const;

void makeEmpty();
void pop();
void push(const Object & x);

Object topAndPop();

const Object & top() const;
const Stack & operator=(const Stack & rhs);

private:
struct ListNode{

Object element;

ListNode *next;
ListNode(const Object & theElement, ListNode * n = NULL)
: element(theElement ),next(n) {}
};
ListNode *topOfStack; // list itself is the stack
};






#endif /* Stack_hpp */
