//
// Created by Irina Manea on 25.04.2026.
//

#include "Utilities.h"

#include "Space.h"

Utilities:: Utilities(): Space(-1,"utilizare generala"), multiplicator(0), idProprietar(-1) {}
Utilities:: Utilities(int id, std::string name, int multiplicator): Space(id,name) {
    this->multiplicator = multiplicator;
    this->idProprietar = id;
}
Utilities:: Utilities(conts Utilities obj): Space(obj), multiplicator(obj,multiplicator), idProprietar(obj.idProprietar) {}
Utilities& Utilities::operator = (const Utilities& obj) {
    if (this != &obj) {
        Space :: operator =(obj);
        this->multiplicator = obj.multiplicator;
        this->idProprietar = obj.idProprietar;
    }
    return *this;
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
int Utilities::getIdProprietar() const {
    return this_>idProprietar= id;
}

//OPERATORI PLUS FCT