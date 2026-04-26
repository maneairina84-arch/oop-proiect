//
// Created by Irina Manea on 15.04.2026.
//

#include "Player.h"

int Player:: noPlayers=0;
Player:: Player(): id(noPlayers++),
    name("unknown"),
    moneyBalance(1500),
    currentPosition(0),
    inJail(false),
    rundeDeStat(0){}

Player:: Player(std::string name, long moneyBalance): id(noPlayers++) {
    this->name=name;
    this->moneyBalance=moneyBalance;
    this->currentPosition=0;
    this->inJail=false;
    this->rundeDeStat=0;
}

Player:: Player(const Player& obj): id(noPlayers++),
name(obj.name),
moneyBalance(obj.moneyBalance),
currentPosition(obj.currentPosition),
inJail(obj.inJail),
rundeDeStat(obj.rundeDeStat),
ownProperties(obj.ownProperties){}

Player& Player::operator= (const Player& obj) {
    if (this != &obj) {
        this-> name= obj.name;
        this-> moneyBalance= obj.moneyBalance;
        this-> currentPosition= obj.currentPosition;
        this-> inJail= obj.inJail;
        this-> rundeDeStat= obj.rundeDeStat;
        this-> ownProperties= obj.ownProperties;
    }
    return *this;
}

Player:: ~Player(){}

//getters
int Player:: getId() const {
    return this->id;
}
std::string Player::getName() const {
    return this->name;
}
long Player::getMoneyBalance() const {
    return this->moneyBalance;
}
int Player::getCurrentPosition() const {
    return this->currentPosition;
}
bool Player::getInJail() const {
    return this->inJail;
}

std::vector<int> Player::getOwnProperties() const {
    return this->ownProperties;
}

//setters
void Player:: setName(std::string name) {
    this->name=name;
}
void Player:: setMoneyBalance(long moneyBalance) {
    this->moneyBalance=moneyBalance;
}
void Player:: setCurrentPosition(int currentPosition) {
    this->currentPosition=currentPosition;
}
void Player:: setInJail(bool inJail) {
    this->inJail=inJail;
}

//serializare

void Player::sendToJail() {
    this->inJail = true;
    this->rundeDeStat = 3;
    std::cout << this->name << " a fost trimis la inchisoare!";
}
void Player::noRoundsInJail() {
    if (this->inJail) {
        if (this->rundeDeStat > 0) {
            this->rundeDeStat--;
            std::cout<< this->name << " mai are de stat " << this->rundeDeStat << " runde.";
        }
        if (this->rundeDeStat == 0) {
            this->inJail = false;
            std::cout <<this->name << " a fost eliberat!" ;
        }
    }
}

bool Player::payBail() {

    if (this->moneyBalance >= 50) {
        this->moneyBalance -= 50;
        this->inJail = false;
        this->rundeDeStat = 0;

        std::cout << this->name << " a platit taxa fixa de " << TAXA_FIXA << " $ a fost eliberat!";
        return true;
    } else {
        std::cout << this->name << " nu are 50 $ pentru a iesi din inchisoare!";
        return false;
    }
}