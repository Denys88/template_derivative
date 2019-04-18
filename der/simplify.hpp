//
//  simplify.hpp
//  der
//
//  Created by Denys Makoviichuk on 3/31/19.
//  Copyright © 2019 Denys Makoviichuk. All rights reserved.
//

namespace tr {
    template<class E>
    struct Simplify {
        using Result = E;
    };
    
    template <class E>
    using S = typename Simplify<E>::Result;
    
    template<class L>
    struct Simplify<BinaryOperation<L, ZeroConstant, Add>> {
        using Result = S<L>;
    };
    
    template<class R>
    struct Simplify<BinaryOperation<ZeroConstant, R, Add>> {
        using Result = S<R>;
    };
    
    template<>
    struct Simplify<BinaryOperation<ZeroConstant, ZeroConstant, Add>> {
        using Result = ZeroConstant;
    };
    
    template<class L>
    struct Simplify<BinaryOperation<L, ZeroConstant, Mul>> {
        using Result = ZeroConstant;
    };
    
    template<class R>
    struct Simplify<BinaryOperation<ZeroConstant, R, Mul>> {
        using Result = ZeroConstant;
    };
    
    template<>
    struct Simplify<BinaryOperation<ZeroConstant, ZeroConstant, Mul>> {
        using Result = ZeroConstant;
    };
    
    template<class L>
    struct Simplify<BinaryOperation<L, OneConstant, Mul>> {
        using Result = S<L>;
    };
    
    template<class R>
    struct Simplify<BinaryOperation<OneConstant, R, Mul>> {
        using Result = S<R>;
    };
    
    template<>
    struct Simplify<BinaryOperation<OneConstant, OneConstant, Mul>> {
        using Result = OneConstant;
    };
    
    template<class E>
    struct Simplify<MinusOperation<MinusOperation<E>>> {
        using Result = S<E>;
    };

    template<class L, class R>
    struct Simplify<BinaryOperation<MinusOperation<L>, R, Mul>> {
        using Result = MinusOperation<S<BinaryOperation<L, R, Mul>>>;
    };

    template<class R>
    struct Simplify<BinaryOperation<OneConstant, MinusOperation<R>, Mul>> {
        using Result = MinusOperation<R>;
    };
    
    template<auto Op, class E>
    struct Simplify<UnaryOperation<Op, E>> {
        using Result = UnaryOperation<Op, S<E>>;
    };
    
    template<class L, class R, class Op>
    struct Simplify<BinaryOperation<L, R, Op>> {
        using Result = BinaryOperation<S<L>, S<R>, Op>;
    };
    
    template<class L, class R>
    struct Simplify<BinaryOperation<L, MinusOperation<R>, Mul>> {
        using Result = MinusOperation<S<BinaryOperation<L, R, Mul>>>;
    };

    
    template<class L, class R>
    struct Simplify<BinaryOperation<MinusOperation<L>, MinusOperation<R>, Mul>> {
        using Result = S<BinaryOperation<L, R, Mul>>;
    };
    
    template<class L, class R>
    struct Simplify<BinaryOperation<MinusOperation<L>, MinusOperation<R>, Add>> {
        using Result = MinusOperation<S<BinaryOperation<L, R, Add>>>;
    };
    
    template<class L, class R>
    struct Simplify<BinaryOperation<MinusOperation<L>, R, Add>> {
        using Result = S<BinaryOperation<R, L, Sub>>;
    };
    
    template<class L, class R>
    struct Simplify<BinaryOperation<L, MinusOperation<R>, Add>> {
        using Result = S<BinaryOperation<L, R, Sub>>;
    };
    
    template<class L, class R>
    struct Simplify<BinaryOperation<L, MinusOperation<R>, Sub>> {
        using Result = S<BinaryOperation<L, R, Add>>;
    };
    
    template<class LR>
    struct Simplify<BinaryOperation<LR, LR, Add>> {
        using Result = BinaryOperation<IntConstant<2>, S<LR>, Mul>;
    };
    
    template<class L>
    struct Simplify<BinaryOperation<L, OneConstant, Exp>> {
        using Result = L;
    };
    
    template<class L>
    struct Simplify<BinaryOperation<L, ZeroConstant, Exp>> {
        using Result = OneConstant;
    };
    
    /*template<class L1, class R1, class L2, class R2>
    struct Simplify<BinaryOperation<BinaryOperation<L1, R1, Add>, BinaryOperation<L2, R2, Add>, Mul>> {
        using L1L2 = BinaryOperation<L1, L2, Mul>;
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using R1L2 = BinaryOperation<R1, L2, Mul>;
        using R1R2 = BinaryOperation<R1, R2, Mul>;
        using SUM1 = BinaryOperation<L1L2, L1R2, Add>;
        using SUM2 = BinaryOperation<R1L2, R1R2, Add>;
        using Result = S<BinaryOperation<SUM1, SUM2, Add>>;
    };
    
    template<class L1, class R1, class L2, class R2>
    struct Simplify<BinaryOperation<BinaryOperation<L1, R1, Sub>, BinaryOperation<L2, R2, Sub>, Mul>> {
        using L1L2 = BinaryOperation<L1, L2, Mul>;
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using R1L2 = BinaryOperation<R1, L2, Mul>;
        using R1R2 = BinaryOperation<R1, R2, Mul>;
        using SUM1 = BinaryOperation<L1L2, L1R2, Sub>;
        using SUM2 = BinaryOperation<R1R2, R1L2, Sub>;
        using Result = S<BinaryOperation<SUM1, SUM2, Add>>;
    };
    
    template<class L1, class R1, class L2, class R2>
    struct Simplify<BinaryOperation<BinaryOperation<L1, R1, Sub>, BinaryOperation<L2, R2, Add>, Mul>> {
        using L1L2 = BinaryOperation<L1, L2, Mul>;
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using R1L2 = BinaryOperation<R1, L2, Mul>;
        using R1R2 = BinaryOperation<R1, R2, Mul>;
        using SUM1 = BinaryOperation<L1L2, L1R2, Add>;
        using SUM2 = BinaryOperation<R1R2, R1L2, Add>;
        using Result = S<BinaryOperation<SUM2, SUM1, Sub>>;
    };
    
    template<class L1, class R1, class L2, class R2>
    struct Simplify<BinaryOperation<BinaryOperation<L1, R1, Add>, BinaryOperation<L2, R2, Sub>, Mul>> {
        using L1L2 = BinaryOperation<L1, L2, Mul>;
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using R1L2 = BinaryOperation<R1, L2, Mul>;
        using R1R2 = BinaryOperation<R1, R2, Mul>;
        using SUM1 = BinaryOperation<L1L2, L1R2, Sub>;
        using SUM2 = BinaryOperation<R1R2, R1L2, Sub>;
        using Result = S<BinaryOperation<SUM2, SUM1, Add>>;
    };
    
    template<class L1, class L2, class R2>
    struct Simplify<BinaryOperation<L1, BinaryOperation<L2, R2, Add>, Mul>> {
        using L1L2 = BinaryOperation<L1, L2, Mul>;
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using Result = S<BinaryOperation<L1L2, L1R2, Add>>;
    };
    
    template<class L1, class R1, class R2>
    struct Simplify<BinaryOperation<BinaryOperation<L1, R1, Add>, R2, Mul>> {
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using R1R2 = BinaryOperation<R1, R2, Mul>;
        using Result = S<BinaryOperation<L1R2, R1R2, Add>>;
    };
    
    template<class L1, class R1, class R2>
    struct Simplify<BinaryOperation<BinaryOperation<L1, R1, Sub>, R2, Mul>> {
        using L1R2 = BinaryOperation<L1, R2, Mul>;
        using R1R2 = BinaryOperation<R1, R2, Mul>;
        using Result = S<BinaryOperation<L1R2, R1R2, Sub>>;
    };*/
    
}
