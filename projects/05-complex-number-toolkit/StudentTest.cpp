#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "ComplexArray.hpp"

using namespace complex_math;

TEST_CASE("Student - default complex is zero") {
    Complex value;

    CHECK(value.isZero());
}

TEST_CASE("Student - set real and imaginary values") {
    Complex value;

    value.setReal(4);
    value.setImag(5);

    CHECK(value == Complex(4, 5));
}

TEST_CASE("Student - conjugate changes imaginary sign") {
    Complex value(2, 7);

    CHECK(value.conjugate() == Complex(2, -7));
}

TEST_CASE("Student - magnitude of 6 and 8") {
    Complex value(6, 8);

    CHECK(value.magnitude() == doctest::Approx(10.0));
}

TEST_CASE("Student - complex addition") {
    Complex first(1, 2);
    Complex second(3, 4);

    CHECK(first + second == Complex(4, 6));
}

TEST_CASE("Student - complex subtraction") {
    Complex first(5, 6);
    Complex second(2, 1);

    CHECK(first - second == Complex(3, 5));
}

TEST_CASE("Student - complex multiplication") {
    Complex first(1, 2);
    Complex second(3, 4);

    CHECK(first * second == Complex(-5, 10));
}

TEST_CASE("Student - divide by zero throws") {
    Complex value(1, 1);

    CHECK_THROWS_AS(value / Complex(0, 0), std::invalid_argument);
}

TEST_CASE("Student - prefix increment changes real part") {
    Complex value(1, 2);

    ++value;

    CHECK(value == Complex(2, 2));
}

TEST_CASE("Student - explicit bool conversion") {
    CHECK((bool)Complex(1, 0));
    CHECK_FALSE((bool)Complex(0, 0));
}

TEST_CASE("Student - add elements to array") {
    ComplexArray array;

    array.add(Complex(1, 1));
    array.add(Complex(2, 2));

    CHECK(array.getSize() == 2);
}

TEST_CASE("Student - array starts with requested capacity") {
    ComplexArray array(3);

    CHECK(array.getCapacity() == 3);
}

TEST_CASE("Student - array grows when full") {
    ComplexArray array(1);

    array.add(Complex(1, 0));
    array.add(Complex(2, 0));

    CHECK(array.getCapacity() == 2);
}

TEST_CASE("Student - remove first element by index") {
    ComplexArray array;

    array.add(Complex(1, 1));
    array.add(Complex(3, 3));
    array.remove(0);

    CHECK(array[0] == Complex(3, 3));
}

TEST_CASE("Student - remove invalid index does nothing") {
    ComplexArray array;

    array.add(Complex(1, 1));
    array.remove(9);

    CHECK(array.getSize() == 1);
}

TEST_CASE("Student - find existing value") {
    ComplexArray array;

    array.add(Complex(1, 1));
    array.add(Complex(2, 2));

    CHECK(array.find(Complex(2, 2)) == 1);
}

TEST_CASE("Student - contains missing value") {
    ComplexArray array;

    array.add(Complex(1, 1));

    CHECK_FALSE(array.contains(Complex(9, 9)));
}

TEST_CASE("Student - array addition is element wise") {
    ComplexArray first;
    first.add(Complex(1, 2));
    first.add(Complex(3, 4));

    ComplexArray second;
    second.add(Complex(10, 20));
    second.add(Complex(30, 40));

    ComplexArray result = first + second;

    CHECK(result[0] == Complex(11, 22));
    CHECK(result[1] == Complex(33, 44));
}

TEST_CASE("Student - add complex to every array element") {
    ComplexArray array;

    array.add(Complex(1, 1));
    array.add(Complex(2, 2));

    ComplexArray result = array + Complex(10, 0);

    CHECK(result[0] == Complex(11, 1));
    CHECK(result[1] == Complex(12, 2));
}

TEST_CASE("Student - copy constructor makes deep copy") {
    ComplexArray original;

    original.add(Complex(1, 1));

    ComplexArray copy(original);
    copy[0] = Complex(9, 9);

    CHECK(original[0] == Complex(1, 1));
}