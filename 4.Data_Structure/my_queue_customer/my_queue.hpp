//
//  my_queue.hpp
//  20170410
//
//  Created by chenchao on 2017/4/10.
//  Copyright © 2017年 chenchao. All rights reserved.
//

#ifndef my_queue_hpp
#define my_queue_hpp

#include "customer.hpp"
#include <stdio.h>

class MyQueue {
public:
    MyQueue(int capacity);
    virtual ~MyQueue();
    
    bool IsEmpty() const;
    bool IsFull() const;
    bool Enqueue(Customer element);
    bool Dequeue(Customer & element);
    void QueueTraverse();
    
private:
    Customer * m_pQueue;
    int m_iQueueLength;
    int m_iQueueCapacity;
    int m_iHead;
    int m_iTail;
};

#endif /* my_queue_hpp */
