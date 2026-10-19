
#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Grade.hpp"
#include <string>
#include <vector>
#include <utility>

namespace grading {


struct Course {
    std::string courseName;
    std::string courseCode;
    int courseCredits;
    Course(std::string name = "", std::string code = "", int credits = 0) 
        : courseName(std::move(name)), courseCode(std::move(code)), courseCredits(credits) {}
};

class Student {
private:
    std::string studentFullName;
    std::string studentIdNumber;
    std::vector<Course> coursesVector;
    std::vector<Grade> gradesVector;
    
    static int totalStudentsCounter;
    static int currentStudentsInMem;

    // GPA mapping constants
    static constexpr double GPA_VAL_A = 4.0;
    static constexpr double GPA_VAL_B = 3.0;
    static constexpr double GPA_VAL_C = 2.0;
    static constexpr double GPA_VAL_D = 1.0;
    static constexpr double LIMIT_A = 90.0;
    static constexpr double LIMIT_B = 80.0;
    static constexpr double LIMIT_C = 70.0;
    static constexpr double LIMIT_D = 60.0;

public:
    // Constructors & Destructor
    Student(); 
    Student(std::string nameInput, std::string idInput, int initialCapacity = 2);
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);

    // Getters & Status
    std::string getName() const { return studentFullName; }
    void setName(std::string newName) { studentFullName = std::move(newName); }
    std::string getStudentID() const { return studentIdNumber; }
    int getGradeCount() const { return static_cast<int>(gradesVector.size()); }
    int getCapacity() const { return static_cast<int>(gradesVector.capacity()); }

    static int getTotalStudentsCreated() { return totalStudentsCounter; }
    static int getCurrentStudentCount() { return currentStudentsInMem; }

    // Management functions
    void addGrade(const Grade& newGrade, const Course& newCourse);
    void addGrade(const Grade& newGrade, const std::string& newCourseName);
    void removeGrade(int gradeIndex); 

    // Statistics
    double calculateAverage() const;
    double calculateGPA() const;
    int countPassingGrades() const;
    const Grade& getHighestGrade() const;
    const Grade& getLowestGrade() const;
    void printGrades() const;

    // Bracket Operators []
    Grade& operator[](int index);
    const Grade& operator[](int index) const;
    Grade& operator[](const std::string& nameOfCourse);

    // Parentheses Operators () - Averaging logic
    double operator()() const;
    double operator()(int limit) const;
    double operator()(int start, int end) const;
    double operator()(int index, double weight) const;

    // Bulk arithmetic on all student's grades
    Student operator+(double bonusPoints) const;
    Student operator*(double multiplyFactor) const;
    Student& operator+=(double bonusPoints);
    Student& operator*=(double multiplyFactor);

    // Student Comparison by GPA
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<(const Student& other) const;

    // Global helper friends
    friend bool compareByAverage(const Student& first, const Student& second);
    friend bool haveSameGPA(const Student& first, const Student& second);
    friend std::ostream& operator<<(std::ostream& outputStream, const Student& studentToPrint);
};

} // namespace grading

#endif