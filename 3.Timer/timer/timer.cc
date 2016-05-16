 ///
 /// @file    timer.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-15 11:44:34
 ///
 
#include "timer.h"
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

int CreateTimerFd() {
    //参数1:int clockid:
    //  CLOCK_REALTIME:相对时间，1970开始;
    //  CLOCK_MONOTONIC：绝对时间，系统重启开始.
    //参数2:int flags:默认为0.
    //RETURN: new fd, -1 is error.
	int fd=::timerfd_create(CLOCK_REALTIME,0);
	if(-1==fd) {
		perror("timerfd_create error");
	}
	return fd;
}

void SetTimerfd(int timerfd,int initial_time,int interval_time) {
	struct itimerspec new_time;
	new_time.it_value.tv_sec=initial_time;
	new_time.it_value.tv_nsec=0;
	new_time.it_interval.tv_sec=interval_time;
	new_time.it_interval.tv_nsec=0;
    //参数1:int fd.
    //参数2:int flags:0表示相对定时器;TFD_TIMER_ABSTIME:绝对定时器.
    //参数3:见man timerfd_create:
    //  const struct itimerspec*:struct timespec it_value和it_interval.
    //  struct timespec:time_t tv_sec和long tv_nsec.
    //参数4:struct itimerspec:默认为NULL.
    //RETURN:0 is success;-1 is error.
	int ret=::timerfd_settime(timerfd,0,&new_time,NULL);
	if(-1==ret) {
		perror("timerfd_settime error");
	}
}

void StopTimerfd(int timerfd) {
	SetTimerfd(timerfd,0,0);
}

int ReadTimerfd(int timerfd) {
	uint64_t howmany;
	int ret=read(timerfd,&howmany,sizeof(uint64_t));
	if(ret!=sizeof(uint64_t)){
		perror("read error");
	}
	return ret;
}

namespace ccspace {

Timer::Timer(int initial_time,int interval_time,TimerCallback callback)
	: timerfd_(CreateTimerFd()),
	  initial_time_(initial_time),
	  interval_time_(interval_time),
	  is_started_(false),
	  callback_(callback) {
}

Timer::~Timer() {
	if(is_started_){
		Stop();
	}
}

void Timer::Start() {
	SetTimerfd(timerfd_,initial_time_,interval_time_);
	is_started_=true;

	struct pollfd pollfd;
	pollfd.fd=timerfd_;
	pollfd.events=POLLIN;  //there is data to read

	while(is_started_){
        //参数1:struct pollfd fds[]，用于存放需要检测状态的pollfd数组.
        //  struct pooled:int fd;short events(requested events);short revents(returned).
        //参数2:nfds_t nfds,struct pollfd结构体数量(数组的大小).
        //参数3:int timeout:poll函数调用阻塞的时间(毫秒).
        //  如果timeout==0，那么poll() 函数立即返回而不阻塞;
        //  如果timeout==INFTIM，那么poll() 函数会一直阻塞下去.
        //RETURN:>0:数组fds中准备好读、写或出错状态的那些socket描述符的总数量.
        //  0 is timeout;-1 is error并会自动设置全局变量errno.
        /*每当调用这个函数之后，系统不会清空这个数组，操作起来比较方便；特别是
        对于socket连接比较多的情况下，在一定程度上可以提高处理的效率；这一点与
        select()函数不同，调用select()函数之后，select()函数会清空它所检测的
        socket描述符集合，导致每次调用select()之前都必须把socket描述符重新加入
        到待检测的集合中；因此，select()函数适合于只检测一个socket描述符的情况，
        而poll()函数适合于大量socket描述符的情况. */
		int ret=::poll(&pollfd,1,5000); 
		if(-1==ret){
			if(errno==EINTR)
				continue;
			exit(EXIT_FAILURE);
		}else if(0==ret){
			cout<<"poll timeout"<<endl;
		}else{
			if(pollfd.revents & POLLIN){
				ReadTimerfd(timerfd_);
				if(callback_){
					callback_();  //处理任务
				}
			}
		}
	}
}

void Timer::Stop() {
	if(is_started_){
		::StopTimerfd(timerfd_);
		is_started_=false;
	}
}
}  //namespace ccspace
