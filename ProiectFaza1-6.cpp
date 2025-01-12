#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class Serviciu {
protected:
    float pret;

public:
    Serviciu(float pret = 0) : pret(pret) {}
    virtual float calcul_pret() const = 0;
    virtual ~Serviciu() {}

    float getPret() const { return pret; }
    void setPret(float pretNou) { pret = pretNou; }

    virtual void scrieInFisierText(ofstream& out) const = 0;
    virtual void citesteDinFisierText(ifstream& in) = 0;

    virtual void scrieInFisierBinar(ofstream& out) const = 0;
    virtual void citesteDinFisierBinar(ifstream& in) = 0;

    friend ostream& operator<<(ostream& out, const Serviciu& s) {
        out << "Pret: " << s.pret << " lei";
        return out;
    }

    friend istream& operator>>(istream& in, Serviciu& s) {
        in >> s.pret;
        return in;
    }

    Serviciu& operator+=(float valoare) {
        pret += valoare;
        return *this;
    }

    Serviciu& operator-=(float valoare) {
        pret -= valoare;
        return *this;
    }

    bool operator>(const Serviciu& s) const {
        return pret > s.pret;
    }

    bool operator<(const Serviciu& s) const {
        return pret < s.pret;
    }

    Serviciu& operator=(float valoare) {
        pret = valoare;
        return *this;
    }

    bool operator==(const Serviciu& s) const {
        return pret == s.pret;
    }
};

class Tuns : public Serviciu {
public:
    Tuns(float pret = 20) : Serviciu(pret) {}
    float calcul_pret() const override { return pret; }

    void scrieInFisierText(ofstream& out) const override {
        out << "Tuns " << pret << endl;
    }

    void citesteDinFisierText(ifstream& in) override {
        in >> pret;
    }

    void scrieInFisierBinar(ofstream& out) const override {
        out.write((char*)&pret, sizeof(pret));
    }

    void citesteDinFisierBinar(ifstream& in) override {
        in.read((char*)&pret, sizeof(pret));
    }

    friend ostream& operator<<(ostream& out, const Tuns& t) {
        out << "Tuns - Pret: " << t.pret << " lei";
        return out;
    }
};

class Frezat : public Serviciu {
public:
    Frezat(float pret = 50) : Serviciu(pret) {}
    float calcul_pret() const override { return pret; }

    void scrieInFisierText(ofstream& out) const override {
        out << "Frezat " << pret << endl;
    }

    void citesteDinFisierText(ifstream& in) override {
        in >> pret;
    }

    void scrieInFisierBinar(ofstream& out) const override {
        out.write((char*)&pret, sizeof(pret));
    }

    void citesteDinFisierBinar(ifstream& in) override {
        in.read((char*)&pret, sizeof(pret));
    }

    friend ostream& operator<<(ostream& out, const Frezat& f) {
        out << "Frezat - Pret: " << f.pret << " lei";
        return out;
    }
};

class Barbierit : public Serviciu {
public:
    Barbierit(float pret = 5) : Serviciu(pret) {}
    float calcul_pret() const override { return pret; }

    void scrieInFisierText(ofstream& out) const override {
        out << "Barbierit " << pret << endl;
    }

    void citesteDinFisierText(ifstream& in) override {
        in >> pret;
    }

    void scrieInFisierBinar(ofstream& out) const override {
        out.write((char*)&pret, sizeof(pret));
    }

    void citesteDinFisierBinar(ifstream& in) override {
        in.read((char*)&pret, sizeof(pret));
    }

    friend ostream& operator<<(ostream& out, const Barbierit& b) {
        out << "Barbierit - Pret: " << b.pret << " lei";
        return out;
    }
};

class Frizerie {
private:
    char* adresa;
    int nr_frizeri;
    bool are_discount;
    string denumire;
    Serviciu** servicii;
    int nr_servicii;

public:
    Frizerie() : adresa(nullptr), nr_frizeri(0), are_discount(false), denumire("Necunoscut"), servicii(nullptr), nr_servicii(0) {}

    Frizerie(const char* adresa, int nr_frizeri, const string& denumire, bool are_discount)
        : nr_frizeri(nr_frizeri), are_discount(are_discount), denumire(denumire), nr_servicii(0), servicii(nullptr) {
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
    }

    //~Frizerie() {
    //    delete[] adresa;
    //    for (int i = 0; i < nr_servicii; i++) {
    //        delete servicii[i];
    //    }
    //    delete[] servicii;
    //}

    Frizerie& operator+=(Serviciu* serviciu) {
        Serviciu** temp = new Serviciu * [nr_servicii + 1];
        for (int i = 0; i < nr_servicii; i++) {
            temp[i] = servicii[i];
        }
        temp[nr_servicii] = serviciu;
        delete[] servicii;
        servicii = temp;
        nr_servicii++;
        return *this;
    }

    Frizerie operator+(int frizeri) const {
        Frizerie temp(*this);
        temp.nr_frizeri += frizeri;
        return temp;
    }

    bool operator==(const Frizerie& f) const {
        return nr_frizeri == f.nr_frizeri && strcmp(adresa, f.adresa) == 0;
    }

    friend ostream& operator<<(ostream& out, const Frizerie& f) {
        out << "Adresa: " << (f.adresa ? f.adresa : "N/A") << endl;
        out << "Numar frizeri: " << f.nr_frizeri << endl;
        out << "Denumire: " << f.denumire << endl;
        out << "Are discount: " << (f.are_discount ? "Da" : "Nu") << endl;
        out << "Numar servicii: " << f.nr_servicii << endl;
        for (int i = 0; i < f.nr_servicii; i++) {
            out << "  - Serviciu " << i + 1 << ": " << *f.servicii[i] << endl;
        }
        return out;
    }
};

class Salon {
private:
    string numeSalon;
    vector<Frizerie> frizerii;
    vector<Serviciu*> serviciiDisponibile;
    int nrAngajati;
    bool arePromotii;

public:
    Salon() : numeSalon("Necunoscut"), nrAngajati(0), arePromotii(false) {}

    Salon(const string& nume, int nrAngajati, bool arePromotii)
        : numeSalon(nume), nrAngajati(nrAngajati), arePromotii(arePromotii) {}

    ~Salon() {
        for (auto serviciu : serviciiDisponibile) {
            delete serviciu;
        }
    }

    void adaugaFrizerie(const Frizerie& frizerie) {
        frizerii.push_back(frizerie);
    }

    void adaugaServiciu(Serviciu* serviciu) {
        serviciiDisponibile.push_back(serviciu);
    }

    bool operator==(const Salon& f) const {
        return this->nrAngajati==f.nrAngajati;
    }

    void operator()() {
        cout << "Apel operator functie " << endl;
    }

    bool operator!() {
        return !this->arePromotii;
    }

    friend ostream& operator<<(ostream& out, const Salon& s) {
        out << "Salon: " << s.numeSalon << endl;
        out << "Numar angajati: " << s.nrAngajati << endl;
        out << "Promotii disponibile: " << (s.arePromotii ? "Da" : "Nu") << endl;
        out << "Frizerii:\n";
        for (size_t i = 0; i < s.frizerii.size(); i++) {
            out << "  Frizerie " << i + 1 << ":\n" << s.frizerii[i] << endl;
        }
        out << "Servicii disponibile:\n";
        for (size_t i = 0; i < s.serviciiDisponibile.size(); i++) {
            out << "  Serviciu " << i + 1 << ": " << *s.serviciiDisponibile[i] << endl;
        }
        return out;
    }
};

int main() {
    vector<Tuns> vectorTuns;
    vector<Frezat> vectorFrezat;
    vector<Barbierit> vectorBarbierit;
    int n;

    cout << "Introduceti numarul de obiecte Tuns: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Tuns t;
        cout << "Introduceti datele pentru Tuns " << i + 1 << ": ";
        cin >> t;
        vectorTuns.push_back(t);
    }

    cout << "Introduceti numarul de obiecte Frezat: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Frezat f;
        cout << "Introduceti datele pentru Frezat " << i + 1 << ": ";
        cin >> f;
        vectorFrezat.push_back(f);
    }

    cout << "Introduceti numarul de obiecte Barbierit: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Barbierit b;
        cout << "Introduceti datele pentru Barbierit " << i + 1 << ": ";
        cin >> b;
        vectorBarbierit.push_back(b);
    }

    Tuns t1(20), t2(30);
    cout << "Tuns 1: " << t1 << "\nTuns 2: " << t2 << endl;
    t1 += 5;
    t2 -= 10;
    cout << "Tuns 1 dupa +=: " << t1 << endl;
    cout << "Tuns 2 dupa -=: " << t2 << endl;
    cout << "Tuns 1 > Tuns 2: " << (t1 > t2 ? "Da" : "Nu") << endl;
    cout << "Tuns 1 < Tuns 2: " << (t1 < t2 ? "Da" : "Nu") << endl;
    cout << "Tuns 1 == Tuns 2: " << (t1 == t2 ? "Da" : "Nu") << endl;
    t1 = 40;
    cout << "Tuns 1 dupa =: " << t1 << endl;

    Frezat f1(50), f2(60);
    cout << "Frezat 1: " << f1 << "\nFrezat 2: " << f2 << endl;
    f1 += 10;
    f2 -= 15;
    cout << "Frezat 1 dupa +=: " << f1 << endl;
    cout << "Frezat 2 dupa -=: " << f2 << endl;
    cout << "Frezat 1 > Frezat 2: " << (f1 > f2 ? "Da" : "Nu") << endl;
    cout << "Frezat 1 < Frezat 2: " << (f1 < f2 ? "Da" : "Nu") << endl;
    cout << "Frezat 1 == Frezat 2: " << (f1 == f2 ? "Da" : "Nu") << endl;
    f1 = 70;
    cout << "Frezat 1 dupa =: " << f1 << endl;

    Barbierit b1(5), b2(10);
    cout << "Barbierit 1: " << b1 << "\nBarbierit 2: " << b2 << endl;
    b1 += 2;
    b2 -= 3;
    cout << "Barbierit 1 dupa +=: " << b1 << endl;
    cout << "Barbierit 2 dupa -=: " << b2 << endl;
    cout << "Barbierit 1 > Barbierit 2: " << (b1 > b2 ? "Da" : "Nu") << endl;
    cout << "Barbierit 1 < Barbierit 2: " << (b1 < b2 ? "Da" : "Nu") << endl;
    cout << "Barbierit 1 == Barbierit 2: " << (b1 == b2 ? "Da" : "Nu") << endl;
    b1 = 8;
    cout << "Barbierit 1 dupa =: " << b1 << endl;

    Frizerie fz1("Strada Mare", 5, "Frizeria X", true);
    Frizerie fz2("Strada Mica", 3, "Frizeria Y", false);
    cout << "\nOperator + pentru Frizerie: " << fz1 + 2 << endl;
    cout << "Operator == pentru Frizerie: " << (fz1 == fz2 ? "Da" : "Nu") << endl;

    Salon s1("Salonul 1", 10, true);
    Salon s2("Salonul 2", 12, false);
    cout << "\nOperator == pentru Salon: " << (s1 == s2 ? "Da" : "Nu") << endl;

    ofstream outText("servicii.txt");
    for (const auto& t : vectorTuns) t.scrieInFisierText(outText);
    for (const auto& f : vectorFrezat) f.scrieInFisierText(outText);
    for (const auto& b : vectorBarbierit) b.scrieInFisierText(outText);
    outText.close();

    ofstream outBinary("servicii.bin", ios::binary);
    for (const auto& t : vectorTuns) t.scrieInFisierBinar(outBinary);
    for (const auto& f : vectorFrezat) f.scrieInFisierBinar(outBinary);
    for (const auto& b : vectorBarbierit) b.scrieInFisierBinar(outBinary);
    outBinary.close();

    ifstream inBinary("servicii.bin", ios::binary);
    for (auto& t : vectorTuns) t.citesteDinFisierBinar(inBinary);
    for (auto& f : vectorFrezat) f.citesteDinFisierBinar(inBinary);
    for (auto& b : vectorBarbierit) b.citesteDinFisierBinar(inBinary);
    inBinary.close();

    Salon salon("Salon de Lux", 15, true);
    salon.adaugaFrizerie(Frizerie("Strada Mare", 3, "Frizeria Moderna", true));
    salon.adaugaServiciu(new Tuns(25));
    salon.adaugaServiciu(new Frezat(50));
    salon.adaugaServiciu(new Barbierit(10));

    cout << "\nSalon detalii:\n" << salon;

    return 0;
}

