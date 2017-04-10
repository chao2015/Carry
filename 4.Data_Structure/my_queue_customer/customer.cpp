//
//  customer.cpp
//  20170410
//
//  Created by chenchao on 2017/4/10.
//  Copyright © 2017年 chenchao. All rights reserved.
//

#include "customer.hpp"
#include <iostream>
using namespace std;

Customer::Customer(string name, int age) {
    m_strName = name;
    m_iAge = age;
}

void Customer::printInfo() const {
    cout << "姓名：" << m_strName << endl;
    cout << "年龄：" << m_iAge << endl;
}
