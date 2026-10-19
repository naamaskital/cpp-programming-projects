
#include "Student.hpp"
#include <iostream>
#include <stdexcept>

namespace grading {

int Student::totalStudentsCounter = 0;
int Student::currentStudentsInMem = 0;

// Default constructor
Student::Student() : studentFullName("Unknown"), studentIdNumber("Unknown") {
    totalStudentsCounter++;
    currentStudentsInMem++;
}

Student::Student(std::string nameInput, std::string idInput, int initialCapacity) 
    : studentFullName(std::move(nameInput)), studentIdNumber(std::move(idInput)) {
    if (initialCapacity > 0) {
        coursesVector.reserve(static_cast<size_t>(initialCapacity));
        gradesVector.reserve(static_cast<size_t>(initialCapacity));
    }
    totalStudentsCounter++;
    currentStudentsInMem++;
}

Student::~Student() {
    currentStudentsInMem--;
}

Student::Student(const Student& other) 
    : studentFullName(other.studentFullName), 
      studentIdNumber(other.studentIdNumber),
      coursesVector(other.coursesVector),
      gradesVector(other.gradesVector) {
    totalStudentsCounter++;
    currentStudentsInMem++;
}

Student& Student::operator=(const Student& other) {
    if(this != &other) {
        studentFullName = other.studentFullName;
        studentIdNumber = other.studentIdNumber;
        coursesVector = other.coursesVector;
        gradesVector = other.gradesVector;
    }
    return *this;
}

void Student::addGrade(const Grade& newGrade, const Course& newCourse) {
    coursesVector.push_back(newCourse);
    gradesVector.push_back(newGrade);
}

void Student::removeGrade(int gradeIndex) {
    if (gradeIndex < 0 || gradeIndex >= static_cast<int>(gradesVector.size())) {
        throw std::out_of_range("Grade index out of bounds");
    }
    coursesVector.erase(coursesVector.begin() + gradeIndex);
    gradesVector.erase(gradesVector.begin() + gradeIndex);
}

void Student::addGrade(const Grade& newGrade, const std::string& newCourseName) {
    addGrade(newGrade, Course(newCourseName));
}

double Student::calculateAverage() const {
    if(gradesVector.empty()) { return 0.0; }
    double totalSum = 0.0;
    for(const auto& grade : gradesVector) {
        totalSum += grade.getScore();
    }
    return totalSum / static_cast<double>(gradesVector.size());
}

double Student::calculateGPA() const {
    if(gradesVector.empty()) { return 0.0; }
    double gpaSum = 0.0;
    for(const auto& grade : gradesVector) {
        double score = grade.getScore();
        if(score >= LIMIT_A) { gpaSum += GPA_VAL_A; }
        else if(score >= LIMIT_B) { gpaSum += GPA_VAL_B; }
        else if(score >= LIMIT_C) { gpaSum += GPA_VAL_C; }
        else if(score >= LIMIT_D) { gpaSum += GPA_VAL_D; }
    }
    return gpaSum / static_cast<double>(gradesVector.size());
}

Grade& Student::operator[](int index) {
    return gradesVector.at(static_cast<size_t>(index));
}

const Grade& Student::operator[](int index) const {
    return gradesVector.at(static_cast<size_t>(index));
}

Grade& Student::operator[](const std::string& nameOfCourse) {
    for(size_t i = 0; i < coursesVector.size(); ++i) {
        if(coursesVector[i].courseName == nameOfCourse) {
            return gradesVector[i];
        }
    }
    throw std::out_of_range("Course name not found");
}

double Student::operator()() const { return calculateAverage(); }

double Student::operator()(int limit) const {
    if (limit <= 0) { return 0.0; }
    double sumVal = 0.0;
    int actualLimit = (limit > static_cast<int>(gradesVector.size())) ? static_cast<int>(gradesVector.size()) : limit;
    for(int i = 0; i < actualLimit; ++i) {
        sumVal += gradesVector[static_cast<size_t>(i)].getScore();
    }
    return sumVal / actualLimit;
}

double Student::operator()(int start, int end) const {
    double sumRange = 0.0;
    int itemsCount = 0;
    for(int i = start; i <= end && i < static_cast<int>(gradesVector.size()); ++i) {
        sumRange += gradesVector[static_cast<size_t>(i)].getScore();
        itemsCount++;
    }
    return (itemsCount == 0) ? 0.0 : sumRange / itemsCount;
}

double Student::operator()(int index, double weightValue) const {
    if (gradesVector.empty()) { return 0.0; }
    double sumOfOthers = 0.0;
    for(size_t i = 0; i < gradesVector.size(); ++i) {
        if(static_cast<int>(i) != index) {
            sumOfOthers += gradesVector[i].getScore();
        }
    }
    return (gradesVector.at(static_cast<size_t>(index)).getScore() * weightValue + sumOfOthers) / 
           (weightValue + static_cast<double>(gradesVector.size()) - 1.0);
}

void Student::printGrades() const {
    for(size_t i = 0; i < gradesVector.size(); ++i) {
        std::cout << coursesVector[i].courseName << ": " << gradesVector[i] << "\n";
    }
}

int Student::countPassingGrades() const {
    int passedCount = 0;
    for(const auto& grade : gradesVector) {
        if(grade.isPassing()) { passedCount++; }
    }
    return passedCount;
}

const Grade& Student::getHighestGrade() const {
    if (gradesVector.empty()) { throw std::runtime_error("Empty grade list"); }
    size_t bestIdx = 0;
    for(size_t i = 1; i < gradesVector.size(); ++i) {
        if(gradesVector[i].getScore() > gradesVector[bestIdx].getScore()) {
            bestIdx = i;
        }
    }
    return gradesVector[bestIdx];
}

const Grade& Student::getLowestGrade() const {
    if (gradesVector.empty()) { throw std::runtime_error("Empty grade list"); }
    size_t worstIdx = 0;
    for(size_t i = 1; i < gradesVector.size(); ++i) {
        if(gradesVector[i].getScore() < gradesVector[worstIdx].getScore()) {
            worstIdx = i;
        }
    }
    return gradesVector[worstIdx];
}

Student Student::operator+(double bonusPoints) const {
    Student result(*this);
    for(auto& grade : result.gradesVector) {
        grade += bonusPoints;
    }
    return result;
}

Student Student::operator*(double multiplyFactor) const {
    Student result(*this);
    for(auto& grade : result.gradesVector) {
        grade.setScore(grade.getScore() * multiplyFactor);
    }
    return result;
}

Student& Student::operator+=(double bonusPoints) {
    for(auto& grade : gradesVector) {
        grade += bonusPoints;
    }
    return *this;
}

Student& Student::operator*=(double multiplyFactor) {
    for(auto& grade : gradesVector) {
        grade.setScore(grade.getScore() * multiplyFactor);
    }
    return *this;
}

bool Student::operator==(const Student& other) const { return calculateGPA() == other.calculateGPA(); }
bool Student::operator!=(const Student& other) const { return !(*this == other); }
bool Student::operator>(const Student& other) const { return calculateGPA() > other.calculateGPA(); }
bool Student::operator<(const Student& other) const { return calculateGPA() < other.calculateGPA(); }

bool compareByAverage(const Student& first, const Student& second) { 
    return first.calculateAverage() > second.calculateAverage(); 
}
bool haveSameGPA(const Student& first, const Student& second) { 
    return first.calculateGPA() == second.calculateGPA(); 
}

std::ostream& operator<<(std::ostream& outputStream, const Student& studentToPrint) {
    outputStream << "Student: " << studentToPrint.studentFullName << " (" << studentToPrint.studentIdNumber << ")\nGPA: " << studentToPrint.calculateGPA() << "\nGrades:\n";
    for(size_t i = 0; i < studentToPrint.gradesVector.size(); ++i) {
        outputStream << "- " << studentToPrint.coursesVector[i].courseName 
                     << " [" << studentToPrint.coursesVector[i].courseCode << "]: " 
                     << studentToPrint.gradesVector[i] << "\n";
    }
    return outputStream;
}

} // namespace grading