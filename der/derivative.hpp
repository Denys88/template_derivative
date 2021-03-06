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
    template <int DIM, class E> struct Der;
    
    template<int DIM, class E>
    using D = S<typename Der<DIM, E>::Result>;
    
    template<int DIM, template<int> class V, int VDIM>
    struct Der<DIM, V<VDIM> > {
        using Result = ZeroConstant;
    };

    template<int DIM>
    struct Der<DIM, Variable<DIM>> {
        using Result = OneConstant;
    };
    
    template<int DIM, int N>
    struct Der<DIM, IntConstant<N>> {
        using Result = ZeroConstant;
    };
    
    template<int DIM, class L, class R>
    struct Der<DIM, BinaryOperation<L,R, Add>> {
        using DL =D<DIM, L>;
        using DR = D<DIM, R>;
        using Result = S<BinaryOperation<DL, DR, Add>>;
    };
    
    template<int DIM, class L, class R>
    struct Der<DIM, BinaryOperation<L,R, Sub>> {
        using DL = D<DIM, L>;
        using DR = D<DIM, R>;
        using Result = S<BinaryOperation<DL, DR, Sub>>;
    };
    
    template<int DIM, class L, class R>
    struct Der<DIM, BinaryOperation<L,R, Mul>> {
        using DL = D<DIM, L>;
        using DR = D<DIM, R>;
        using LDR = S<BinaryOperation<L, DR, Mul>>;
        using RDL = S<BinaryOperation<DL, R, Mul>>;
        using Result = S<BinaryOperation<LDR, RDL, Add>>;
    };
    
    template<int DIM, class L, class R>
    struct Der<DIM, BinaryOperation<L,R, Div>> {
        using DL = D<DIM, L>;
        using DR = D<DIM, R>;
        using LDR = S<BinaryOperation<L, DR, Mul>>;
        using RDL = S<BinaryOperation<DL, R, Mul>>;
        using RR = S<BinaryOperation<R, R, Mul>>;
        using DIFF = S<BinaryOperation<LDR, RDL, Sub>>;
        using Result = S<BinaryOperation<DIFF, RR, Div>>;
    };
    
    template<int DIM, class L, int E>
    struct Der<DIM, BinaryOperation<L,IntConstant<E>, Exp>> {
        using DL = D<DIM, L>;
        using EL = BinaryOperation<L, IntConstant<E-1>, Exp>;
        using DLE = BinaryOperation<DL, IntConstant<E>, Mul>;
        using Result = S<BinaryOperation<DLE, EL, Mul>>;
    };
    
    template<int DIM, class L, class R>
    struct Der<DIM, BinaryOperation<L,R, Exp>> {
        using LOGL = LogOperation<L>;
        using M = BinaryOperation<LOGL,R, Mul>;
        using Result = S<D<DIM, ExpOperation<M>>>;
    };
    
    template<int DIM, template<class> class UnOp, class E>
    struct Der<DIM, UnOp<E>> {
        using DE = D<DIM, E>;
        using DOP = typename UnOp<E>::Derivative;
        using Result = BinaryOperation<DE, DOP, Mul>;
    };
    

    template <int DIM>
    auto diff = [](auto f) {
        return D<DIM, decltype(f)>();
    };
}
