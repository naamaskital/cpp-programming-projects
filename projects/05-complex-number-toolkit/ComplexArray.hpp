#ifndef COMPLEX_ARRAY_HPP
#define COMPLEX_ARRAY_HPP

#include "Complex.hpp"
#include <iostream>

namespace complex_math {

class ComplexArray {
private:
    Complex* data;
    int size;
    int capacity;

    static int totalArraysCreated;
    static int currentArrayCount;

    void resize(int newCapacity);

public:
    ComplexArray();
    ComplexArray(int startCapacity);
    ComplexArray(const ComplexArray& other);
    ~ComplexArray();

    ComplexArray& operator=(const ComplexArray& other);

    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;

    void add(const Complex& value);
    void remove(int index);
    void clear();

    int find(const Complex& value) const;
    bool contains(const Complex& value) const;

    Complex& operator[](int index);
    const Complex& operator[](int index) const;

    ComplexArray operator+(const ComplexArray& other) const;
    ComplexArray operator+(const Complex& value) const;
    ComplexArray operator*(double scalar) const;

    bool operator==(const ComplexArray& other) const;
    bool operator!=(const ComplexArray& other) const;

    Complex sum() const;
    Complex average() const;
    Complex max() const;

    static int getTotalArraysCreated();
    static int getCurrentArrayCount();

    friend std::ostream& operator<<(std::ostream& output, const ComplexArray& array);
};

}

#endif