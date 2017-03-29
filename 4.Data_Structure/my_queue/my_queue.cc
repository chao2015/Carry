 ///
 /// @file    my_queue.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-29 16:56:48
 ///
 
#include "my_queue.h"
#include <iostream>
using namespace std;

MyQueue::MyQueue(int queueCapacity) {
	m_iQueueCapacity = queueCapacity;
	m_pQueue = new int[m_iQueueCapacity];
	ClearQueue();
	/* m_iHead=0;
	 * m_iTail=0;
	 * m_iQueueLength=0;*/
}

MyQueue::~MyQueue() {
	delete [] m_pQueue;
	m_pQueue = NULL;
}

void MyQueue::ClearQueue() {
	m_iHead = 0;
	m_iTail = 0;
	m_iQueueLength = 0;
}

bool MyQueue::QueueEmpty() const {
	return m_iQueueCapacity == 0 ? true : false;
}

bool MyQueue::QueueFull() const {
	return m_iQueueCapacity == m_iQueueLength ? true : false;
}

int MyQueue::QueueLength() const {
	return m_iQueueLength;
}

bool MyQueue::Enqueue(int element) {
	if(QueueFull()) {
		return false;
	} else {
		m_pQueue[m_iTail] = element;
		m_iTail++;
		m_iTail = m_iTail % m_iQueueCapacity;
		m_iQueueLength++;
		return true;
	}
}

bool MyQueue::Dequeue(int & element) {
	if(QueueEmpty()) {
		return false;
	} else {
		element = m_pQueue[m_iHead];
		m_iHead++;
		m_iHead = m_iHead % m_iQueueCapacity;
		m_iQueueLength--;
		return true;
	}
}

void MyQueue::QueueTraverse() {
	for(int i = m_iHead; i < m_iQueueLength + m_iHead; ++i) {
		cout << m_pQueue[i % m_iQueueCapacity] << endl;
	}
}
