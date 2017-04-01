 ///
 /// @file    my_stack_template.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-31 01:07:24
 ///
 
#include <iostream>
using namespace std;

template <class T = int>
class MyStack {
public:
	MyStack(int stack_size);
	~MyStack();

	bool IsEmpty();
	bool IsFull();
	int & GetPos();
	bool Push(const T);
	bool Pop(T &);

private:
	int size;
	int point;
	T * stack;
};

template <class T>
MyStack<T>::MyStack(int stack_size) {
	size = stack_size;
	point = 0;
	stack = new T[size];
}

template <class T>
MyStack<T>::~MyStack() {
	delete [] stack;
}

template <class T>
bool MyStack<T>::IsEmpty() {
	return point == 0;
}

template <class T>
bool MyStack<T>::IsFull() {
	return point == size;	//这里是设置size成员变量的原因
}

template <class T>
int & MyStack<T>::GetPos() {
	return point;
}

template <class T>
bool MyStack<T>::Push(const T element) {
	if(IsFull()) {
		return false;
	} else {
		stack[point++] = element;
		return true;
	}
}

template <class T>
bool MyStack<T>::Pop(T & element) {
	if(IsEmpty()) {
		return false;
	} else {
		element = stack[--point];
		return true;
	}
}

