 ///
 /// @file    my_stack.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-30 23:53:07
 ///
 
#include "my_stack.h"
#include <iostream>

MyStack::MyStack(int input_size = 1) {
	point = 0;
	size = input_size;
	stack = new int[size];
}

MyStack::~MyStack() {
	delete [] stack;
}

bool MyStack::IsEmpty() {
	return point == 0;
}

bool MyStack::IsFull() {
	return point == size;
}

int & MyStack::GetPos() {
	return point;
}

bool MyStack::Push(const int & obj) {
	if(IsFull()) {
		return false;
	} else {
		stack[point++] = obj;
		return true;
	}
}

bool MyStack::Pop(int & obj) {
	if(IsEmpty()) {
		return false;
	} else {
		obj = stack[--point];
		return true;
	}
}
