//
//  main.cpp
//  der
//
//  Created by Denys Makoviichuk on 3/28/19.
//  Copyright © 2019 Denys Makoviichuk. All rights reserved.
//


#include "derivative.hpp"
#include <iostream>

template<class T> void test(const T& t) {
    using DT = tr::D<T>;
    DT dt;
    std::cout << "f = " << t << std::endl;
    std::cout << "df = " << dt << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    tr::Variable x;
    tr::IntConstant<5> _5;
    tr::IntConstant<5> _4;
    tr::IntConstant<2> _2;
    tr::OneConstant _1;
    //auto f1 = (sin(x) - cos(x))/(sin(x) + cos(x));
   // auto f = _5^x;
    //auto f = sin(pow(x, _2) +x);
    test(pow(x, _5) + _4 * pow(x, _2));
    return 0;
}
