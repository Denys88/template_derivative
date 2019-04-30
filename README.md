# С++ Template Compile-Time Differentiation

Test:

```cpp
    tr::Variable<0> x0;
    tr::Variable<1> x1;
    tr::IntConstant<5> _5;
    tr::IntConstant<4> _4;
    tr::IntConstant<3> _3;
    tr::IntConstant<2> _2;
    tr::OneConstant _1;
    auto f = (x0 + _1) * sin(x0*x0) + cos(x1);
    std::cout<< f << std::endl;
    std::cout<< f({0.0}) << std::endl;
    std::cout<< f({-1.0}) << std::endl;
    using DX0 = tr::D<0, decltype(f)>;
    using DX1 = tr::D<1, decltype(f)>;
    DX0 dfdx0;
    DX1 dfdx1;
    std::cout<< dfdx0({0.0}) << std::endl;
    std::cout<< dfdx1({-1.0}) << std::endl;
    
    std::cout<< dfdx0 << std::endl;
    std::cout<< dfdx1 << std::endl;
```
