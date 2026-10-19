
#include "Grade.hpp"
#include <iomanip>

namespace grading {

int Grade::totalGradesCounter = 0;

Grade::Grade(double val) : gradeValue(MIN_GRADE) {
    setScore(val);
    totalGradesCounter++;
}

Grade::Grade(const Grade& other) : gradeValue(other.gradeValue) {
    totalGradesCounter++;
}

void Grade::setScore(double newScore) {
    if (newScore < MIN_GRADE) {
        gradeValue = MIN_GRADE;
    } else if (newScore > MAX_GRADE) {
        gradeValue = MAX_GRADE;
    } else {
        gradeValue = newScore;
    }
}

std::string Grade::getLetterGrade() const {
    if (gradeValue >= GRADE_A_LIMIT) { return "A"; }
    if (gradeValue >= GRADE_B_LIMIT) { return "B"; }
    if (gradeValue >= GRADE_C_LIMIT) { return "C"; }
    if (gradeValue >= GRADE_D_LIMIT) { return "D"; }
    return "F";
}

// Math logic
Grade Grade::operator+(const Grade& other) const { return Grade(gradeValue + other.gradeValue); }
Grade Grade::operator-(const Grade& other) const { return Grade(gradeValue - other.gradeValue); }
Grade Grade::operator*(const Grade& other) const { return Grade(gradeValue * other.gradeValue); }
Grade Grade::operator/(const Grade& other) const { 
    if (other.gradeValue == MIN_GRADE) { return Grade(MIN_GRADE); }
    return Grade(gradeValue / other.gradeValue); 
}

Grade& Grade::operator+=(const Grade& other) { setScore(gradeValue + other.gradeValue); return *this; }
Grade& Grade::operator-=(const Grade& other) { setScore(gradeValue - other.gradeValue); return *this; }
Grade& Grade::operator*=(const Grade& other) { setScore(gradeValue * other.gradeValue); return *this; }

Grade operator+(double lhs, const Grade& rhs) { return Grade(lhs + rhs.gradeValue); }
Grade operator*(double lhs, const Grade& rhs) { return Grade(lhs * rhs.gradeValue); }

// Comparison logic
bool Grade::operator==(const Grade& other) const { return gradeValue == other.gradeValue; }
bool Grade::operator!=(const Grade& other) const { return !(*this == other); }
bool Grade::operator<(const Grade& other) const { return gradeValue < other.gradeValue; }
bool Grade::operator>(const Grade& other) const { return gradeValue > other.gradeValue; }
bool Grade::operator<=(const Grade& other) const { return gradeValue <= other.gradeValue; }
bool Grade::operator>=(const Grade& other) const { return gradeValue >= other.gradeValue; }

// Increment logic
Grade& Grade::operator++() { setScore(gradeValue + 1.0); return *this; }
Grade Grade::operator++(int) { Grade temp = *this; ++(*this); return temp; }
Grade& Grade::operator--() { setScore(gradeValue - 1.0); return *this; }
Grade Grade::operator--(int) { Grade temp = *this; --(*this); return temp; }

std::ostream& operator<<(std::ostream& outputStream, const Grade& gradeToPrint) {
    outputStream << std::fixed << std::setprecision(2) << gradeToPrint.gradeValue << " (" << gradeToPrint.getLetterGrade() << ")";
    return outputStream;
}

} // namespace grading