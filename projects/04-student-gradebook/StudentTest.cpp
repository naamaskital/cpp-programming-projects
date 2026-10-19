
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Student.hpp"
#include <stdexcept>

using namespace grading;

TEST_CASE("Grade - Limits and Clamping") {
    Grade low(-1.0);
    Grade high(150.0);
    CHECK(low.getScore() == 0.0);
    CHECK(high.getScore() == 100.0);
}

TEST_CASE("Grade - Basic Operations") {
    Grade g1(70.0);
    Grade g2 = g1 + 20.0;
    CHECK(g2.getScore() == 90.0);
    CHECK(g2.getLetterGrade() == "A");
    
    Grade g3 = g1 / 0.0;
    CHECK(g3.getScore() == 0.0);
}

TEST_CASE("Student - Basic Record") {
    Student s("Naama", "313");
    s.addGrade(Grade(100.0), "Operating Systems");
    CHECK(s.getName() == "Naama");
    CHECK(s.getGradeCount() == 1);
    CHECK(s[0].getScore() == 100.0);
}

TEST_CASE("Student - Error Handling") {
    Student s("Naama", "1");
    s.addGrade(Grade(80.0), "C++");
    CHECK_THROWS_AS(s[10], std::out_of_range);
    CHECK_THROWS_AS(s["Algorithms"], std::out_of_range);
}

TEST_CASE("Student - GPA Logic") {
    Student s("GPA Test", "0");
    s.addGrade(Grade(95.0), "A"); // 4.0
    s.addGrade(Grade(85.0), "B"); // 3.0
    s.addGrade(Grade(75.0), "C"); // 2.0
    s.addGrade(Grade(65.0), "D"); // 1.0
    s.addGrade(Grade(55.0), "F"); // 0.0
    CHECK(s.calculateGPA() == doctest::Approx(2.0));
}

TEST_CASE("Student - Multi-Average Overloads") {
    Student s("Avg Test", "1");
    s.addGrade(Grade(100.0), "C1");
    s.addGrade(Grade(80.0), "C2");
    s.addGrade(Grade(60.0), "C3");
    
    CHECK(s() == doctest::Approx(80.0));
    CHECK(s(2) == doctest::Approx(90.0));
    CHECK(s(1, 2) == doctest::Approx(70.0));
}

TEST_CASE("Student - Modification & Removal") {
    Student s("Edit Test", "1");
    s.addGrade(Grade(100), "C1");
    s.addGrade(Grade(50), "C2");
    s.removeGrade(0);
    CHECK(s.getGradeCount() == 1);
    CHECK(s[0].getScore() == 50.0);
}

TEST_CASE("Student - Student Comparisons") {
    Student s1("Best", "1");
    s1.addGrade(Grade(100), "C1");
    Student s2("Worst", "2");
    s2.addGrade(Grade(20), "C1");
    
    CHECK(s1 > s2);
    CHECK(s2 < s1);
    CHECK(s1 != s2);
}

TEST_CASE("Student - Weighted Grade Average") {
    Student s("Weight", "1");
    s.addGrade(Grade(90), "C1"); // weight 2
    s.addGrade(Grade(100), "C2"); // weight 1
    CHECK(s(0, 2.0) == doctest::Approx(93.3333));
}

TEST_CASE("Student - Highest and Lowest") {
    Student s("Stats", "1");
    s.addGrade(Grade(70), "C1");
    s.addGrade(Grade(95), "C2");
    s.addGrade(Grade(50), "C3");
    CHECK(s.getHighestGrade().getScore() == 95.0);
    CHECK(s.getLowestGrade().getScore() == 50.0);
    CHECK(s.countPassingGrades() == 2);
}

TEST_CASE("Student - Copy Independence") {
    Student original("S1", "1");
    original.addGrade(Grade(90), "C1");
    Student copy = original;
    copy[0] = Grade(60);
    CHECK(original[0].getScore() == 90.0);
    CHECK(copy[0].getScore() == 60.0);
}

TEST_CASE("Student - Assignment Safety") {
    Student s1("S1", "1");
    s1.addGrade(Grade(80), "C1");
    Student s2;
    s2 = s1;
    s2[0] = Grade(100);
    CHECK(s1[0].getScore() == 80.0);
}

TEST_CASE("Student - Bonus Calculation") {
    Student s("Bonus", "1");
    s.addGrade(Grade(70), "C1");
    s += 10.0;
    CHECK(s[0].getScore() == 80.0);
}

TEST_CASE("Student - Grade Multiplier") {
    Student s("Curve", "1");
    s.addGrade(Grade(50), "C1");
    s *= 1.2;
    CHECK(s[0].getScore() == 60.0);
}

TEST_CASE("Grade - Incrementation Logic") {
    Grade g(90.0);
    Grade pre = ++g;
    CHECK(pre.getScore() == 91.0);
    
    Grade post = g++;
    CHECK(post.getScore() == 91.0);
    CHECK(g.getScore() == 92.0);
}

TEST_CASE("Grade - Conversion Casts") {
    Grade g(85.5);
    CHECK((int)g == 85);
    CHECK((double)g == 85.5);
    CHECK((std::string)g == "B");
}

TEST_CASE("Student - Empty Result Safety") {
    Student s;
    CHECK(s.calculateAverage() == 0.0);
    CHECK(s.calculateGPA() == 0.0);
}

TEST_CASE("Static Counters - Students") {
    int start = Student::getCurrentStudentCount();
    {
        Student temp;
        CHECK(Student::getCurrentStudentCount() == start + 1);
    }
    CHECK(Student::getCurrentStudentCount() == start);
}

TEST_CASE("Student - Search by Name") {
    Student s("Find", "1");
    s.addGrade(Grade(88), "Math");
    CHECK(s["Math"].getScore() == 88.0);
}

TEST_CASE("Student - Capacity Reporting") {
    Student s("Cap", "1", 5);
    CHECK(s.getCapacity() >= 5);
}