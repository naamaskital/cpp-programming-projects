#ifndef BIRD_HPP
#define BIRD_HPP

#include "Animal.hpp"

namespace zoo {

class Bird : public Animal {
private:
    // Bird-specific fields.
    bool canFly;
    double wingspan;

public:
    Bird(const std::string& name, int age, const std::string& species, bool fly, double span);
    Bird(const Bird& other);
    virtual ~Bird() override;

    // Creates a copy of the current Bird object.
    Animal* clone() const override { return new Bird(*this); }

    bool getCanFly() const { return canFly; }
    void setCanFly(bool f) { canFly = f; }

    double getWingspanMeters() const { return wingspan; }
    void setWingspanMeters(double w);

    // Implement Animal's virtual functions.
    std::string makeSound() const override;
    std::string getAnimalType() const override;
    std::string getDiet() const override;
};

}

#endif
