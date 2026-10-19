#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

namespace zoo {

class Animal {
protected:
    // Common data for every animal.
    std::string name;
    std::string species;
    int age;

    // Counts how many Animal objects currently exist.
    static int animalCount;

public:
    Animal(const std::string& name, int age, const std::string& species);
    Animal(const Animal& other);
    virtual ~Animal();

    // Creates a copy of the real derived animal.
    virtual Animal* clone() const = 0;

    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    int getAge() const { return age; }
    void setAge(int a);

    std::string getSpecies() const { return species; }

    static int getAnimalCount() { return animalCount; }

    // Functions that every derived animal must implement.
    virtual std::string makeSound() const = 0;
    virtual std::string getAnimalType() const = 0;
    virtual std::string getDiet() const = 0;

    // Returns a full description of the animal.
    virtual std::string getDescription() const;
};

}

#endif