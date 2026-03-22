//
// Created by Irina Manea on 20.03.2026.
////
// Created by Irina Manea on 20.03.2026.
//

#include <iostream>
#include <string.h>
#include <ctime>
#include<cstdlib>

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
    bool esteActiv;
public:

    //cpnstructori &destructor
    Player (); // constructor default
    Player (char* name, int points, int noCards); // c cu atribute // no cards??????????
    Player (const Player &obj); // copy constructor
    Player& operator=(const Player &obj); //operatorul egal
    ~Player(); //destructor

    //getters
    int getId() const;
    const char* getName() const;
    int getPoints() const;
    int getNoCards() const;
    const TipResursa* getResurse() const;
    int getSateTotal() const;
    int getOraseTotal() const;
    int getDrumuriTotal() const;

    //setters
    void setName(char* name);
    void setPoints(int points);
    void setNoCards(int noCards);
    void setSateTotal(int sateTotal);
    void setOraseTotal(int oraseTotal);
    void setDrumuriTotal(int drumuriTotal);
    void setResurse(int noCards, TipResursa* resurse);
    void setEsteActiv(bool esteActiv);


    friend ostream& operator<<(ostream& os, const Player& obj);
    friend istream& operator>>(istream& is, Player& obj);

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

//getters
int Player:: getId() const {
    return id;
}
const char* Player:: getName() const {
    return name;
}
int Player:: getPoints() const {
    return points;
}
int Player:: getNoCards() const {
    return noCards;
}

const TipResursa *Player::getResurse() const {
    return resurse;
}

int Player::getSateTotal() const {
    return sateTotal;
}

int Player::getOraseTotal() const {
    return oraseTotal;
}
int Player::getDrumuriTotal() const {
    return drumuriTotal;
}

//setters
void Player:: setName (char* name) {
    delete[] this->name;
    this->name= new char[strlen(name)+1];
    strcpy(this->name, name);
}
void Player:: setPoints (int points) {
    this->points = points;
}
void Player:: setNoCards (int noCards) {
    this->noCards = noCards;
}
void Player:: setSateTotal (int sateTotal) {
    this->sateTotal = sateTotal;
}
void Player:: setOraseTotal (int oraseTotal) {
    this->oraseTotal = oraseTotal;
}
void Player:: setDrumuriTotal (int drumuriTotal) {
    this->drumuriTotal = drumuriTotal;
}
void Player:: setResurse (int noCards, TipResursa *resurse) {
    delete[] this->resurse;
    this->noCards = noCards;
    if (resurse!=nullptr && noCards>0) {
        this->resurse= new TipResursa[noCards];
        for (int i=0; i<noCards; i++) {
            this->resurse[i]= resurse[i];
        }
    }
    else {
        this->resurse=nullptr;
    }
}

void Player::setEsteActiv(bool esteActiv) {
    this->esteActiv = esteActiv;
}

//operator<<
ostream& operator<<(ostream& os, const Player& obj) {
    os<<"========================================" << endl;
    os<<"STATISTICI JUCATOR (ID: " << obj.id << ")" << endl;
    os<<"========================================" << endl;
    os<<"NUME: "<< obj.name<<endl;
    os<<"PUNCTE: "<< obj.points<<endl;
    os<<"CARTI AVUTE: "<< obj.noCards<<endl;
    os << "----------------------------------------" << endl;
    os<<"CONSTRUCTII"<<endl;
    os<<"   Sate ramase: "<<obj.sateTotal<<endl;
    os<<"   Orase ramase "<<obj.oraseTotal<<endl;
    os<<"   Drumuri ramase"<<obj.drumuriTotal<<endl;
    os<<"---------------------------------------" << endl;
    if (obj.resurse!=nullptr && obj.noCards>0) {
        os<<"RESURSE: ";
        for (int i=0; i<obj.noCards; i++) {
            os<<obj.resurse[i]<<" ";
        }
        os<<endl;
    }
    return os;
}

//operator>>
istream& operator>>(istream& is, Player& obj) {
    char buffer[256];
    cout<<"Nume: ";
    is>>buffer;
    obj.setName(buffer);

    int p;
    cout<<"Puncte: ";
    is>>p;
    obj.setPoints(p);

    bool  activ;
    cout<<"1 (Da, este activ), 0(Nu, nu este activ) ";
    is>>activ;
    obj.setEsteActiv(activ);

    int sate, orase, drumuri;
    cout<<"Sate ramase: ";
    is>>sate;
    obj.setSateTotal(sate);
    cout<<"Orase ramase: ";
    is>>orase;
    obj.setOraseTotal(orase);
    cout<<"Drumuri ramase: ";
    is>>drumuri;
    obj.setDrumuriTotal(drumuri);
    cout<<"Care este numarul de carti de resurse avute?";
    int n;
    is>>n;
    obj.setResurse(n, nullptr);
    if (n>0) {
        cout<<"Introduceti tipul resurselor (0-4):"<<endl;
        for (int i=0; i<n; i++) {
            int valoareCitita;
            cout<<"Resursa"<<i+1<<": ";
            is>>valoareCitita;
            obj.resurse[i]=(TipResursa)valoareCitita;
        }

    }
    return is;
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
Map :: Map(int linii, int coloane): id(noAll++){
    noMaps++;
    linii=4;
    coloane=5;
    grid=new TipResursa*[linii];
    jetoane=new int*[linii];
    for (int i=0; i<linii; i++) {
        grid[i]= new TipResursa[coloane];
        jetoane[i]= new int[coloane];
    }
}
Map:: Map (const Map &obj):id(noAll++) {
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
        for (int i=0; i<linii; i++) {
            delete [] grid[i];
            delete [] jetoane[i];
        }
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
    return *this;


}
Map:: ~Map() {
    if (grid!=nullptr) {
        for (int i=0; i<linii; i++) {
            delete [] grid[i];
            delete [] jetoane[i];
        }
    }
    delete [] grid;
    delete [] jetoane;
    Map::noMaps--;
}

class Game {
    static int noGame;
    const int id;
    int noParticipants; // apartin jocului actual vs noplayers playerii creati in total
    Player** Participants;
    int rundaCurenta;
    double durataTura;//timpul alocat fiecarui jucator (secunde)
    Map* gameMap;
    //ceva cu float
public:
    Game();
    Game(int noParticipants, int liniiHarta, int coloaneHarta, double durataTura);
    Game(const Game &obj);
    Game & operator=(const Game &obj);
    ~Game();
    string poateIncepeJocul() {
        if (noParticipants<2) {
            return "Nu sunt suficienti jucatori, trebuie sa fie minim 2.";
        }
        return "Jocul poate incepe!";
    }
    int displayDice()
{
        // Generăm numărul (asigură-te că generator și distribution sunt definite)
        int dieRoll = rand()%6 +1;

        if (dieRoll == 1) {
            cout << " ------- " << endl;
            cout << "|       |" << endl;
            cout << "|   o   |" << endl;
            cout << "|       |" << endl;
            cout << " ------- " << endl;
        }
        else if (dieRoll == 2) {
            cout << " ------- " << endl;
            cout << "| o     |" << endl;
            cout << "|       |" << endl;
            cout << "|     o |" << endl;
            cout << " ------- " << endl;
        }
        else if (dieRoll == 3) {
            cout << " ------- " << endl;
            cout << "|     o |" << endl;
            cout << "|   o   |" << endl;
            cout << "| o     |" << endl;
            cout << " ------- " << endl;
        }
        else if (dieRoll == 4) {
            cout << " ------- " << endl;
            cout << "| o   o |" << endl;
            cout << "|       |" << endl;
            cout << "| o   o |" << endl;
            cout << " ------- " << endl;
        }
        else if (dieRoll == 5) {
            cout << " ------- " << endl;
            cout << "| o   o |" << endl;
            cout << "|   o   |" << endl;
            cout << "| o   o |" << endl;
            cout << " ------- " << endl;
        }
        else {
            cout << " ------- " << endl;
            cout << "| o   o |" << endl;
            cout << "| o   o |" << endl;
            cout << "| o   o |" << endl;
            cout << " ------- " << endl;
        }

        return dieRoll;
}
    void rundaNoua() {
        cout << "\n>>> INCEPE RUNDA " << this->rundaCurenta << " <<<" << endl;
        cout << "Jucatorul arunca zarurile..." << endl;
        int z1 =displayDice();
        int z2= displayDice();
        int sumaTotala = z1+z2;
        cout << "Suma totala a zarurilor este: "<<sumaTotala << endl;
        // if (sumaTotala==7) {
        //     cout<<"S-a dat 7, fiecare jucator pierde jumatate de carti"<<endl;
        // }
        cout << "Se impart resurse pentru numarul " << sumaTotala << "." << endl;
        this->rundaCurenta++;
        cout << "------------------------------------------" << endl;
    }

};
int Game::noGame=0;
Game::Game (): id(noGame++) {
    noParticipants=0;
    Participants= nullptr;
    rundaCurenta=0;
    durataTura=0.0;
    gameMap= nullptr;
}
Game:: Game(int noParticipants, int liniiHarta, int coloaneHarta, double durataTura): id(noGame++) {
    this->noParticipants=noParticipants;
    this->durataTura=durataTura;
    this-> rundaCurenta=1;
    this-> gameMap= new Map(liniiHarta,coloaneHarta);
    if (this->noParticipants>=2) {
        this->Participants=new Player*[this->noParticipants];
        for (int i=0; i<this->noParticipants; i++) {
            this->Participants[i]= nullptr;
        }
    }
    else {
        this->Participants=nullptr;
    }
}

Game::Game(const Game &obj) :id(noGame++) {
    this->noParticipants=obj.noParticipants;
    this->rundaCurenta=obj.rundaCurenta;
    this->durataTura=obj.durataTura;
    if (obj.gameMap !=nullptr) {
        this->gameMap=new Map(*obj.gameMap);//copeim obiect de tip map deci se apeleaza copy constrcutorul de la map
    }
    else {
        this->gameMap=nullptr;
    }
    if (obj.Participants!=nullptr) {
        this->Participants=new Player*[this->noParticipants];
        for (int i=0; i<this->noParticipants; i++) {
            this->Participants[i]=obj.Participants[i];
        }
    }
    else {
        this->Participants=nullptr;
    }
}
Game & Game::operator=(const Game &obj) {
    if (this == &obj) {
        return *this;
    }
    if (this->gameMap!=nullptr) {
        delete [] this->gameMap;
    }
    if (obj.Participants!=nullptr) {
        delete [] this->Participants;
    }
    this->noParticipants=obj.noParticipants;
    this->rundaCurenta=obj.rundaCurenta;
    this->durataTura=obj.durataTura;
    if (obj.gameMap !=nullptr) {
        this->gameMap=new Map(*obj.gameMap);//copeim obiect de tip map deci se apeleaza copy constrcutorul de la map
    }
    else {
        this->gameMap=nullptr;
    }
    if (obj.Participants!=nullptr) {
        this->Participants=new Player*[this->noParticipants];
        for (int i=0; i<this->noParticipants; i++) {
            this->Participants[i]=obj.Participants[i];
        }
    }
    else {
        this->Participants=nullptr;
    }
    return *this;
}

Game::~Game() {
    if (this->gameMap!=nullptr) {
        delete this->gameMap;
    }
    if (this->Participants!=nullptr) {
        delete [] this->Participants;
    }
    Game::noGame--;
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