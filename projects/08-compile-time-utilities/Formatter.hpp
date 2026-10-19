#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

namespace metaengine {

template <typename T>
struct Formatter {
    static std::string format(const T& value) {
        std::ostringstream output;
        output << value;
        return output.str();
    }

    static std::string formatWithLabel(const std::string& label, const T& value) {
        return label + ": " + format(value);
    }
};

template <>
struct Formatter<int> {
    static std::string format(int value) {
        return std::to_string(value);
    }

    static std::string formatHex(int value) {
        std::ostringstream output;
        output << "0x" << std::uppercase << std::hex << value;
        return output.str();
    }

    static std::string formatWithLabel(const std::string& label, int value) {
        return label + ": " + format(value);
    }
};

template <>
struct Formatter<double> {
    static std::string format(double value, int precision = 2) {
        std::ostringstream output;
        output << std::fixed << std::setprecision(precision) << value;
        return output.str();
    }

    static std::string formatScientific(double value, int precision = 2) {
        std::ostringstream output;
        output << std::scientific << std::setprecision(precision) << value;
        return output.str();
    }

    static std::string formatWithLabel(const std::string& label, double value) {
        return label + ": " + format(value);
    }
};

template <>
struct Formatter<bool> {
    static std::string format(bool value) {
        return value ? "true" : "false";
    }

    static std::string formatYesNo(bool value) {
        return value ? "Yes" : "No";
    }

    static std::string formatOnOff(bool value) {
        return value ? "ON" : "OFF";
    }

    static std::string formatWithLabel(const std::string& label, bool value) {
        return label + ": " + format(value);
    }
};

template <>
struct Formatter<std::string> {
    static std::string format(const std::string& value) {
        return "\"" + value + "\"";
    }

    static std::string formatUpper(const std::string& value) {
        std::string result = value;
        for (char& letter : result) {
            letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
        }
        return result;
    }

    static std::string formatLower(const std::string& value) {
        std::string result = value;
        for (char& letter : result) {
            letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
        }
        return result;
    }

    static std::string formatWithLabel(const std::string& label, const std::string& value) {
        return label + ": " + format(value)
            + " (length: " + std::to_string(value.length()) + ")";
    }
};

} // namespace metaengine

#endif
