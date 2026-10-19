#include "Mammal.hpp"
#include <stdexcept>

namespace zoo {

Mammal::Mammal(const std::string& name, int age, const std::string& species, bool isDom, int legs)
    : Animal(name, age, species), isDomesticated(isDom), numLegs(legs) {
    // Number of legs cannot be negative.
    if (legs < 0) {
        throw std::invalid_argument("Legs cannot be negative");
    }

    std::cout << "Mammal constructed: " << name << std::endl;
}

Mammal::Mammal(const Mammal& other) 
    : Animal(other), isDomesticated(other.isDomesticated), numLegs(other.numLegs) {
    // Copy constructor for Mammal.
    std::cout << "Mammal copy-constructed: " << name << std::endl;
}

Mammal::~Mammal() { std::cout << "Mammal destructed: " << name << std::endl; }

void Mammal::setNumberOfLegs(int l) {
    // Do not allow invalid number of legs.
    if (l < 0) {
        throw std::invalid_argument("Legs cannot be negative");
    }

    numLegs = l;
}

// Returns a sound based on whether the mammal is domesticated.
std::string Mammal::makeSound() const { return isDomesticated ? "Purr..." : "Roar!"; }

// Returns the type of this animal.
std::string Mammal::getAnimalType() const { return "Mammal"; }

// Returns the mammal diet.
std::string Mammal::getDiet() const { return isDomesticated ? "Meat and plants" : "Meat"; }

}
