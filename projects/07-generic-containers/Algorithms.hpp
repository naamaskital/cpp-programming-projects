#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace containers {

// Generic swap function.
template <typename T>
void swapValues(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

// Return an iterator to the first matching value, or end if not found.
template <typename Iterator, typename T>
Iterator find(Iterator begin, Iterator end, const T& value) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it == value) {
            return it;
        }
    }

    return end;
}

// Return the index of the first matching value, or -1 if not found.
template <typename T>
int find(const Container<T>& container, const T& value) {
    for (int i = 0; i < container.getCount(); i++) {
        if (container.get(i) == value) {
            return i;
        }
    }

    return -1;
}

// Count how many times a value appears in an iterator range.
template <typename Iterator, typename T>
int count(Iterator begin, Iterator end, const T& value) {
    int result = 0;

    for (Iterator it = begin; it != end; ++it) {
        if (*it == value) {
            result++;
        }
    }

    return result;
}

// Count how many times a value appears in a Container.
template <typename T>
int count(const Container<T>& container, const T& value) {
    int result = 0;

    for (int i = 0; i < container.getCount(); i++) {
        if (container.get(i) == value) {
            result++;
        }
    }

    return result;
}

// Check if a value exists in an iterator range.
template <typename Iterator, typename T>
bool contains(Iterator begin, Iterator end, const T& value) {
    return find(begin, end, value) != end;
}

// Check if a value exists in a Container.
template <typename T>
bool contains(const Container<T>& container, const T& value) {
    return find(container, value) != -1;
}

// Apply a function to every element in the iterator range.
template <typename Iterator, typename Function>
void transform(Iterator begin, Iterator end, Function function) {
    for (Iterator it = begin; it != end; ++it) {
        function(*it);
    }
}

// Apply a function to every element in a Container.
template <typename T, typename Function>
void transform(Container<T>& container, Function function) {
    transform(container.begin(), container.end(), function);
}

// Replace every matching value in an iterator range.
template <typename Iterator, typename T>
void replace(Iterator begin, Iterator end, const T& oldValue, const T& newValue) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it == oldValue) {
            *it = newValue;
        }
    }
}

// Replace every matching value in a Container.
template <typename T>
void replace(Container<T>& container, const T& oldValue, const T& newValue) {
    replace(container.begin(), container.end(), oldValue, newValue);
}

// Run a function on each element.
template <typename Iterator, typename Function>
void forEach(Iterator begin, Iterator end, Function function) {
    for (Iterator it = begin; it != end; ++it) {
        function(*it);
    }
}

template <typename T, typename Function>
void forEach(Container<T>& container, Function function) {
    forEach(container.begin(), container.end(), function);
}

// Return the sum of all elements.
template <typename T>
T sum(const Container<T>& container) {
    T result = T();

    for (int i = 0; i < container.getCount(); i++) {
        result = result + container.get(i);
    }

    return result;
}

// Return the smallest element.
template <typename T>
T min(const Container<T>& container) {
    if (container.getCount() == 0) {
        throw std::underflow_error("Container is empty");
    }

    T result = container.get(0);

    for (int i = 1; i < container.getCount(); i++) {
        if (container.get(i) < result) {
            result = container.get(i);
        }
    }

    return result;
}

// Return the largest element.
template <typename T>
T max(const Container<T>& container) {
    if (container.getCount() == 0) {
        throw std::underflow_error("Container is empty");
    }

    T result = container.get(0);

    for (int i = 1; i < container.getCount(); i++) {
        if (result < container.get(i)) {
            result = container.get(i);
        }
    }

    return result;
}

// Create a new Container with only the elements that match the condition.
template <typename T, typename Function>
Container<T> filter(const Container<T>& container, Function function) {
    int resultCapacity = container.getCount();

    if (resultCapacity <= 0) {
        resultCapacity = 1;
    }

    Container<T> result(resultCapacity);

    for (int i = 0; i < container.getCount(); i++) {
        if (function(container.get(i))) {
            result.add(container.get(i));
        }
    }

    return result;
}

// Reverse the order of the elements in the Container.
template <typename T>
void reverse(Container<T>& container) {
    int left = 0;
    int right = container.getCount() - 1;

    while (left < right) {
        swapValues(container.get(left), container.get(right));
        left++;
        right--;
    }
}

// Convert a Container to a string.
template <typename T>
std::string toString(const Container<T>& container) {
    std::ostringstream oss;

    oss << "[";

    for (int i = 0; i < container.getCount(); i++) {
        oss << container.get(i);

        if (i + 1 < container.getCount()) {
            oss << ", ";
        }
    }

    oss << "]";

    return oss.str();
}

// Convert a Stack to a string.
template <typename T>
std::string toString(const Stack<T>& stack) {
    std::ostringstream oss;

    oss << "Stack(bottom -> top): [";

    int index = 0;

    for (typename Container<T>::Iterator it = stack.begin(); it != stack.end(); ++it) {
        oss << *it;

        if (index + 1 < stack.getCount()) {
            oss << ", ";
        }

        index++;
    }

    oss << "]";

    return oss.str();
}

// Convert a Queue to a string.
template <typename T>
std::string toString(const Queue<T>& queue) {
    std::ostringstream oss;

    oss << "Queue(front -> back): [";

    int index = 0;

    for (typename Container<T>::Iterator it = queue.begin(); it != queue.end(); ++it) {
        oss << *it;

        if (index + 1 < queue.getCount()) {
            oss << ", ";
        }

        index++;
    }

    oss << "]";

    return oss.str();
}

// Print different container types to a given output stream.
template <typename T>
void print(const Container<T>& container, std::ostream& out) {
    out << toString(container);
}

template <typename T>
void print(const Stack<T>& stack, std::ostream& out) {
    out << toString(stack);
}

template <typename T>
void print(const Queue<T>& queue, std::ostream& out) {
    out << toString(queue);
}

// Print different container types to the console.
template <typename T>
void print(const Container<T>& container) {
    print(container, std::cout);
    std::cout << std::endl;
}

template <typename T>
void print(const Stack<T>& stack) {
    print(stack, std::cout);
    std::cout << std::endl;
}

template <typename T>
void print(const Queue<T>& queue) {
    print(queue, std::cout);
    std::cout << std::endl;
}

}

#endif