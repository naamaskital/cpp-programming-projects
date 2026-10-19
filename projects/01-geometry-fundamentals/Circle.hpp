#pragma once
#include "Point.hpp"

namespace Geometry {

struct Circle {
    Point center;
    double radius;
};

// Calculate area of the circle
double calculateArea(Circle circle);

// Calculate circumference of the circle
double calculateCircumference(Circle circle);

// Check if a point is inside the circle
bool isPointInside(Circle circle, Point p);

// Print circle - should output in format Circle: center=(x,y), radius=r
void printCircle(Circle circle);

} // namespace Geometry