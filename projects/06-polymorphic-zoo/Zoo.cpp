#include "Zoo.hpp"
#include <stdexcept>
#include <iostream>

namespace zoo {

// Static counter for created Zoo objects.
int Zoo::totalZoosCreated = 0;

Zoo::Zoo() : zooName("Unnamed Zoo"), capacity(4), currentSize(0) {
    animals = new Animal*[capacity];
    totalZoosCreated++;
}

Zoo::Zoo(const std::string& name) : zooName(name), capacity(4), currentSize(0) {
    animals = new Animal*[capacity];
    totalZoosCreated++;
}

Zoo::Zoo(const std::string& name, int cap) : zooName(name), currentSize(0) {
    // Capacity must be valid.
    if (cap <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }

    capacity = static_cast<size_t>(cap);
    animals = new Animal*[capacity];
    totalZoosCreated++;
}

Zoo::~Zoo() {
    // Delete all cloned animals.
    for (size_t i = 0; i < currentSize; i++) {
        delete animals[i];
    }

    delete[] animals;
}

void Zoo::addAnimal(const Animal& animal) {
    // Increase storage if the array is full.
    if (currentSize == capacity) {
        resize();
    }

    // Store a cloned copy of the animal.
    animals[currentSize++] = animal.clone();
}

void Zoo::resize() {
    // Double the capacity of the array.
    capacity *= 2;
    Animal** newArr = new Animal*[capacity];

    for (size_t i = 0; i < currentSize; i++) {
        newArr[i] = animals[i];
    }

    delete[] animals;
    animals = newArr;
}

const Animal& Zoo::getAnimal(int index) const {
    // Check that the index is valid.
    if (index < 0 || static_cast<size_t>(index) >= currentSize) {
        throw std::out_of_range("Index out of range");
    }

    return *animals[index];
}

void Zoo::removeAnimal(int index) {
    size_t idx = static_cast<size_t>(index);

    // Check that the index is valid.
    if (index < 0 || idx >= currentSize) {
        throw std::out_of_range("Index out of range");
    }

    delete animals[idx];

    // Shift the remaining animals left.
    for (size_t i = idx; i < currentSize - 1; i++) {
        animals[i] = animals[i+1];
    }

    currentSize--;
}

void Zoo::printAllAnimals() const {
    std::cout << "=== " << zooName << " ===" << std::endl;

    for (size_t i = 0; i < currentSize; i++) {
        std::cout << i + 1 << ". " << animals[i]->getDescription() << std::endl;
    }
}

void Zoo::makeAllSounds() const {
    // Calls the correct makeSound implementation for each animal.
    for (size_t i = 0; i < currentSize; i++) {
        std::cout << animals[i]->getName() << " says: " << animals[i]->makeSound() << std::endl;
    }
}

Animal* Zoo::findAnimal(const std::string& name) const {
    // Search animal by name.
    for (size_t i = 0; i < currentSize; i++) {
        if (animals[i]->getName() == name) {
            return animals[i];
        }
    }

    return nullptr;
}

}
