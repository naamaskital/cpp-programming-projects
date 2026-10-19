#include "CourseManager.hpp"

#include <stdexcept>

namespace registration {

// Checks if a student exists in the system.
void CourseManager::validateStudentExists(int studentId) const {
    if (students.find(studentId) == students.end()) {
        throw std::invalid_argument("Student does not exist");
    }
}

// Checks if a course exists in the system.
void CourseManager::validateCourseExists(const std::string& courseName) const {
    if (courseEnrollments.find(courseName) == courseEnrollments.end()) {
        throw std::invalid_argument("Course does not exist");
    }
}

// Checks if the grade is in the valid range.
void CourseManager::validateGrade(double grade) const {
    if (grade < 0.0 || grade > 100.0) {
        throw std::invalid_argument("Grade must be between 0 and 100");
    }
}

// Adds a new student to the system.
void CourseManager::addStudent(const StudentRecord& record) {
    // Get the student id from the record.
    int studentId = getId(record);

    // Do not allow two students with the same id.
    if (students.find(studentId) != students.end()) {
        throw std::invalid_argument("Student already exists");
    }

    // Save the student in the students map.
    students[studentId] = record;
}

// Returns a student record by id.
StudentRecord CourseManager::getStudent(int studentId) const {
    validateStudentExists(studentId);
    return students.at(studentId);
}

// Creates a new empty course.
void CourseManager::createCourse(const std::string& courseName) {
    // Do not create the same course twice.
    if (courseEnrollments.find(courseName) != courseEnrollments.end()) {
        throw std::invalid_argument("Course already exists");
    }

    // Create an empty set of students for this course.
    courseEnrollments[courseName] = std::set<int>{};

    // Create an empty grades map for this course.
    courseGrades[courseName] = std::map<int, double>{};
}

// Enrolls an existing student to an existing course.
void CourseManager::enrollStudent(int studentId, const std::string& courseName) {
    validateStudentExists(studentId);
    validateCourseExists(courseName);

    // Do not enroll the same student twice.
    if (courseEnrollments[courseName].count(studentId) > 0) {
        throw std::invalid_argument("Student is already enrolled");
    }

    // Add the student id to the course set.
    courseEnrollments[courseName].insert(studentId);
}

// Removes a student from a course.
void CourseManager::removeStudent(int studentId, const std::string& courseName) {
    validateStudentExists(studentId);
    validateCourseExists(courseName);

    // The student must be enrolled in the course before removing.
    if (courseEnrollments[courseName].count(studentId) == 0) {
        throw std::invalid_argument("Student is not enrolled");
    }

    // Remove the student from the course.
    courseEnrollments[courseName].erase(studentId);

    // Remove the student's grade from this course.
    courseGrades[courseName].erase(studentId);
}

// Checks if a student is enrolled in a course.
bool CourseManager::isEnrolled(int studentId, const std::string& courseName) const {
    // If the course does not exist, the student is not enrolled.
    if (courseEnrollments.find(courseName) == courseEnrollments.end()) {
        return false;
    }

    // Return true if the student id appears in the course set.
    return courseEnrollments.at(courseName).count(studentId) > 0;
}

// Returns the number of students in a course.
int CourseManager::getEnrollmentCount(const std::string& courseName) const {
    validateCourseExists(courseName);
    return static_cast<int>(courseEnrollments.at(courseName).size());
}

// Returns all student ids enrolled in a course.
std::vector<int> CourseManager::getEnrolledStudents(const std::string& courseName) const {
    validateCourseExists(courseName);

    std::vector<int> result;

    // Copy all student ids from the set into the vector.
    for (int studentId : courseEnrollments.at(courseName)) {
        result.push_back(studentId);
    }

    return result;
}

// Returns all courses that a student is enrolled in.
std::vector<std::string> CourseManager::getStudentCourses(int studentId) const {
    validateStudentExists(studentId);

    std::vector<std::string> result;

    // Go over all courses in the system.
    for (const auto& coursePair : courseEnrollments) {
        const std::string& courseName = coursePair.first;
        const std::set<int>& enrolledStudents = coursePair.second;

        // Add the course only if the student is enrolled in it.
        if (enrolledStudents.count(studentId) > 0) {
            result.push_back(courseName);
        }
    }

    return result;
}

// Returns students that are enrolled in both courses.
std::vector<int> CourseManager::studentsInBothCourses(const std::string& firstCourse,
                                                      const std::string& secondCourse) const {
    validateCourseExists(firstCourse);
    validateCourseExists(secondCourse);

    std::vector<int> result;
    const std::set<int>& firstStudents = courseEnrollments.at(firstCourse);
    const std::set<int>& secondStudents = courseEnrollments.at(secondCourse);

    // Add only students that appear in both sets.
    for (int studentId : firstStudents) {
        if (secondStudents.count(studentId) > 0) {
            result.push_back(studentId);
        }
    }

    return result;
}

// Returns students that are enrolled in at least one of the two courses.
std::vector<int> CourseManager::studentsInEitherCourse(const std::string& firstCourse,
                                                       const std::string& secondCourse) const {
    validateCourseExists(firstCourse);
    validateCourseExists(secondCourse);

    std::set<int> allStudents;
    const std::set<int>& firstStudents = courseEnrollments.at(firstCourse);
    const std::set<int>& secondStudents = courseEnrollments.at(secondCourse);

    // Add all students from the first course.
    for (int studentId : firstStudents) {
        allStudents.insert(studentId);
    }

    // Add all students from the second course.
    // The set prevents duplicates automatically.
    for (int studentId : secondStudents) {
        allStudents.insert(studentId);
    }

    std::vector<int> result;

    // Copy the final set into a vector.
    for (int studentId : allStudents) {
        result.push_back(studentId);
    }

    return result;
}

// Assigns a grade to a student in a course.
void CourseManager::assignGrade(int studentId, const std::string& courseName, double grade) {
    validateStudentExists(studentId);
    validateCourseExists(courseName);
    validateGrade(grade);

    // A grade can only be assigned to an enrolled student.
    if (!isEnrolled(studentId, courseName)) {
        throw std::invalid_argument("Student is not enrolled");
    }

    // Save or update the student's grade in this course.
    courseGrades[courseName][studentId] = grade;
}

// Calculates the average grade of a course.
double CourseManager::getCourseAverage(const std::string& courseName) const {
    validateCourseExists(courseName);

    const std::map<int, double>& grades = courseGrades.at(courseName);

    // Cannot calculate an average without grades.
    if (grades.empty()) {
        throw std::invalid_argument("No grades for this course");
    }

    double sum = 0.0;

    // Add all grades together.
    for (const auto& gradePair : grades) {
        sum += gradePair.second;
    }

    // Divide the sum by the number of grades.
    return sum / static_cast<double>(grades.size());
}

// Returns the total number of students in the system.
int CourseManager::getTotalStudents() const {
    return static_cast<int>(students.size());
}

// Returns the total number of courses in the system.
int CourseManager::getTotalCourses() const {
    return static_cast<int>(courseEnrollments.size());
}

// Returns the names of all courses in the system.
std::vector<std::string> CourseManager::getAllCourses() const {
    std::vector<std::string> result;

    // Copy every course name into the vector.
    for (const auto& coursePair : courseEnrollments) {
        result.push_back(coursePair.first);
    }

    return result;
}

// Returns the ids of all students in the system.
std::vector<int> CourseManager::getAllStudentIds() const {
    std::vector<int> result;

    // Copy every student id into the vector.
    for (const auto& studentPair : students) {
        result.push_back(studentPair.first);
    }

    return result;
}

} // namespace registration
