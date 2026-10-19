#include "Complex.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace complex_math {

int Complex::totalCreated = 0;
int Complex::currentCount = 0;

Complex::Complex(double realValue, double imagValue)
    : real(realValue), imag(imagValue) {
    totalCreated++;
    currentCount++;
}

Complex::Complex(const Complex& other)
    : real(other.real), imag(other.imag) {
    totalCreated++;
    currentCount++;
}

Complex::~Complex() {
    currentCount--;
}

double Complex::getReal() const {
    return real;
}

double Complex::getImag() const {
    return imag;
}

void Complex::setReal(double realValue) {
    real = realValue;
}

void Complex::setImag(double imagValue) {
    imag = imagValue;
}

Complex Complex::fromPolar(double radius, double theta) {
    return Complex(radius * std::cos(theta), radius * std::sin(theta));
}

double Complex::magnitude() const {
    return std::sqrt(real * real + imag * imag);
}

Complex Complex::conjugate() const {
    return Complex(real, -imag);
}

bool Complex::isZero() const {
    return real == 0.0 && imag == 0.0;
}

bool Complex::isReal() const {
    return imag == 0.0;
}

std::string Complex::toRectangularString() const {
    std::ostringstream stream;
    stream << real;

    if (imag >= 0.0) {
        stream << "+";
    }

    stream << imag << "i";
    return stream.str();
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    double resultReal = real * other.real - imag * other.imag;
    double resultImag = real * other.imag + imag * other.real;

    return Complex(resultReal, resultImag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;

    if (denominator == 0.0) {
        throw std::invalid_argument("Cannot divide by zero complex number");
    }

    double resultReal = (real * other.real + imag * other.imag) / denominator;
    double resultImag = (imag * other.real - real * other.imag) / denominator;

    return Complex(resultReal, resultImag);
}

Complex Complex::operator-() const {
    return Complex(-real, -imag);
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;

    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imag -= other.imag;

    return *this;
}

Complex& Complex::operator*=(double scalar) {
    real *= scalar;
    imag *= scalar;

    return *this;
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

bool Complex::operator>(const Complex& other) const {
    return magnitude() > other.magnitude();
}

bool Complex::operator<(const Complex& other) const {
    return magnitude() < other.magnitude();
}

Complex& Complex::operator++() {
    real += 1.0;
    return *this;
}

Complex Complex::operator++(int) {
    Complex oldValue(*this);
    real += 1.0;

    return oldValue;
}

Complex& Complex::operator--() {
    real -= 1.0;
    return *this;
}

Complex Complex::operator--(int) {
    Complex oldValue(*this);
    real -= 1.0;

    return oldValue;
}

Complex::operator double() const {
    return magnitude();
}

Complex::operator bool() const {
    return !isZero();
}

Complex::operator std::string() const {
    return toRectangularString();
}

int Complex::getTotalComplexCreated() {
    return totalCreated;
}

int Complex::getCurrentComplexCount() {
    return currentCount;
}

std::ostream& operator<<(std::ostream& output, const Complex& value) {
    output << value.toRectangularString();
    return output;
}

std::istream& operator>>(std::istream& input, Complex& value) {
    input >> value.real >> value.imag;
    return input;
}

double distance(const Complex& first, const Complex& second) {
    return (first - second).magnitude();
}

}