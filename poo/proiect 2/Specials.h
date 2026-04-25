//
// Created by Irina Manea on 25.04.2026.
//

#ifndef UNTITLED_SPECIALS_H
#define UNTITLED_SPECIALS_H
#include<iostream>
#include<string>
#include<vector>
#include<Property.h>
#include<Utilities.h>

class Specials: public Property, public Utilities {
private:
    std::string special; //pt bonusuri/ detalii specifice
public:
    Specials();
    Specials(int id, std::string name, long chirie, long pret, int multiplicator, std:: string special);
    Specials(const Specials& obj);
    Specials& operator=(const Specials& obj);
    virtual ~Specials()=default;

    //getter
    std::string getSpecial() const;
    //setter
    void setSpecial(std::string special);

    friend std::ostream& operator<<(std::ostream& os, const Specials& obj);
    friend std::istream& operator>>(istream& is, Specials& obj);
};


#endif //UNTITLED_SPECIALS_H