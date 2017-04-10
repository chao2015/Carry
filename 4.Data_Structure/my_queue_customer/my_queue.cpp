//
//  my_queue.cpp
//  20170410
//
//  Created by chenchao on 2017/4/10.
//  Copyright © 2017年 chenchao. All rights reserved.
//

#include "my_queue.hpp"
#include <iostream>
using namespace std;

MyQueue::MyQueue(int capacity) {
    m_iQueueCapacity = capacity;
    m_pQueue = new Customer[m_iQueueCapacity];
    m_iQueueLength = 0;
    m_iHead = 0;
    m_iTail = 0;
}

MyQueue::~MyQueue() {
    delete [] m_pQueue;
}

bool MyQueue::IsEmpty() const {
    return m_iQueueLength == 0 ? true : false;
}

bool MyQueue::IsFull() const {
    return m_iQueueLength == m_iQueueCapacity ? true : false;
}

bool MyQueue::Enqueue(Customer element) {
    if(IsFull())
        return false;
    m_pQueue[m_iTail++] = element;
    m_iTail = m_iTail % m_iQueueCapacity;
    ++m_iQueueLength;
    return true;
}

bool MyQueue::Dequeue(Customer & element) {
    if(IsEmpty())
        return false;
    element = m_pQueue[m_iHead++];
    m_iHead = m_iHead % m_iQueueCapacity;
    --m_iQueueLength;
    return true;
}

void MyQueue::QueueTraverse() {
    for (int i = m_iHead; i < m_iHead + m_iQueueLength; ++i) {
        m_pQueue[i % m_iQueueCapacity].printInfo();
        cout << "前面还有" << (i - m_iHead) << "人在排队" << endl;
        cout << endl;
    }
}

