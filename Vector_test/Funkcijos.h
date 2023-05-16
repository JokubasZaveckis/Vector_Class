#pragma once
#include "Header.h"
#include "MyVector.h"
///
/// Vardu atsitinktiniam generavimui konstanta
/// 
const string VARDAI[100] = {
    "Adomas", "Aivaras", "Albertas", "Aleksandras", "Algis", "Alvydas", "Andrius", "Antanas", "Arminas", "Arnoldas", //10
    "Arturas", "Aurimas", "Benas", "Dainius", "Dalius", "Danas", "Darius", "Deividas", "Domantas", "Donatas", //10
    "Dovydas", "Edgaras", "Edvinas", "Egidijus", "Evaldas", "Gediminas", "Gintaras", "Gytis", "Ignas", "Ilja", //10
    "Ilona", "Inga", "Ingrida", "Jonas", "Juras", "Juozapas", "Justinas", "Kajus", "Karolis", "Kasparas", //10
    "Kestutis", "Kipras", "Klaudijus", "Konstantinas", "Kristijonas", "Laimonas", "Linas", "Mantas", "Marius", "Martynas", //10
    "Mindaugas", "Meta", "Nerijus", "Nijole", "Olegas", "Osvaldas", "Ovidijus", "Patrikas", "Paulius", "Petras", //10
    "Raimondas", "Ricardas", "Rimantas", "Rolandas", "Rokas", "Romualdas", "Saulius", "Simone", "Simonas", "Stanislovas", //10
    "Svetlana", "Sarunas", "Tadas", "Tauras", "Tautvydas", "Teodoras", "Tomas", "Valdas", "Valentinas", "Vidmantas", //10
    "Vidmante", "Viktoras", "Vilius", "Vytautas", "Zilvinas", "Zygimantas", "Karolis", "Aretas", "Nojus", "Giedrius",//10
    "Dominykas", "Dziugas", "Arnas", "Augustas", "Algimantas", "Maksas", "Orestas", "Tautrimas", "Vladas", "Rytis" //10
};
///
/// Pavardziu atsitinktiniam generavimui konstanta
/// 
const string PAVARDES[100] = {
    "Adomaitis", "Alekna", "Aleknavicius", "Andriuskevicius", "Antanaitis", "Arlauskas", "Baksys", "Balciunas", "Baltuska", "Baranauskas", //10
    "Bartkus", "Bendikas", "Bikulcius", "Birzietis", "Bubnys", "Budrys", "Buivydas", "Cepulis", "Cerniauskas", "Cesnulevicius",
    "Dambrauskas", "Dapkus", "Didziokas", "Dilys", "Dobilas", "Dobrovolskis", "Dovydaitis", "Drevinskas", "Dubickas", "Dumbrys",
    "Duda", "Dumbliauskas", "Eidimtas", "Gedvilas", "Gintalas", "Girdauskas", "Girg dys", "Grybauskas", "Grigaitis", "Gudaitis",
    "Gudynas", "Gulbinas", "Gvildys", "Janilionis", "Jankauskas", "Jankunas", "Jonauskas", "Juska", "Juskevicius", "Jusys",
    "Kairys", "Kazlauskas", "Klimasauskas", "Kraujalis", "Kudirka", "Kulvietis", "Lapenas", "Lapinas", "Laukaitis", "Laurinaitis",
    "Laurusaitis", "Liubinas", "Maciulis", "Makaveckas", "Malinauskas", "Markauskas", "Markevicius", "Marozas", "Masalskis", "Maskoliunas",
    "Mazeika", "Mikalauskas", "Miknevicius", "Milaknis", "Miliauskas", "Mockus", "Monstvilas", "Montvilas", "Narkevicius", "Navickas",
    "Norkus", "Pakalniskis", "Pakalniskis", "Palionis", "Petrulis", "Pocius", "Povilaitis", "Rakauskas", "Razmas", "Rimkus", //10
    "Rimsa", "Rupsys", "Rusinas", "Rutkauskas", "Ruzgys", "Sabaliauskas", "Sabonis", "Sakalauskas", "Samsonas", "Savickas" //10
};
///
/// Bazine klase
/// 

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:

    Zmogus() : vardas_(""), pavarde_("") {}

    string getVardas() const { return vardas_; }
    string getPavarde() const { return pavarde_; }

    virtual void setVardas(string& vardas) = 0;
    virtual void setPavarde(string& pavarde) = 0;

    virtual ~Zmogus() {}
};
///
/// Derived klase
/// 

class Studentas : public Zmogus {
private:
    int egzaminas_;
    double vidurkis_;
    double mediana_;
    vector<int> pazymiai_;

public:
    Studentas() : egzaminas_(0), vidurkis_(0), mediana_(0) {}

    Studentas(string vardas, string pavarde, vector<int>& pazymiai, int egzaminas) {
        vardas_ = vardas;
        pavarde_ = pavarde;
        Vidurkis(pazymiai, egzaminas);
        Mediana(pazymiai, egzaminas);
        pazymiai.clear();
    }
    ///
    /// Copy constructor
    ///
    Studentas(const Studentas& other)
        : Zmogus(other), egzaminas_(other.egzaminas_), vidurkis_(other.vidurkis_), mediana_(other.mediana_), pazymiai_(other.pazymiai_) {}
    ///
    /// Copy assignment operator
    /// 
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            egzaminas_ = other.egzaminas_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;
            pazymiai_ = other.pazymiai_;
        }
        return *this;
    }
    ///
    /// Move constructor
    /// 
    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other)), egzaminas_(other.egzaminas_), vidurkis_(other.vidurkis_), mediana_(other.mediana_), pazymiai_(std::move(other.pazymiai_)) {}
    ///
    /// Move assignment operator
    ///
    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            Zmogus::operator=(std::move(other));
            egzaminas_ = other.egzaminas_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;
            pazymiai_ = std::move(other.pazymiai_);
        }
        return *this;
    }
    ///
    /// Getters
    /// 
    string getVardas() const { return vardas_; }
    string getPavarde() const { return pavarde_; }
    int get_egzaminas() const { return egzaminas_; }
    double get_vidurkis() const { return vidurkis_; }
    double get_mediana() const { return mediana_; }
    vector<int> get_pazymiai() const { return pazymiai_; }
    ///
    /// Setters
    ///
    void setVardas(std::string& vardas) override { vardas_ = vardas; }
    void setPavarde(std::string& pavarde) override { pavarde_ = pavarde; }
    void set_egzaminas(int egzaminas) { egzaminas_ = egzaminas; }
    void set_vidurkis(double vidurkis) { vidurkis_ = vidurkis; }
    void set_mediana(double mediana) { mediana_ = mediana; }
    void set_pazymiai(const vector<int>& pazymiai) { pazymiai_ = pazymiai; }

    ///
    /// Vidurkio skaiciavimo funkcija
    ///
    void Vidurkis(vector<int> pazymiai, int egzaminas)
    {
        double suma = accumulate(pazymiai.begin(), pazymiai.end(), 0);
        vidurkis_ = suma / pazymiai.size() * 0.4 + egzaminas * 0.6;
    }
    ///
    /// Medianos skaiciavimo funkcija
    ///
    void Mediana(vector<int> pazymiai, int egzaminas)
    {
        int n = pazymiai.size();
        sort(pazymiai.begin(), pazymiai.end());
        double mediana;
        if (n % 2 == 0)
        {
            mediana = (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0;
        }
        else
        {
            mediana = pazymiai[n / 2];
        }
        mediana_ = mediana * 0.4 + egzaminas * 0.6;
    }

    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
    ///
    /// Destruktorius
    ///
    ~Studentas() {
        pazymiai_.clear();
    }
};

void Skaitymas(MyVector <Studentas>& grupe, float& nuskaitymas);
bool Palyginimas(const Studentas& a, Studentas& b);
void IsvedimasIFaila(vector<Studentas> protingi, vector<Studentas> neprotingi, float& isvedimas);
void FailoSukurimas(MyVector <Studentas>&, int failoDydis, int pazymiuSkaicius);
bool Palyginimas1(const Studentas& a, Studentas& b);
void KitiSkaiciavimai(MyVector <Studentas>& grupe, string strategija);
