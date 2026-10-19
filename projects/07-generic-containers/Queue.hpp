#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Container.hpp"
#include <stdexcept>

namespace containers {

template <typename T>
class Queue {
private:
    // Internal container that stores the queue values.
    Container<T> values;

public:
    Queue() : values() {
    }

    explicit Queue(int capacity) : values(capacity) {
    }

    // Add one value to the back of the queue.
    void enqueue(const T& value) {
        values.add(value);
    }

    // Add all values from an iterator range.
    template <typename Iterator>
    void enqueue(Iterator begin, Iterator end) {
        for (Iterator it = begin; it != end; ++it) {
            enqueue(*it);
        }
    }

    // Remove and return the front value.
    T dequeue() {
        if (values.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }

        T value = values.get(0);
        values.removeAt(0);
        return value;
    }

    // Return the first value in the queue.
    T& front() {
        if (values.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }

        return values.get(0);
    }

    const T& front() const {
        if (values.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }

        return values.get(0);
    }

    // Return the last value in the queue.
    T& back() {
        if (values.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }

        return values.get(values.getCount() - 1);
    }

    const T& back() const {
        if (values.isEmpty()) {
            throw std::underflow_error("Queue is empty");
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

    void clear() {
        values.clear();
    }

    // Allow iteration over the queue values.
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