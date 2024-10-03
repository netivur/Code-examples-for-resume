#pragma once
#include "Duck.h"
#include "Turkey.h"
#include <iostream>
class TurkeyAdapter : public Duck {
public:
    TurkeyAdapter(std::shared_ptr<Turkey> turkey)
        : turkey_{ turkey } {}

    void quack() override {
        turkey_->gobble();
    }

    void fly() override {
        turkey_->fly();
    }

private:
    std::shared_ptr<Turkey> turkey_;
};
