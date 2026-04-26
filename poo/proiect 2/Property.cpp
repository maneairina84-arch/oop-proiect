//
// Created by Irina Manea on 25.04.2026.
//

#include "Property.h"

#include "Space.h"

Property:: Property(): Space(0, "basic"), chirie(0), pret(0), idProprietar(-1) {}
Property:: Property(int id, std::string name, long chirie, long pret): Space(id, name) {
    this->chirie = chirie;
    this->pret = pret;
    this->idProprietar = -1;

}
Property:: Property(const Property& obj): Space(obj) {
    this->chirie = obj.chirie;
    this->pret = obj.pret;
    this->idProprietar = obj.idProprietar;
}
Property& Property::operator=( const Property& obj) {
    if (this!=&obj) {
        Space:: operator=(obj);
        this->chirie = obj.chirie;
        this->pret = obj.pret;
        this->idProprietar = obj.idProprietar;
    }
    return *this;
}

Space* Property::clone() const {
    return new Property(*this);
}

//getters
long Property:: getChirie() const {
    return chirie;
}
long Property:: getPret() const {
    return pret;
}
int Property::getIdProprietar() const {
    return idProprietar;
}

//setters
void Property::setIdProprietar(int id) {
    this->idProprietar = id;
}
void Property::setChirie(long chirie) {
    this->chirie = chirie;
}
void Property::setPret(long pret) {
    this->pret = pret;
}


void Property::updatePosition(Player& p, std::vector<Player*>& allPlayers, int pasi) {
    std::cout <<"Ai ajuns pe" << this->getName();
    //proprietatea e libera
    if (this->idProprietar == -1) {
        std::cout << "Aceasta proprietate este libera. Pret: " << this->pret << " $";
        std::cout << "Soldul tau actual: " << p.getMoneyBalance() << " $";
        std::cout << "Doresti sa o cumperi? (1 - DA / 2 - NU): ";
        int optiune;
        std::cin >> optiune;
        if (optiune == 1) {
            if (p.getMoneyBalance() >= this->pret) {
                p.setMoneyBalance(p.getMoneyBalance() - this->pret);
                this->idProprietar = p.getId();
                p.addProperties(this->getId());
                std::cout << "FELICITARI! Ai cumparat " << this->getName() << "!";
            } else {
                std::cout << "FONDURI INSUFICIENTE pentru a cumpara aceasta proprietate.";
            }
        }
        else {
            std::cout << "Ai ales sa nu cumperi proprietatea." ;
        }
    }

    //este deja a jucatorului curent
    else if (this->idProprietar == p.getId()) {
        std::cout << "Te afli pe propria ta proprietate." ;
    }
    // este luata de altcineva
    else{
        std::cout << "Proprietatea este detinuta de Jucatorul cu id " << this->idProprietar << "." ;
        std::cout << "Trebuie sa platesti o chirie de: " << this->chirie << " $" ;

        long soldCurent = p.getMoneyBalance();
        p.setMoneyBalance(soldCurent - this->chirie);
        std::cout << "Ai platit chiria. Sold ramas: " << p.getMoneyBalance() << " $" ;
    }
}
    //operatori
std::ostream& operator<<(std::ostream& os, const Property& obj) {
    os << obj.getName() << " (ID: " << obj.getId() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Property& obj) {
    is >> obj.pret >> obj.chirie;
    obj.idProprietar = -1;
    return is;
}