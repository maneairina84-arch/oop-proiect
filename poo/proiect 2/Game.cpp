//
// Created by Irina Manea on 25.04.2026.
//

#include "Game.h"
#include <iostream>
#include<cstdlib>
#include <ctime>
#include<vector>
#include<string>
#include<fstream>
#include <stdexcept>

#include "Space.h"

//desen
std::string Game::getPlayerAtPos(int pos) const {
    std::string s = "";
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->getCurrentPosition() == pos) {
            s += "P" + std::to_string(players[i]->getId());
        }
    }
    while (s.length() < 5) s += " "; //aliniere la 5 caract
    return s;
}
std::string Game::getNameFixed(int pos) const {
    if (pos >= board.size()) return "     ";
    std::string name = board[pos]->getName();
    Property* prop = dynamic_cast<Property*>(board[pos]);

    if (prop && prop->getIdProprietar() != -1) {
        if (name.length() > 3) name = name.substr(0, 3);
        name += "(" + std::to_string(prop->getIdProprietar()) + ")";
    } else {
        if (name.length() > 5) name = name.substr(0, 5);
    }

    while (name.length() < 5) name += " ";
    return name;
}

Game:: Game(): currentPlayerIndex(0), gameOver(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}
Game:: Game(int nrJucatori):currentPlayerIndex(0), gameOver(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < nrJucatori; i++) {
        players.push_back(new Player("Jucator"+ std::to_string (i+1),1500));
    }
}
Game::Game(const Game& obj) {
    this->currentPlayerIndex = obj.currentPlayerIndex;
    this->gameOver = obj.gameOver;
    this->players = obj.players;
    for (Space* s : obj.board) {
        if (s != nullptr) this->board.push_back(s->clone());
        else this->board.push_back(nullptr);
    }
}
Game& Game::operator= (const Game& obj) {
    if (this!=&obj) {
        for (Space* s: this->board) {
            delete s;
        }
        this->board.clear();
        this->currentPlayerIndex = obj.currentPlayerIndex;
        this->gameOver = obj.gameOver;
        this->players = obj.players;
        for (Space* s: obj.board) {
            if (s!=nullptr) {
                this->board.push_back(s->clone());
            }
        }
    }
    return *this;
}
Game:: ~Game() {
    for (Space* s: this->board) {
        delete s;
    }
    board.clear();
    std::cout<<"DEBUG : Memoria jocului a fost eliberata!";
}
//getter
int Game::getNrPlayers() const {
    return static_cast<int>(players.size());
}


void Game::initGame() {
    for (Space* s : board) {
        delete s;
    }
    board.clear();

    std::ifstream fConfig("config.txt");

    board.push_back(new Events(0, "START", "Salariu", 200));

    if (!fConfig.is_open()) {
        board.push_back(new Property(1, "Vitan", 100, 50));
        board.push_back(new Property(2, "Cotroceni", 120, 60));
    } else {
        int id, pret, chirie;
        std::string nume;
        for(int i = 0; i < 2; ++i) {
            if(fConfig >> id >> nume >> pret >> chirie)
                board.push_back(new Property(id, nume, pret, chirie));
        }
    }

    board.push_back(new Specials(3, "Gara", 500, 100, 2, "Transport"));
    board.push_back(new Utilities(4, "Apa", 7));

    if (fConfig.is_open()) {
        int id, pret, chirie;
        std::string nume;
        if(fConfig >> id >> nume >> pret >> chirie)
            board.push_back(new Property(id, nume, pret, chirie));
    } else {
        board.push_back(new Property(5, "PBT", 150, 70));
    }

    board.push_back(new Events(6, "Vizita", "Inchisoare", 0));

    if (fConfig.is_open()) {
        int id, pret, chirie;
        std::string nume;
        for(int i = 0; i < 2; ++i) {
            if(fConfig >> id >> nume >> pret >> chirie)
                board.push_back(new Property(id, nume, pret, chirie));
        }
    } else {
        board.push_back(new Property(7, "Magheru", 300, 150));
        board.push_back(new Property(8, "Unirii", 350, 180));
    }

    board.push_back(new Specials(9, "Port", 500, 100, 2, "Transport"));
    board.push_back(new Events(10, "Jail", "Inchisoare", 0));
    board.push_back(new Events(11, "Chest", "Noroc?", 50));

    if (fConfig.is_open()) fConfig.close();
    try {
        if (board.size() < 12) {
            throw std::runtime_error("CRITICAL: Tabla de joc nu are 12 casute! Verifica config.txt");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

    }
}



//zaruri
int Game:: displayDice() {
    int dieRoll = std::rand() % 6 + 1;

    if (dieRoll == 1) {
        std::cout << " ------- " << std::endl;
        std::cout << "|       |" << std::endl;
        std::cout << "|   o   |" << std::endl;
        std::cout << "|       |" << std::endl;
        std::cout << " ------- " << std::endl;
    }
    else if (dieRoll == 2) {
        std::cout << " ------- " << std::endl;
        std::cout << "| o     |" << std::endl;
        std::cout << "|       |" << std::endl;
        std::cout << "|     o |" << std::endl;
        std::cout << " ------- " << std::endl;
    }
    else if (dieRoll == 3) {
        std::cout << " ------- " << std::endl;
        std::cout << "|     o |" << std::endl;
        std::cout << "|   o   |" << std::endl;
        std::cout << "| o     |" << std::endl;
        std::cout << " ------- " << std::endl;
    }
    else if (dieRoll == 4) {
        std::cout << " ------- " << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << "|       |" << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << " ------- " << std::endl;
    }
    else if (dieRoll == 5) {
        std::cout << " ------- " << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << "|   o   |" << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << " ------- " << std::endl;
    }
    else {
        std::cout << " ------- " << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << "| o   o |" << std::endl;
        std::cout << " ------- " << std::endl;
    }

    return dieRoll;
}

//se creeaza tabla standard
void Game::drawBoard() const {
    if (board.size()< BOARD_SIZE) return; // refacut cu try catch

    std::cout << "\n   " << getNameFixed(0) << "   " << getNameFixed(1) << "   " << getNameFixed(2) << "   " << getNameFixed(3) << "\n";
    std::cout << " +-------+-------+-------+-------+\n";
    std::cout << " | " << getPlayerAtPos(0) << " | " << getPlayerAtPos(1) << " | " << getPlayerAtPos(2) << " | " << getPlayerAtPos(3) << " |\n";
    std::cout << " +-------+-------+-------+-------+\n";

    // Mijloc
    std::cout << " | " << getPlayerAtPos(11) << " |               | " << getPlayerAtPos(4) << " |   " << getNameFixed(4) << "\n";
    std::cout << " +-------+   MONOPOLY    +-------+\n";
    std::cout << " | " << getPlayerAtPos(10) << " |               | " << getPlayerAtPos(5) << " |   " << getNameFixed(5) << "\n";

    // Latura de jos
    std::cout << " +-------+-------+-------+-------+\n";
    std::cout << " | " << getPlayerAtPos(9) << " | " << getPlayerAtPos(8) << " | " << getPlayerAtPos(7) << " | " << getPlayerAtPos(6) << " |\n";
    std::cout << " +-------+-------+-------+-------+\n";
    std::cout << "   " << getNameFixed(9) << "   " << getNameFixed(8) << "   " << getNameFixed(7) << "   " << getNameFixed(6) << "\n";
}

//operatori
std::ostream& operator<< (std::ostream& os, const Game& obj) {
    obj.drawBoard();
    os << "\n>>> RANDUL LUI: " << obj.players[obj.currentPlayerIndex]->getName() << " <<<\n";
    return os;
}

std::istream& operator>>(std::istream& is, Game& obj) {
    int nr;
    bool valid = false;
    while (!valid) {
        try {
            std::cout << "Numar jucatori (2-4): ";
            if (!(is >> nr)) {
                is.clear();
                is.ignore(1000, '\n');
                throw std::invalid_argument("Eroare: Trebuie sa introduci un numar intreg!");
            }
            if (nr < 2 || nr > 4) {
                throw std::out_of_range("Eroare: Jocurile de Monopoly se joaca in 2-4 persoane!");
            }
            valid = true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    obj.players.clear();
    for(int i = 0; i < nr; ++i) {
        std::string n;
        std::cout << "Nume Jucator " << i+1 << ": ";
        is >> n;
        obj.players.push_back(new Player(n, 1500));
    }
    return is;
}
void Game:: playTurn() {
    Player* p=players[currentPlayerIndex];
    if (p->getInJail()) {
        this->payToEscapeJail();
        if (p->getInJail()) {
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            return;
        }
    }
   std:: cout << "Jucatorul arunca zarurile...\n";
    int z1=displayDice();
    int z2=displayDice();
    int sumaTotala=z1+z2;
    std:: cout << "Jucatorul a aruncat zarurile...\n";
    std::cout << "Suma totala a zarurilor este: "<<sumaTotala<<"\n";
    int pasi=sumaTotala;
    int oldPos= p->getCurrentPosition();
    int nowPos= (oldPos+pasi)%BOARD_SIZE;

    if (nowPos<oldPos) {
        std::cout << "Ai trecut pe la START! +200$\n";
        p->setMoneyBalance(p->getMoneyBalance()+200);
    }
    p->setCurrentPosition(nowPos);

    board[nowPos]->updatePosition(*p, this->players, pasi);
    std::cin.ignore(1000, '\n');
    currentPlayerIndex=(currentPlayerIndex+1)%players.size();
}

void Game::startGame() {
    std::cin >> *this;

    this->initGame();

    int nrTure = 0;
    bool validTure = false;

    while (!validTure) {
        try {
            std::cout << "\nCate ture doriti sa aiba jocul? ";
            if (!(std::cin >> nrTure)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                throw std::invalid_argument("Eroare: Introdu un numar valid!");
            }
            if (nrTure <= 0) {
                throw std::out_of_range("Eroare: Numarul de ture trebuie sa fie pozitiv!");
            }
            validTure = true;
            std::cin.ignore(1000, '\n'); // Curatam buffer-ul dupa numarul de ture
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    for (int tura = 1; tura <= nrTure; tura++) {
        std::cout << "\n==========================================";
        std::cout << "\n          INCEPE TURA " << tura << " DIN " << nrTure;
        std::cout << "\n==========================================\n";

        for (int i = 0; i < getNrPlayers(); i++) {
            std::cout << *this;
            this->playTurn();

            std::cout << "\n[Tura " << tura << "] Apasa ENTER sau 'Q' pentru meniu: ";

            std::string input;
            std::getline(std::cin, input);


            if (!input.empty() && (input[0] == 'q' || input[0] == 'Q')) {
                std::cout << "\nSe revine la meniul principal...\n";
                return;
            }
        }

        }

    this->announceWinner();
    std::cout << "\nJocul s-a terminat. Apasa Enter pentru meniu...";
    std::cin.get();
}

void Game::announceWinner() {
    if (players.empty()) return; //try catch

    long maxBalance = players[0]->getMoneyBalance();
    for (size_t i = 1; i < players.size(); i++) {
        if (players[i]->getMoneyBalance() > maxBalance) {
            maxBalance = players[i]->getMoneyBalance();
        }
    }
    std::vector<Player*> winners;
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i]->getMoneyBalance() == maxBalance) {
            winners.push_back(players[i]);
        }

    }
    std::cout << "\n\n";
    std::cout << "       ___________" << std::endl;
    std::cout << "      '._==_==_=_.'" << std::endl;
    std::cout << "      .-\\:      /-." << std::endl;
    std::cout << "     | (|:.     |) |" << std::endl;
    std::cout << "      '-|:.     |-' " << std::endl;
    std::cout << "        \\::.    /  " << std::endl;
    std::cout << "         '::. .'   " << std::endl;
    std::cout << "           ) (     " << std::endl;
    std::cout << "         _.' '._   " << std::endl;
    std::cout << "        `-------`  " << std::endl;

    std::cout << "\n==========================================";
    std::cout << "\n          FINALUL JOCULUI";
    std::cout << "\n==========================================";
    if (winners.size() > 1) {
        std::cout << "\n  AVEM EGALITATE! CASTIGATORII SUNT:";
        for (Player* w : winners) {
            std::cout << "\n  - " << w->getName();
        }
    } else {
        std::cout << "\n  FELICITARI, " << winners[0]->getName() << "!";
        std::cout << "\n  Ai castigat cu: " << maxBalance << "$ in cont!";
        std::cout << "\n==========================================";
    }
}

void Game::payToEscapeJail() {
    Player* p=players[currentPlayerIndex];
    if (p->getInJail()) {
        std::cout << p->getName() << ", vrei sa platesti 50 RON? (1-DA, 2-NU): ";
        int optiune;
        std::cin >> optiune;

        if (optiune == 1) {
            bool plataReusita = p->payBail();

            if (plataReusita) {
                std::cout << "Poti sa dai cu zarul acum!";
            } else {
                std::cout << "Ramai in inchisoare tura asta." << std::endl;
                p->noRoundsInJail();
                return;
            }
        } else {
            p->noRoundsInJail();
            return;
        }
    }
}

//serializare
void Game::saveGame(const std::string& filename) const {
    std::ofstream fout(filename);

    if (!fout.is_open()) {
        throw std::runtime_error("Eroare critica: Nu s-a putut crea fisierul de salvare!");
    }

    fout << players.size() << "\n";

    for (const auto& p : players) {
        fout << p->getName() << " "
             << p->getMoneyBalance() << " "
             << p->getCurrentPosition() << "\n";
    }

    for (const auto& s : board) {
        Property* prop = dynamic_cast<Property*>(s);

        if (prop) {
            fout << prop->getId() << " " << prop->getIdProprietar() << "\n";
        }
    }

    fout.close();

}

