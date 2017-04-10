//
//  main.cpp
//  20170409
//  这是一个简易的顾客排队系统
//  Created by chenchao on 2017/4/9.
//  Copyright © 2017年 chenchao. All rights reserved.
//

#include "my_queue.hpp"
#include "customer.hpp"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    MyQueue iqueue(4);
    Customer C1("刘备", 20);
    Customer C2("曹操", 25);
    Customer C3("孙权", 18);
    iqueue.Enqueue(C1);
    iqueue.Enqueue(C2);
    iqueue.Enqueue(C3);
    iqueue.QueueTraverse();
    
    Customer C4;
    iqueue.Dequeue(C4);
    cout << "正在办理的顾客：" << endl;
    C4.printInfo();
    cout << endl;
    iqueue.QueueTraverse();
    
    return 0;
}
