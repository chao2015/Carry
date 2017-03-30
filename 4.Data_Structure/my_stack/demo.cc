 ///
 /// @file    my_stack_demo.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-31 00:05:57
 ///
 
#include "my_stack.h"
#include <iostream>
using namespace std;

int main() {
	MyStack mystack(10);
	cout << "开始时mystack是否为空？" << boolalpha 
		 << mystack.IsEmpty() << endl;	//true

	mystack.Push(0);
	cout << "此时mystack是否为空？" << boolalpha
		 << mystack.IsEmpty() << endl;	//false

	for (int i = 1; i < 10; ++i) {
		mystack.Push(i);
	}
	cout << "此时mystack是否已满？" << boolalpha
		 << mystack.IsFull() << endl;	//true

	int pop_element = 0;
	while (mystack.Pop(pop_element))
		cout << pop_element << " ";
	cout << endl;

	return 0;
}
