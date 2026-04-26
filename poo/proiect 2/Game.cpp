//
// Created by Irina Manea on 25.04.2026.
//

#include "Game.h"
#include <iostream>
#include<cstdlib>
#include <ctime>

#include "Space.h"

//desen
std::string Game::getPlayerAtPos(int pos) const {
    std::string s = "";
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getCurrentPosition() == pos) {
            s += "P" + std::to_string(players[i].getId());
        }
    }
    while (s.length() < 5) s += " "; //aliniere la 5 caract
    return s;
}
std::string Game::getNameFixed(int pos) const {
    if (pos >= board.size()) return "     ";
    std::string name = board[pos]->getName();
    if (name.length() > 5) name = name.substr(0, 5);
    while (name.length() < 5) name += " ";
    return name;
}

Game:: Game(): currentPlayerIndex(0), gameOver(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}
Game:: Game(int nrJucatori):currentPlayerIndex(0), gameOver(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < nrJucatori; i++) {
        players.push_back(Player("Jucator"+ std::string (i+1),1500));
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

//se creeaza casutele standard
void Game::initGame() {
    for (Space* s: board) {
        delete s;
    }
    board.clear();
    board.push_back(new Events(0, "START", "Salariu", 200));
    board.push_back(new Property(1, "Vitan", 100, 50));
    board.push_back(new Property(2, "Cotroceni", 120, 60));
    board.push_back(new Specials(3, "Gara", 500, 100, 2, "Transport"));
    board.push_back(new Utilities(4, "Apa", 150, 70));
    board.push_back(new Property(5, "Gaz", 150, 70));
    board.push_back(new Events(6, "Vizita", "Inchisoare", 0));
    board.push_back(new Property(7, "Magheru", 300, 150));
    board.push_back(new Property(8, "Unirii", 350, 180));
    board.push_back(new Specials(9, "Port", 500, 100, 2, "Transport"));
    board.push_back(new Property(10, "PBT", 400, 200));
    board.push_back(new Events(11, "Chest", "Noroc", 50));
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
    os << "\n>>> RANDUL LUI: " << obj.players[obj.currentPlayerIndex].getName() << " <<<\n";
    return os;
}

std::istream& operator>>(std::istream& is, Game& obj) {
    int nr;
    std::cout << "Numar jucatori (2-4): "; // sa fac si cu try catch
    is >> nr;
    obj.players.clear();
    for(int i = 0; i < nr; ++i) {
        std::string n;
        std::cout << "Nume Jucator " << i+1 << ": ";
        is >> n;
        obj.players.push_back(Player(n, 1500));
    }
    return is;
}

void Game:: playTurn() {
    Player& p=players[currentPlayerIndex];
    int pasi=displayDice();
    int old= p.getCurrentPosition();
    int now= (old+pasi)%BOARD_SIZE;

    if (now<old) {
        p.setMoneyBalance(p.getMoneyBalance()+200);
    }
    p.setCurrentPosition(now);

    board[now]->updatePosition(p, pasi);
    currentPlayerIndex=(currentPlayerIndex+1)%players.size();
}

void Game:: startGame() {
    std::cin>> *this;
    this-> initGame();
    int nrTure;
    std::cout << "\nCate ture doriti sa aiba jocul? "; //try catch cu nr de ture invalid
    std::cin>>nrTure;

    for (int tura=1; tura<=nrTure; tura++) {
        std::cout << "\n==========================================";
        std::cout << "\n          INCEPE TURA " << tura << " DIN " << nrTure;
        std::cout << "\n==========================================\n";

        int n= getNrPlayers();
        for (int i=0; i<n; i++) {
            std::cout<< *this;
            this-> playTurn;

            std::cout << "Apasa Enter pentru a trece la urmatorul jucator!";
            std::cin.ignore(1000, '\n');
            std::cin.get();
        }
    }
    this->announceWinner();
}

void Game::announceWinner() {
    if (players.empty()) return; //try catch

    int winnerIdx =0;
    for (size_t i=0; i<players.size(); i++) {
        if  (players[i].getMoneyBalance()> player[winnerIdx].getMoneyBalance()) {
            winnerIdx = i;
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

    // 3. Mesajul de felicitare
    std::cout << "\n==========================================";
    std::cout << "\n          FINALUL JOCULUI";
    std::cout << "\n==========================================";
    std::cout << "\n  FELICITARI, " << players[winnerIndex].getName() << "!";
    std::cout << "\n  Ai castigat cu: " << players[winnerIndex].getMoneyBalance() << "$ in cont!";
    std::cout << "\n==========================================";

}

