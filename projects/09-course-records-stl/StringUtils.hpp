#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

namespace registration {

// Converts a string to uppercase letters.
std::string toUpper(const std::string& text);

// Converts a string to lowercase letters.
std::string toLower(const std::string& text);

// Removes spaces from the beginning and end of a string.
std::string trim(const std::string& text);

// Splits a string into parts using a delimiter.
std::vector<std::string> split(const std::string& text, char delimiter);

// Joins a vector of strings into one string.
std::string join(const std::vector<std::string>& parts, const std::string& delimiter);

// Checks if a string starts with a given prefix.
bool startsWith(const std::string& text, const std::string& prefix);

// Checks if a string ends with a given suffix.
bool endsWith(const std::string& text, const std::string& suffix);

// Replaces all appearances of one string with another string.
std::string replaceAll(const std::string& text, const std::string& from, const std::string& to);

// Counts how many times a character appears in a string.
int countChar(const std::string& text, char wanted);

// Checks if a string reads the same forward and backward.
bool isPalindrome(const std::string& text);

// Returns the string in reverse order.
std::string reverseString(const std::string& text);

} // namespace registration

#endif