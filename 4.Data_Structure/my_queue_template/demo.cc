 ///
 /// @file    demo.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-04-04 17:20:09
 ///
 
#include "my_queue.h"
#include <iostream>
using namespace std;

int main() {
	MyQueue<int> myqueue(4);
	myqueue.Enqueue(10);
	myqueue.Enqueue(12);
	myqueue.Enqueue(14);
	myqueue.Enqueue(16);
	myqueue.Enqueue(18);
	myqueue.QueueTraverse();	// 10 12 14 16

	int delete_element = 0;
	myqueue.Dequeue(delete_element);
	cout << delete_element << endl;	// 10
	myqueue.QueueTraverse();	// 12 14 16

	myqueue.ClearQueue();
	myqueue.QueueTraverse();	// endl

	myqueue.Enqueue(20);
	myqueue.Enqueue(30);
	myqueue.QueueTraverse();	// 20 30

	return 0;
}
