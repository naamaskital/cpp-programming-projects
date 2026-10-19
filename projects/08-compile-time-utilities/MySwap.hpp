#ifndef MYSWAP_HPP
#define MYSWAP_HPP

#include <string>

namespace metaengine {

// Generic swap implementation using copy and assignment.
template <typename T>
void mySwap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

// Full specialization for int using XOR swap.
template <>
inline void mySwap<int>(int& first, int& second) {
    // Avoid XOR swap on the same variable.
    if (&first == &second) {
        return;
    }

    first ^= second;
    second ^= first;
    first ^= second;
}

// Full specialization for string using the built-in string swap.
template <>
inline void mySwap<std::string>(std::string& first, std::string& second) {
    first.swap(second);
}

// Full specialization for bool using a temporary variable.
template <>
inline void mySwap<bool>(bool& first, bool& second) {
    const bool temp = first;
    first = second;
    second = temp;
}

} // namespace metaengine

#endif