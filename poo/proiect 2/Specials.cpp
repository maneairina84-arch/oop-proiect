//
// Created by Irina Manea on 25.04.2026.
//

#include "Specials.h"

#include "Property.h"
#include "Space.h"
#include "Utilities.h"

Specials:: Specials(): Space (-1, "s basic"), Property(), Utilities(), special("Fara detalii"){}
Specials:: Specials(int id, std::string name, long chirie, long pret, int multiplicator, std:: string special): Space(id, name), Property(id, name, pret, chirie), Utilities(id, name, multiplicator, special) {
    this-> special= special;
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

//getter
std::string Specials::getSpecial() const {
    return special;
}
void Specials::setSpecial(std::string special) {
    this->special=special;
}

//operatori plus functii netriviale