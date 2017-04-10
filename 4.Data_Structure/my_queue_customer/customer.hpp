//
//  customer.hpp
//  20170410
//
//  Created by chenchao on 2017/4/10.
//  Copyright © 2017年 chenchao. All rights reserved.
//

#ifndef customer_hpp
#define customer_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Customer {
public:
    Customer(string name = "", int age = 0);
    void printInfo() const;
    
private:
    string m_strName;
    int m_iAge;
};

#endif /* customer_hpp */
