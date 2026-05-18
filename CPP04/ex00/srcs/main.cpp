#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

static void printSeparator(const char* title) {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << title << std::endl;
    std::cout << "========================================" << std::endl;
}

static void testPolymorphism(void) {
    printSeparator("TEST: Polymorphism with Animal pointers");

    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << std::endl;
    std::cout << "--- getType() calls ---" << std::endl;
    std::cout << "j (Dog) type: " << j->getType() << std::endl;
    std::cout << "i (Cat) type: " << i->getType() << std::endl;
    std::cout << "meta (Animal) type: " << meta->getType() << std::endl;

    std::cout << std::endl;
    std::cout << "--- makeSound() calls ---" << std::endl;
    std::cout << "Dog says: ";
    j->makeSound();
    std::cout << "Cat says: ";
    i->makeSound();
    std::cout << "Animal says: ";
    meta->makeSound();

    delete meta;
    delete j;
    delete i;
}

static void testDirectObjects(void) {
    printSeparator("TEST: Direct object instantiation");

    std::cout << "Creating Dog object:" << std::endl;
    Dog dog;
    std::cout << "Dog type: " << dog.getType() << std::endl;
    std::cout << "Dog says: ";
    dog.makeSound();

    std::cout << std::endl;
    std::cout << "Creating Cat object:" << std::endl;
    Cat cat;
    std::cout << "Cat type: " << cat.getType() << std::endl;
    std::cout << "Cat says: ";
    cat.makeSound();

    std::cout << std::endl;
    std::cout << "Creating Animal object:" << std::endl;
    Animal animal;
    std::cout << "Animal type: " << animal.getType() << std::endl;
    std::cout << "Animal says: ";
    animal.makeSound();
}

static void testWrongHierarchy(void) {
    printSeparator("TEST: WrongAnimal/WrongCat (non-virtual makeSound)");

    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongI = new WrongCat();

    std::cout << std::endl;
    std::cout << "--- getType() calls ---" << std::endl;
    std::cout << "WrongCat type: " << wrongI->getType() << std::endl;
    std::cout << "WrongAnimal type: " << wrongMeta->getType() << std::endl;

    std::cout << std::endl;
    std::cout << "--- makeSound() calls (WRONG - no polymorphism) ---" << std::endl;
    std::cout << "WrongCat says: ";
    wrongI->makeSound();
    std::cout << "WrongAnimal says: ";
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongI;
}

static void testCopyConstructor(void) {
    printSeparator("TEST: Copy constructors (Orthodox Canonical Form)");

    std::cout << "Creating original Dog:" << std::endl;
    Dog originalDog;
    std::cout << std::endl;

    std::cout << "Creating Dog copy via copy constructor:" << std::endl;
    Dog dogCopy(originalDog);
    std::cout << "Copy type: " << dogCopy.getType() << std::endl;
    std::cout << "Copy says: ";
    dogCopy.makeSound();

    std::cout << std::endl;
    std::cout << "Creating original Cat:" << std::endl;
    Cat originalCat;
    std::cout << std::endl;

    std::cout << "Creating Cat copy via copy constructor:" << std::endl;
    Cat catCopy(originalCat);
    std::cout << "Copy type: " << catCopy.getType() << std::endl;
    std::cout << "Copy says: ";
    catCopy.makeSound();
}

static void testAssignmentOperator(void) {
    printSeparator("TEST: Assignment operators (Orthodox Canonical Form)");

    std::cout << "Creating Dog A:" << std::endl;
    Dog dogA;
    std::cout << std::endl;

    std::cout << "Creating Dog B:" << std::endl;
    Dog dogB;
    std::cout << std::endl;

    std::cout << "Assigning Dog A to Dog B:" << std::endl;
    dogB = dogA;
    std::cout << "Dog B type after assignment: " << dogB.getType() << std::endl;

    std::cout << std::endl;
    std::cout << "Creating Cat C:" << std::endl;
    Cat catC;
    std::cout << std::endl;

    std::cout << "Creating Cat D:" << std::endl;
    Cat catD;
    std::cout << std::endl;

    std::cout << "Assigning Cat C to Cat D:" << std::endl;
    catD = catC;
    std::cout << "Cat D type after assignment: " << catD.getType() << std::endl;
}

static void testSelfAssignment(void) {
    printSeparator("TEST: Self-assignment protection");

    Dog dog;
    Dog* ptr = &dog;
    std::cout << "Self-assigning Dog to itself via pointer:" << std::endl;
    dog = *ptr;
    std::cout << "Dog type after self-assignment: " << dog.getType() << std::endl;
}

static void testArrayOfAnimals(void) {
    printSeparator("TEST: Array of Animal pointers with various types");

    const int size = 6;
    const Animal* animals[size];

    animals[0] = new Animal();
    animals[1] = new Dog();
    animals[2] = new Cat();
    animals[3] = new Dog();
    animals[4] = new Cat();
    animals[5] = new Animal();

    std::cout << std::endl;
    std::cout << "--- Iterating through array ---" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "Animal[" << i << "] type: " << animals[i]->getType() << std::endl;
        std::cout << "Animal[" << i << "] says: ";
        animals[i]->makeSound();
        std::cout << std::endl;
    }

    for (int i = 0; i < size; ++i) {
        delete animals[i];
    }
}

static void testWrongCatDirectInstantiation(void) {
    printSeparator("TEST: WrongCat direct instantiation");

    std::cout << "Creating WrongCat object:" << std::endl;
    WrongCat wrongCat;
    std::cout << "WrongCat type: " << wrongCat.getType() << std::endl;
    std::cout << "WrongCat says (direct): ";
    wrongCat.makeSound();

    std::cout << std::endl;
    std::cout << "Creating WrongAnimal object:" << std::endl;
    WrongAnimal wrongAnimal;
    std::cout << "WrongAnimal type: " << wrongAnimal.getType() << std::endl;
    std::cout << "WrongAnimal says: ";
    wrongAnimal.makeSound();
}

int main(void) {
    testDirectObjects();
    testPolymorphism();
    testWrongHierarchy();
    testCopyConstructor();
    testAssignmentOperator();
    testSelfAssignment();
    testArrayOfAnimals();
    testWrongCatDirectInstantiation();

    printSeparator("All tests completed successfully!");
    return 0;
}