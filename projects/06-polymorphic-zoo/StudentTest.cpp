#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Zoo.hpp"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"

using namespace zoo;

// Mammal tests

TEST_CASE("Mammal - Basic Construction") {
    Mammal m("Simba", 5, "Lion", false, 4);
    CHECK(m.getName() == "Simba");
    CHECK(m.getAge() == 5);
}

TEST_CASE("Mammal - Wild Sound") {
    Mammal m("Simba", 5, "Lion", false, 4);
    CHECK(m.makeSound() == "Roar!");
}

TEST_CASE("Mammal - Domestic Sound") {
    Mammal m("Mitzi", 2, "Cat", true, 4);
    CHECK(m.makeSound() == "Purr...");
}

TEST_CASE("Mammal - Diet") {
    Mammal m("Simba", 5, "Lion", false, 4);
    CHECK(m.getDiet() == "Meat");
}

TEST_CASE("Mammal - Setters Validation") {
    Mammal m("Leo", 5, "Lion", false, 4);

    // Negative values should throw exceptions.
    CHECK_THROWS_AS(m.setAge(-1), std::invalid_argument);
    CHECK_THROWS_AS(m.setNumberOfLegs(-1), std::invalid_argument);
}

// Bird tests

TEST_CASE("Bird - Basic Construction") {
    Bird b("Sky", 3, "Eagle", true, 2.0);
    CHECK(b.getSpecies() == "Eagle");
    CHECK(b.getWingspanMeters() == doctest::Approx(2.0));
}

TEST_CASE("Bird - Flying Sound") {
    Bird b("Sky", 3, "Eagle", true, 2.0);
    CHECK(b.makeSound() == "Tweet tweet!");
}

TEST_CASE("Bird - Non-flying Sound") {
    Bird b("Pingu", 2, "Penguin", false, 0.5);
    CHECK(b.makeSound() == "Squawk!");
}

TEST_CASE("Bird - Wingspan Validation") {
    Bird b("Zazu", 4, "Hornbill", true, 0.5);

    // Wingspan must be positive.
    CHECK_THROWS_AS(b.setWingspanMeters(0), std::invalid_argument);
}

TEST_CASE("Bird - Getters Check") {
    Bird b("Zazu", 4, "Hornbill", true, 0.5);
    CHECK(b.getCanFly() == true);
}

// Reptile tests

TEST_CASE("Reptile - Basic Construction") {
    Reptile r("Sly", 2, "Snake", true, 1.5);
    CHECK(r.getName() == "Sly");
    CHECK(r.getBodyLengthCm() == doctest::Approx(1.5));
}

TEST_CASE("Reptile - Venomous Sound") {
    Reptile r("Kaa", 5, "Cobra", true, 3.0);
    CHECK(r.makeSound() == "Hisss!");
}

TEST_CASE("Reptile - Non-venomous Sound") {
    Reptile r("Turtle", 10, "Sea Turtle", false, 1.0);
    CHECK(r.makeSound() == "...");
}

TEST_CASE("Reptile - Length Validation") {
    Reptile r("Kaa", 5, "Cobra", true, 3.0);

    // Body length must be positive.
    CHECK_THROWS_AS(r.setBodyLengthCm(-5), std::invalid_argument);
}

// Zoo tests

TEST_CASE("Zoo - Empty State") {
    Zoo z;
    CHECK(z.isEmpty() == true);
    CHECK(z.getCount() == 0);
}

TEST_CASE("Zoo - Name Persistence") {
    Zoo z("Safari Park");
    CHECK(z.getZooName() == "Safari Park");
}

TEST_CASE("Zoo - Deep Copy via Clone") {
    Zoo myZoo("Safari", 2);
    {
        Mammal m("Original", 5, "Lion", false);
        myZoo.addAnimal(m);
        m.setName("Changed"); 
    } 

    // The zoo keeps its own cloned copy.
    CHECK(myZoo.getAnimal(0).getName() == "Original");
}

TEST_CASE("Zoo - Removal Logic") {
    Zoo z;
    Mammal m("A", 1, "T", true);
    z.addAnimal(m);
    CHECK(z.getCount() == 1);
    z.removeAnimal(0);
    CHECK(z.getCount() == 0);
}

TEST_CASE("Zoo - Out of Range Exception") {
    Zoo z;

    // Accessing a missing animal should throw an exception.
    CHECK_THROWS_AS(z.getAnimal(0), std::out_of_range);
}

TEST_CASE("Zoo - Find Animal Check") {
    Zoo z;
    Mammal m("Leo", 5, "Lion", false);
    z.addAnimal(m);
    CHECK(z.findAnimal("Leo") != nullptr);
    CHECK(z.findAnimal("Mufasa") == nullptr);
}

// Static counter tests

TEST_CASE("Static - Animal Counter Logic") {
    int before = Animal::getAnimalCount();
    Mammal m("T", 1, "T", true);
    CHECK(Animal::getAnimalCount() == before + 1);
}

TEST_CASE("Static - Zoo Counter Logic") {
    int before = Zoo::getTotalZoosCreated();
    Zoo z1;
    Zoo z2;
    CHECK(Zoo::getTotalZoosCreated() == before + 2);
}
