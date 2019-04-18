//
//  main.cpp
//  der
//
//  Created by Denys Makoviichuk on 3/28/19.
//  Copyright © 2019 Denys Makoviichuk. All rights reserved.
//


#include "derivative.hpp"
#include <iostream>

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
    auto f = pow(x, _5) + _4 * pow(x, _2);
    using F = decltype(f);
    using DF = tr::D<F>;
    DF df;
    std::cout << f << "\n";
    std::cout << df << "\n";
    //std::cout << f(M_PI) << "\n";
    //std::cout << df(M_PI) << "\n";
    //std::cout << f << "\n";
    //auto f2 = _1 * cos(x);
    //tr::S<decltype(f2)> sf2;
    //std::cout << sf2 << "\n";
    return 0;
}
