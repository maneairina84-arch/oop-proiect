//
// Created by Irina Manea on 25.04.2026.
//

#ifndef UNTITLED_UTILITIES_H
#define UNTITLED_UTILITIES_H
#include <string>
#include<iostream>
#include<vector>
#include"Space.h"

#include "Space.h"


class Utilities: virtual public Space {
protected:
    int multiplicator;
    int idProprietar;
public:
    Utilities();
    Utilities(int id, std::string name, int multiplicator);
    Utilities(const Utilities& obj);
    Utilities& operator=(const Utilities& obj);
    virtual ~Utilities()=default;

    Space* clone() const override;

    //getters
    int getMultiplicator() const;
    int getIdProprietar() const;

    //setters
    void setIdProprietar(int id);
    void setMultiplicator(int multiplicator);

    friend std:: ostream& operator<<(std:: ostream& os, const Utilities& obj);
    friend std:: istream& operator> (std::istream& is, Utilities& obj);

    void updatePosition(Player& p, std::vector<Player*>& allPlayers, int pasi) override;

};


#endif //UNTITLED_UTILITIES_H