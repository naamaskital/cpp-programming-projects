#ifndef ZOO_HPP
#define ZOO_HPP

#include "Animal.hpp"

namespace zoo {

class Zoo {
private:
    std::string zooName;

    // Dynamic array of Animal pointers.
    Animal** animals;

    size_t capacity;
    size_t currentSize;

    // Counts how many Zoo objects were created.
    static int totalZoosCreated;

    // Expands the animals array when it is full.
    void resize();

public:
    Zoo();
    Zoo(const std::string& name);
    Zoo(const std::string& name, int cap);
    ~Zoo();
    
    // Prevent copying because Zoo owns dynamic memory.
    Zoo(const Zoo&) = delete;
    Zoo& operator=(const Zoo&) = delete;

    static int getTotalZoosCreated() { return totalZoosCreated; }

    void addAnimal(const Animal& animal);
    void removeAnimal(int index);
    
    const Animal& getAnimal(int index) const;

    int getCount() const { return static_cast<int>(currentSize); }
    int getCapacity() const { return static_cast<int>(capacity); }

    std::string getZooName() const { return zooName; }
    void setZooName(const std::string& name) { zooName = name; }

    bool isEmpty() const { return currentSize == 0; }
    
    void printAllAnimals() const;
    void makeAllSounds() const;

    // Returns a pointer to an animal by name, or nullptr if not found.
    Animal* findAnimal(const std::string& name) const;
};

}

#endif
