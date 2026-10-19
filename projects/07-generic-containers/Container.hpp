#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstddef>
#include <stdexcept>

namespace containers {

template <typename T>
class Container {
private:
    T* data;
    std::size_t count;
    std::size_t capacityValue;

    // Allocate a larger array and copy the existing elements into it.
    void resize(std::size_t newCapacity) {
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacityValue = newCapacity;
    }

public:
    // Simple iterator over the internal array.
    class Iterator {
    private:
        T* pointer;

    public:
        explicit Iterator(T* ptr = nullptr) {
            pointer = ptr;
        }

        T& operator*() {
            return *pointer;
        }

        const T& operator*() const {
            return *pointer;
        }

        Iterator& operator++() {
            ++pointer;
            return *this;
        }

        Iterator operator++(int) {
            Iterator old = *this;
            ++pointer;
            return old;
        }

        bool operator!=(const Iterator& other) const {
            return pointer != other.pointer;
        }

        bool operator==(const Iterator& other) const {
            return pointer == other.pointer;
        }
    };

    // Create an empty container with a small default capacity.
    Container() {
        capacityValue = 4;
        count = 0;
        data = new T[capacityValue];
    }

    // Create an empty container with a user given capacity.
    explicit Container(int capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }

        capacityValue = static_cast<std::size_t>(capacity);
        count = 0;
        data = new T[capacityValue];
    }

    // Deep copy constructor: allocate a new array and copy the elements.
    Container(const Container& other) {
        count = other.count;
        capacityValue = other.capacityValue;
        data = new T[capacityValue];

        for (std::size_t i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    // Deep copy assignment operator.
    Container& operator=(const Container& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        count = other.count;
        capacityValue = other.capacityValue;
        data = new T[capacityValue];

        for (std::size_t i = 0; i < count; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    ~Container() {
        delete[] data;
    }

    // Add a new value at the end of the container.
    void add(const T& value) {
        if (count == capacityValue) {
            resize(capacityValue * 2);
        }

        data[count] = value;
        count++;
    }

    T& get(int index) {
        if (index < 0 || static_cast<std::size_t>(index) >= count) {
            throw std::out_of_range("Index out of range");
        }

        return data[static_cast<std::size_t>(index)];
    }

    const T& get(int index) const {
        if (index < 0 || static_cast<std::size_t>(index) >= count) {
            throw std::out_of_range("Index out of range");
        }

        return data[static_cast<std::size_t>(index)];
    }

    // Access an element using array syntax.
    T& operator[](int index) {
        return get(index);
    }

    const T& operator[](int index) const {
        return get(index);
    }

    // Remove an element and shift the following elements one place left.
    void removeAt(int index) {
        if (index < 0 || static_cast<std::size_t>(index) >= count) {
            throw std::out_of_range("Index out of range");
        }

        std::size_t place = static_cast<std::size_t>(index);

        for (std::size_t i = place; i + 1 < count; i++) {
            data[i] = data[i + 1];
        }

        count--;
    }

    int getCount() const {
        return static_cast<int>(count);
    }

    int getCapacity() const {
        return static_cast<int>(capacityValue);
    }

    bool isEmpty() const {
        return count == 0;
    }

    // Remove all logical elements.
    void clear() {
        count = 0;
    }

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + count);
    }

    Iterator begin() const {
        return Iterator(data);
    }

    Iterator end() const {
        return Iterator(data + count);
    }
};

}

#endif