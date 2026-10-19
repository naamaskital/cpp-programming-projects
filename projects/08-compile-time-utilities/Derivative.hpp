#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

#include <string>

namespace metaengine {

// Represents a constant number known at compile time.
template <int N>
struct Const {
    static constexpr int eval(int /* x */) {
        return N;
    }

    static std::string toString() {
        return std::to_string(N);
    }
};

// Represents the variable x.
struct Var {
    static constexpr int eval(int x) {
        return x;
    }

    static std::string toString() {
        return "x";
    }
};

// Represents addition of two expressions.
template <typename Left, typename Right>
struct Add {
    static constexpr int eval(int x) {
        return Left::eval(x) + Right::eval(x);
    }

    static std::string toString() {
        return "(" + Left::toString() + " + " + Right::toString() + ")";
    }
};

// Represents multiplication of two expressions.
template <typename Left, typename Right>
struct Mul {
    static constexpr int eval(int x) {
        return Left::eval(x) * Right::eval(x);
    }

    static std::string toString() {
        return "(" + Left::toString() + " * " + Right::toString() + ")";
    }
};

// Represents Base^Exponent using compile-time recursion.
template <typename Base, int Exponent>
struct Power {
    static constexpr int eval(int x) {
        return Base::eval(x) * Power<Base, Exponent - 1>::eval(x);
    }

    static std::string toString() {
        return "(" + Base::toString() + "^" + std::to_string(Exponent) + ")";
    }
};

// Base case for power recursion.
template <typename Base>
struct Power<Base, 0> {
    static constexpr int eval(int /* x */) {
        return 1;
    }

    static std::string toString() {
        return "(" + Base::toString() + "^0)";
    }
};

// Main template for symbolic derivative.
template <typename Expression>
struct Derive;

// Helper alias for getting the derivative type.
template <typename Expression>
using Derivative = typename Derive<Expression>::type;

// The derivative of a constant is 0.
template <int N>
struct Derive<Const<N>> {
    using type = Const<0>;
};

// The derivative of x is 1.
template <>
struct Derive<Var> {
    using type = Const<1>;
};

// Sum rule: (f + g)' = f' + g'.
template <typename Left, typename Right>
struct Derive<Add<Left, Right>> {
    using type = Add<Derivative<Left>, Derivative<Right>>;
};

// Product rule: (f * g)' = f' * g + f * g'.
template <typename Left, typename Right>
struct Derive<Mul<Left, Right>> {
    using type = Add<Mul<Derivative<Left>, Right>, Mul<Left, Derivative<Right>>>;
};

} // namespace metaengine

#endif