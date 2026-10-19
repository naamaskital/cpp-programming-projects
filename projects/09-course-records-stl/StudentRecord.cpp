#include "StudentRecord.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace registration {

// Creates a new student record.
StudentRecord createRecord(const std::string& name, int id, double grade) {
    // Student id must be positive.
    if (id <= 0) {
        throw std::invalid_argument("Student id must be positive");
    }

    // Grade must be between 0 and 100.
    if (grade < 0.0 || grade > 100.0) {
        throw std::invalid_argument("Grade must be between 0 and 100");
    }

    // Create and return a tuple with name, id, and grade.
    return StudentRecord{name, id, grade};
}

// Returns the student name from the record.
std::string getName(const StudentRecord& record) {
    return std::get<0>(record);
}

// Returns the student id from the record.
int getId(const StudentRecord& record) {
    return std::get<1>(record);
}

// Returns the student grade from the record.
double getGrade(const StudentRecord& record) {
    return std::get<2>(record);
}

// Splits the record values into separate variables.
void unpackRecord(const StudentRecord& record, std::string& name, int& id, double& grade) {
    std::tie(name, id, grade) = record;
}

// Returns the record as a formatted string.
std::string formatRecord(const StudentRecord& record) {
    std::ostringstream out;
    out << getName(record) << " (ID: " << getId(record) << ", Grade: "
        << std::fixed << std::setprecision(1) << getGrade(record) << ")";
    return out.str();
}

// Calculates the average grade of all records.
double averageGrade(const std::vector<StudentRecord>& records) {
    // Cannot calculate average if there are no records.
    if (records.empty()) {
        throw std::invalid_argument("Cannot calculate average of empty records");
    }

    double sum = 0.0;

    // Add all grades together.
    for (const StudentRecord& record : records) {
        sum += getGrade(record);
    }

    // Divide the sum by the number of records.
    return sum / static_cast<double>(records.size());
}

// Finds the student with the highest grade.
StudentRecord bestStudent(const std::vector<StudentRecord>& records) {
    // Cannot find the best student if the vector is empty.
    if (records.empty()) {
        throw std::invalid_argument("Cannot find best student in empty records");
    }

    // Start by assuming the first student is the best.
    StudentRecord best = records[0];

    // Check if another student has a higher grade.
    for (const StudentRecord& record : records) {
        if (getGrade(record) > getGrade(best)) {
            best = record;
        }
    }

    return best;
}

// Sorts the records by grade from highest to lowest.
std::vector<StudentRecord> sortByGrade(const std::vector<StudentRecord>& records) {
    std::vector<StudentRecord> sorted = records;

    std::stable_sort(sorted.begin(), sorted.end(),
                     [](const StudentRecord& first, const StudentRecord& second) {
                         return getGrade(first) > getGrade(second);
                     });

    return sorted;
}
// Sorts the records by name in alphabetical order.
std::vector<StudentRecord> sortByName(const std::vector<StudentRecord>& records) {
    std::vector<StudentRecord> sorted = records;

    std::stable_sort(sorted.begin(), sorted.end(),
                     [](const StudentRecord& first, const StudentRecord& second) {
                         return getName(first) < getName(second);
                     });

    return sorted;
}

// Returns only records with grade higher than minGrade.
std::vector<StudentRecord> filterByGrade(const std::vector<StudentRecord>& records, double minGrade) {
    std::vector<StudentRecord> result;

    // Add only students with a high enough grade.
    for (const StudentRecord& record : records) {
        if (getGrade(record) > minGrade) {
            result.push_back(record);
        }
    }

    return result;
}

} // namespace registration