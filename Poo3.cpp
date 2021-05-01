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

enum class SolistType{
    Tenor = 0 ,
    Bass = 1,
    Bariton = 2
};

class Solist{
protected:
    string nume;
    SolistType type;
public:
    const string getNume();
    void setNume(const string& nume);

    SolistType getType() const;
    void setType(SolistType type);

    Solist();
    Solist(const Solist& solist);
    Solist(const string &nume) : nume(nume) {}
    virtual ~Solist(){};
    Solist& operator=(Solist& solist);

    friend istream& operator>>(istream& is, Solist& solist){return solist.readSolist(is);}
    friend ostream& operator<<(ostream&os, Solist& solist){return solist.printSolist(os);}

    virtual istream& readSolist(istream& is) = 0;
    virtual ostream& printSolist(ostream& os) = 0;

    static Solist* Create(string SolistType);
};
Solist::Solist() {
    nume = "";
}
Solist::Solist(const Solist &solist) {
    this->nume = solist.nume;
}
Solist & Solist::operator=(Solist &solist) {
    this->nume = solist.nume;
    return *this;
}

SolistType Solist::getType() const {
    return type;
}

void Solist::setType(SolistType type) {
    Solist::type = type;
}


class SolistTenor:public Solist{

public:
    SolistTenor():Solist(){Solist::type = SolistType::Tenor;};
    SolistTenor(const SolistTenor& solistTenor):Solist(solistTenor){Solist::type = SolistType::Tenor;};
    SolistTenor(string &nume):Solist(nume){Solist::type = SolistType::Tenor;}
    virtual ~SolistTenor(){}
    SolistTenor& operator=(SolistTenor& solistTenor);

    virtual istream& readSolist(istream& is);
    virtual ostream& printSolist(ostream& os);
};
SolistTenor & SolistTenor::operator=(SolistTenor &solistTenor) {
    Solist::operator=(solistTenor);
    return *this;
}
istream & SolistTenor::readSolist(istream &is) {
    cout << "Introduceti un Solist Tenor: \n";
    Solist::type = SolistType::Tenor;
    getline(is, nume);
    return is;
}
ostream & SolistTenor::printSolist(ostream &os) {
    os << "Numele Solistului Tenor este: " << nume <<'\n';
    return os;
}

class SolistBass:public Solist{
public:
    SolistBass():Solist(){Solist::type = SolistType::Bass;};
    SolistBass(const SolistBass& solistBass):Solist(solistBass){Solist::type = SolistType::Bass;};
    SolistBass(string &nume):Solist(nume){Solist::type = SolistType::Bass;}
    virtual ~SolistBass(){}
    SolistBass& operator=(SolistBass& solistBass);

    virtual istream& readSolist(istream& is);
    virtual ostream& printSolist(ostream& os);

};
SolistBass & SolistBass::operator=(SolistBass &solistBass) {
    Solist::operator=(solistBass);
    return *this;
}
istream & SolistBass::readSolist(istream &is) {
    cout << "Introduceti un Solist Bass: \n";
    getline(is, nume);
    Solist::type = SolistType::Bass;
    is.get();
    return is;
}
ostream & SolistBass::printSolist(ostream &os) {
    os << "Numele Solistului Bass este: " << nume <<'\n';
    return os;
}

class SolistBariton:public Solist{
public:
    SolistBariton():Solist(){Solist::type = SolistType::Bariton;};
    SolistBariton(const SolistBariton& solistBariton):Solist(solistBariton){Solist::type = SolistType::Bariton;};
    SolistBariton(string &nume):Solist(nume){Solist::type = SolistType::Bariton;}
    virtual ~SolistBariton(){}
    SolistBariton& operator=(SolistBariton& solistBariton);

    virtual istream& readSolist(istream& is);
    virtual ostream& printSolist(ostream& os);
};
SolistBariton & SolistBariton::operator=(SolistBariton &solistBariton) {
    Solist::operator=(solistBariton);
    return *this;
}
istream & SolistBariton::readSolist(istream &is) {
    cout << "Introduceti un Solist Bariton: \n";
    Solist::type = SolistType::Bariton;
    getline(is, nume);
    return is;
}
ostream & SolistBariton::printSolist(ostream &os) {
    os << "Numele Solistului Bariton este: " << nume <<'\n';
    return os;
}
Solist * Solist::Create(string SolistType) {
    if (SolistType == "Tenor")
        return new SolistTenor();
    else if (SolistType == "Bass")
        return new SolistBass();
    else if (SolistType == "Bariton")
        return new SolistBariton();
    else return nullptr;
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
//istream & Spectacol::read(istream &is) {
//    cout << "Introduceti denumirea spectacolului:\n";
//    is >> this->denumireSpectacol;
//    is.get();
//    cout << "Introduceti durata spectacolului:\n";
//    is >> this->durataSpectacol;
//    cout << "Introduceti pretul biletului:\n";
//    is >> this->pretBilet;
//    is.get();
//    return is;
//}
//ostream & Spectacol::print(ostream &os) {
//    os << "Denumirea spectacolului: " << denumireSpectacol<< '\n';
//    os << "Durata spectacolului: " << durataSpectacol<< '\n';
//    os << "Pretul Biletului: " << pretBilet << '\n';
//    os << '\n';
//    return os;
//}
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
    Solist *solist;
    int nrActe;
    vector<int>durataActe;
    int durataPauza;
public:
    const Solist *getSolist();
    const int getNrActe();
    const vector<int> &getDurataActe();
    const int getDurataPauza();

    void setSolist(Solist *solist);
    void setNrActe(int nrActe);
    void setDurataActe(const vector<int> &durataActe);
    void setDurataPauza(int durataPauza);

    SpectacolOpera();
    SpectacolOpera(const SpectacolOpera& spectacolOpera);
    SpectacolOpera(const string &denumireSpectacol, int durataSpectacol,double pretBilet, Solist *solist, int nrActe,
                   const vector<int> &durataActe, int durataPauza);
    virtual ~SpectacolOpera(){};
    SpectacolOpera& operator=(const SpectacolOpera& spectacolOpera);

    virtual istream& read(istream &is);
    virtual ostream& print(ostream &os);
};
const Solist * SpectacolOpera::getSolist() {
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

void SpectacolOpera::setSolist(Solist *solist) {
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
    solist = NULL;
    nrActe = 0;
    durataPauza = 0;
}
SpectacolOpera::SpectacolOpera(const string &denumireSpectacol, int durataSpectacol, double pretBilet, Solist *solist, int nrActe,
                               const vector<int> &durataActe, int durataPauza) : Spectacol(denumireSpectacol,
                                                                                           durataSpectacol,pretBilet), nrActe(nrActe),
                                                                                 durataActe(durataActe),
                                                                                 durataPauza(durataPauza) {
    if(SolistTenor *solistTenor = dynamic_cast<SolistTenor*>(solist)){
        delete this->solist;
        this->solist = Solist::Create("Tenor");
        this->solist = solist;
    }
    else if(SolistBass *solistBass = dynamic_cast<SolistBass*>(solist)){
        delete this->solist;
        this->solist = Solist::Create("Bass");
        this->solist = solist;
    }
    else if(SolistBariton *solistBariton = dynamic_cast<SolistBariton*>(solist)){
        delete this->solist;
        this->solist = Solist::Create("Bariton");
        this->solist = solist;
    }

}

SpectacolOpera::SpectacolOpera(const SpectacolOpera &spectacolOpera):Spectacol(spectacolOpera) {
    if(SolistTenor *solistTenor = dynamic_cast<SolistTenor*>(spectacolOpera.solist)){
        delete this->solist;
        this->solist = Solist::Create("Tenor");
        this->solist = spectacolOpera.solist;
    }
    else if(SolistBass *solistBass = dynamic_cast<SolistBass*>(spectacolOpera.solist)){
        delete this->solist;
        this->solist = Solist::Create("Bass");
        this->solist = spectacolOpera.solist;
    }
    else if(SolistBariton *solistBariton = dynamic_cast<SolistBariton*>(spectacolOpera.solist)){
        delete this->solist;
        this->solist = Solist::Create("Bariton");
        this->solist = spectacolOpera.solist;
    }

    this->solist = spectacolOpera.solist;
    this->nrActe = spectacolOpera.nrActe;
    this->durataPauza = spectacolOpera.durataPauza;
    this->durataActe = spectacolOpera.durataActe;
}

SpectacolOpera & SpectacolOpera::operator=(const SpectacolOpera &spectacolOpera) {
    Spectacol::operator=(spectacolOpera);
    if(SolistTenor *solistTenor = dynamic_cast<SolistTenor*>(spectacolOpera.solist)){
        delete this->solist;
        this->solist = Solist::Create("Tenor");
        this->solist = spectacolOpera.solist;
    }
    else if(SolistBass *solistBass = dynamic_cast<SolistBass*>(spectacolOpera.solist)){
        delete this->solist;
        this->solist = Solist::Create("Bass");
        this->solist = spectacolOpera.solist;
    }
    else if(SolistBariton *solistBariton = dynamic_cast<SolistBariton*>(spectacolOpera.solist)){
        delete this->solist;
        this->solist = Solist::Create("Bariton");
        this->solist = spectacolOpera.solist;
    }
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
    cout << "Introduceti tipul solistului(Tenor/Bass/Bariton):\n";
    string type;
    is >> type;
    is.get();
    try{
        this->solist = Solist::Create(type);
        if(this->solist == nullptr)
            throw(nullptr);
    }
    catch (Solist *solist1){
        cout << "Ati introdus un tip de solist gresit\n";
        while (type!="Tenor" && type!="Bass" && type!="Bartion"){
            cout << "Introduceti tipul solistului(Tenor/Bass/Bariton) - cu prima litera majuscula:\n";
            is >> type;
            is.get();
        }
        this->solist = Solist::Create(type);
    }
    is >> *solist;
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
    if(SolistTenor *solistTenor = dynamic_cast<SolistTenor*>(solist)){
        os << *solist;
    }
    else if(SolistBass *solistBass = dynamic_cast<SolistBass*>(solist)){
        os << *solist;
    }
    else if(SolistBariton *solistBariton = dynamic_cast<SolistBariton*>(solist)){
        os << *solist;
    }
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
    Spectacol *spectacol = Spectacol::CreateSpectacol("Teatru");
    cin >> *spectacol;
    cout << *spectacol;
    return 0;
}
