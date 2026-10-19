#include "ComplexArray.hpp"
#include <stdexcept>

namespace complex_math {

int ComplexArray::totalArraysCreated = 0;
int ComplexArray::currentArrayCount = 0;

ComplexArray::ComplexArray() : data(nullptr), size(0), capacity(0) {
    totalArraysCreated++;
    currentArrayCount++;
}

ComplexArray::ComplexArray(int startCapacity)
    : data(nullptr), size(0), capacity(startCapacity) {
    if (capacity > 0) {
        data = new Complex[static_cast<unsigned long>(capacity)];
    } else {
        capacity = 0;
    }

    totalArraysCreated++;
    currentArrayCount++;
}

ComplexArray::ComplexArray(const ComplexArray& other)
    : data(nullptr), size(other.size), capacity(other.capacity) {
    if (capacity > 0) {
        data = new Complex[static_cast<unsigned long>(capacity)];
    }

    // Copy each complex number into a new array
    for (int index = 0; index < size; ++index) {
        data[index] = other.data[index];
    }

    totalArraysCreated++;
    currentArrayCount++;
}

ComplexArray::~ComplexArray() {
    delete[] data;
    data = nullptr;

    size = 0;
    capacity = 0;

    currentArrayCount--;
}

ComplexArray& ComplexArray::operator=(const ComplexArray& other) {
    if (this == &other) {
        return *this;
    }

    Complex* newData = nullptr;

    if (other.capacity > 0) {
        newData = new Complex[static_cast<unsigned long>(other.capacity)];
    }

    // Copy before deleting the old array
    for (int index = 0; index < other.size; ++index) {
        newData[index] = other.data[index];
    }

    delete[] data;

    data = newData;
    size = other.size;
    capacity = other.capacity;

    return *this;
}

void ComplexArray::resize(int newCapacity) {
    Complex* newData = new Complex[static_cast<unsigned long>(newCapacity)];

    for (int index = 0; index < size; ++index) {
        newData[index] = data[index];
    }

    delete[] data;

    data = newData;
    capacity = newCapacity;
}

int ComplexArray::getSize() const {
    return size;
}

int ComplexArray::getCapacity() const {
    return capacity;
}

bool ComplexArray::isEmpty() const {
    return size == 0;
}

void ComplexArray::add(const Complex& value) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }

    data[size] = value;
    size++;
}

void ComplexArray::remove(int index) {
    if (index < 0 || index >= size) {
        return;
    }

    // Move all elements after the removed index one place left
    for (int current = index; current < size - 1; ++current) {
        data[current] = data[current + 1];
    }

    size--;
}

void ComplexArray::clear() {
    size = 0;
}

int ComplexArray::find(const Complex& value) const {
    for (int index = 0; index < size; ++index) {
        if (data[index] == value) {
            return index;
        }
    }

    return -1;
}

bool ComplexArray::contains(const Complex& value) const {
    return find(value) != -1;
}

Complex& ComplexArray::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

const Complex& ComplexArray::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

ComplexArray ComplexArray::operator+(const ComplexArray& other) const {
    ComplexArray result;

    int resultSize = (size < other.size) ? size : other.size;

    // Add the arrays element by element
    for (int index = 0; index < resultSize; ++index) {
        result.add(data[index] + other.data[index]);
    }

    return result;
}

ComplexArray ComplexArray::operator+(const Complex& value) const {
    ComplexArray result;

    // Add the same complex number to every element
    for (int index = 0; index < size; ++index) {
        result.add(data[index] + value);
    }

    return result;
}

ComplexArray ComplexArray::operator*(double scalar) const {
    ComplexArray result;

    for (int index = 0; index < size; ++index) {
        result.add(data[index] * Complex(scalar, 0.0));
    }

    return result;
}

bool ComplexArray::operator==(const ComplexArray& other) const {
    if (size != other.size) {
        return false;
    }

    for (int index = 0; index < size; ++index) {
        if (data[index] != other.data[index]) {
            return false;
        }
    }

    return true;
}

bool ComplexArray::operator!=(const ComplexArray& other) const {
    return !(*this == other);
}

Complex ComplexArray::sum() const {
    Complex result;

    for (int index = 0; index < size; ++index) {
        result += data[index];
    }

    return result;
}

Complex ComplexArray::average() const {
    if (size == 0) {
        return Complex();
    }

    return sum() * Complex(1.0 / size, 0.0);
}

Complex ComplexArray::max() const {
    if (size == 0) {
        throw std::runtime_error("Empty array");
    }

    Complex maxValue = data[0];

    for (int index = 1; index < size; ++index) {
        if (data[index] > maxValue) {
            maxValue = data[index];
        }
    }

    return maxValue;
}

int ComplexArray::getTotalArraysCreated() {
    return totalArraysCreated;
}

int ComplexArray::getCurrentArrayCount() {
    return currentArrayCount;
}

std::ostream& operator<<(std::ostream& output, const ComplexArray& array) {
    output << "[ ";

    for (int index = 0; index < array.size; ++index) {
        output << array.data[index] << " ";
    }

    output << "]";
    return output;
}

}