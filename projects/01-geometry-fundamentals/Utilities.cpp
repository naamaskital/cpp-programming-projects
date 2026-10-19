#include "Utilities.hpp"
#include "Point.hpp"
#include "Circle.hpp"
#include <span>

namespace Utils {

    // Helper to create a circle with given center and radius
    Geometry::Circle createCircle(double centerX, double centerY, double radius) { // NOLINT(bugprone-easily-swappable-parameters)
        Geometry::Circle newCircle{};
        newCircle.center.x = centerX;
        newCircle.center.y = centerY;
        newCircle.radius = radius;
        return newCircle;
    }

    // Find the point in the array that is closest to (0,0)
    Geometry::Point findClosestToOrigin(Geometry::Point* points, int size)  {
        if (size <= 0) {
            return {0, 0};
        }

        // Use span to safely wrap the array
        std::span<Geometry::Point> pointsSpan(points, static_cast<size_t>(size));
        
        Geometry::Point closestPoint = pointsSpan[0];
        const Geometry::Point originPoint = {0, 0};
        
        // Loop through the points to find the minimum distance
        for (const auto& currentPoint : pointsSpan) {
            if (Geometry::distance(currentPoint, originPoint) < Geometry::distance(closestPoint, originPoint)) {
                closestPoint = currentPoint;
            }
        }
        return closestPoint;
    }

    // Calculate the average of numbers in an array
    double calculateAverage(const double* arr, int size) {
        if (size <= 0) {
            return 0.0;
        }
        
        // Use span to wrap the double array
        std::span<const double> valuesSpan(arr, static_cast<size_t>(size));
        double sumValues = 0.0;
        
        // Sum all numbers in the array
        for (const double val : valuesSpan) {
            sumValues += val;
        }
        
        // Divide sum by total size to get the average
        return sumValues / static_cast<double>(size);
    }

} // namespace Utils