//
// Created by Irina Manea on 25.04.2026.
//

#ifndef UNTITLED_SPACE_H
#define UNTITLED_SPACE_H
#include<iostream>
#include<string>
#include<vector>
#include"Player.h"


class Space {
protected:
    const int id;
    std::string name;
public:
    Space();
    Space(int id, std::string name);
    Space(const Space& obj);
    Space& operator=(const Space& obj);
    virtual ~Space() = default;

    virtual Space* clone() const = 0;
    virtual void updatePosition(Player& p, std::vector<Player*>& allPlayers, int pasi) = 0;


    //getters
    int getId() const;
    std::string getName() const;

    friend std:: ostream& operator<<(std::ostream& os, const Space& obj);
    friend std:: istream& operator>>(std::istream is, Space& obj);

    //fctie netriviala
};


#endif //UNTITLED_SPACE_H