 ///
 /// @file    test_timer.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-15 13:57:15
 ///
 
#include "timer_thread.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

struct Producer {
	void product() {
		::srand(::time(NULL));
		int num=::rand()%100;
		cout<<"produce a number:"<<num<<endl;
	}
};

int main() {
	Producer producer;
	ccspace::TimerThread timer(1,6,std::bind(&Producer::product,&producer));
	timer.Start();
	::sleep(10);
	timer.Stop();  //最后总会打印一次timeout是因为Stop里重置定时器将timeout设为0不阻塞
	return 0;
}
