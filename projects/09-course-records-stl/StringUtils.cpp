#include "StringUtils.hpp"

namespace registration {

// Checks if a character is a whitespace character.
bool isWhiteSpace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

// Converts one lowercase letter to uppercase.
char toUpperChar(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return static_cast<char>(ch - 'a' + 'A');
    }

    return ch;
}

// Converts one uppercase letter to lowercase.
char toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<char>(ch - 'A' + 'a');
    }

    return ch;
}

// Converts the whole string to uppercase.
std::string toUpper(const std::string& text) {
    std::string result = text;

    // Change each character in the copied string.
    for (char& ch : result) {
        ch = toUpperChar(ch);
    }

    return result;
}

// Converts the whole string to lowercase.
std::string toLower(const std::string& text) {
    std::string result = text;

    // Change each character in the copied string.
    for (char& ch : result) {
        ch = toLowerChar(ch);
    }

    return result;
}

// Removes whitespace from the beginning and end of the string.
std::string trim(const std::string& text) {
    std::size_t start = 0;

    // Move start forward while there are spaces at the beginning.
    while (start < text.size() && isWhiteSpace(text[start])) {
        ++start;
    }

    std::size_t end = text.size();

    // Move end backward while there are spaces at the end.
    while (end > start && isWhiteSpace(text[end - 1])) {
        --end;
    }

    // Return only the part without the extra spaces.
    return text.substr(start, end - start);
}

// Splits a string into parts using a delimiter character.
std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> result;
    std::string current;

    // Build each part until the delimiter is found.
    for (char ch : text) {
        if (ch == delimiter) {
            result.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }

    // Add the last part.
    result.push_back(current);
    return result;
}

// Joins strings together with a delimiter between them.
std::string join(const std::vector<std::string>& parts, const std::string& delimiter) {
    std::string result;

    // Add each part to the final string.
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) {
            result += delimiter;
        }

        result += parts[i];
    }

    return result;
}

// Checks if a string starts with a specific prefix.
bool startsWith(const std::string& text, const std::string& prefix) {
    if (prefix.size() > text.size()) {
        return false;
    }

    // Compare the beginning of the text with the prefix.
    for (std::size_t i = 0; i < prefix.size(); ++i) {
        if (text[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

// Checks if a string ends with a specific suffix.
bool endsWith(const std::string& text, const std::string& suffix) {
    if (suffix.size() > text.size()) {
        return false;
    }

    std::size_t start = text.size() - suffix.size();

    // Compare the end of the text with the suffix.
    for (std::size_t i = 0; i < suffix.size(); ++i) {
        if (text[start + i] != suffix[i]) {
            return false;
        }
    }

    return true;
}

// Replaces all appearances of one string with another string.
std::string replaceAll(const std::string& text, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return text;
    }

    std::string result = text;
    std::size_t position = 0;

    // Keep searching and replacing until there are no more matches.
    while ((position = result.find(from, position)) != std::string::npos) {
        result.replace(position, from.size(), to);
        position += to.size();
    }

    return result;
}

// Counts how many times a character appears in the string.
int countChar(const std::string& text, char wanted) {
    int counter = 0;

    for (char ch : text) {
        if (ch == wanted) {
            ++counter;
        }
    }

    return counter;
}

// Returns the string in reverse order.
std::string reverseString(const std::string& text) {
    std::string result;

    // Start from the end and add characters one by one.
    for (std::size_t i = text.size(); i > 0; --i) {
        result.push_back(text[i - 1]);
    }

    return result;
}

// Checks if a string is a palindrome.
bool isPalindrome(const std::string& text) {
    std::string clean;

    // Remove whitespace and make all letters lowercase.
    for (char ch : text) {
        if (!isWhiteSpace(ch)) {
            clean.push_back(toLowerChar(ch));
        }
    }

    // Compare the cleaned string with its reversed version.
    std::string reversed = reverseString(clean);
    return clean == reversed;
}

} // namespace registration