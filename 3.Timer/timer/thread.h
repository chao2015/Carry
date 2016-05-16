 ///
 /// @file    Thread.h
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-14 15:38:10
 ///

#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include "noncopyable.h"
#include <pthread.h>
#include <functional>

namespace ccspace {
//注意：1.std::function<void()>和头文件
class Thread : Noncopyable {
	typedef std::function<void()> ThreadCallback;

 public:
	Thread(ThreadCallback callback);
	~Thread();

	void Start();
	void Join();
	//void setThreadCallback(ThreadCallback callback);
	static void* ThreadFunc(void* arg);

 private:
	pthread_t thread_id_;
	bool is_running_;
	ThreadCallback callback_;
};

}  //namespace ccspace

#endif
