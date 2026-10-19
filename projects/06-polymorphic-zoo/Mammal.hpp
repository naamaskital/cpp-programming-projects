#ifndef MAMMAL_HPP
#define MAMMAL_HPP

#include "Animal.hpp"

namespace zoo {

class Mammal : public Animal {
private:
    // Mammal-specific fields.
    bool isDomesticated;
    int numLegs;

public:
    Mammal(const std::string& name, int age, const std::string& species, bool isDom, int legs = 4);
    Mammal(const Mammal& other);
    virtual ~Mammal() override;

    // Creates a copy of the current Mammal object.
    Animal* clone() const override { return new Mammal(*this); }

    bool getIsDomesticated() const { return isDomesticated; }
    void setDomesticated(bool d) { isDomesticated = d; }

    int getNumberOfLegs() const { return numLegs; }
    void setNumberOfLegs(int l);

    // Implement Animal's virtual functions.
    std::string makeSound() const override;
    std::string getAnimalType() const override;
    std::string getDiet() const override;
};

}

#endif
