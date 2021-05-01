#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
//Tema 13
//Se dorește implementarea unei aplicații OOP care sa permita gestionarea rezervarilor la spectacolele
// de la sălile de spectacol apartinand proprietarului Y. Pentru fiecare sala de spectacol se cunoaște
// cel puțin tipul spectacolului care se desfășoară (e.g. opera, teatru), numele spectacolului,
// genul acestuia (de ex: comedie, drama, etc.) și prețul biletului.
// Cunoaștem despre toate spectacolele cel puțin faptul că au o durata și un nume, durata fiind variabila.
// Piesele de teatru au un singur act. Unele piese de teatru sunt interactive (presupun participarea publicului).
// Despre spectacolele de opera se cunoaște faptul că au un solist principal.
// Solistul principal are un nume și poate fi tenor, bariton sau bass.
// Unele opere pot avea mai multe acte (2-7), cu durate diferite, specificate pentru fiecare act în parte.
// Între acte se ia o pauza fixă specifică operei ce se va adăuga la durata totală a piesei, pentru a putea să îi estimăm durata totală.
//Să se construiască clasa template GestionareRezervariSpectacole care sa conțină informații despre diversele tipuri de spectacole
// și să permită efectuarea unor rezervări pentru acestea. Clasa conține indexul spectacolului
// (incrementat automat la adaugarea unui nou spectacol), și o structura de obiecte,
// alocată dinamic care sa gestioneze rezervările care se pot face la un anumit spectacol tinand cont ca
// fiecare spectacol este prezentat în mai multe zile pe parcursul stagiunii și fiecare prezentare are un număr limitat de locuri.
//Structura de date: unordered_map sau unordered_set <id_spectacol, pair<data_spectacol, locuri disponibile>>
//- Să se adauge toate câmpurile relevante pentru modelarea acestei probleme.
//Cerința suplimentară:
//Dat fiind că la sălile de spectacol au început să fie prezentate și spectacole de stand-up
// (care conțin suplimentar față de un spectacol obișnuit și numele headliner-ului),
// să se construiască o specializare aferentă acestui tip de spectacol ce ne va permite să aflăm numărul de bilete vândute
// în urma rezervărilor făcute la stand-up.
//


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

    friend istream& operator>>(istream& is, Solist& solist);
    friend ostream& operator<<(ostream&os, Solist& solist);
};
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
        getline(is, solist.nume);
    }
    return is;
}
ostream& operator<<(ostream&os, Solist& solist){
    if(solist.solistType == "Tenor"){
        os << "Numele Solistului Tenor:" << solist.nume <<"\n";
    }
    else if (solist.solistType == "Bass"){
        os << "Numele Solistului Bass:" << solist.nume <<"\n";
    }
    else if(solist.solistType == "Bariton"){
        os << "Numele Solistului Bariton:" << solist.nume <<"\n";
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



//--------------------------------------------------------------------------------------------------------------------
class Spectacol{
protected:
    string denumireSpectacol;
    int durataSpectacol;
    double pretBilet;
public:
    const int getDurataSpectacol();
    const string getDenumireSpectacol();
    const double getPretBilet();

    void setDurataSpectacol(int durata);
    void setDenumireSpectacol(const string &denumire);
    void setPretBilet(double pret);

    Spectacol();
    Spectacol(const Spectacol& spectacol);
    Spectacol(const string &denumireSpectacol, int durataSpectacol,double pretBilet) : denumireSpectacol(denumireSpectacol),durataSpectacol(durataSpectacol),pretBilet(pretBilet) {}
    Spectacol& operator=(const Spectacol& spectacol);
    virtual ~Spectacol();

    friend istream& operator>>(istream& is, Spectacol& spectacol){return spectacol.read(is);}
    friend ostream& operator<<(ostream& os, Spectacol& spectacol){return spectacol.print(os);}
    virtual istream& read(istream& is) = 0;
    virtual ostream& print(ostream& os) = 0;

    static Spectacol* CreateSpectacol(string SpectacolType);
};
const double Spectacol::getPretBilet() {
    return pretBilet;
}
void Spectacol::setPretBilet(double pret) {
    this->pretBilet = pret;
}

Spectacol & Spectacol::operator=(const Spectacol &spectacol) {
    this->denumireSpectacol = spectacol.denumireSpectacol;
    this->durataSpectacol = spectacol.durataSpectacol;
    this->pretBilet = spectacol.pretBilet;
    return *this;
}
Spectacol::Spectacol() {
    denumireSpectacol = "";
    pretBilet = 0.0;
    durataSpectacol = 0;
}
Spectacol::Spectacol(const Spectacol &spectacol) {
    this->denumireSpectacol = spectacol.denumireSpectacol;
    this->durataSpectacol = spectacol.durataSpectacol;
    this->pretBilet = spectacol.pretBilet;
}
Spectacol::~Spectacol() {
}
const string Spectacol::getDenumireSpectacol() {
    return denumireSpectacol;
}
const int Spectacol::getDurataSpectacol() {
    return durataSpectacol;
}
void Spectacol::setDenumireSpectacol(const string &denumire) {
    denumireSpectacol = denumire;
}
void Spectacol::setDurataSpectacol(int durata) {
    durataSpectacol = durata;
}

class SpectacolTeatru: public Spectacol{
protected:
    string interactiva;

public:
    const string &getInteractiva() const;
    void setInteractiva(const string &interactiva);

    SpectacolTeatru();
    SpectacolTeatru(const SpectacolTeatru &spectacolTeatru);
    SpectacolTeatru(const string &denumireSpectacol, int durataSpectacol,double pretBilet, const string &interactiva);
    virtual ~SpectacolTeatru();
    SpectacolTeatru& operator=(const SpectacolTeatru& spectacolTeatru);

    virtual istream& read(istream &is);
    virtual ostream& print(ostream &os);

};
SpectacolTeatru & SpectacolTeatru::operator=(const SpectacolTeatru &spectacolTeatru) {
    Spectacol::operator=(spectacolTeatru);
    this->interactiva = spectacolTeatru.interactiva;
    return *this;
}

istream & SpectacolTeatru::read(istream &is) {
    cout << "Introduceti denumirea spectacolului de teatru:\n";
    is >> this->denumireSpectacol;
    is.get();
    cout << "Introduceti durata spectacolului de teatru:\n";
    is >> this->durataSpectacol;
    cout << "Introduceti pretul biletului:\n";
    is >> this->pretBilet;
    is.get();
    cout << "Introduceti 'da' daca spectacolul de teatru este interactiv, 'nu' altfel:\n";
    is >> this->interactiva;
    is.get();
    return is;
}
ostream & SpectacolTeatru::print(ostream &os) {
    os << "Denumirea spectacolului de teatru: " << denumireSpectacol << '\n';
    os << "Durata spectacolului de teatru: " << durataSpectacol<< '\n';
    os << "Pretul Biletului: " << pretBilet <<'\n';
    os << "Este spectacolul de teatru interactiv? " << interactiva<< '\n';
    os << '\n';
    return os;
}
SpectacolTeatru::SpectacolTeatru(const string &denumireSpectacol, int durataSpectacol,double pretBilet, const string &interactiva)
        : Spectacol(denumireSpectacol, durataSpectacol,pretBilet), interactiva(interactiva) {}

SpectacolTeatru::SpectacolTeatru():Spectacol() {
    interactiva = "";
}
SpectacolTeatru::SpectacolTeatru(const SpectacolTeatru &spectacolTeatru) : Spectacol(spectacolTeatru){
    this->interactiva = spectacolTeatru.interactiva;
}
SpectacolTeatru::~SpectacolTeatru() {

}
void SpectacolTeatru::setInteractiva(const string &interactiva) {
    SpectacolTeatru::interactiva = interactiva;
}
const string &SpectacolTeatru::getInteractiva() const {
    return interactiva;
}


class SpectacolOpera:public Spectacol{
protected:
    Solist solist;
    int nrActe;
    vector<int>durataActe;
    int durataPauza;
public:
    const Solist getSolist();
    const int getNrActe();
    const vector<int> &getDurataActe();
    const int getDurataPauza();

    void setSolist(Solist solist);
    void setNrActe(int nrActe);
    void setDurataActe(const vector<int> &durataActe);
    void setDurataPauza(int durataPauza);

    SpectacolOpera();
    SpectacolOpera(const SpectacolOpera& spectacolOpera);
    SpectacolOpera(const string &denumireSpectacol, int durataSpectacol,double pretBilet, Solist solist, int nrActe,
                   const vector<int> &durataActe, int durataPauza);
    virtual ~SpectacolOpera(){};
    SpectacolOpera& operator=(const SpectacolOpera& spectacolOpera);

    virtual istream& read(istream &is);
    virtual ostream& print(ostream &os);
};
const Solist  SpectacolOpera::getSolist() {
    return solist;
}
const int SpectacolOpera::getNrActe() {
    return nrActe;
}
const vector<int> & SpectacolOpera::getDurataActe() {
    return durataActe;
}
const int SpectacolOpera::getDurataPauza() {
    return durataPauza;
}

void SpectacolOpera::setSolist(Solist solist) {
    SpectacolOpera::solist = solist;
}

void SpectacolOpera::setNrActe(int nrActe) {
    SpectacolOpera::nrActe = nrActe;
}

void SpectacolOpera::setDurataActe(const vector<int> &durataActe) {
    SpectacolOpera::durataActe = durataActe;
}

void SpectacolOpera::setDurataPauza(int durataPauza) {
    SpectacolOpera::durataPauza = durataPauza;
}
SpectacolOpera::SpectacolOpera() :Spectacol(){
    Solist s;
    solist = s;
    nrActe = 0;
    durataPauza = 0;
}
SpectacolOpera::SpectacolOpera(const string &denumireSpectacol, int durataSpectacol, double pretBilet, Solist solist, int nrActe,
                               const vector<int> &durataActe, int durataPauza) : Spectacol(denumireSpectacol,
                                                                                           durataSpectacol,pretBilet), nrActe(nrActe),
                                                                                 durataActe(durataActe),
                                                                                 durataPauza(durataPauza) {
    this->solist = solist;
}

SpectacolOpera::SpectacolOpera(const SpectacolOpera &spectacolOpera):Spectacol(spectacolOpera) {
    this->solist = spectacolOpera.solist;
    this->nrActe = spectacolOpera.nrActe;
    this->durataPauza = spectacolOpera.durataPauza;
    this->durataActe = spectacolOpera.durataActe;
}

SpectacolOpera & SpectacolOpera::operator=(const SpectacolOpera &spectacolOpera) {
    Spectacol::operator=(spectacolOpera);
    this->solist = spectacolOpera.solist;
    this->nrActe = spectacolOpera.nrActe;
    this->durataPauza = spectacolOpera.durataPauza;
    this->durataActe = spectacolOpera.durataActe;
    return *this;
}

istream & SpectacolOpera::read(istream &is) {
    cout << "Introduceti denumirea spectacolului de opera:\n";
    is >> this->denumireSpectacol;
    is.get();
    cout << "Introduceti durata spectacolului de opera:\n";
    is >> this->durataSpectacol;
    cout << "Introduceti pretul biletului:\n";
    is >> this->pretBilet;
    is.get();
    is >> solist;
    cout << "Introduceti numarul de acte:\n";
    is >> this->nrActe;
    cout << "Introduceti duratele actelor:\n";
    for(int i=0; i<this->nrActe ;++i){
        cout <<"Introduceti Durata Actului " << i+1 << ":\n";
        int durata;
        is >> durata;
        durataActe.push_back(durata);
    }
    cout << "Introduceti durata Pauzei:\n";
    is >> durataPauza;
    is.get();

    return is;
}
ostream & SpectacolOpera::print(ostream &os) {
    os << "Denumirea spectacolului de opera: " << denumireSpectacol << '\n';
    os << "Durata spectacolului de opera: " << durataSpectacol<< '\n';
    os << "Pretul Biletului: " << pretBilet <<'\n';
    os << solist;
    os << "Numarul de acte al piesei de opera:" << nrActe <<'\n';
    os << "Durata actelor:\n";

    for(int i = 0; i < nrActe ; ++i){
        os << "Actul " << i+1 << " are durata: ";
        os << durataActe[i];
        os <<'\n';
    }
    os << "Durata pauzei: " << durataPauza << '\n';
    os << '\n';
    return os;
}
Spectacol * Spectacol::CreateSpectacol(string SpectacolType) {
    if(SpectacolType == "Teatru")
        return new SpectacolTeatru();
    else if (SpectacolType == "Opera")
        return new SpectacolOpera();
    else return nullptr;
}
class  SpectacolStandUp:public Spectacol{
protected:
    string numeHeadliner;

};
int main() {
    Spectacol *spectacol = Spectacol::CreateSpectacol("Opera");
    cin >> *spectacol;
    cout << *spectacol;
    return 0;
}
