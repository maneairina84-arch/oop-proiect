//
// Created by Irina Manea on 20.03.2026.
////
// Created by Irina Manea on 20.03.2026.
//

#include <iostream>
#include "string.h"

using namespace std;

enum TipResursa {
    LEMN,
    CARAMIDA,
    OAIE,
    FAN,
    PIATRA,
    NIMIC // pt desert
};

class Player {
    static int noPlayers;
    char* name;
    const int id;
    int points;
    int noCards;
    TipResursa* resurse;
    int sateTotal=5;
    int oraseTotal=4;
    int drumuriTotal=15;
public:
    Player (); // constructor default
    Player (char* name, int points, int noCards); // c cu atribute // no cards??????????
    Player (const Player &obj); // copy constructor
    Player& operator=(const Player &obj); //operatorul egal
    ~Player(); //destructor
    bool poateConstruiSat() {
        return sateTotal>0;
    }
    void aConstruiSat() {
        if (sateTotal>0) {
            sateTotal--;
        }
    }

    bool poateConstruiOras() {
        return oraseTotal>0;
    }
    void aConstruiOras() {
        if (oraseTotal>0) {
            oraseTotal--;
        }
    }
    bool poateConstruiDrum() {
        return drumuriTotal>0;
    }
    void aConstruiDrum() {
        if (drumuriTotal>0) {
            drumuriTotal--;
        }
    }
    void afisarePlayer() {
        cout<<"Jucator: "<<name<<"| Id: "<<id<<"| Sate ramase "<<sateTotal<< "| Orase ramase "<< oraseTotal<< "| Drumuri ramase "<<drumuriTotal<<endl;
    }
};
int Player:: noPlayers=0;
Player::Player(): id(noPlayers++) {
    name= new char[4];
    strcpy(name,"N/A");
    points=0;
    noCards=0;
    resurse= nullptr;
}
Player:: Player (char* name, int points, int noCards): id(noPlayers++) {
    this-> name= new char[strlen(name)+1];
    strcpy(this-> name, name);
    this->points= points;
    this->noCards= noCards;
    resurse= nullptr;
}
Player:: Player(const Player &obj): id(noPlayers++) {
    this-> name = new char[strlen(obj.name)+1];
    strcpy(this-> name, obj.name);
    this->points= obj.points;
    this->noCards= obj.noCards;
    if (noCards > 0 && obj.resurse!=nullptr) {
        this->resurse= new TipResursa[obj.noCards];
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
        this->resurse= new TipResursa[obj.noCards];
        for (int i=0; i<obj.noCards; i++) {
            this->resurse[i]= obj.resurse[i];
        }
    } else {
        this->resurse = nullptr;
    }
    return *this;
}
Player:: ~Player() {
    if (this->name !=nullptr) {
        delete this->name;
    }
    if (this->resurse !=nullptr) {
        delete [] this->resurse;
    }
}

enum TipConstructie {
    NONE,
    SAT,
    ORAS,
    DRUM
};
class Construction {
    TipConstructie tip;
    static int noTotal;
    const int id;
    Player* proprietar;
public:
    Construction();
    Construction(TipConstructie tip, Player* proprietar);
    Construction(const Construction &obj);
    Construction& operator=(const Construction &obj);
    ~Construction();

    void afisareConstructie() {
        cout << "Constructie Id: " << id << " | Tip: ";
        if(tip == SAT) cout << "SAT";
        else if(tip == ORAS) cout << "ORAS";
        else if(tip == DRUM) cout << "DRUM";
        else cout << "NONE";
    }
};

int Construction::noTotal=0;
Construction :: Construction(): id(noTotal++) {
    this-> proprietar= nullptr;
    this->tip=NONE;
}
Construction:: Construction(TipConstructie tip, Player* proprietar): id(noTotal++) {
    this-> proprietar= proprietar;
    this->tip=tip;
}
Construction:: Construction(const Construction &obj): id(noTotal++) {
    this-> proprietar= obj.proprietar;
    this->tip=obj.tip;
}
Construction& Construction::operator=(const Construction &obj) {
    if (this == &obj) {
        return *this;
    }
    this-> proprietar= obj.proprietar;
    this->tip=obj.tip;
    return *this;
}

Construction::~Construction() {

}
class Map {
    static int noMaps; // cate harti avem (trebuie la fnalul jocului sa fie 0 ca sa nu avem meory leaks)
    const int id;
    static int noAll;
    int linii;
    int coloane;
    TipResursa** grid; //matricea care va fi formata din resurse
    int** jetoane; // nr pe care le pui peste resurse
public:
    Map();
    Map(int linii, int coloane);
    Map(const Map &obj);
    Map& operator=(const Map &obj);
    ~Map();
};
int Map::noMaps=0;
int Map::noAll=0;
Map:: Map (): id(noAll++) {
    noMaps++;
    linii= 0;
    coloane= 0;
    grid= nullptr;
    jetoane= nullptr;
}
Map :: Map(): id(noAll++) {
    noMaps++;
    linii=4;
    coloane=5;
    grid=new TipResursa*[linii];
    jetoane=new int*[linii];
    for (int i=0; i<linii; i++) {
        grid[i]= new TipResursa*[i];
        jetoane[i]= new int*[coloane];
    }
}
Map:: Map ():id(noAll++) {
    noMaps++;
    linii=obj.linii;
    coloane=obj.coloane;
    if (obj.grid != nullptr && linii>0 && coloane>0) {
        grid= new TipResursa*[linii];
        jetoane= new int*[linii];
        for (int i=0; i<linii; i++) {
            grid[i]= new TipResursa[coloane];
            jetoane[i]= new int[coloane];
            for (int j=0; j<coloane; j++) {
                grid[i][j]= obj.grid[i][j];
                jetoane[i][j]= obj.jetoane[i][j];
            }
        }
    }
    else {
        grid=nullptr;
        jetoane=nullptr;
    }

}
Map & Map::operator=(const Map &obj) {
    if (this == &obj) {
        return *this;
    }
    if (grid!=nullptr) {
        delete [] grid;
        delete [] jetoane;
    }
    this->linii= obj.linii;
    this->coloane= obj.coloane;
    if (obj.grid != nullptr && linii>0 && coloane>0) {
        grid= new TipResursa*[linii];
        jetoane= new int*[linii];
        for (int i=0; i<linii; i++) {
            grid[i]= new TipResursa[coloane];
            jetoane[i]= new int[coloane];
            for (int j=0; j<coloane; j++) {
                grid[i][j]= obj.grid[i][j];
                jetoane[i][j]= obj.jetoane[i][j];
            }
        }
    }
    else {
        this->grid=nullptr;
        this->jetoane=nullptr;
    }


}
Map:: ~Map() {
    if (this->grid!=nullptr) {
        delete [] this->grid;
    }
    if (this->jetoane!=nullptr) {
        delete [] this->jetoane;
    }
}

int main() {



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