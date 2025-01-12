#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>  //pt conceptul de container STL
using namespace std;

//Virtualizare = presupune creearea unei clase abstracte care poate contine doar metode virtual pure
//Clasa abstracta = clasa care nu poate fi instantiata (nu se pot creea obiecte) (folosita doar pt mostenire) (serveste ca sablon pt alte clase)
//Metoda virtual pura = functie care nu are corp, ci doar semnatura/antet (este folosita pt a fi suprascrisa in clasele ce mostenesc clasa abstracta)
//A supra defini = a-i da o implementare intr-o alta clasa

class GestiuneInregistrariSTL {
private:
	vector <string> inregistrari;
public:
	void adaugaInregistrare(string& inregistrare) {
		inregistrari.push_back(inregistrare); //inserare in vector STL
	}
	void afisareInregistrari() {
		for (const auto& inregistrare : inregistrari) {
			cout << inregistrare << endl;
		}
	}
};

//clasa abstracta
class GestiuneSisteme {
public:
	virtual float calculVenit() = 0;  //metoda virtuala
	//vector <string> tranzactiiSisteme;  //vector de stringuri declarat prin libraria STL
	virtual~GestiuneSisteme() {}
};

class SistemSupraveghere:public GestiuneSisteme {
private:
	int nrCamere;
	string* camere;
	char* informatii;
	float durata;
	bool stare;
	static int capacitate;
	GestiuneInregistrariSTL gestiuneInregistrariSTL; //has-a + container STL
	string inregistrare;
public:
	SistemSupraveghere() {
		nrCamere = 0;
		camere = nullptr;
		informatii = nullptr;
		durata = 0;
		stare = false;
		inregistrare = "N/A";
	}
	SistemSupraveghere(int nrCamere, string* camere, const char* informatii, float durata, bool stare, string inregistrare) {
		this->nrCamere = nrCamere;
		this->camere = new string[nrCamere];
		for (int i = 0; i < nrCamere; i++) {
			this->camere[i] = camere[i];
		}
		this->informatii = new char[strlen(informatii) + 1];
		strcpy(this->informatii, informatii);
		this->durata = durata;
		this->stare = stare;
		this->inregistrare = inregistrare;
	}
	SistemSupraveghere(const SistemSupraveghere& s) {
		this->nrCamere = s.nrCamere;
		this->camere = new string[nrCamere];
		for (int i = 0; i < nrCamere; i++) {
			this->camere[i] = s.camere[i];
		}
		this->informatii = new char[strlen(s.informatii) + 1];
		strcpy(this->informatii, s.informatii);
		this->durata = s.durata;
		this->stare = s.stare;
		this->inregistrare = s.inregistrare;
	}
	SistemSupraveghere& operator=(const SistemSupraveghere& s) {
		if (this != &s) {
			this->nrCamere = s.nrCamere;
			this->camere = new string[nrCamere];
			for (int i = 0; i < nrCamere; i++) {
				this->camere[i] = s.camere[i];
			}
			this->informatii = new char[strlen(s.informatii) + 1];
			strcpy(this->informatii, s.informatii);
			this->durata = s.durata;
			this->stare = s.stare;
			this->inregistrare = s.inregistrare;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, SistemSupraveghere& s) {
		out << s.nrCamere << endl;
		for (int i = 0; i < s.nrCamere; i++) {
			out << s.camere[i] << " ";
		}
		out << endl;
		out << s.informatii << endl;
		out << s.durata << endl;
		out << s.stare << endl;
		out << s.inregistrare << endl;
		return out;
	}
	friend istream& operator>>(istream& in, SistemSupraveghere& s) {
		in >> s.nrCamere;
		delete[]s.camere;
		s.camere = new string[s.nrCamere];
		for (int i = 0; i < s.nrCamere; i++) {
			in >> s.camere[i];
		}
		char buffer[100];
		in >> ws;
		in.getline(buffer, 100);
		delete[]s.informatii;
		s.informatii = new char[strlen(buffer) + 1];
		strcpy(s.informatii, buffer);
		in >> s.durata;
		in >> s. stare;
		in >> s.inregistrare;
		return in;
	}
	//supradefinire metoda virtual pura
	float calculVenit() override {
		if (nrCamere > 0) {
			return nrCamere * durata * capacitate;
		}
		return 0;
	}
	~SistemSupraveghere() {
		delete[]this->camere;
		delete[]this->informatii;
	}

	void adaugaInregistrare() {
		gestiuneInregistrariSTL.adaugaInregistrare(inregistrare);
	}
	void afisareInformatii() {
		gestiuneInregistrariSTL.afisareInregistrari();
	}

	string operator[](int index){
		if (index >= 0 && index < this->nrCamere) {
			return this->camere[index];
		}
		else {
			return "Camera nu exista!";
		}
	}

	SistemSupraveghere& operator+=(const string& cameraNoua) {
		string* copie = this->camere;
		this->camere = new string[this->nrCamere + 1];
		for (int i = 0; i < this->nrCamere; i++) {
			this->camere[i] = copie[i];
		}
		this->camere[this->nrCamere] = cameraNoua;
		this->nrCamere++;
		delete[]copie;
		return *this;
	}

};

int SistemSupraveghere::capacitate = 100;

int main() {
	SistemSupraveghere s1;
	cin >> s1;
	cout << s1;
	cout << "============================================" << endl;
	string camere[] = { "Camera1", "Camera2", "Camera3" };
	SistemSupraveghere s2(3, camere, "Urgent", 60, true, "Spargere");
	cout << s2;
	cout << "============================================" << endl;
	SistemSupraveghere s3(s1);
	cout << s3;
	cout << "============================================" << endl;
	SistemSupraveghere s4 = s2;
	cout << s4;
	cout << "============================================" << endl;
	cout << s1.calculVenit() << endl;
	cout << "============================================" << endl;
	s1.adaugaInregistrare();
	s1.afisareInformatii();
	cout << "============================================" << endl;
	cout << s1[1] << endl;
	cout << "============================================" << endl;
	s1 += "Camera Noua";
	cout << s1 << endl;
	return 0;
}

