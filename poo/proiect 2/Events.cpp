//
// Created by Irina Manea on 25.04.2026.
//
#include<cstdlib>
#include <ctime>
#include "Events.h"

#include "Space.h"

Events:: Events(): Space(-1, "unknown event"), tipSansa(""), newSum(0){}
Events::Events(int id, std::string name, std::string tipSansa, long newSum): Space(id, name) {
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
    this->newSum=newSum;
}
void Events::setTipSansa(std::string tipSansa) {
    this->tipSansa=tipSansa;
}

//op si fct netriviale
std::ostream& operator<<(std::ostream& os, const Events& obj) {
    os << (Space&)obj;
    os << " Tip Eveniment: " << obj.tipSansa << " | Suma: " << obj.newSum;
    return os;
}

std::istream& operator>>(std::istream& is, Events& obj) {
}
//generare carte sansa
void Events::updatePosition(Player& p, int pasi) {
    std::string tipuri[]={"Taxa de drum", "Amenda","Premiu", "Eroare bancara","Go to Jail"};
    long sume[]= {-50, -150, 500, 100,0};
    int randomIndex= rand()%5;
    this->tipSansa=tipuri[randomIndex];
    this->newSum=sume[randomIndex];

    std::cout << "\n========================================";
    std::cout << "        EVENIMENT: " << this->tipSansa;
    std::cout << "========================================";
    switch (randomIndex) {
        case 0: // Taxa de drum
            std::cout << "Ai fost surprins trecand pe un drum privat.\n";
            std::cout << "Trebuie sa platesti " << std::abs(this->newSum) << " $.";
            break;
        case 1: // Amenda
            std::cout << "Politia te-a oprit pentru viteza excesiva!\n";
            std::cout << "Amenda primita este de " << std::abs(this->newSum) << " $.";
            break;
        case 2: // Premiu
            std::cout << "Felicitari! Ai castigat premiul cel mare la loto.\n";
            std::cout << "Primesti in cont " << this->newSum << " $.";
            break;
        case 3: // Eroare bancara
            std::cout << "Ai noroc! Banca a gresit calculele in favoarea ta.\n";
            std::cout << "Ti s-au creditat " << this->newSum << " $!";
            break;
        case 4: // go to jail
            std::cout << "Mergi direct la inchisoare fara sa treci prin Start!" << std::endl;
            p.sendToJail();
            p.setCurrentPosition(10);
            break;
    }
    if (randomIndex!=4) {
        long updatedBalance=p.getMoneyBalance();
        p.setMoneyBalance(updatedBalance+ this->newSum);
    }

    std::cout << "========================================\n";
    std::cout << " Jucator: " << p.getName() << " | Sold Nou: " << p.getMoneyBalance() << " $";
    std::cout << "========================================\n";

}