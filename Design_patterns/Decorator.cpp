#include <iostream>
#include <string>

namespace SB {
    class Beverage {
    protected:
        std::string description_{ "Unknown" };
    public:
        virtual ~Beverage() {}
        virtual std::string getDiscription() = 0;
        virtual double cost() = 0;
    };

    class CondimentDecorator : public Beverage {
    protected:
        Beverage* pBeverage_;
    public:
        CondimentDecorator(Beverage* pBeverage) : pBeverage_(pBeverage) {}
        std::string getDiscription() override {
            return this->pBeverage_->getDiscription();
        }
        double cost() override {
            return this->pBeverage_->cost();
        }
    };

    class Mocha : public CondimentDecorator {
    public:
        Mocha(Beverage* pBeverage) : CondimentDecorator(pBeverage) {}

        std::string getDiscription() override {
            return CondimentDecorator::getDiscription() + ", Mocha";
        }
        double cost() override {
            return CondimentDecorator::cost() + 0.20;
        }
    };

    class Whip : public CondimentDecorator {
    public:
        Whip(Beverage* pBeverage) : CondimentDecorator(pBeverage) {}

        std::string getDiscription() override {
            return CondimentDecorator::getDiscription() + ", Whip";
        }
        double cost() override {
            return CondimentDecorator::cost() + 0.40;
        }
    };

    class Soy : public CondimentDecorator {
    public:
        Soy(Beverage* pBeverage) : CondimentDecorator(pBeverage) {}

        std::string getDiscription() override {
            return CondimentDecorator::getDiscription() + ", Soy";
        }
        double cost() override {
            return CondimentDecorator::cost() + 0.15;
        }
    };

    class Espresso final : public Beverage {
    public:
        Espresso() {
            description_ = "Espresso";
        }

        std::string getDiscription() override {
            return description_;
        }

        double cost() override {
            return 1.99;
        }
    };

    class HouseBlend final : public Beverage {
    public:
        HouseBlend() {
            description_ = "HouseBlend";
        }
        std::string getDiscription() override {
            return description_;
        }

        double cost() override {
            return 0.89;
        }
    };    
}

int main(){
    
    SB::Beverage* pBev = new SB::Espresso();
    std::cout << pBev->getDiscription() << " $" << pBev->cost() << std::endl;

    SB::Beverage* pBev2 = new SB::HouseBlend();
    SB::Beverage* pBevDecMoch = new SB::Mocha(pBev2);
    SB::Beverage* pBevDecMoch2 = new SB::Mocha(pBevDecMoch);
    std::cout << pBevDecMoch2->getDiscription() << " $" << pBevDecMoch2->cost() << std::endl;
    delete pBev;
    delete pBev2;
    delete pBevDecMoch;
    delete pBevDecMoch2;
    return 0;
}
