#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

//Tema 13
//Se dorește implementarea unei aplicații OOP care să permită gestionarea rezervărilor la sălile de spectacol apartinand proprietarului Y.
//Pentru fiecare sală de spectacol se cunoaște cel puțin tipul spectacolului care se desfășoară (e.g. opera, teatru),
//numele spectacolului, genul acestuia (de ex: comedie, drama, etc.) și prețul biletului. Cunoaștem despre toate spectacolele
//cel puțin faptul că au o durata și un nume, durata fiind variabila.
//Piesele de teatru au un singur act. Unele piese de teatru sunt interactive (presupun participarea publicului).
//Despre spectacolele de operă se cunoaște faptul că au un solist principal. Solistul principal are un nume și poate fi tenor, bariton sau bass.
//Unele opere pot avea mai multe acte (2-7), cu durate diferite, specificate pentru fiecare act în parte.
//Între acte se ia o pauza fixă specifică operei ce se va adăuga la durata totală a piesei, pentru a putea să îi estimăm durata totală.
//Să se construiască clasa template GestionareRezervariSpectacole care sa conțină informații despre diversele tipuri de spectacole
//        și să permită efectuarea unor rezervări pentru acestea. Clasa conține indexul rezervarii
//        (incrementat automat la adaugarea unei noi rezervări), și o structura de obiecte, alocată dinamic care sa gestioneze rezervările care se pot face la un anumit spectacol.
//Structura de date: unordered_map sau unordered_set <id_rezervare, structura care reține datele spectacolului rezervat>
//- Să se adauge toate câmpurile relevante pentru modelarea acestei probleme.
//Cerința suplimentară:
//Dat fiind că la sălile de spectacol au început să fie prezentate și spectacole de stand-up,
//să se construiască o specializare aferentă acestui tip de spectacol ce ne va permite să aflăm veniturile obținute de proprietarul Y
//pe baza biletelor vândute la stand-up.

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------

class Solist{
protected:
    string nume;
    string solistType;
public:
    const string getNume();
    void setNume(const string& nume);

    string getSolistType() const;
    void setSolistType(string type);

    Solist();
    Solist(const Solist& solist);
    Solist(const string &nume,const string &type) : nume(nume),solistType(type) {}
    virtual ~Solist(){};
    Solist& operator=(const Solist& solist);

    bool operator==(const Solist &solist) const;
    bool operator!=(const Solist &solist) const;

    friend istream& operator>>(istream& is, Solist& solist);
    friend ostream& operator<<(ostream&os, Solist& solist);
};
const string Solist::getNume() {
    return nume;
}
void Solist::setNume(const string &nume) {
    this->nume = nume;
}
istream & operator >> (istream & is, Solist & solist) {
    cout << "Introduceti tipul solistului (Tenor/Bass/Bariton):\n";
    getline(is, solist.solistType);
    if (solist.solistType == "Tenor") {
        cout << "Introduceti un Solist Tenor: \n";
        getline(is, solist.nume);
    } else if (solist.solistType == "Bass") {
        cout << "Introduceti un Solist Bass: \n";
        getline(is, solist.nume);
    } else if (solist.solistType == "Bariton") {
        cout << "Introduceti un Solist Bariton: \n";
        getline(is, solist.nume);
    } else {
        while (solist.solistType != "Tenor" && solist.solistType != "Bass" && solist.solistType != "Bariton") {
            cout << "Ati introdus un tip gresit\n";
            cout << "Introduceti tipul solistului(Tenor/Bass/Bariton) - cu prima litera majuscula:\n";
            getline(is, solist.solistType);
        }
        cout << "Introduceti numele solistului:\n";

        getline(is, solist.nume);
    }
    return is;
}
ostream& operator<<(ostream&os, Solist& solist){
    if(solist.solistType == "Tenor"){
        os << "Numele Solistului Tenor: " << solist.nume <<"\n";
    }
    else if (solist.solistType == "Bass"){
        os << "Numele Solistului Bass: " << solist.nume <<"\n";
    }
    else if(solist.solistType == "Bariton"){
        os << "Numele Solistului Bariton: " << solist.nume <<"\n";
    }
    return os;
}

Solist::Solist() {
    nume = "";
    solistType = "";
}
Solist::Solist(const Solist &solist) {
    this->nume = solist.nume;
    this->solistType = solist.solistType;
}
Solist & Solist::operator=(const Solist &solist) {
    this->nume = solist.nume;
    this->solistType = solist.solistType;
    return *this;
}

string Solist::getSolistType() const {
    return solistType;
}

void Solist::setSolistType(string type) {
    solistType = type;
}

bool Solist::operator==(const Solist &solist) const {
    return nume == solist.nume &&
           solistType == solist.solistType;
}

bool Solist::operator!=(const Solist &solist) const {
    return !(solist == *this);
}

//--------------------------------------------------------------------------------------------------------------------------

class Spectacol{

protected:
    int durataTotala;
    string numeSpectacol;
    int nrActe;
    string genSpectacol;
    double pretBilet;
    int nrLocuri;

public:
    const int get_durataTotala();
    const string get_numeSpectacol();
    const int get_nrActe();
    const double get_pretBilet();
    const string get_genSpetacol();
    const int get_nrLocuri();

    void set_durataTotala(int durata);
    void set_numeSpectacol(string nume);
    void set_nrActe(int numar);
    void set_pretBilet(double pret);
    void set_genSpectacol(string gen);
    void set_nrLocuri(int nrLocuri);

    Spectacol();
    Spectacol(const Spectacol& spectacol);
    Spectacol(int durata, const string& denumire, int nrActe, const string& gen, double pret,int nrLocuri);
    virtual ~Spectacol();
    Spectacol& operator=(const Spectacol& spectacol);

    friend istream& operator>>(istream& is, Spectacol& spectacol);
    friend ostream& operator<<(ostream& os, Spectacol& spectacol);
    virtual istream& readSpectacol(istream& is) = 0;
    virtual ostream& printSpectacol(ostream& os) = 0;

    static Spectacol* CreateSpectacol(string SpectacolType);



    bool operator==(const Spectacol &spectacol) const;
    bool operator!=(const Spectacol &spectacol) const;

};

istream& operator>>(istream& is, Spectacol& spectacol){
    return spectacol.readSpectacol(is);
}
ostream& operator<<(ostream& os, Spectacol& spectacol){
    return spectacol.printSpectacol(os);
}

const double Spectacol::get_pretBilet() {
    return pretBilet;
}
const string Spectacol::get_genSpetacol() {
    return genSpectacol;
}
const int Spectacol::get_durataTotala() {
    return durataTotala;
}
const int Spectacol::get_nrActe() {
    return nrActe;
}
const string Spectacol::get_numeSpectacol() {
    return numeSpectacol;
}
void Spectacol::set_genSpectacol(string gen) {
    genSpectacol = gen;
}
void Spectacol::set_pretBilet(double pret) {
    pretBilet = pret;
}
void Spectacol::set_durataTotala(int durata) {
    durataTotala = durata;
}
void Spectacol::set_nrActe(int numar) {
    nrActe = numar;
}
void Spectacol::set_numeSpectacol(string nume) {
    numeSpectacol = nume;
}

Spectacol::Spectacol() {
    durataTotala = 0;
    numeSpectacol = "";
    nrActe = 0;
    genSpectacol = "";
    pretBilet = 0.0;
    nrLocuri = 0;
}
Spectacol::Spectacol(const Spectacol &spectacol) {
    durataTotala = spectacol.durataTotala;
    numeSpectacol = spectacol.numeSpectacol;
    nrActe = spectacol.nrActe;
    genSpectacol = spectacol.genSpectacol;
    pretBilet = spectacol.pretBilet;
    nrLocuri = spectacol.nrLocuri;

}
Spectacol::Spectacol(int durata, const string &denumire, int nrActe,const string& gen, double pret,int locuri) {
    this->durataTotala = durata;
    this->numeSpectacol = denumire;
    this->nrActe = nrActe;
    this->genSpectacol = gen;
    this->pretBilet = pret;
    this->nrLocuri = locuri;
}
Spectacol::~Spectacol() {
    durataTotala = 0;
    numeSpectacol = "";
    nrActe = 0;
    genSpectacol = "";
    pretBilet = 0.0;
    nrLocuri = 0;
}
Spectacol & Spectacol::operator=(const Spectacol &spectacol) {
    this->durataTotala = spectacol.durataTotala;
    this->numeSpectacol = spectacol.numeSpectacol;
    this->nrActe = spectacol.nrActe;
    this->genSpectacol = spectacol.genSpectacol;
    this->pretBilet = spectacol.pretBilet;
    return *this;
}

bool Spectacol::operator==(const Spectacol &spectacol) const {
    return durataTotala == spectacol.durataTotala &&
           numeSpectacol == spectacol.numeSpectacol &&
           nrActe == spectacol.nrActe && pretBilet == spectacol.pretBilet && genSpectacol == spectacol.genSpectacol  && nrLocuri == spectacol.nrLocuri;

}

bool Spectacol::operator!=(const Spectacol &spectacol) const {
    return !(spectacol == *this);
}


//--------------------------------------------------------------------------------------------------------------------------------


class SpectacolTeatru : public Spectacol{

private:
    bool interactiv;

public:

    const bool get_interactiv();
    void set_interactiv(bool ok);

    SpectacolTeatru():Spectacol(),interactiv(false){}
    SpectacolTeatru(const SpectacolTeatru& spectacolTeatru);
    SpectacolTeatru(int durataTotala, const string numeSpectacol,const string gen, double pret, bool interactiv,int locuri):Spectacol(durataTotala,numeSpectacol, 1,gen,pret,locuri),interactiv(interactiv){}
    virtual ~SpectacolTeatru();
    SpectacolTeatru& operator=(const SpectacolTeatru& spectacolTeatru);

    bool operator==(const SpectacolTeatru &spectacol) const;
    bool operator!=(const SpectacolTeatru &rhs) const;

    virtual istream& readSpectacol(istream& is);
    virtual ostream& printSpectacol(ostream& os);

};

istream & SpectacolTeatru::readSpectacol(istream &is) {
    cout << "Introduceti denumirea spectacolului de teatru:\n";
    getline(is,numeSpectacol);
    cout << "Introduceti durata spectacolului de teatru:\n";
    is >> this->durataTotala;
    is.get();
    cout << "Introduceti numarul de locuri disponibile:\n";
    is >> this->nrLocuri;
    is.get();
    cout << "Introduceti genul spectacolului de teatru:\n";
    getline(is,this->genSpectacol);
    cout << "Introduceti pretul biletului:\n";
    is >> this->pretBilet;
    this->nrActe = 1;
    cout << "Introduceti 1 daca spectacolul de teatru este interactiv, 0 altfel:\n";
    is >> this->interactiv;
    is.get();
    return is;
}
ostream & SpectacolTeatru::printSpectacol(ostream &os) {
    os << "Denumirea spectacolului de teatru: " << numeSpectacol << '\n';
    os << "Durata spectacolului de teatru: " << durataTotala<< '\n';
    os << "Numarul de locuri disponibile: " << nrLocuri << '\n';
    os << "Numarul de acte: " << nrActe << '\n';
    os << "Genul spectacolului de teatru: " << genSpectacol <<'\n';
    os << "Pretul biletului: " << pretBilet <<'\n';
    os << "Este spectacolul de teatru interactiv? " << interactiv<<'\n';
    os << '\n';
    return os;
}

const bool SpectacolTeatru::get_interactiv() {
    return interactiv;
}
void SpectacolTeatru::set_interactiv(bool ok) {
    interactiv = ok;
}


SpectacolTeatru::SpectacolTeatru(const SpectacolTeatru &spectacolTeatru): Spectacol(spectacolTeatru) {
    this->interactiv = spectacolTeatru.interactiv;
}
SpectacolTeatru::~SpectacolTeatru(){
    interactiv = "";
}
SpectacolTeatru & SpectacolTeatru::operator=(const SpectacolTeatru &spectacolTeatru) {
    Spectacol::operator=(spectacolTeatru);
    this->interactiv = spectacolTeatru.interactiv;
    return *this;
}

bool SpectacolTeatru::operator==(const SpectacolTeatru &spectacol) const {
    return static_cast<const Spectacol &>(*this) == static_cast<const Spectacol &>(spectacol) &&
           interactiv == spectacol.interactiv;
}

bool SpectacolTeatru::operator!=(const SpectacolTeatru &spectacol) const {
    return !(spectacol == *this);
}


//-------------------------------------------------------------------------------------------------------------------------------------------

class SpectacolOpera : public Spectacol {

private:
    Solist solist;
    vector<int> durataActe;
    int durataPauza;

public:

    SpectacolOpera();
    SpectacolOpera(const SpectacolOpera& spectacolOpera);
    SpectacolOpera(const string& denumire, int nrActe, const string& gen, double pret, int locuri, Solist solist, vector<int>durataActe, int durataPauza);
    virtual ~SpectacolOpera();
    SpectacolOpera& operator=(const SpectacolOpera& spectacolOpera);

    bool operator==(const SpectacolOpera &spectacol) const;

    bool operator!=(const SpectacolOpera &spectacol) const;

    virtual istream& readSpectacol(istream& is);
    virtual ostream& printSpectacol(ostream& os);
};

SpectacolOpera::SpectacolOpera():Spectacol() {
    Solist s;
    solist = s;
    durataPauza = 0;
}
SpectacolOpera::SpectacolOpera(const SpectacolOpera &spectacolOpera):Spectacol(spectacolOpera) {
    this->solist = spectacolOpera.solist;
    this->durataActe = spectacolOpera.durataActe;
    this->durataPauza = spectacolOpera.durataPauza;
}
SpectacolOpera::SpectacolOpera(const string &denumire, int nrActe,const string& gen, double pret, int locuri, Solist solist, vector<int> durataActe, int durataPauza) {
    int durataTot = durataPauza;
    for(int i = 0; i < durataActe.size(); ++i)
        durataTot += durataActe[i];
    this->nrLocuri = locuri;
    this->durataTotala = durataTot;
    this->numeSpectacol = denumire;
    this->genSpectacol = gen;
    this->pretBilet = pret;
    this->nrActe = nrActe;
    this->solist = solist;
    this->durataActe = durataActe;
    this->durataPauza = durataPauza;
}
SpectacolOpera::~SpectacolOpera() {
    durataPauza = 0;
}
SpectacolOpera & SpectacolOpera::operator=(const SpectacolOpera &spectacolOpera) {
    Spectacol::operator=(spectacolOpera);
    this->solist = spectacolOpera.solist;
    this->durataActe = spectacolOpera.durataActe;
    this->durataPauza = spectacolOpera.durataPauza;
    this->genSpectacol = spectacolOpera.genSpectacol;
    this->pretBilet = spectacolOpera.pretBilet;
    return *this;
}

istream & SpectacolOpera::readSpectacol(istream &is) {
    cout << "Introduceti denumirea spectacolului de opera:\n";
    getline(is, numeSpectacol);
    cout << "Introduceti solistul: \n";
    is >> solist;
    cout << "Introduceti genul spectacolului de opera:\n";
    getline(is,this->genSpectacol);
    cout << "Introduceti pretul biletului:\n";
    is >> this->pretBilet;
    cout << "Introduceti numarul de locuri disponibile:\n";
    is >> this->nrLocuri;
    cout << "Introduceti numarul de acte:\n";
    is >> this->nrActe;
    int durataTot = 0;
    cout << "Introduceti duratele actelor:\n";
    for(int i=0; i<this->nrActe ;++i){
        cout <<"Introduceti Durata Actului " << i+1 << ":\n";
        int durata;
        is >> durata;
        durataTot +=  durata;
        durataActe.push_back(durata);
    }
    cout << "Introduceti durata Pauzei:\n";
    is >> durataPauza;
    is.get();
    durataTot += durataPauza;
    durataTotala = durataTot;
    return is;
}
ostream & SpectacolOpera::printSpectacol(ostream &os) {
    os << "Denumirea spectacolului de opera: " << numeSpectacol << '\n';
    os << solist;
    os << "Genul spectacolului de opera: " << genSpectacol <<'\n';
    os << "Numarul de locuri disponibile: " <<nrLocuri << '\n';
    os << "Pretul biletului: " << pretBilet <<'\n';
    os << "Durata spectacolului de opera: " << durataTotala<< '\n';
    os << "Numarul de acte: " << nrActe << '\n';
    for(int i = 0; i < nrActe; ++i){
        cout <<"Durata Actului " << i+1 << " : " << durataActe[i] << '\n';
    }
    os << "Durata Pauzei : " << durataPauza << '\n';
    os << '\n';
    return os;
}

bool SpectacolOpera::operator==(const SpectacolOpera &spectacol) const {
    return static_cast<const Spectacol &>(*this) == static_cast<const Spectacol &>(spectacol) &&
           solist == spectacol.solist &&
           durataActe == spectacol.durataActe &&
           durataPauza == spectacol.durataPauza;
}

bool SpectacolOpera::operator!=(const SpectacolOpera &spectacol) const {
    return !(spectacol == *this);
}


class SpectacolStandup : public Spectacol{

private:
    string numeHeadliner;

public:

    string get_numeHeadliner();
    void set_numeHeadliner(const string& nume);

    SpectacolStandup();
    SpectacolStandup(const SpectacolStandup& spectacolStandup);
    SpectacolStandup(int durata, const string& denumire, const string& gen, double pret, const string& nume,int locuri);
    virtual ~SpectacolStandup();
    SpectacolStandup& operator=(const SpectacolStandup& spectacolStandup);

    virtual istream& readSpectacol(istream& is);
    virtual ostream& printSpectacol(ostream& os);

};

string SpectacolStandup::get_numeHeadliner() {
    return numeHeadliner;
}
void SpectacolStandup::set_numeHeadliner(const string& nume) {
    numeHeadliner = nume;
}

SpectacolStandup::SpectacolStandup():Spectacol() {
    numeHeadliner = "";
}
SpectacolStandup::SpectacolStandup(const SpectacolStandup& spectacolStandup) : Spectacol(spectacolStandup){
    numeHeadliner = spectacolStandup.numeHeadliner;
}
SpectacolStandup::SpectacolStandup(int durata, const string &denumire, const string& gen, double pret, const string &nume,int locuri) :Spectacol(durata,denumire,1,gen,pret,locuri),numeHeadliner(nume){}
SpectacolStandup::~SpectacolStandup() {
    numeHeadliner = "";
}
SpectacolStandup & SpectacolStandup::operator=(const SpectacolStandup &spectacolStandup) {
    Spectacol::operator=(spectacolStandup);
    this->numeHeadliner = spectacolStandup.numeHeadliner;
    return *this;
}

istream & SpectacolStandup::readSpectacol(istream &is) {
    cout << "Introduceti denumirea spectacolului de standup:\n";
    getline(is, numeSpectacol);
    this->nrActe = 1;
    cout << "Introduceti durata spectacolului:\n";
    is >> this->durataTotala;
    is.get();
    cout << "Introduceti numarul de locuri disponibile:\n";
    is >> this->nrLocuri;
    is.get();
    cout << "Introduceti pretul biletului:\n";
    is >> this->pretBilet;
    is.get();
    this->genSpectacol = "comedie";
    cout << "Introduceti numele Headliner-ului:\n";
    getline(is,numeHeadliner);
    return is;
}
ostream & SpectacolStandup::printSpectacol(ostream &os) {
    os << "Denumirea spectacolului de standup: " << numeSpectacol << '\n';
    os << "Durata spectacolului de standup: " << durataTotala<< '\n';
    os << "Pretul biletului: " << pretBilet <<'\n';
    os << "Numarul de locuri disponibile: " << nrLocuri << '\n';
    os << "Numarul de acte: " << nrActe << '\n';
    os << "Numele Headliner-ului : " << numeHeadliner << '\n';
    os << '\n';
    return os;
}

Spectacol * Spectacol::CreateSpectacol(string SpectacolType) {
    if(SpectacolType == "Teatru")
        return new SpectacolTeatru();
    else if (SpectacolType == "Opera")
        return new SpectacolOpera();
    else if(SpectacolType == "Standup")
        return new SpectacolStandup();
    else return nullptr;
}



//--------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
class GestionareRezervariSpectacole{

private:
    T spectacol;
    static int idSpectacol;
    static unordered_map <int, pair<string, int>> myMap; //static unordered_map <id_spectacol, pair<data_spectacol, locuri disponibile>>
public:

    GestionareRezervariSpectacole(){
    }
    GestionareRezervariSpectacole(T obiect){
        spectacol = obiect;
        myMap[idSpectacol] = obiect;
        ++idSpectacol;
    }
    GestionareRezervariSpectacole(const GestionareRezervariSpectacole& obiect){
        spectacol = obiect.spectacol;
    }
    ~GestionareRezervariSpectacole(){
        idSpectacol = 0;
        myMap = {};
    }
    GestionareRezervariSpectacole& operator=(const GestionareRezervariSpectacole& obiect){
        spectacol = obiect.spectacol;
        return *this;
    }
    GestionareRezervariSpectacole& operator+=(T &spect){
        spectacol = spect;
        idSpectacol++;
        return *this;
    }
    void adaugaRezervare(T  &spect, string date, int number){

        (*this)+=spect;
        myMap[idSpectacol].first = date;
        myMap[idSpectacol].second = number;
    }
    template<typename U>
    friend ostream& operator<<(ostream& os, GestionareRezervariSpectacole<U> &obiect);

    template<typename U>
    friend istream& operator>>(istream& is, GestionareRezervariSpectacole<U> &obiect);

};
template <typename T>
int GestionareRezervariSpectacole<T>::idSpectacol = 0;
template <typename T>
unordered_map <int, pair<string,int>> GestionareRezervariSpectacole<T>::myMap;

template<typename U>
ostream& operator<<(ostream& os, GestionareRezervariSpectacole<U> &obiect){
    os << "Gestionare Rezervarilor pentru: ";

    U *ob = new U(obiect.spectacol);

    if(SpectacolTeatru *teatru = dynamic_cast<SpectacolTeatru*>(ob))
        os << "Teatru\n";
    else if(SpectacolOpera *opera = dynamic_cast<SpectacolOpera*>(ob))
        os <<"Opera\n";

    if(GestionareRezervariSpectacole<U>::idSpectacol == 0)
        os << "Nu s-au facut rezervari de acest fel\n";
    else{
        os << "Numarul de rezervari de acest fel este: " << GestionareRezervariSpectacole<U>::idSpectacol << '\n';
        os << "Rezervarile de acest fel sunt: \n";
        int nrRezervare;

        for (typename unordered_map<int,pair<string,int>>::iterator it = GestionareRezervariSpectacole<U>::myMap.begin();it!=GestionareRezervariSpectacole<U>::myMap.end();++it){
            os << "~~~~~~~Rezervarea " << nrRezervare << "~~~~~~~~~\n";
            os << "Data rezervarii: " << it->second.first <<'\n';
            os << "Numarul de locuri rezervate: " << it->second.second << '\n';
            cout << '\n';
            ++nrRezervare;
        }
    }
    return os;
}

template<typename U>
istream& operator>>(istream& is, GestionareRezervariSpectacole<U> &obiect){
    U ob;
    is >> ob;
    obiect+=ob;
    return is;
}


class singleton
{
    static singleton *instanta;

    singleton(){
        cout<<"Cum spectacol doriti sa vedeti? : "<<endl;
        cout<<"1->opera"<<endl;
        cout<<"2->teatru"<<endl;
    }
public:
    static singleton * getInstanta()
    {
        if(instanta==NULL)
            instanta=new singleton;
        return instanta;
    }
    void citire(int &n, vector<Spectacol*>& v, GestionareRezervariSpectacole<SpectacolOpera>& opera, GestionareRezervariSpectacole<SpectacolTeatru>& teatru){
        int  i=0,ok=0;
        do {
            try {
                cout << "Cate rezervari vrei sa faci? ";
                cin >> n;
                if (n == 0)
                    throw "Ai ales sa NU rezervi!";
                else if (n < 0)
                    throw "NU poti face mai putin de o rezervare";
                else if(n>3)
                    throw "Nu poti face mai mult de 3 rezervari";
                ok = 1;
            }
            catch (const char *s)
            {
                cout << s << '\n';

            }
        }
        while(ok==0);

        while (i<n)
        {


            try {
                int optiune;
                cout << "Dati tipul spectacolului (1-opera, 2-teatru, 3 -standup):";
                cin >> optiune;
                cin.get();
                if (optiune <= 0 || optiune >= 4)
                    throw
                            "Nu ai ales corect!! mai alege o data ";
                i++;

                if(optiune==1)
                {
                    //opera
                    SpectacolOpera *op=new SpectacolOpera;
                    cin>>*op;
                    string date;
                    cout << "Introduceti Data:\n";
                    getline(cin,date);
                    int number ;
                    cout << "Introduceti Numarul de locuri:\n";
                    cin >> number;
                    cin.get();
                    v.push_back(op);
                    opera.adaugaRezervare(*op,date,number);

                } else if(optiune==2)
                {
                    //teatru
                    SpectacolTeatru *tea=new SpectacolTeatru;
                    cin>>*tea;
                    string date;
                    cout << "Introduceti Data:\n";
                    getline(cin,date);
                    int number ;
                    cout << "Introduceti cate locuri rezervati:\n";
                    cin >> number;
                    cin.get();
                    v.push_back(tea);
                    teatru.adaugaRezervare(*tea,date,number);

                }

            }
            catch (const char *s) {
                cout << s<<endl;
            }
        }
    }

    void afisare( vector<Spectacol*>& v, GestionareRezervariSpectacole<SpectacolOpera>& opera, GestionareRezervariSpectacole<SpectacolTeatru>& teatru)
    {
        cout<<"-----------------------------"<<endl;
        cout << "Rezervari efectuate sunt:" << endl;
        int i=0;
        for(typename vector<Spectacol*>::iterator it = v.begin();it!=v.end();++it)
        {
            cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~Spectacol"<<i<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout << **it;
            i++;
        }
        cout<<"---------Statistica pe gestiuni---------"<<endl;
        cout<<opera;
        cout<<teatru;

    }
    void op3()
    {


    }
    void op4()
    {

    }
    void op5()
    {

    }
    void op6()
    {

    }
    void op7()
    {

    }


};
singleton * singleton :: instanta;
int main() {
    singleton *s;
    int n;
    vector<Spectacol*> v;
    GestionareRezervariSpectacole<SpectacolOpera> opera ;
    GestionareRezervariSpectacole<SpectacolTeatru> teatru;

    while (true)
    {

        try {
            int optiune;
            cout << "Ce vreti sa faceti? (1-citire/2-afisare) ";
            cin >> optiune;
            cin.get();
            if (optiune <= 0 || optiune > 10)
                throw
                        "Nu ati ales corect! Mai alegeti o data! \n";

            if(optiune==1)
            {
                s->citire(n,v,opera,teatru);
            }
            else

            if(optiune==2)
            {
                s->afisare(v,opera,teatru);
            }

        }
        catch (const char *s)
        {
            cout << s<<endl;

        }
        cout<<"Doriti sa continuati? (da/nu): ";
        string rasp;
        getline(cin,rasp);
        if(rasp=="nu")
            break;
    }

    return 0;
}
