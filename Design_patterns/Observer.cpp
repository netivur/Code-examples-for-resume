#include <iostream>
#include <list>

namespace WS {
    class Observer {
    public:
        virtual ~Observer() {};
        virtual void update(double temp, double humidity, double pressure) = 0;
    };
    class Subject {
        public:
            virtual ~Subject() {};
            virtual void registerObserver(Observer* o) = 0;
            virtual void removeObserver(Observer* o) = 0;
            virtual void notifyObservers() = 0;
    };
    class DisplayElement {
    public:
        virtual ~DisplayElement() {};
        virtual void display() = 0;
    };
    
    
    class WeatherData : public Subject{
    private:
        std::list<Observer*> lO;
        double temperature{ 0 };
        double humidity{ 0 };
        double pressure{ 0 };
    public:
        virtual ~WeatherData() {
            std::cout << "Goodbye, I was the WeatherData.\n";
        }
        void registerObserver(Observer* o) override {
            lO.push_back(o);
        }
        void removeObserver(Observer* o) override {
            lO.remove(o);
        }
        void notifyObservers() {
            std::list<Observer*>::iterator l_o_i = lO.begin();
            while (l_o_i != lO.end()) {
                (*l_o_i)->update(temperature, humidity, pressure);
                ++l_o_i;
                //Для варианта обновдений только нужных Наблюдателям параметров
                //(*l_o_i)->selfUpdate();
            }
            //или так:
            /*
            for (auto&& obs : lO) {
                (*obs).update(temperature, humidity, pressure);
                //Для варианта обновдений только нужных параметров
                //(*obs).selfUpdate();
            }
            */
        }     
        void meansurementsChanged() {
            notifyObservers();
        }
        void setMeansurement(double temp, double hum, double press) {
            temperature = temp;
            humidity = hum;
            pressure = press;
            meansurementsChanged();
        }
        double getTempr() {
            return temperature;
        }
        double gethumidity() {
            return humidity;
        }
    };

    class CurrentConditionDisplay : public Observer, public DisplayElement {
    private:
        double temperature_{ 0 };
        double humidity_{ 0 };        
        WeatherData& wd_;
        static int static_number_;
        int number_;
    public:
        CurrentConditionDisplay(WeatherData& wd) : wd_(wd){
            this->wd_.registerObserver(this);
            ++CurrentConditionDisplay::static_number_;
            this->number_ = CurrentConditionDisplay::static_number_;
        }
        
        void update(double te, double hu, double pr) {
            temperature_ = te;
            humidity_ = hu;
            this->display();
        }
        //Для варианта обновдений только нужных параметров
        void selfUpdate() {
            temperature_ = wd_.getTempr();
            humidity_ = wd_.gethumidity();            
            this->display();
        }
        void display(){
            std::cout << "Current conditions: \nTemperature: " << temperature_ <<
                " C;\n Humidity: " << humidity_ << " %;" << std::endl;
        }
        void RemoveMeFromTheList() {
            wd_.removeObserver(this);
            std::cout << "Obs CurrentConditionDisplay \"" << number_ << "\" removed from the list.\n";
        }
        void PrintInfo() {
            std::cout << "Obs CurrentConditionDisplay \"" << this->number_ << "\n";
        }
    };
    int CurrentConditionDisplay::static_number_ = 0;
}

int main(){
    WS::WeatherData* pWeDa = new WS::WeatherData;
    WS::CurrentConditionDisplay* pCCD1 = new WS::CurrentConditionDisplay(*pWeDa);
    WS::CurrentConditionDisplay* pCCD2 = new WS::CurrentConditionDisplay(*pWeDa); 
    WS::CurrentConditionDisplay* pCCD3 = new WS::CurrentConditionDisplay(*pWeDa);
    
    pWeDa->setMeansurement(24.5, 37.4, 742.6);
    pWeDa->setMeansurement(27.5, 39.4, 752.6);
    pCCD2->RemoveMeFromTheList();
    pWeDa->setMeansurement(10.5, 50.4, 720.6);
    pCCD1->selfUpdate();

    delete pCCD3;
    delete pCCD2;
    delete pCCD1;
    delete pWeDa;
    return 0;
}
