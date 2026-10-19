#include "Animal.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace zoo {

// Static counter for all existing Animal objects.
int Animal::animalCount = 0;

Animal::Animal(const std::string& name, int age, const std::string& species)
    : name(name), species(species), age(age) {
    // Age must be valid.
    if (age < 0) {
        throw std::invalid_argument("Age cannot be negative");
    }

    // A new animal was created.
    animalCount++;
    std::cout << species << " Animal constructed: " << name << std::endl;
}

Animal::Animal(const Animal& other)
    : name(other.name), species(other.species), age(other.age) {
    // Copying creates another Animal object.
    animalCount++;
    std::cout << species << " Animal copy-constructed: " << name << std::endl;
}

Animal::~Animal() {
    std::cout << species << " Animal destructed: " << name << std::endl;
    
    // One Animal object was destroyed.
    animalCount--;
}

void Animal::setAge(int a) {
    // Do not allow negative age.
    if (a < 0) {
        throw std::invalid_argument("Age cannot be negative");
    }

    age = a;
}

std::string Animal::getDescription() const {
    std::stringstream ss;

    // Build a full description using virtual functions.
    ss << "[" << getAnimalType() << "] "
       << name << " (" << species << "), Age: " << age
       << ", Sound: " << makeSound()
       << ", Diet: " << getDiet();

    return ss.str();
}

}