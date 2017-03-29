 ///
 /// @file    my_queue.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2017-03-29 15:21:50
 ///
 
#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

class MyQueue {
public:
	MyQueue(int queueCapacity);
	virtual ~MyQueue();

	void ClearQueue();
	bool QueueEmpty() const;
	bool QueueFull() const;
	int QueueLength() const;
	bool Enqueue(int element);
	bool Dequeue(int & element);
	void QueueTraverse();

private:
	int *m_pQueue;
	int m_iQueueLength;
	int m_iQueueCapacity;
	int m_iHead;
	int m_iTail;
};

#endif
