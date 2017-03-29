 ///
 /// @file    demo.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-29 18:26:25
 ///
 
#include "my_queue.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
	MyQueue * p = new MyQueue(4);

	p->Enqueue(1);
	p->Enqueue(2);
	p->Enqueue(3);
	p->Enqueue(4);
	p->Enqueue(5);
	p->QueueTraverse();	//1 2 3 4
	cout << endl;

	int delete_number = 0;
	p->Dequeue(delete_number);
	cout << delete_number << endl;	//1
	cout << endl;

	p->Dequeue(delete_number);
	cout << delete_number << endl;	//2
	cout << endl;

	p->QueueTraverse(); //3 4
	cout << endl;

	p->ClearQueue();
	cout << "after clear:" << endl;
	p->QueueTraverse(); //after clear:
	cout << endl;

	p->Enqueue(10);
	p->Enqueue(11);
	p->QueueTraverse();	//10 11

	delete p;
	p = NULL;

	//system("pause");  //windows
	return 0;
}
