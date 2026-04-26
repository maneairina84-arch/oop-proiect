//
// Created by Irina Manea on 15.04.2026.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H
#include<iostream>
#include<string>
#include<vector>


class Player {
    static int noPlayers;
    const int id;
    std::string name;
    long moneyBalance;
    int currentPosition;
    bool inJail;
    int rundeDeStat;
    std::vector<int>ownProperties; //se stocheaza casutacde pe tabla de joc

public:
    Player();
    Player(std::string name, long moneyBalance);
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    ~Player();

 //getters
    int getId() const;
    std::string getName() const;
    long getMoneyBalance() const;
    int getCurrentPosition() const;
    bool getInJail() const;
    std::vector<int> getOwnProperties() const;

 //setters
    void setName(std::string name);
    void setMoneyBalance(long moneyBalance);
    void setCurrentPosition(int currentPosition);
    void setInJail(bool inJail);


    friend std:: ostream& operator<< (std:: ostream& os, const Player& obj);
    friend std:: iostream& operator>>(std:: iostream& is, Player& obj);

    void noRoundsInJail(); // Scade automat rundeDeStat pana la 0
    void sendToJail();
    bool payBail();

};


#endif //UNTITLED_PLAYER_H