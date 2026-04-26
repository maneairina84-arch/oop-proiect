//
// Created by Irina Manea on 26.04.2026.
//

#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H
#include <iostream>
#include"Game.h"


class Menu {
    Game game;
    bool running;

    void displayMenu() const;
    void handleMenu(int option);
public:
    Menu();
    Menu(const Menu& other) = default;
    Menu& operator=(const Menu& other) = default;
    ~Menu() = default;

    friend std::ostream& operator<<(std::ostream& os, const Menu& m);
    friend std::istream& operator>>(std::istream& is, Menu& m);

    void run();
};


#endif //UNTITLED_MENU_H