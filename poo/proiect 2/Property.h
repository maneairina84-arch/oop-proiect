//
// Created by Irina Manea on 25.04.2026.
//

#ifndef UNTITLED_PROPERTY_H
#define UNTITLED_PROPERTY_H
#include<iostream>
#include<string>
#include<vector>
#include"Space.h"


class Property: virtual public Space{
protected:
    long chirie;
    long pret;
    int idProprietar;
public:
    Property();
    Property(int id, std::string name, long chirie, long pret);
    Property(const Property& obj);
    Property& operator=(const Property& obj);
    virtual ~Property()=default;


    Space* clone() const override;

    //getters
    long getPret() const;
    long getChirie() const;
    int getIdProprietar() const;

    //setters
    void setIdProprietar(int id);
    void setPret(long pret);
    void setChirie(long chirie);

    friend std::ostream& operator<<(std:: ostream & os, const Property& obj);
    friend std:: istream& operator>>(std::istream& is, Property& obj);

    void updatePosition(Player& p, std::vector<Player*>& allPlayers, int pasi) override;




};


#endif //UNTITLED_PROPERTY_H