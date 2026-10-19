#ifndef DECLTYPEUTILS_HPP
#define DECLTYPEUTILS_HPP

namespace metaengine {

// Default case: type is not floating point.
template <typename T>
struct IsFloating {
    static constexpr bool value = false;
};

// Specializations for floating point types.
template <>
struct IsFloating<float> {
    static constexpr bool value = true;
};

template <>
struct IsFloating<double> {
    static constexpr bool value = true;
};

template <>
struct IsFloating<long double> {
    static constexpr bool value = true;
};

// Default case: type is not integral.
template <typename T>
struct IsIntegral {
    static constexpr bool value = false;
};

// Specializations for integral types.
template <>
struct IsIntegral<bool> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<char> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<signed char> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<unsigned char> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<short> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<unsigned short> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<int> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<unsigned int> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<long> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<unsigned long> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<long long> {
    static constexpr bool value = true;
};

template <>
struct IsIntegral<unsigned long long> {
    static constexpr bool value = true;
};

// Return type is automatically based on the expression result.
template <typename T, typename U>
auto add(T first, U second) -> decltype(first + second) {
    return first + second;
}

template <typename T, typename U>
auto multiply(T first, U second) -> decltype(first * second) {
    return first * second;
}

template <typename T, typename U>
auto maxOf(T first, U second) -> decltype(first + second) {
    return first > second ? first : second;
}

template <typename T, typename U>
auto minOf(T first, U second) -> decltype(first + second) {
    return first < second ? first : second;
}

// Check if the addition result is a floating point type.
template <typename T, typename U>
constexpr bool isAddResultFloating() {
    return IsFloating<decltype(T{} + U{})>::value;
}

// Check if the multiplication result is an integral type.
template <typename T, typename U>
constexpr bool isMulResultIntegral() {
    return IsIntegral<decltype(T{} * U{})>::value;
}

} // namespace metaengine

#endif