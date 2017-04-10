 ///
 /// @file    my_queue.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-04-01 09:23:51
 ///

#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

#include <iostream>
using namespace std;

template <class T>
class MyQueue {
public:
	MyQueue(int queueCapacity);
	virtual ~MyQueue();
	
	void ClearQueue();
	bool IsEmpty() const;
	bool IsFull() const;
	int QueueLength();
	bool Enqueue(T element);
	bool Dequeue(T & element);
	void QueueTraverse();
private:
	T * m_pQueue;
	int m_iQueueLength;
	int m_iQueueCapacity;
	int m_iHead;
	int m_iTail;
};

template <class T>
MyQueue<T>::MyQueue(int queueCapacity) {
	m_iQueueCapacity = queueCapacity;
	m_pQueue = new T[m_iQueueCapacity];
	ClearQueue();
}

template <class T>
MyQueue<T>::~MyQueue() {
	delete [] m_pQueue;
}

template <class T>
void MyQueue<T>::ClearQueue() {
	m_iQueueLength = 0;
	m_iHead = 0;
	m_iTail = 0;
}

template <class T>
bool MyQueue<T>::IsEmpty() const {
	return m_iQueueLength == 0 ? true : false;
}

template <class T>
bool MyQueue<T>::IsFull() const {
	return m_iQueueLength == m_iQueueCapacity ? true : false;
}

template <class T>
int MyQueue<T>::QueueLength() {
	return m_iQueueLength;
}

template <class T>
bool MyQueue<T>::Enqueue(T element) {
	if(IsFull()) {
		return false;
	} else {
		m_pQueue[m_iTail++] = element;
		++m_iQueueLength;
		return true;
	}
}

template <class T>
bool MyQueue<T>::Dequeue(T & element) {
	if(IsEmpty()) {
		return false;
	} else {
		element = m_pQueue[m_iHead++];
		--m_iQueueLength;
		return true;
	}
}

template <class T>
void MyQueue<T>::QueueTraverse() {
	for(int i = m_iHead; i < m_iHead + m_iQueueLength; ++i) {
		cout << m_pQueue[i % m_iQueueCapacity] << " ";
	}
	cout << endl;
}


#endif
