#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "StudentRecord.hpp"
#include "CourseManager.hpp"
#include "StringUtils.hpp"
#include "TypeTraitsUtils.hpp"

#include <string>
#include <vector>
#include <type_traits>

using namespace registration;

TEST_CASE("create valid record") {
    StudentRecord r = createRecord("Naama", 123, 95.5);

    CHECK(getName(r) == "Naama");
    CHECK(getId(r) == 123);
    CHECK(getGrade(r) == doctest::Approx(95.5));
}

TEST_CASE("invalid student id") {
    CHECK_THROWS_AS(createRecord("Bad", 0, 80.0), std::invalid_argument);
}

TEST_CASE("invalid grade") {
    CHECK_THROWS_AS(createRecord("Bad", 1, 101.0), std::invalid_argument);
}

TEST_CASE("average grade") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 80.0),
        createRecord("B", 2, 90.0),
        createRecord("C", 3, 100.0)
    };

    CHECK(averageGrade(records) == doctest::Approx(90.0));
}

TEST_CASE("best student") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 70.0),
        createRecord("B", 2, 98.0),
        createRecord("C", 3, 85.0)
    };

    StudentRecord best = bestStudent(records);

    CHECK(getName(best) == "B");
    CHECK(getGrade(best) == doctest::Approx(98.0));
}

TEST_CASE("sort by grade descending") {
    std::vector<StudentRecord> records = {
        createRecord("Low", 1, 60.0),
        createRecord("High", 2, 99.0),
        createRecord("Mid", 3, 80.0)
    };

    std::vector<StudentRecord> sorted = sortByGrade(records);

    CHECK(getName(sorted[0]) == "High");
    CHECK(getName(sorted[1]) == "Mid");
    CHECK(getName(sorted[2]) == "Low");
}

TEST_CASE("sort by name ascending") {
    std::vector<StudentRecord> records = {
        createRecord("Charlie", 3, 70.0),
        createRecord("Alice", 1, 90.0),
        createRecord("Bob", 2, 80.0)
    };

    std::vector<StudentRecord> sorted = sortByName(records);

    CHECK(getName(sorted[0]) == "Alice");
    CHECK(getName(sorted[1]) == "Bob");
    CHECK(getName(sorted[2]) == "Charlie");
}

TEST_CASE("filter by grade") {
    std::vector<StudentRecord> records = {
        createRecord("A", 1, 70.0),
        createRecord("B", 2, 90.0),
        createRecord("C", 3, 85.0)
    };

    std::vector<StudentRecord> filtered = filterByGrade(records, 80.0);

    CHECK(filtered.size() == 2);
    CHECK(getName(filtered[0]) == "B");
    CHECK(getName(filtered[1]) == "C");
}

TEST_CASE("add and get student") {
    CourseManager cm;

    cm.addStudent(createRecord("Naama", 1, 95.0));

    StudentRecord r = cm.getStudent(1);

    CHECK(getName(r) == "Naama");
    CHECK(getId(r) == 1);
}

TEST_CASE("duplicate student throws") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));

    CHECK_THROWS_AS(cm.addStudent(createRecord("B", 1, 80.0)), std::invalid_argument);
}

TEST_CASE("create course and enroll student") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));
    cm.createCourse("CPP");
    cm.enrollStudent(1, "CPP");

    CHECK(cm.isEnrolled(1, "CPP") == true);
    CHECK(cm.getEnrollmentCount("CPP") == 1);
}

TEST_CASE("enroll to missing course throws") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));

    CHECK_THROWS_AS(cm.enrollStudent(1, "Missing"), std::invalid_argument);
}

TEST_CASE("remove student from course") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));
    cm.createCourse("CPP");
    cm.enrollStudent(1, "CPP");

    cm.removeStudent(1, "CPP");

    CHECK(cm.isEnrolled(1, "CPP") == false);
    CHECK(cm.getEnrollmentCount("CPP") == 0);
}

TEST_CASE("get enrolled students sorted") {
    CourseManager cm;

    cm.addStudent(createRecord("C", 3, 70.0));
    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));

    cm.createCourse("CPP");

    cm.enrollStudent(3, "CPP");
    cm.enrollStudent(1, "CPP");
    cm.enrollStudent(2, "CPP");

    std::vector<int> students = cm.getEnrolledStudents("CPP");

    CHECK(students[0] == 1);
    CHECK(students[1] == 2);
    CHECK(students[2] == 3);
}

TEST_CASE("students in both courses") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));
    cm.addStudent(createRecord("C", 3, 70.0));

    cm.createCourse("CPP");
    cm.createCourse("Math");

    cm.enrollStudent(1, "CPP");
    cm.enrollStudent(2, "CPP");
    cm.enrollStudent(1, "Math");
    cm.enrollStudent(3, "Math");

    std::vector<int> both = cm.studentsInBothCourses("CPP", "Math");

    CHECK(both.size() == 1);
    CHECK(both[0] == 1);
}

TEST_CASE("assign grades and course average") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));

    cm.createCourse("CPP");

    cm.enrollStudent(1, "CPP");
    cm.enrollStudent(2, "CPP");

    cm.assignGrade(1, "CPP", 100.0);
    cm.assignGrade(2, "CPP", 80.0);

    CHECK(cm.getCourseAverage("CPP") == doctest::Approx(90.0));
}

TEST_CASE("total students and courses") {
    CourseManager cm;

    cm.addStudent(createRecord("A", 1, 90.0));
    cm.addStudent(createRecord("B", 2, 80.0));

    cm.createCourse("CPP");
    cm.createCourse("Math");

    CHECK(cm.getTotalStudents() == 2);
    CHECK(cm.getTotalCourses() == 2);
}

TEST_CASE("toUpper and toLower") {
    CHECK(toUpper("Hello") == "HELLO");
    CHECK(toLower("Hello") == "hello");
}

TEST_CASE("trim") {
    CHECK(trim("  hello  ") == "hello");
    CHECK(trim("\t hello \n") == "hello");
    CHECK(trim("   ") == "");
}

TEST_CASE("split") {
    std::vector<std::string> parts = split("a,b,c", ',');

    CHECK(parts.size() == 3);
    CHECK(parts[0] == "a");
    CHECK(parts[1] == "b");
    CHECK(parts[2] == "c");
}

TEST_CASE("join") {
    std::vector<std::string> parts = {"a", "b", "c"};

    CHECK(join(parts, "-") == "a-b-c");
}

TEST_CASE("startsWith and endsWith") {
    CHECK(startsWith("Hello World", "Hello") == true);
    CHECK(endsWith("Hello World", "World") == true);
    CHECK(startsWith("Hello World", "World") == false);
    CHECK(endsWith("Hello World", "Hello") == false);
}

TEST_CASE("palindrome") {
    CHECK(isPalindrome("racecar") == true);
    CHECK(isPalindrome("Race Car") == true);
    CHECK(isPalindrome("hello") == false);
}

TEST_CASE("describe type") {
    CHECK(describeType<int>() == "integral");
    CHECK(describeType<double>() == "floating-point");
    CHECK(describeType<std::string>() == "string");
    CHECK(describeType<int*>() == "pointer");
}

TEST_CASE("safeAdd") {
    auto result1 = safeAdd(3, 4);
    auto result2 = safeAdd(3, 4.5);

    CHECK(result1 == 7);
    CHECK(result2 == doctest::Approx(7.5));

    static_assert(std::is_same<decltype(result1), long long>::value,
                  "int + int should return long long");

    static_assert(std::is_same<decltype(result2), double>::value,
                  "int + double should return double");
}