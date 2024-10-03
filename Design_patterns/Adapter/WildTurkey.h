#pragma once
#include <iostream>

#include "Turkey.h"

class WildTurkey : public Turkey {
public:
    void gobble() override {
        std::cout << "Gobble gobble!\n";
    }

    void fly() override {
        std::cout << "I'm flying a short distance\n";
    }
};
