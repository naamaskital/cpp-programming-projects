#ifndef STUDENT_RECORD_HPP
#define STUDENT_RECORD_HPP

#include <string>
#include <tuple>
#include <vector>

namespace registration {

// Defines StudentRecord as a tuple of name, id, and grade.
using StudentRecord = std::tuple<std::string, int, double>;

// Creates a new student record.
StudentRecord createRecord(const std::string& name, int id, double grade);

// Returns the student name from the record.
std::string getName(const StudentRecord& record);

// Returns the student id from the record.
int getId(const StudentRecord& record);

// Returns the student grade from the record.
double getGrade(const StudentRecord& record);

// Splits the record values into separate variables.
void unpackRecord(const StudentRecord& record, std::string& name, int& id, double& grade);

// Returns the record as a formatted string.
std::string formatRecord(const StudentRecord& record);

// Calculates the average grade of all records.
double averageGrade(const std::vector<StudentRecord>& records);

// Returns the student with the highest grade.
StudentRecord bestStudent(const std::vector<StudentRecord>& records);

// Sorts the records by grade from highest to lowest.
std::vector<StudentRecord> sortByGrade(const std::vector<StudentRecord>& records);

// Sorts the records by name in alphabetical order.
std::vector<StudentRecord> sortByName(const std::vector<StudentRecord>& records);

// Returns only records with grade higher than minGrade.
std::vector<StudentRecord> filterByGrade(const std::vector<StudentRecord>& records, double minGrade);

} // namespace registration

#endif