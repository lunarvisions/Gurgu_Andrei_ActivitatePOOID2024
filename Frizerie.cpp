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

    void scrieInFisierBinar(ofstream& out) const override {}
    void citesteDinFisierBinar(ifstream& in) override {}

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

    void scrieInFisierBinar(ofstream& out) const override {}
    void citesteDinFisierBinar(ifstream& in) override {}

    friend ostream& operator<<(ostream& out, const Frezat& f) {
        out << "Frezat - Pret: " << f.pret << " lei";
        return out;
    }
};

class Barbierit : public Serviciu {
public:
    Barbierit(float pret = 5) : Serviciu(pret) {}
    float calcul_pret() const override { return pret; }

    void scrieInFisierText(ofstream& out) const override {}
    void citesteDinFisierText(ifstream& in) override {}

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

    ~Frizerie() {
        delete[] adresa;
        for (int i = 0; i < nr_servicii; i++) {
            delete servicii[i];
        }
        delete[] servicii;
    }

    Frizerie& operator+=(Serviciu* serviciu) {
        Serviciu** temp = new Serviciu*[nr_servicii + 1];
        for (int i = 0; i < nr_servicii; i++) {
            temp[i] = servicii[i];
        }
        temp[nr_servicii] = serviciu;
        delete[] servicii;
        servicii = temp;
        nr_servicii++;
        return *this;
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

    cout << "\nVector Tuns:\n";
    for (const auto& t : vectorTuns) {
        cout << t << endl;
    }

    cout << "\nVector Frezat:\n";
    for (const auto& f : vectorFrezat) {
        cout << f << endl;
    }

    cout << "\nVector Barbierit:\n";
    for (const auto& b : vectorBarbierit) {
        cout << b << endl;
    }

    Salon salon("Salon de Lux", 15, true);
    salon.adaugaFrizerie(Frizerie("Strada Mare", 3, "Frizeria Moderna", true));
    salon.adaugaServiciu(new Tuns(25));
    salon.adaugaServiciu(new Frezat(50));
    salon.adaugaServiciu(new Barbierit(10));

    cout << "\nSalon detalii:\n" << salon;

    return 0;
}