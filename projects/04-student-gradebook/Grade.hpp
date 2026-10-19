
#ifndef GRADE_HPP
#define GRADE_HPP

#include <iostream>
#include <string>

namespace grading {

class Grade {
private:
    double gradeValue;
    static int totalGradesCounter;
    
    // Named constants for better readability and Tidy compliance
    static constexpr double MIN_GRADE = 0.0;
    static constexpr double MAX_GRADE = 100.0;
    static constexpr double PASSING_THRESHOLD = 60.0;
    static constexpr double GRADE_A_LIMIT = 90.0;
    static constexpr double GRADE_B_LIMIT = 80.0;
    static constexpr double GRADE_C_LIMIT = 70.0;
    static constexpr double GRADE_D_LIMIT = 60.0;

public:
    // Constructors
    Grade(double val = MIN_GRADE);
    Grade(const Grade& other);

    // Getters & Logic
    double getScore() const { return gradeValue; }
    void setScore(double newScore);
    bool isPassing() const { return gradeValue >= PASSING_THRESHOLD; }
    std::string getLetterGrade() const;

    // Static statistics
    static int getTotalGradesCreated() { return totalGradesCounter; }
    static double getPassingGrade() { return PASSING_THRESHOLD; }

    // Math Operators
    Grade operator+(const Grade& other) const;
    Grade operator-(const Grade& other) const;
    Grade operator*(const Grade& other) const;
    Grade operator/(const Grade& other) const;
    Grade& operator+=(const Grade& other);
    Grade& operator-=(const Grade& other);
    Grade& operator*=(const Grade& other);

    // Friend math for: double + Grade
    friend Grade operator+(double lhs, const Grade& rhs);
    friend Grade operator*(double lhs, const Grade& rhs);

    // Comparisons
    bool operator==(const Grade& other) const;
    bool operator!=(const Grade& other) const;
    bool operator<(const Grade& other) const;
    bool operator>(const Grade& other) const;
    bool operator<=(const Grade& other) const;
    bool operator>=(const Grade& other) const;

    // Increments (Prefix and Postfix)
    Grade& operator++();    
    Grade operator++(int);  
    Grade& operator--();
    Grade operator--(int);

    // Explicit Type Conversion
    explicit operator int() const { return static_cast<int>(gradeValue); }
    explicit operator double() const { return gradeValue; }
    explicit operator std::string() const { return getLetterGrade(); }

    // Output formatting
    friend std::ostream& operator<<(std::ostream& outputStream, const Grade& gradeToPrint);
};

} // namespace grading

#endif