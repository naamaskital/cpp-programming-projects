#include "Circle.hpp"
#include "Point.hpp"
#include <iostream>
#include <cmath>
#include <numbers> // Required for std::numbers::pi

namespace Geometry {
    double calculateArea(Circle circleTarget) {
        // Calculate circle area: pi * r^2
        return std::numbers::pi * (circleTarget.radius * circleTarget.radius);
    }

    double calculateCircumference(Circle circleTarget) {
        // Calculate circle circumference: 2 * pi * r
        return 2 * std::numbers::pi * circleTarget.radius;
    }

    bool isPointInside(Circle circleTarget, Point pointToCheck) {
        // Check if the distance to the center is less than or equal to the radius
        return distance(circleTarget.center, pointToCheck) <= circleTarget.radius;
    }

    void printCircle(Circle circleToPrint) {
        // Print circle details to the screen
        std::cout << "Circle at ";
        printPoint(circleToPrint.center);
        std::cout << " with radius " << circleToPrint.radius << "\n";
    }
}