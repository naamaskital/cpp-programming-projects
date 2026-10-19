#include "Bird.hpp"
#include <stdexcept>

namespace zoo {

Bird::Bird(const std::string& name, int age, const std::string& species, bool fly, double span)
    : Animal(name, age, species), canFly(fly), wingspan(span) {
    // Wingspan must be a positive value.
    if (span <= 0) {
        throw std::invalid_argument("Wingspan must be positive");
    }

    std::cout << "Bird constructed: " << name << std::endl;
}

Bird::Bird(const Bird& other) 
    : Animal(other), canFly(other.canFly), wingspan(other.wingspan) {
    // Copy constructor for Bird.
    std::cout << "Bird copy-constructed: " << name << std::endl;
}

Bird::~Bird() {
    // Bird object is being destroyed.
    std::cout << "Bird destructed: " << name << std::endl;
}

void Bird::setWingspanMeters(double w) {
    // Do not allow invalid wingspan.
    if (w <= 0) {
        throw std::invalid_argument("Wingspan must be positive");
    }

    wingspan = w;
}

// Returns the bird sound according to its ability to fly.
std::string Bird::makeSound() const { return canFly ? "Tweet tweet!" : "Squawk!"; }

// Returns the type of this animal.
std::string Bird::getAnimalType() const { return "Bird"; }

// Returns the bird diet.
std::string Bird::getDiet() const { return "Seeds and insects"; }

}
