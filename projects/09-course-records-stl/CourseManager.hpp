#ifndef COURSE_MANAGER_HPP
#define COURSE_MANAGER_HPP

#include "StudentRecord.hpp"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace registration {

// This class manages students, courses, enrollments, and grades.
class CourseManager {
private:
    // Stores all students by their student id.
    std::map<int, StudentRecord> students;

    // Stores each course name with the ids of the students enrolled in it.
    std::map<std::string, std::set<int>> courseEnrollments;

    // Stores each course name with the grades of its students.
    std::map<std::string, std::map<int, double>> courseGrades;

    // Checks if a student exists.
    void validateStudentExists(int studentId) const;

    // Checks if a course exists.
    void validateCourseExists(const std::string& courseName) const;

    // Checks if a grade is valid.
    void validateGrade(double grade) const;

public:
    // Adds a new student.
    void addStudent(const StudentRecord& record);

    // Returns a student by id.
    StudentRecord getStudent(int studentId) const;

    // Creates a new course.
    void createCourse(const std::string& courseName);

    // Enrolls a student to a course.
    void enrollStudent(int studentId, const std::string& courseName);

    // Removes a student from a course.
    void removeStudent(int studentId, const std::string& courseName);

    // Checks if a student is enrolled in a course.
    bool isEnrolled(int studentId, const std::string& courseName) const;

    // Returns the number of students in a course.
    int getEnrollmentCount(const std::string& courseName) const;

    // Returns all student ids in a course.
    std::vector<int> getEnrolledStudents(const std::string& courseName) const;

    // Returns all courses of a specific student.
    std::vector<std::string> getStudentCourses(int studentId) const;

    // Returns students that are enrolled in both courses.
    std::vector<int> studentsInBothCourses(const std::string& firstCourse,
                                           const std::string& secondCourse) const;

    // Returns students that are enrolled in at least one of the courses.
    std::vector<int> studentsInEitherCourse(const std::string& firstCourse,
                                            const std::string& secondCourse) const;

    // Assigns a grade to a student in a course.
    void assignGrade(int studentId, const std::string& courseName, double grade);

    // Calculates the average grade of a course.
    double getCourseAverage(const std::string& courseName) const;

    // Returns the total number of students.
    int getTotalStudents() const;

    // Returns the total number of courses.
    int getTotalCourses() const;

    // Returns all course names.
    std::vector<std::string> getAllCourses() const;

    // Returns all student ids.
    std::vector<int> getAllStudentIds() const;
};

} // namespace registration

#endif