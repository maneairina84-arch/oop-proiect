//
// Created by Irina Manea on 26.04.2026.
//

#include "Menu.h"

Menu::Menu(): running(true){}

void Menu::displayMenu() const {
    std::cout << "\n==== MONOPOLY ====\n";
    std::cout << "1. Start Joc\n";
    std::cout << "2. Salveaza Progresul\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alege o optiune: ";
}

void Menu::run() {
    int optiune;
    while (running) {
        displayMenu();
        try {
            if (!(std::cin >> optiune)) {
                throw std::invalid_argument("Eroare: Te rog introdu un numar valid (0, 1 sau 2)!");
            }

            if (optiune == 0) {
                running = false;
                std::cout << "Iesire din program...\n";
            } else {
                handleMenu(optiune);
            }
        } catch (const std::exception& e) {
            std::cerr << "\n" << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
}
void Menu::handleMenu(int option) {
    switch (option) {
        case 1:
            game.startGame();
            break;
        case 2:
            try {
                game.saveGame("progres_salvat.txt");
                std::cout << "Progresul a fost salvat cu succes in 'save_progres.txt'!\n";
            }
            catch (const std::exception& e) {
                std::cerr << "Eroare la salvare: " << e.what() << std::endl;
            }
            break;

        default:
            std::cout << "Optiune invalida! Incearca 0, 1 sau 2.\n";
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Menu& m) {
    os << "Interfata principala Monopoly";
    return os;
}

std::istream& operator>>(std::istream& is, Menu& m) {
    return is;
}


