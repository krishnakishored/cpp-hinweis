// ——- ANIMAL.H ——- 

// This guards against including this header in multiple
// files that make up the program along with #endif
#ifndef ANIMAL_H

// Read the following lines once
#define ANIMAL_H

#include <string>

class Animal {
public:
    Animal();
    Animal(const Animal& orig);
    virtual ~Animal();
    std::string name;
private:

};

#endif /* ANIMAL_H */
