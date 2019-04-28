//
//  main.cpp
//  der
//
//  Created by Denys Makoviichuk on 3/28/19.
//  Copyright © 2019 Denys Makoviichuk. All rights reserved.
//


#include "derivative.hpp"
#include <iostream>
#include <chrono>

template<class T> void test(const T& t) {
    using DT0 = tr::D<0, T>;
    using DT1 = tr::D<1, T>;
    DT0 dt0;
    DT1 dt1;
    std::cout << "f = " << t << std::endl;
    std::cout << "df0 = " << dt0 << std::endl;
    std::cout << "df1 = " << dt1 << std::endl;
    
    std::cout << "f(1, 2) = " << t({1, 2}) << std::endl;
    std::cout << "df0(1, 2) = " << dt0({1, 2}) << std::endl;
    std::cout << "df1(1, 2) = " << dt1({1, 2}) << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    tr::Variable<0> x1, x;
    tr::Variable<1> x2;
    tr::IntConstant<5> _5;
    tr::IntConstant<4> _4;
    tr::IntConstant<2> _2;
    tr::OneConstant _1;
    //auto f1 = (sin(x) - cos(x))/(sin(x) + cos(x));
    auto f = 1.0 * x;
    auto dfdx = 1 / (x * log(x));
    //auto f = sin(pow(x, _2) +x);
    //test(pow(x1, _5));

    //test(f);
    //test((x1 + 1.0) * sin(x1*x1));

    test(sin(x1) + _2 * (x2*x2) + x1*x2);
    test(f);
    
    
    return 0;
}
