#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <string>

namespace complex_math {

class Complex {
private:
    double real;
    double imag;

    static int totalCreated;
    static int currentCount;

public:
    Complex(double realValue = 0.0, double imagValue = 0.0);
    Complex(const Complex& other);
    ~Complex();

    double getReal() const;
    double getImag() const;
    void setReal(double realValue);
    void setImag(double imagValue);

    double magnitude() const;
    Complex conjugate() const;
    bool isZero() const;
    bool isReal() const;
    std::string toRectangularString() const;

    static Complex fromPolar(double radius, double theta);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    Complex operator-() const;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(double scalar);

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator<(const Complex& other) const;

    Complex& operator++();
    Complex operator++(int);
    Complex& operator--();
    Complex operator--(int);

    explicit operator double() const;
    explicit operator bool() const;
    explicit operator std::string() const;

    static int getTotalComplexCreated();
    static int getCurrentComplexCount();

    friend std::ostream& operator<<(std::ostream& output, const Complex& value);
    friend std::istream& operator>>(std::istream& input, Complex& value);
};

double distance(const Complex& first, const Complex& second);

}

#endif