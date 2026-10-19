#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

#include <cstddef>
#include <string>

namespace metaengine {

// General template for types without a special implementation.
template <typename T>
struct TypeInfo {
    static constexpr const char* name = "Unknown";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(T);

    static std::string describe() {
        return "Unknown type of size " + std::to_string(size) + " bytes";
    }
};

// Full specialization for int.
template <>
struct TypeInfo<int> {
    static constexpr const char* name = "int";
    static constexpr bool is_numeric = true;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(int);
    static constexpr int min_value = (-2147483647 - 1);
    static constexpr int max_value = 2147483647;

    static std::string describe() {
        return "int: numeric type, size " + std::to_string(size)
            + " bytes, range [" + std::to_string(min_value)
            + ", " + std::to_string(max_value) + "]";
    }
};

// Full specialization for double.
template <>
struct TypeInfo<double> {
    static constexpr const char* name = "double";
    static constexpr bool is_numeric = true;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(double);
    static constexpr double epsilon = 1e-9;

    static std::string describe() {
        return "double: floating-point type, size " + std::to_string(size)
            + " bytes, epsilon " + std::to_string(epsilon);
    }
};

// Full specialization for bool.
template <>
struct TypeInfo<bool> {
    static constexpr const char* name = "bool";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(bool);

    static std::string describe() {
        return "bool: boolean type, size " + std::to_string(size) + " bytes";
    }
};

// Full specialization for std::string.
template <>
struct TypeInfo<std::string> {
    static constexpr const char* name = "string";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = false;
    static constexpr std::size_t size = sizeof(std::string);

    static std::string describe() {
        return "string: text type, size " + std::to_string(size) + " bytes";
    }
};

// Partial specialization for all pointer types.
template <typename T>
struct TypeInfo<T*> {
    static constexpr const char* name = "pointer";
    static constexpr bool is_numeric = false;
    static constexpr bool is_pointer = true;
    static constexpr std::size_t size = sizeof(T*);

    static std::string describe() {
        return "pointer to " + std::string(TypeInfo<T>::name)
            + ", size " + std::to_string(size) + " bytes";
    }
};

} // namespace metaengine

#endif