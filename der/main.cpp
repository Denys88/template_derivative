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
tr::Variable<0> x0;
tr::Variable<1> x1;
tr::IntConstant<5> _5;
tr::IntConstant<4> _4;
tr::IntConstant<3> _3;
tr::IntConstant<2> _2;
tr::OneConstant _1;

__attribute__((noinline)) double run1(double v) {
    tr::D<0, decltype(pow(x0, _5) + pow(x0, _4) + x0)> func;
    return func({v});
};

__attribute__((noinline)) double run2(double v) {
    return 5.0 * pow(v, 4.0) + 4.0 * pow(v, 3.0) + 1.0;
};

__attribute__((noinline)) double run3(double v) {
    tr::D<0, decltype(pow(x0, _5) + pow(x0, _4) + x0 * sin(x0))> func;
    return func({v});
};

__attribute__((noinline)) double run4(double v) {
    return 5.0 * pow(v, 4.0) + 4.0 * pow(v, 3.0) + sin(v) + v * cos(v);
};

auto testrun34() {
    double res3 = 0.0;
    double res4 = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1e7; i++) {
        res3 += run3(double(i) / 1e6);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double time3 = std::chrono::duration<double, std::milli>(end-start).count();
    std::cout << "time1:" << time3 << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1e7; i++) {
        res4 += run4(double(i) / 1e6);
    }
    end = std::chrono::high_resolution_clock::now();
    double time4 = std::chrono::duration<double, std::milli>(end-start).count();
    std::cout << "time2:" << time4 << std::endl;
    return std::pair(time3, time4);
}

int main(int argc, const char * argv[]) {
    // insert code here...
   /* std::cout << "Hello, World!\n";
    
    std::cout<< run1(2.322) << std::endl;
    std::cout<< run2(2.322) << std::endl;
    std::cout<< run3(2.322) << std::endl;
    std::cout<< run4(2.322) << std::endl;
    for (size_t i = 0; i < 10; i++) {
        auto res = testrun34();
        std::cout << res.first << ' vs ' << res.second << std::endl;
    }*/
    
    auto f = (x0 + _1) * sin(x0*x0);
    std::cout<< f({0.0}) << std::endl;
    std::cout<< f({-1.0}) << std::endl;
    return 0;
}
