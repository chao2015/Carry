 ///
 /// @file    my_stack.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-30 23:39:22
 ///
 
#include <iostream>
using namespace std;

class MyStack {
public:
	MyStack(int input_size);
	~MyStack();
	
	bool IsEmpty();
	bool IsFull();
	int & GetPos();
	bool Push(const int & obj);
	bool Pop(int & obj);

private:
	int point;
	int size;
	int * stack;
};


