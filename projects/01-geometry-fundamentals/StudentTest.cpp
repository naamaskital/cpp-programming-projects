#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Point.hpp"
#include "Circle.hpp"
#include "Utilities.hpp"
#include <cmath>

using namespace Geometry;

// --- Section 1: Points and Distance ---

TEST_CASE("1: Distance between 0,0 and 3,4") { CHECK(distance({0, 0}, {3, 4}) == doctest::Approx(5.0)); }
TEST_CASE("2: Distance between same points") { CHECK(distance({10, 10}, {10, 10}) == doctest::Approx(0.0)); }
TEST_CASE("3: Distance between 1,1 and 4,5") { CHECK(distance({1, 1}, {4, 5}) == doctest::Approx(5.0)); }
TEST_CASE("4: Distance with negative numbers") { CHECK(distance({-1, -1}, {1, 1}) == doctest::Approx(std::sqrt(8))); }
TEST_CASE("5: Distance with vertical points") { CHECK(distance({0, 0}, {0, -10}) == doctest::Approx(10.0)); }
TEST_CASE("6: Distance with decimals") { CHECK(distance({1.5, 2.5}, {4.5, 6.5}) == doctest::Approx(5.0)); }

// --- Section 2: Circle Area ---

TEST_CASE("7: Area of radius 2") { CHECK(calculateArea({{0, 0}, 2}) == doctest::Approx(M_PI * 4)); }
TEST_CASE("8: Area of radius 10") { CHECK(calculateArea({{5, 5}, 10}) == doctest::Approx(M_PI * 100)); }
TEST_CASE("9: Area of radius 0") { CHECK(calculateArea({{1, 1}, 0}) == doctest::Approx(0.0)); }

// --- Section 3: Circle Circumference ---

TEST_CASE("10: Circumference of radius 2") { CHECK(calculateCircumference({{0, 0}, 2}) == doctest::Approx(M_PI * 4)); }
TEST_CASE("11: Circumference of radius 10") { CHECK(calculateCircumference({{5, 5}, 10}) == doctest::Approx(M_PI * 20)); }
TEST_CASE("12: Circumference of radius 0") { CHECK(calculateCircumference({{1, 1}, 0}) == doctest::Approx(0.0)); }

// --- Section 4: Points Inside Circle ---

TEST_CASE("13: Point at center is inside") { CHECK(isPointInside({{0, 0}, 5}, {0, 0}) == true); }
TEST_CASE("14: Point on horizontal edge is inside") { CHECK(isPointInside({{0, 0}, 5}, {5, 0}) == true); }
TEST_CASE("15: Point on vertical edge is inside") { CHECK(isPointInside({{0, 0}, 5}, {0, 5}) == true); }
TEST_CASE("16: Negative point inside") { CHECK(isPointInside({{0, 0}, 5}, {-3, -4}) == true); }
TEST_CASE("17: Point outside on X axis") { CHECK(isPointInside({{0, 0}, 5}, {6, 0}) == false); }
TEST_CASE("18: Point outside on Y axis") { CHECK(isPointInside({{0, 0}, 5}, {0, 5.1}) == false); }
TEST_CASE("19: Point far away outside") { CHECK(isPointInside({{0, 0}, 5}, {10, 10}) == false); }
TEST_CASE("20: Point near edge outside") { CHECK(isPointInside({{0, 0}, 5}, {4, 4}) == false); }

// --- Section 5: Utilities ---

TEST_CASE("21: Closest to origin from 3 points") { 
    Point pts[] = {{10, 10}, {1, 1}, {5, 0}};
    CHECK(Utils::findClosestToOrigin(pts, 3).x == 1); 
}
TEST_CASE("22: Closest to origin from 1 point") { 
    Point p_single[] = {{7, 7}};
    CHECK(Utils::findClosestToOrigin(p_single, 1).y == 7); 
}
TEST_CASE("23: Average of 1 to 5") { 
    double arr[] = {1, 2, 3, 4, 5};
    CHECK(Utils::calculateAverage(arr, 5) == doctest::Approx(3.0)); 
}
TEST_CASE("24: Average with zeros") { 
    double arr[] = {-10, 10, 0};
    CHECK(Utils::calculateAverage(arr, 3) == doctest::Approx(0.0)); 
}
TEST_CASE("25: Average with decimals") { 
    double arr[] = {2.5, 2.5, 5.0};
    CHECK(Utils::calculateAverage(arr, 3) == doctest::Approx(3.33333)); 
}
TEST_CASE("26: Create circle X check") { CHECK(Utils::createCircle(1, 2, 3).center.x == 1); }
TEST_CASE("27: Create circle Y check") { CHECK(Utils::createCircle(1, 2, 3).center.y == 2); }
TEST_CASE("28: Create circle Radius check") { CHECK(Utils::createCircle(1, 2, 3).radius == 3); }

// --- Section 6: Extra Checks ---

TEST_CASE("29: Point at 0,0 distance to 0,0") { CHECK(distance({0,0}, {0,0}) == 0); }
TEST_CASE("30: Create large circle check") { CHECK(Utils::createCircle(0, 0, 100).radius == 100); }