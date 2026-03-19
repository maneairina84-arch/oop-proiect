
#include <iostream>
#include "string.h"

using namespace std;

class Player {
    static int noPlayers;
    char* name;
    const int id;
    int points;
    int noCards;
    int* resurse;
public:
    Player (); // constructor default
    Player (char* name, int points, int noCards); // c cu atribute // no cards??????????
    Player (const Player &obj); // copy constructor
    Player& operator=(const Player &obj); //operatorul egal
    ~Player(); //destructor
};
int Player:: noPlayers=0;
Player::Player(): id(noPlayers++) {
    name= new char[4];
    strcpy(name,"N/A");
    points=0;
    noCards=0;
    resurse= nullptr;
}
Player:: Player (char* name, int points): id(noPlayers++) {
    this-> name= new char[strlen(name)+1];
    strcpy(this-> name, name);
    this->points= points;
    noCards=0;
    resurse= nullptr;
}
Player:: Player(const Player &obj): id(noPlayers++) {
    this-> name = new char[strlen(obj.name)+1];
    strcpy(this-> name, obj.name);
    this->points= obj.points;
    this->noCards= obj.noCards;
    if (noCards > 0 ) {
        this->resurse= new int[obj.noCards];
        for (int i=0; i<noCards; i++) {
            this->resurse[i]= obj.resurse[i];
        }
    } else {
        this->resurse = nullptr;
    }

}
Player& Player::operator=(const Player &obj) {
    if (this == &obj) {
        return *this;

    }
    delete[] name;
    this-> name= new char[strlen(obj.name)+1];
    strcpy(this-> name, obj.name);
    this->points= obj.points;
    this->noCards= obj.noCards;
    delete [] this-> resurse;
    if (obj.noCards > 0 && obj.resurse!=nullptr ) {
        this->resurse= new int[obj.noCards];
        for (int i=0; i<obj.noCards; i++) {
            this->resurse[i]= obj.resurse[i];
        }
    } else {
        this->resurse = nullptr;
    }
    return *this;
}
Player:: ~Player() {
    if (this->name =nullptr) {
        delete this->name;
    }
    if (this->resurse =nullptr) {
        delete [] this->resurse;
    }
}

int main (){
    Player p1("Andrei", 10);
    Player p2;
    p2 = p1;
    cout << "Jucator creat cu succes!";
    return 0;
}



// //Player
// Name, id, colour, timestamp
//
// Constructie (drum, asezare)
//
// Harta (random resurse)
//
// Resurse (enum)
//
// Game (zar, lista cărți jucător)
//
// + clasa meniu in proiect extra ((construcție tor default dra nu trb neaparat și ceilalți constructori)
//overload pe opertaori