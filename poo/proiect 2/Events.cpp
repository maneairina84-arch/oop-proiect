//
// Created by Irina Manea on 25.04.2026.
//

#include "Events.h"

#include "Space.h"

Events:: Events(): Space(-1, "unknown event"), tipSansa(-1), newSum(0){}
Events::Events(int id, std::string nume, std::string tipSansa, long newSum): Space(id, name) {
    this->tipSansa=tipSansa;
    this->newSum=newSum;
}

Events::Events(const Events &obj): Space(obj), tipSansa(obj.tipSansa), newSum(obj.newSum){}
Events& Events::operator=(const Events& obj) {
    if (this != &obj) {
        Space::operator=(obj);
        this->tipSansa=obj.tipSansa;
        this->newSum=obj.newSum;
    }
    return *this;
}

//polimorfism
Space* Events::clone() const {
    return new Events(*this);
}

//getters
std::string Events::getTipSansa() const {
    return tipSansa;
}
long Events::getNewSum() const {
    return newSum;
}

//setters
void Events::setNewSum(long newSum) {
    this->newSum=suma;
}
void Events::setTipSansa(std::string tipSansa) {
    this->tipSansa=tip;
}

//op si fct netriviale