#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "TypeInfo.hpp"
#include "MySwap.hpp"
#include "Formatter.hpp"
#include "Derivative.hpp"
#include "PhysicsUnits.hpp"
#include "DecltypeUtils.hpp"

#include <string>

using namespace metaengine;

// TypeInfo tests

TEST_CASE("type info char is unknown") {
    CHECK(std::string(TypeInfo<char>::name) == "Unknown");
    CHECK(TypeInfo<char>::is_numeric == false);
}

TEST_CASE("type info string description") {
    const std::string description = TypeInfo<std::string>::describe();
    CHECK(description.find("text") != std::string::npos);
}

TEST_CASE("pointer to string") {
    CHECK(TypeInfo<std::string*>::is_pointer == true);
    CHECK(TypeInfo<std::string*>::describe().find("pointer to string") != std::string::npos);
}

// Swap tests

TEST_CASE("swap char values") {
    char first = 'a';
    char second = 'z';
    mySwap(first, second);
    CHECK(first == 'z');
    CHECK(second == 'a');
}

TEST_CASE("swap doubles with negative value") {
    double first = -1.5;
    double second = 8.25;
    mySwap(first, second);
    CHECK(first == doctest::Approx(8.25));
    CHECK(second == doctest::Approx(-1.5));
}

TEST_CASE("swap bool false true") {
    bool first = false;
    bool second = true;
    mySwap(first, second);
    CHECK(first == true);
    CHECK(second == false);
}

// Formatter tests

TEST_CASE("int hex lowercase value remains uppercase") {
    CHECK(Formatter<int>::formatHex(31) == "0x1F");
}

TEST_CASE("formatter int label") {
    CHECK(Formatter<int>::formatWithLabel("score", 100) == "score: 100");
}

TEST_CASE("formatter double rounds up") {
    CHECK(Formatter<double>::format(2.999, 2) == "3.00");
}

TEST_CASE("formatter scientific small number") {
    CHECK(Formatter<double>::formatScientific(0.01, 1).find("e") != std::string::npos);
}

TEST_CASE("formatter bool label") {
    CHECK(Formatter<bool>::formatWithLabel("valid", true) == "valid: true");
}

TEST_CASE("formatter string mixed case lower") {
    CHECK(Formatter<std::string>::formatLower("AbC123") == "abc123");
}

TEST_CASE("formatter string mixed case upper") {
    CHECK(Formatter<std::string>::formatUpper("AbC123") == "ABC123");
}

// Compile-time expression tests

TEST_CASE("const negative expression") {
    CHECK(Const<-7>::eval(100) == -7);
    CHECK(Const<-7>::toString() == "-7");
}

TEST_CASE("nested add expression") {
    using Expr = Add<Add<Var, Const<2>>, Const<3>>;
    CHECK(Expr::eval(4) == 9);
}

TEST_CASE("nested mul expression") {
    using Expr = Mul<Add<Var, Const<1>>, Const<2>>;
    CHECK(Expr::eval(5) == 12);
}

TEST_CASE("power fourth") {
    using Expr = Power<Var, 4>;
    CHECK(Expr::eval(2) == 16);
}

// Physics units tests

TEST_CASE("temperature same point") {
    CHECK(celsiusToFahrenheit(-40.0) == doctest::Approx(-40.0));
}

TEST_CASE("miles to km zero") {
    CHECK(milesToKm(0.0) == doctest::Approx(0.0));
}

TEST_CASE("radians degrees zero") {
    CHECK(radiansToDegrees(0.0) == doctest::Approx(0.0));
}

TEST_CASE("constexpr power one") {
    constexpr double result = power(7.0, 1);
    CHECK(result == doctest::Approx(7.0));
}

TEST_CASE("abs positive") {
    CHECK(absVal(12.5) == doctest::Approx(12.5));
}

// decltype utility tests

TEST_CASE("add result type value") {
    CHECK(add(10, 0.5) == doctest::Approx(10.5));
}

TEST_CASE("multiply negative") {
    CHECK(multiply(-3, 4) == -12);
}

TEST_CASE("max equal doubles") {
    CHECK(maxOf(2.5, 2.5) == doctest::Approx(2.5));
}

TEST_CASE("min negative mixed") {
    CHECK(minOf(-2, 3.5) == doctest::Approx(-2.0));
}

TEST_CASE("add result float") {
    CHECK(isAddResultFloating<float, float>() == true);
}

TEST_CASE("multiply result unsigned int") {
    CHECK(isMulResultIntegral<unsigned int, int>() == true);
}

// More expression and derivative tests

TEST_CASE("complex expression evaluation with add and mul") {
    using Expr = Mul<Add<Var, Const<3>>, Add<Var, Const<1>>>;
    CHECK(Expr::eval(2) == 15);
    CHECK(Expr::eval(0) == 3);
}

TEST_CASE("derivative of nested product") {
    using Expr = Derivative<Mul<Add<Var, Const<2>>, Var>>;
    CHECK(Expr::eval(3) == 8);
    CHECK(Expr::eval(0) == 2);
}

TEST_CASE("derivative of product with constant multiplier") {
    using Expr = Derivative<Mul<Const<5>, Var>>;
    CHECK(Expr::eval(10) == 5);
    CHECK(Expr::eval(-3) == 5);
}

TEST_CASE("power of shifted variable") {
    using Expr = Power<Add<Var, Const<1>>, 2>;
    CHECK(Expr::eval(3) == 16);
    CHECK(Expr::eval(0) == 1);
}

// Edge case tests

TEST_CASE("self swap int does not change value") {
    int value = 7;
    mySwap(value, value);
    CHECK(value == 7);
}

TEST_CASE("pointer to pointer type info") {
    CHECK(TypeInfo<int**>::is_pointer == true);
    CHECK(std::string(TypeInfo<int**>::name) == "pointer");
}
