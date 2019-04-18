//
//  ast.hpp
//  der
//
//  Created by Denys Makoviichuk on 3/28/19.
//  Copyright © 2019 Denys Makoviichuk. All rights reserved.
//
#include <iostream>
#include <math.h>

namespace tr {
    template <class E> struct CosOperation;
    template <class E> struct SinOperation;
    template <class E> struct ExpOperation;
    template <class E> struct LogOperation;
    template <class E> struct MinusOperation;
    template <class E> struct Simplify;
    template <class L, class R, class Op> struct BinaryOperation;
    
    
    
    template<class T>
    auto operator<<(std::ostream& os, const T& t) -> decltype(t.print(os), os)
    {
        t.print(os);
        return os;
    }
    
    template<int V> struct IntConstant{
        double operator()(double inValue) const {
            return V;
        }
        
        void print(std::ostream& os) const {
            os << V;
        }
    };
    
    struct Variable {
        double operator()(double x) const {
            return x;
        }
        
        void print(std::ostream& os) const {
            os << "x";
        }
    };
    
    using ZeroConstant = IntConstant<0>;
    using OneConstant = IntConstant<1>;
    
    
    struct Add {
        inline static double apply(double a, double b) {
            return a + b;
        }
        inline static const char* name() {
            return "+";
        }
    };

    struct Exp {
        inline static double apply(double a, double b) {
            return pow(a, b);
        }
        inline static const char* name() {
            return "^";
        }
    };
    
    struct Sub {
        inline static double apply(double a, double b) {
            return a - b;
        }
        inline static const char* name() {
            return "-";
        }
    };
    
    struct Mul {
        inline static double apply(double a, double b) {
            return a * b;
        }
        inline static const char* name() {
            return "*";
        }
    };
    
    struct Div {
        inline static double apply(double a, double b) {
            return a / b;
        }
        inline static const char* name() {
            return "/";
        }
    };
    
    template <class L, class R, class Op>
    struct BinaryOperation {
        L left;
        R right;
        inline double operator()(double x) const {
            return Op::apply(left(x), right(x));
        }
        
        void print(std::ostream& os) const{
            os << "(" << left << Op::name() << right <<")";
        }
    };
    
    template<class L, class R>
    inline BinaryOperation<L,R, Add> operator+(const L& l, const R& r) {
        return BinaryOperation<L,R, Add>{l, r};
    }
    
    template<class L, class R>
    inline BinaryOperation<L,R, Sub> operator-(const L& l, const R& r) {
        return BinaryOperation<L,R, Sub>{l, r};
    }
   
    template<class L, class R>
    inline BinaryOperation<L,R, Mul> operator*(const L& l, const R& r) {
        return BinaryOperation<L,R, Mul>{l, r};
    }
    
    template<class L, class R>
    inline BinaryOperation<L,R, Div> operator/(const L& l, const R& r) {
        return BinaryOperation<L,R, Div>{l, r};
    }
    
    template<class L, class R>
    inline BinaryOperation<L,R, Exp> pow(const L& l, const R& r) {
        return BinaryOperation<L,R, Exp>{l, r};
    }
    
    template <double(*func)(double) , class E>
    struct UnaryOperation {
        E e;
        inline double operator()(double x) const {
            return func(e(x));
        }
    };

    template <class E>
    struct MinusOperation {
        E e;
        
        void print(std::ostream& os) const{
            os << "-" << this->e;
        }
        
        inline double operator()(double x) const {
            return -e(x);
        }
        
        using Derivative = MinusOperation<OneConstant>;
    };
    
    template<class E>
    inline MinusOperation<E> operator-(const E& e) {
        return MinusOperation<E>{e};
    }
    
    template <class E>
    struct ExpOperation : UnaryOperation<&exp, E> {
        void print(std::ostream& os) const{
            os << "exp"<< "(" << this->e << ")";
        }
        using Derivative = ExpOperation<E>;
    };
    
    template <class E>
    struct SinOperation : UnaryOperation<&sin, E> {
        void print(std::ostream& os) const{
            os << "sin"<< "(" << this->e << ")";
        }
        using Derivative = CosOperation<E>;
    };
    
    template <class E>
    struct CosOperation : UnaryOperation<&cos, E> {
        void print(std::ostream& os) const{
            os << "cos"<< "(" << this->e << ")";
        }
        using Derivative = MinusOperation<SinOperation<E>>;
    };
    
    template <class E>
    struct LogOperation : UnaryOperation<&log, E> {
        void print(std::ostream& os) const{
            os << "log"<< "(" << this->e << ")";
        }
        using Derivative = BinaryOperation<OneConstant, E, Div>;
    };

    template <class E>
    inline ExpOperation<E> exp(const E& rexpr) {
        return ExpOperation<E>{rexpr};
    }
    
    template <class E>
    inline SinOperation<E> sin(const E& rexpr) {
        return SinOperation<E>{rexpr};
    }
    
    template <class E>
    inline CosOperation<E> cos(const E& rexpr) {
        return CosOperation<E>{rexpr};
    }

    template <class E>
    inline LogOperation<E> log(const E& rexpr) {
        return LogOperation<E>{rexpr};
    }
    
}


