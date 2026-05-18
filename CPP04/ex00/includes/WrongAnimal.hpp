#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal {
protected:
    std::string type;

public:
    WrongAnimal(void);
    WrongAnimal(const WrongAnimal& other);
    virtual ~WrongAnimal(void);

    WrongAnimal& operator=(const WrongAnimal& other);

    virtual void makeSound(void) const;
    const std::string& getType(void) const;
};

#endif