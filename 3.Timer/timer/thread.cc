 ///
 /// @file    thread.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-14 15:55:59
 ///

#include "thread.h"

namespace ccspace {

Thread::Thread(ThreadCallback callback)
	: thread_id_(0),
	  is_running_(false), 
	  callback_(callback) {
}

Thread::~Thread() {
	if(is_running_){
		pthread_detach(thread_id_);
	}
	is_running_=false;
}

void Thread::Start() {
	pthread_create(&thread_id_,NULL,ThreadFunc,this);
	is_running_=true;
}

void Thread::Join() {
	pthread_join(thread_id_,NULL);
	is_running_=false;
}
#if 0
void Thread::setThreadCallback(ThreadCallback callback) {
	callback_=callback;
}
#endif
void* Thread::ThreadFunc(void* arg) {
	Thread* pThread=static_cast<Thread*>(arg);
	if(pThread){
		pThread->callback_();  //执行回调函数，在class Product和class Consume中实现回调函数
	}
}

}  //namespace ccspace
