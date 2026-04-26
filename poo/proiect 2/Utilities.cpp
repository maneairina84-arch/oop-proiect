//
// Created by Irina Manea on 25.04.2026.
//

#include "Utilities.h"

#include "Space.h"
#include <stdexcept>

Utilities:: Utilities(): Space(-1,"utilizare generala"), multiplicator(0), idProprietar(-1) {}
Utilities:: Utilities(int id, std::string name, int multiplicator): Space(id,name) {
    this->multiplicator = multiplicator;
    this->idProprietar = -1;
}
Utilities:: Utilities(const Utilities& obj): Space(obj), multiplicator(obj.multiplicator), idProprietar(obj.idProprietar) {}
Utilities& Utilities::operator = (const Utilities& obj) {
    if (this != &obj) {
        Space :: operator =(obj);
        this->multiplicator = obj.multiplicator;
        this->idProprietar = obj.idProprietar;
    }
    return *this;
}
//polimorfism
Space* Utilities::clone() const {
    return new Utilities(*this);
}

//getters
int Utilities::getMultiplicator() const {
    return multiplicator;
}
int Utilities::getIdProprietar() const {
    return idProprietar;
}

//setters
void Utilities::setMultiplicator(int multiplicator) {
    this->multiplicator = multiplicator;
}
void Utilities::setIdProprietar(int id) {
    this->idProprietar = id;
}

//operatori
std::ostream& operator<<(std::ostream& os, const Utilities& obj) {
    os << obj.getName() << " [Util]";
    return os;
}

std::istream& operator>>(std::istream& is, Utilities& obj) {
    int multiplicator;
    if (is>>multiplicator) {
        obj.setMultiplicator(multiplicator);
        obj.setIdProprietar(-1);
    }
    return is;
}

void Utilities::updatePosition(Player& p, std::vector<Player*>& allPlayers, int pasi) {
    if (Utilities::idProprietar == -1) {
        int pretFix=150;
        std::cout << "Aceasta utilitate este libera. Pret: 150 $";
        std::cout << "Soldul tau actual: " << p.getMoneyBalance() << " $";
        std::cout << "Doresti sa o cumperi pentru" <<pretFix<<"$? (1 - DA / 2 - NU): ";
        int optiune;
        std::cin >> optiune;
        if (optiune == 1) {
            if (p.getMoneyBalance() >= pretFix) {
                p.setMoneyBalance(p.getMoneyBalance() -pretFix);
                this->idProprietar = p.getId();
                p.addProperties(this->getId());
                std::cout << "FELICITARI! Ai cumparat " << this->getName() << "!";
            } else {
                std::cout << "FONDURI INSUFICIENTE pentru a cumpara aceasta utilitate.";
            }
        }
        else {
            std::cout << "Ai ales sa nu cumperi proprietatea." ;
        }
    }
    else if (this->idProprietar == p.getId()) {
        std::cout << "Ești acasă la " << this->getName() << ". Nu plătești nimic." << std::endl;
    }
    else {
        Player* proprietarReal = nullptr;
        for (Player* jucator : allPlayers) {
            if (jucator->getId() == this->idProprietar) {
                proprietarReal = jucator;
                break;
            }
        }

        if (proprietarReal != nullptr) {
            long taxa = (long)pasi * this->multiplicator;

            std::cout << "Ai ajuns pe utilitatea lui " << proprietarReal->getName() << "!" << std::endl;
            std::cout << "Ai dat " << pasi << " la zaruri, iar multiplicatorul este x" << this->multiplicator << "." << std::endl;
            std::cout << "Trebuie să plătești: " << taxa << " $." << std::endl;

            p.setMoneyBalance(p.getMoneyBalance() - taxa);
            proprietarReal->setMoneyBalance(proprietarReal->getMoneyBalance() + taxa);

            std::cout << "Tranzacție finalizată." << std::endl;
        }
    }
    }
