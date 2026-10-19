#ifndef REPTILE_HPP
#define REPTILE_HPP

#include "Animal.hpp"

namespace zoo {

class Reptile : public Animal {
private:
    // Reptile-specific fields.
    bool isVenomous;
    double length;

public:
    Reptile(const std::string& name, int age, const std::string& species, bool venom, double len);
    Reptile(const Reptile& other);
    virtual ~Reptile() override;

    // Creates a copy of the current Reptile object.
    Animal* clone() const override { return new Reptile(*this); }

    bool getIsVenomous() const { return isVenomous; }
    void setIsVenomous(bool v) { isVenomous = v; }
    void setVenomous(bool v) { isVenomous = v; }

    double getBodyLengthCm() const { return length; }
    void setBodyLengthCm(double l);

    // Implement Animal's virtual functions.
    std::string makeSound() const override;
    std::string getAnimalType() const override;
    std::string getDiet() const override;
};

}

#endif
