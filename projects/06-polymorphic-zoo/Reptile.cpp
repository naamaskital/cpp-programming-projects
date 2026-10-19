#include "Reptile.hpp"
#include <stdexcept>

namespace zoo {

Reptile::Reptile(const std::string& name, int age, const std::string& species, bool venom, double len)
    : Animal(name, age, species), isVenomous(venom), length(len) {
    // Length must be a positive value.
    if (len <= 0) {
        throw std::invalid_argument("Length must be positive");
    }

    std::cout << "Reptile constructed: " << name << std::endl;
}

Reptile::Reptile(const Reptile& other) 
    : Animal(other), isVenomous(other.isVenomous), length(other.length) {
    // Copy constructor for Reptile.
    std::cout << "Reptile copy-constructed: " << name << std::endl;
}

Reptile::~Reptile() { std::cout << "Reptile destructed: " << name << std::endl; }

void Reptile::setBodyLengthCm(double l) {
    // Do not allow invalid body length.
    if (l <= 0) {
        throw std::invalid_argument("Length must be positive");
    }

    length = l;
}

// Returns a sound based on whether the reptile is venomous.
std::string Reptile::makeSound() const { return isVenomous ? "Hisss!" : "..."; }

// Returns the type of this animal.
std::string Reptile::getAnimalType() const { return "Reptile"; }

// Returns the reptile diet.
std::string Reptile::getDiet() const { return isVenomous ? "Rodents and eggs" : "Insects and plants"; }

}
