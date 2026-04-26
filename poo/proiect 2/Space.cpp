//
// Created by Irina Manea on 25.04.2026.
//

#include "Space.h"

Space:: Space(): id(-1), name("unkown") {
}
Space:: Space(int id, std:: string name): id(id), name(name) {}
Space:: Space(const Space& obj): id(obj.id), name(obj.name) {}
Space& Space::operator=(const Space& obj) {
    if (this != &obj) {
        this->name=name;
    }
    return *this;
}

//getters
int Space:: getId() const {
    return this->id;
}
std::string Space:: getName() const {
    return this->name;
}

//operatorii
std::ostream& operator<<(std::ostream& os, const Space& obj) {
    os << "ID: " << obj.id << " | Nume casuta: " << obj.name;
    return os;
}

std::istream& operator>>(std::istream& is, Space& obj) {
    return is;
}
void Space::updatePosition(Player& p, int pasi) {
}
