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
    DESERT// pt desert
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

    TipConstructie getTip() const;
    Player* getProprietar() const;

    friend ostream& operator<<(ostream& os, const Construction& obj);
    friend istream& operator>>(istream& is, Construction& obj);


    //     void afisareConstructie() {
    //         cout << "Constructie Id: " << id << " | Tip: ";
    //         if(tip == SAT) cout << "SAT";
    //         else if(tip == ORAS) cout << "ORAS";
    //         else if(tip == DRUM) cout << "DRUM";
    //         else cout << "NONE";
    //     }
    // };
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

TipConstructie Construction::getTip() const {
    return this-> tip;
}
Player* Construction::getProprietar() const {
    return this-> proprietar;
}

ostream& operator<<(ostream& os, const Construction& obj) {
    const char* numeTip[]={"NONE", "SAT", "ORAS", "DRUM"};
    os << " | Tip: " << numeTip[obj.tip];
    if (obj.proprietar != nullptr) {
        os << " | Proprietar: " << obj.proprietar->getName();
    } else {
        os << " | Fara proprietar";
    }
    return os;
}istream& operator>>(istream& is, Construction& obj) {
    int optiune;
    cout<<"Tip constructie (0.NONE, 1:SAT, 2:ORAS, 3:DRUM): ";
    is>>optiune;
    if (optiune>=0 && optiune<=3) {
        obj.tip=TipConstructie(optiune);
    }
    else {
        obj.tip=NONE;
    }
    return is;
}

class Map {
    static int noMaps; // cate harti avem (trebuie la fnalul jocului sa fie 0 ca sa nu avem meory leaks)
    const int id;
    static int noAll;
    int linii;
    int coloane;
    TipResursa** grid; //matricea care va fi formata din resurse
    int** jetoane; // nr pe care le pui peste resurse
    Construction** cladiri;
public:
    //constructori si destructor
    Map();
    Map(int linii, int coloane);
    Map(const Map &obj);
    Map& operator=(const Map &obj);
    ~Map();

    void alocaConstructii() {
        cladiri=new Construction *[linii];
        for (int i=0;i<linii;i++) {
            cladiri[i]=new Construction[coloane];
        }
    }
    void amplaseaza (int linii, int coloane, TipConstructie tip, Player* proprietar) {
        cladiri[linii][coloane]=Construction(tip, proprietar);
    }

    friend ostream& operator<<(ostream &os, const Map &obj);
    friend istream& operator>>(istream &is, Map &obj);
};
int Map::noMaps=0;
int Map::noAll=0;
Map:: Map (): id(noAll++) {
    noMaps++;
    linii= 0;
    coloane= 0;
    grid= nullptr;
    jetoane= nullptr;
    cladiri= nullptr;
}
Map :: Map(int linii, int coloane): id(noAll++){
    noMaps++;
    this->linii=linii;
    this->coloane=coloane;
    this->grid=nullptr;
    this->jetoane=nullptr;
    this->cladiri=nullptr;
    }

Map:: Map (const Map &obj):id(noAll++) {
    noMaps++;
    linii=obj.linii;
    coloane=obj.coloane;
    if (obj.grid != nullptr && linii>0 && coloane>0) {
        grid= new TipResursa*[linii];
        jetoane= new int*[linii];
        cladiri=new     Construction *[linii];
        for (int i=0; i<linii; i++) {
            grid[i]= new TipResursa[coloane];
            jetoane[i]= new int[coloane];
            cladiri[i]= new Construction[coloane];
            for (int j=0; j<coloane; j++) {
                grid[i][j]= obj.grid[i][j];
                jetoane[i][j]= obj.jetoane[i][j];
                cladiri[i][j]= obj.cladiri[i][j];
            }
        }
    }
    else {
        grid=nullptr;
        jetoane=nullptr;
        cladiri=nullptr;
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
            delete [] cladiri[i];
        }
        delete [] grid;
        delete [] jetoane;
        delete [] cladiri;
    }
    this->linii= obj.linii;
    this->coloane= obj.coloane;
    if (obj.grid != nullptr && linii>0 && coloane>0) {
        grid= new TipResursa*[linii];
        jetoane= new int*[linii];
        cladiri=new Construction *[linii];
        for (int i=0; i<linii; i++) {
            grid[i]= new TipResursa[coloane];
            jetoane[i]= new int[coloane];
            cladiri[i]= new Construction[coloane];
            for (int j=0; j<coloane; j++) {
                grid[i][j]= obj.grid[i][j];
                jetoane[i][j]= obj.jetoane[i][j];
                cladiri[i][j]= obj.cladiri[i][j];
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
            delete [] cladiri[i];
        }
    }
    delete [] grid;
    delete [] jetoane;
    delete [] cladiri;
    Map::noMaps--;
}

//operatorul<<
ostream& operator<<(ostream &os, const Map &obj) {
    os << "\n========= TABLA DE JOC CATAN =========" << endl;
    if (obj.grid==nullptr) {
        os<<"Harta nu a fost inca generata"<<endl;
        os << "      ======================================" << endl;
        return os;
    }
    //resursele
    const char* numeResurse[] ={"LEMN","CARAMIDA","OAIE","FAN","PIATRA","DESERT"};
    for (int i=0; i<obj.linii; i++) {
        os<<" ";
        for (int j=0; j<obj.coloane; j++) {
            int res=int(obj.grid[i][j]);
            if (res>=0 && res<=5) {
                os<<"["<<numeResurse[res]<<"]";
            }
            else {
                os<<"[???]";
            }
            TipConstructie t=obj.cladiri[i][j].getTip();
            if (t == SAT) os << ". ";
            else if (t == ORAS) os << "..";
            else if (t == DRUM) os << "==";
            else os << "  ";

            os<<" ";
        }
        os<<endl;
        //jetoanele cu numere
        for (int j=0; j<obj.coloane; j++) { //se alineaza nr sub cuvintele de deasupra
            os << "(" ;
            os.width(2);
            os<<right<<obj.jetoane[i][j]<<")";

        }
        os << "\n" << endl;
    }
    return os;
}
//operatorul>>
istream& operator>>(istream &is, Map &obj) {
    if (obj.linii<=0 || obj.coloane<=0) {
        cout<<"Errore! Dimensiunile nu sunt setate corect!"<<endl;
        return is;
    }
    if (obj.grid!=nullptr) {
        for (int i=0; i<obj.linii; i++) {
            delete[] obj.grid[i];
            delete[] obj.jetoane[i];
        }
        delete[] obj.grid;
        delete[] obj.jetoane;
    }
    obj.grid=new TipResursa*[obj.linii];
    obj.jetoane=new int*[obj.linii];
    for (int i=0; i<obj.linii; i++) {
        obj.grid[i]= new TipResursa[obj.coloane];
        obj.jetoane[i]= new int[obj.coloane];
    }
    for (int i=0; i<obj.linii; i++) {
        for (int j=0; j<obj.coloane; j++) {
            obj.grid[i][j]= (TipResursa)(rand()%6); //genereaza de la 0 la 5
            obj.jetoane[i][j]= (rand()%11)+2; //genereaza de la 2 la 12
        }
    }
    return is;
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

    friend ostream& operator<<(ostream &os, const Game &obj);
    friend istream& operator>>(istream &is, Game &obj);

    //getters
    int getId() const;
    int getNoParticipants() const;
    int getRundaCurenta() const;
    double getDurataTura() const;
    Player** getParticipants() const;
    Map* getGameMap() const;

    //setters
    void setDurataTura(double durataTura);
    void setRundaCurenta(int rundaCurenta);
    void setGameMap(Map* gameMap);
    void setParticipants(int noParticipants, Player** Participants);

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
        // if (sumaTotala == 7) {
        cout << "[EVENIMENT] S-a dat 7! Hotul se muta." << endl;
        // for (int i = 0; i < noParticipants; i++) {
        //     if (Participants[i] != nullptr && Participants[i]->getNoCards() > 7) {
        //         cout << "  ! Jucatorul " << Participants[i]->getName()
        //              << " trebuie sa piarda jumatate din carti." << endl;
        //     }
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
//getters
int Game::getNoParticipants() const {
    return this->noParticipants;
}
double Game::getDurataTura() const {
    return this->durataTura;
}
int Game::getId() const {
    return this->id;
}
int Game::getRundaCurenta() const {
    return this->rundaCurenta;
}

Player** Game::getParticipants() const {
    return this->Participants;
}
Map* Game::getGameMap() const {
    return this->gameMap;
}

//setters
void Game::setDurataTura(double durataTura) {
    this->durataTura = durataTura;
}

void Game::setRundaCurenta(int rundaCurenta) {
    this->rundaCurenta = rundaCurenta;
}

void Game::setGameMap(Map *gameMap) {
    if (gameMap!=nullptr) {
        delete this->gameMap;
    }
    this->gameMap = new Map(*gameMap);
}

void Game::setParticipants(int noParticipants, Player **Participants) {
    if (Participants!=nullptr) {
        delete [] this->Participants;
    }
    this->noParticipants = noParticipants;
    if (this->Participants!=nullptr && noParticipants>0) {
        this->Participants = new Player*[noParticipants];
        for (int i=0; i<this->noParticipants; i++) {
            this->Participants[i]=Participants[i];
        }
    }
    else {
        this->Participants=nullptr;
    }
}

//operatorul<<
ostream & operator<<(ostream &os, const Game &obj) {
    os << "RUNDA: " << obj.rundaCurenta << endl;
    os << "TIMP TURA: " << obj.durataTura << "s" << endl;
}

//operatorul>>
istream & operator>>(istream &is, Game &obj) {
    cout << "--- SETARI GENERALE JOC ---" << endl;
    cout << "Setati durata universala a unei ture (secunde): ";
    is >> obj.durataTura;

    return is;
}


// VAD CE POT SA CONSTRUIESC (oras, sate, drum)
bool Player:: cePoateConstrui(TipConstructie tip) {
    //DRUM lemn+caramida
    //SAT lemn+oaie+fan+caramida
    //ORAS 3 pietre+ 2 fan
    if (tip == SAT) {
        int l = 0, c = 0, o = 0, f = 0;
        for(int i = 0; i < noCards; i++) {
            if(resurse[i] == LEMN) l++;
            if(resurse[i] == CARAMIDA) c++;
            if(resurse[i] == OAIE) o++;
            if(resurse[i] == FAN) f++;
        }
        if (l >= 1 && c >= 1 && o >= 1 && f >= 1) {
            return true;
        }
        else return false;
    }
    if (tip==ORAS) {
        int p=0, f = 0;
        for(int i = 0; i < noCards; i++) {
            if(resurse[i] == PIATRA) p++;
            if(resurse[i] == FAN) f++;
        }
        if (p >= 1 && f >= 1) {
            return true;
        }
        else return false;
    }
    if (tip== DRUM) {
        int l=0, c = 0;
        for(int i = 0; i < noCards; i++) {
            if(resurse[i] == LEMN) l++;
            if(resurse[i] == CARAMIDA) c++;
        }
        if (l>=1 && c>=1) {
            return true;
        }
        else return false;
    }
    return false;
}

//SE STERG RESURSELE CU CARE VREAU SA CONSTRUIESC (DACA POT)
void Player:: consumaResurse (TipConstructie tip) {
    int deStersL = 0, deStersC = 0, deStersO = 0, deStersF = 0, deStersP = 0;
    if (tip == SAT) {
        deStersL = 1; deStersC = 1; deStersO = 1; deStersF = 1;
    }
    else if (tip == ORAS) {
        deStersP = 3; deStersF = 2;
    }
    else if (tip == DRUM) {
        deStersL = 1; deStersC = 1;
    }
    int nrResurseNoi= noCards -(deStersL + deStersC + deStersO + deStersF + deStersP);
    TipResursa* resurseNoi = new TipResursa[nrResurseNoi];
    int k=0;
    for (int i=0; i<noCards; i++) {
        if (resurse[i] == LEMN && deStersL > 0) {
            deStersL--; continue;
        }
        if (resurse[i] == CARAMIDA && deStersC > 0) {
            deStersC--; continue;
        }
        if (resurse[i] == OAIE && deStersO > 0) {
            deStersO--; continue;
        }
        if (resurse[i] == FAN && deStersF > 0) {
            deStersF--; continue;
        }
        if (resurse[i] == PIATRA && deStersP > 0) {
            deStersP--; continue;
        }
        resurseNoi[k++] = resurse[i];
    }
    delete[]resurse;
    resurse=resurseNoi;
    noCards = nrResurseNoi;
}

//CONSTRUIESC EFECTIV
void Game::construieste (int idJucator, TipConstructie tip, int x, int y) {
    Player* om= Participants[idJucator];

    bool arePiese= false;
    if (tip==SAT) {
        arePiese=om->poateConstruiSat();
    }
    else if (tip==ORAS) {
        arePiese=om->poateConstruiOras();
    }
    else if (tip==DRUM) {
        arePiese=om->poateConstruiDrum();
    }
    if (!arePiese) {
        cout<<om->getName()<<"nu mai are piese disponibile pentru acest tip"<<endl;
        return;
    }
    if (!om->cePoateConstrui(tip)) {
        cout<<om->getName()<<"nu mai are resurse disponibile pentru a construi acest tip"<<endl;
        return;
    }
    om->consumaResurse(tip);
    gameMap->amplaseaza(x,y,tip,om);
    if (tip == SAT) {
        om->aConstruiSat();
        om->setPoints(om->getPoints() + 1);
        cout <<om->getName() << " a plasat un SAT la" <<x<<","<<y<<" Scorul lui este: " << om->getPoints() << endl;
    }
    else if (tip == ORAS) {
        om->aConstruiOras();
        om->setPoints(om->getPoints() + 1); // Orasul valoreaza mai mult
        cout <<om->getName() << " a plasat un ORAS la" <<x<<","<<y<<" Scorul lui este: " << om->getPoints() << endl;
    }
    else if (tip == DRUM) {
        om->aConstruiDrum();
        cout <<om->getName() << " a plasat un DRUM la" <<x<<","<<y<< endl;
    }
}
int main() {
    // 0. Pregatim generatorul de numere aleatorii
    srand(time(0));

    cout << "========== TESTARE SISTEM COMPLET CATAN ==========" << endl;

    // 1. TESTARE CLASA PLAYER
    // Cream doi jucatori si le setam niste date initiale
    Player* p1 = new Player((char*)"Irina", 2, 0); // 2 puncte
    Player* p2 = new Player((char*)"Matei", 1, 0); // 1 punct

    cout << "1. Jucatori creati:\n" << *p1 << *p2 << endl;

    // 2. TESTARE CLASA CONSTRUCTION
    // Cream o asezare (SAT) pentru Irina
    Construction c1(SAT, p1);
    cout << "2. Test Constructie: " << c1 << endl;

    // 3. TESTARE CLASA GAME & CONFIGURARE
    // 2 participanti, harta 3x3, durata tura 45 secunde
    Game joc(2, 3, 3, 45.0);

    // Incarcam jucatorii in vectorul de participanti din Game
    Player* lista[] = { p1, p2 };
    joc.setParticipants(2, lista);

    // 4. TESTARE CLASA MAP
    // Generam harta folosind operatorul >> (care pune resurse si jetoane random)
    if (joc.getGameMap() != nullptr) {
        // Simulam cin >> harta (fara sa mai introducem de la tastatura, folosind logica de rand())
        cin >> *(joc.getGameMap());
    }

    cout << "3. Harta a fost generata:" << endl;
    cout << *(joc.getGameMap());

    // 5. TESTARE LOGICA DE JOC (RUNDA)
    // Afisam starea curenta (Operatorul << minimalist)
    cout << "4. Stare joc inainte de runda: " << joc << endl;

    // Simulam primele 2 runde
    joc.rundaNoua();
    joc.rundaNoua();

    // 6. AFISARE FINALA (Verificam daca runda a crescut)
    cout << "\n5. Stare joc dupa runde: " << joc << endl;

    // 7. CURATENIE (Destructori)
    // Obiectele Player au fost facute cu new, deci trebuie sterse
    delete p1;
    delete p2;

    cout << "\n================ TEST INCHEIAT ================" << endl;

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

////!!!!!!!!!!de alineat clasa map