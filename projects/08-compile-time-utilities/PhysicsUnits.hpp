#ifndef PHYSICSUNITS_HPP
#define PHYSICSUNITS_HPP

namespace metaengine {

// Common physics constants.
constexpr double PI = 3.14159265358979323846;
constexpr double GRAVITY = 9.80665;
constexpr double SPEED_OF_LIGHT = 299792458.0;

// Temperature conversions.
constexpr double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

constexpr double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Distance conversions.
constexpr double kmToMiles(double kilometers) {
    return kilometers * 0.621371;
}

constexpr double milesToKm(double miles) {
    return miles * 1.60934;
}

// Angle conversions.
constexpr double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

constexpr double radiansToDegrees(double radians) {
    return radians * 180.0 / PI;
}

// Basic physics formulas.
constexpr double kineticEnergy(double mass, double velocity) {
    return 0.5 * mass * velocity * velocity;
}

constexpr double potentialEnergy(double mass, double height) {
    return mass * GRAVITY * height;
}

constexpr double massEnergy(double mass) {
    return mass * SPEED_OF_LIGHT * SPEED_OF_LIGHT;
}

constexpr double freeFallDistance(double time) {
    return 0.5 * GRAVITY * time * time;
}

// Compile-time recursive power function.
constexpr double power(double base, int exponent) {
    return exponent == 0 ? 1.0 : base * power(base, exponent - 1);
}

// Return the absolute value.
constexpr double absVal(double value) {
    return value < 0.0 ? -value : value;
}

} // namespace metaengine

#endif