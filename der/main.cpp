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
    tr::OneConstant _1;
    auto f = (sin(x) - cos(x))/(sin(x) + cos(x));
    //auto f = sin(x*x +x);
    using F = decltype(f);
    using DF = tr::D<F>;
    DF df;
    std::cout << f << "\n";
    std::cout << df << "\n";
    std::cout << f(M_PI) << "\n";
    std::cout << df(M_PI) << "\n";
    std::cout << f << "\n";
    auto f2 = _1 * cos(x);
    tr::S<decltype(f2)> sf2;
    std::cout << sf2 << "\n";
    return 0;
}
