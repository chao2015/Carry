 ///
 /// @file    demo.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-31 02:06:08
 ///

#include "my_stack_template.h"
#include <iostream>
using namespace std;

int main() {
	MyStack<int> mystack(10);
	cout << "开始时mystack是否为空？" << boolalpha
		 << mystack.IsEmpty() << endl;

	mystack.Push(0);
	cout << "此时mystack是否为空？" << boolalpha
		 << mystack.IsEmpty() << endl;

	for (int i = 1; i < 10; ++i) {
		mystack.Push(i);
	}
	cout << "此时mystack是否已满？" << boolalpha
		 << mystack.IsFull() << endl;

	int stack_element = 0;
	while (mystack.Pop(stack_element))
		cout << stack_element << " ";
	cout << endl;

	return 0;
}
