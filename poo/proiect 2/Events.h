//
// Created by Irina Manea on 25.04.2026.
//

#ifndef UNTITLED_EVENTS_H
#define UNTITLED_EVENTS_H
#include <string>


class Events: public Space {
    std::string tipSansa;
    long newSum;
public:
    Events();
    Events(int id, std::string nume, std::string tipSansa, long newSum);
    Events(const Events& obj);
    virtual Events& operator=(const Events& obj);
    virtual ~Events() = default;

    //geters
    std::string getTipSansa() const;
    long getNewSum() const;

    //setters
    void setNewSum(long suma);
    void setTipSansa(std::string tip);

    friend std::ostream& operator<<(std::ostream& os, const Events& obj);
    friend std:: istream& operator >>(std::istream& is, Events& obj);

};


#endif //UNTITLED_EVENTS_H