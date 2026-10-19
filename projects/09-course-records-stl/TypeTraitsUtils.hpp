#ifndef TYPE_TRAITS_UTILS_HPP
#define TYPE_TRAITS_UTILS_HPP

#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

namespace registration {

// Returns a simple description of the type T.
template <typename T>
std::string describeType() {
    // Check if T is a pointer type.
    if constexpr (std::is_pointer<T>::value) {
        return "pointer";

    // Check if T is exactly std::string.
    } else if constexpr (std::is_same<T, std::string>::value) {
        return "string";

    // Check if T is an integer type.
    } else if constexpr (std::is_integral<T>::value) {
        return "integral";

    // Check if T is a floating point type.
    } else if constexpr (std::is_floating_point<T>::value) {
        return "floating-point";

    // If none of the checks matched, return unknown.
    } else {
        return "unknown";
    }
}

// Checks if T is a numeric type.
template <typename T>
constexpr bool isNumeric() {
    return std::is_integral<T>::value || std::is_floating_point<T>::value;
}

// Checks if T and U are the same type.
template <typename T, typename U>
constexpr bool areSameType() {
    return std::is_same<T, U>::value;
}

// Converts a numeric value to a string.
template <typename T>
std::string numericToString(T value) {
    // Make sure this function is used only with numeric types.
    static_assert(std::is_arithmetic<T>::value, "numericToString requires numeric type");

    // If the value is an integer, use std::to_string.
    if constexpr (std::is_integral<T>::value) {
        return std::to_string(value);

    // If the value is not an integer, format it with 2 digits after the point.
    } else {
        std::ostringstream out;
        out << std::fixed << std::setprecision(2) << value;
        return out.str();
    }
}

// Adds two numeric values safely.
template <typename T, typename U>
auto safeAdd(T left, U right) {
    // Make sure both values are numeric.
    static_assert(isNumeric<T>() && isNumeric<U>(), "safeAdd requires numeric types");

    // If both values are integers, return the result as long long.
    if constexpr (std::is_integral<T>::value && std::is_integral<U>::value) {
        return static_cast<long long>(left) + static_cast<long long>(right);

    // Otherwise, return the result as double.
    } else {
        return static_cast<double>(left) + static_cast<double>(right);
    }
}

// Returns the zero/default value of type T.
template <typename T>
T getZero() {
    return T{};
}

} // namespace registration

#endif