#include "Point.hpp"
#include <iostream>
#include <cmath>

namespace Geometry {
    double distance(Point point1, Point point2) {
        // Calculate the difference between X and Y coordinates
        const double diffX = point1.x - point2.x;
        const double diffY = point1.y - point2.y;
        
        // Return the Euclidean distance using the Pythagorean theorem
        return std::sqrt(diffX * diffX + diffY * diffY);
    }

    void printPoint(Point pointToPrint) {
        // Print the point coordinates in (x,y) format
        std::cout << "(" << pointToPrint.x << "," << pointToPrint.y << ")\n";
    }
}