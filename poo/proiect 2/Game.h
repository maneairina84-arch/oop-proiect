//
// Created by Irina Manea on 25.04.2026.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include <string>
#include<iostream>
#include<vector>
#include<Space.h>
#include<Property.h>
#include<Utilities.h>
#include<Specials.h>
#include<Events.h>
#include<Player.h>

#include "Player.h"

class Game {
    std::vector<Space*> board;
    std:: vector<Player*> players;
    int currentPlayerIndex;
    bool gameOver;

public:
    Game();
    Game(int nrJucatori);
    Game(const Game& obj);
    Game& operator=(const Game& obj);
    ~Game();

    friend std::ostream& operator<<(std::ostream& os, const Game& obj);
    friend std::istream& operator>>(std::istream& is, Game& obj);

};


#endif //UNTITLED_GAME_H