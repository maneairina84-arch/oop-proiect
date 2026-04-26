//
// Created by Irina Manea on 25.04.2026.
//

#include "Specials.h"

#include "Property.h"
#include "Space.h"
#include "Utilities.h"

Specials:: Specials(): Space (-1, "s basic"), Property(), Utilities(), special("Fara detalii"){}
// Constructorul ar trebui să arate așa (verifică ordinea argumentelor):
Specials::Specials(int id, std::string name, long chirie, long pret, int multiplicator, std::string special): Space(id, name), Property(id, name, chirie, pret), Utilities(id, name, multiplicator), special(special) {
    Property::idProprietar = -1;
}
Specials:: Specials(const Specials& obj): Space(obj), Property(obj), Utilities(obj), special(obj.special){}
Specials& Specials:: operator=(const Specials& obj) {
    if (this!=&obj) {
        Property::operator=(obj);
        Utilities::operator=(obj);
        this->special= obj.special;
    }
    return *this;
}

//polimorfism
Space* Specials::clone() const {
    return new Specials(*this);
}
//getter
std::string Specials::getSpecial() const {
    return special;
}
void Specials::setSpecial(std::string special) {
    this->special=special;
}

//operatori plus functii netriviale

void Specials::updatePosition(Player& p, std::vector<Player*>& allPlayers, int pasi) {
    std::cout << "\n AI AJUNS PE UN LOC  SPECIAL: " << this->getName() << std::endl;

    if (Property::idProprietar == -1) {
        std::cout << "Pret achizitie: " << this->pret << " $. Cumperi? (1-DA, 2-NU): ";
        int optiune;
        std::cin >> optiune;
        if (optiune == 1 && p.getMoneyBalance() >= this->pret) {
            p.setMoneyBalance(p.getMoneyBalance() - this->pret);
            Property::idProprietar = p.getId();
            p.addProperties(this->getId());
            this->multiplicator = 1;
            std::cout << "Acum detii " << this->getName() << "!\n";
        }
    }
    else if (Property::idProprietar == p.getId()) {
        std::cout << "Este gara/portul tau.\n";
    }
    else {
        Player* proprietarReal = nullptr;
        for (Player* jucator : allPlayers) {
            if (jucator->getId() == Property::idProprietar) {
                proprietarReal = jucator;
                break;
            }
        }

        if (proprietarReal != nullptr) {
            int nrGariDetinute = 0;
            std::vector<int> idGari = {3, 9};

            for (int idProprietate : proprietarReal->getOwnProperties()) {
                for (int idG : idGari) {
                    if (idProprietate == idG) {
                        nrGariDetinute++;
                    }
                }
            }

            //try catch

            long chirieFinala = (long)this->chirie * nrGariDetinute;

            std::cout << "Esti pe gara lui " << proprietarReal->getName() << "!\n";
            std::cout << "Proprietarul detine " << nrGariDetinute << " gari.\n";
            std::cout << "Platesti chirie (" << this->chirie << " * " << nrGariDetinute << "): " << chirieFinala << " $\n";

            p.setMoneyBalance(p.getMoneyBalance() - chirieFinala);
            proprietarReal->setMoneyBalance(proprietarReal->getMoneyBalance() + chirieFinala);
            std::cout << "Banii au fost transferati cu succes.\n";
        }
    }
}