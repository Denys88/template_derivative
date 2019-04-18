//
//  derivative.hpp
//  der
//
//  Created by Denys Makoviichuk on 3/31/19.
//  Copyright © 2019 Denys Makoviichuk. All rights reserved.
//
#include "ast.hpp"
#include "simplify.hpp"

namespace tr {
    template <class E> struct SimpleD;
    template <class E> struct Der;
    template<class E>
    using D = typename Der<E>::Result;
    
    template<>
    struct SimpleD<Variable> {
        using Result = OneConstant;
    };
    
    template<int N>
    struct SimpleD<IntConstant<N>> {
        using Result = ZeroConstant;
    };
    
    
    template<class L, class R>
    struct SimpleD<BinaryOperation<L,R, Add>> {
        using DL = typename SimpleD<L>::Result;
        using DR = typename SimpleD<R>::Result;
        using Result = BinaryOperation<DL, DR, Add>;
    };
    
    template<class L, class R>
    struct SimpleD<BinaryOperation<L,R, Sub>> {
        using DL = typename SimpleD<L>::Result;
        using DR = typename SimpleD<R>::Result;
        using Result = BinaryOperation<DL, DR, Sub>;
    };
    
    template<class L, class R>
    struct SimpleD<BinaryOperation<L,R, Mul>> {
        using DL = typename SimpleD<L>::Result;
        using DR = typename SimpleD<R>::Result;
        using LDR = BinaryOperation<L, DR, Mul>;
        using RDL = BinaryOperation<DL, R, Mul>;
        using Result = BinaryOperation<LDR, RDL, Add>;
    };
    
    template<class L, class R>
    struct SimpleD<BinaryOperation<L,R, Div>> {
        using DL = typename SimpleD<L>::Result;
        using DR = typename SimpleD<R>::Result;
        using LDR = BinaryOperation<L, DR, Mul>;
        using RDL = BinaryOperation<DL, R, Mul>;
        using RR = BinaryOperation<R, R, Mul>;
        using DIFF = BinaryOperation<LDR, RDL, Sub>;
        using Result = BinaryOperation<DIFF, RR, Div>;
    };
    
    template<template<class> class UnOp, class E>
    struct SimpleD<UnOp<E>> {
        using DE = typename SimpleD<E>::Result;
        using DOP = typename UnOp<E>::Derivative;
        using Result = BinaryOperation<DE, DOP, Mul>;
    };
    
    template<>
    struct Der<Variable> {
        using Result = OneConstant;
    };
    
    template<int N>
    struct Der<IntConstant<N>> {
        using Result = ZeroConstant;
    };
    
    
    template<class L, class R>
    struct Der<BinaryOperation<L,R, Add>> {
        using DL =S<D<L>>;
        using DR = S<D<R>>;
        using Result = S<BinaryOperation<DL, DR, Add>>;
    };
    
    template<class L, class R>
    struct Der<BinaryOperation<L,R, Sub>> {
        using DL = S<D<L>>;
        using DR = S<D<R>>;
        using Result = S<BinaryOperation<DL, DR, Sub>>;
    };
    
    template<class L, class R>
    struct Der<BinaryOperation<L,R, Mul>> {
        using DL = S<D<L>>;
        using DR = S<D<R>>;
        using LDR = S<BinaryOperation<L, DR, Mul>>;
        using RDL = S<BinaryOperation<DL, R, Mul>>;
        using Result = S<BinaryOperation<LDR, RDL, Add>>;
    };
    
    template<class L, class R>
    struct Der<BinaryOperation<L,R, Div>> {
        using DL = S<D<L>>;
        using DR = S<D<R>>;
        using LDR = S<BinaryOperation<L, DR, Mul>>;
        using RDL = S<BinaryOperation<DL, R, Mul>>;
        using RR = S<BinaryOperation<R, R, Mul>>;
        using DIFF = S<BinaryOperation<LDR, RDL, Sub>>;
        using Result = S<BinaryOperation<DIFF, RR, Div>>;
    };
    
    template<class L, int E>
    struct Der<BinaryOperation<L,IntConstant<E>, Exp>> {
        using DL = S<D<L>>;
        using EL = BinaryOperation<L,IntConstant<E-1>, Exp>;
        using Result = S<BinaryOperation<IntConstant<E>, EL, Mul>>;
    };
    
    template<class L, class R>
    struct Der<BinaryOperation<L,R, Exp>> {
        using LOGL = LogOperation<L>;
        using M = BinaryOperation<LOGL,R, Mul>;
        using DM = S<D<M>>;
        using Result = BinaryOperation<DM, ExpOperation<M>, Mul>;
    };
    
    template<template<class> class UnOp, class E>
    struct Der<UnOp<E>> {
        using DE = S<D<E>>;
        using DOP = typename UnOp<E>::Derivative;
        using Result = S<BinaryOperation<DE, DOP, Mul>>;
    };
    

}
