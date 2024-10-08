#pragma once
#include <iostream>

#include "Duck.h"

class MallardDuck : public Duck {
public:
    void quack() override {
        std::cout << "Quack!\n";
    }

    void fly() override {
        std::cout << "I'm flying!\n";
    }
};
