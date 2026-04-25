//
// Created by Irina Manea on 25.04.2026.
//

#include "Property.h"

#include "Space.h"

Property:: Property(): Space(0, "basic"), chirie(0), pret(0), idProprietar(-1) {}
Property:: Property(int id, std::strng name, long chirie, long pret): Space(id, name) {
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
    if (this!=obj) {
        Space:: operator=(obj);
        this->chirie = obj.chirie;
        this->pret = obj.pret;
        this->idProprietar = obj.idProprietar;
    }
    return *this;
}

//getters
long Property:: getChirie() const {
    return chirie;
}
long Property:: getPret() const {
    return pret;
}
long Property::getIdProprietar() const {
    return idProprietar;
}

//setters
void Property::setIdProprietar(int id) {
    this->idProprietar = id;
}

//operatori


