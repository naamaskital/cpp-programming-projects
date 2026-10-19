#ifndef STACK_HPP
#define STACK_HPP

#include "Container.hpp"
#include <stdexcept>

namespace containers {

template <typename T>
class Stack {
private:
    // Internal container that stores the stack values.
    Container<T> values;

public:
    Stack() : values() {
    }

    explicit Stack(int capacity) : values(capacity) {
    }

    // Push one value to the top of the stack.
    void push(const T& value) {
        values.add(value);
    }

    // Push all values in the iterator range.
    template <typename Iterator>
    void push(Iterator begin, Iterator end) {
        for (Iterator it = begin; it != end; ++it) {
            push(*it);
        }
    }

    // Remove and return the top value.
    T pop() {
        if (values.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        T value = values.get(values.getCount() - 1);
        values.removeAt(values.getCount() - 1);
        return value;
    }

    // Return the top value.
    T& top() {
        if (values.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        return values.get(values.getCount() - 1);
    }

    const T& top() const {
        if (values.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }

        return values.get(values.getCount() - 1);
    }

    int getCount() const {
        return values.getCount();
    }

    int size() const {
        return values.getCount();
    }

    bool isEmpty() const {
        return values.isEmpty();
    }

    bool empty() const {
        return values.isEmpty();
    }

    void clear() {
        values.clear();
    }

    // Allow iteration over the stack values.
    typename Container<T>::Iterator begin() {
        return values.begin();
    }

    typename Container<T>::Iterator end() {
        return values.end();
    }

    typename Container<T>::Iterator begin() const {
        return values.begin();
    }

    typename Container<T>::Iterator end() const {
        return values.end();
    }
};

}

#endif