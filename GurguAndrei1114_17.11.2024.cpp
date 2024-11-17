#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//clasa este o entitate din viata reala, este formata din atribute/campuri, se definesc mereu in zona privata
//in rest tot codul va fi in zona publica
//constructorii sunt functii prin care creem obiecte
//creem mai multe autobuze, fiecare autobuz este un obect
class Autobuz {

private:


	static int nrAutobuze; //nu se pune ca param in constructori
	const int idAutobuz; //nu se pune ca param in constr.
	int capacitate;
	int nrPersoaneImbarcate;
	char* producator;


public:
	//constructor fara param.
	Autobuz() : idAutobuz(nrAutobuze++) {
		capacitate = 0;
		nrPersoaneImbarcate = 0;
		producator = new char[4];
		strcpy_s(producator, 4, "N/A");
	}

	//constructor cu param.
	Autobuz(int capacitate, int nrPersoaneImbarcate, const char* producator) : idAutobuz(nrAutobuze++) {
		if (capacitate > 0 && capacitate >= nrPersoaneImbarcate) {
			this->capacitate = capacitate;
		}
		if (nrPersoaneImbarcate > 0 && nrPersoaneImbarcate <= capacitate) {
			this->nrPersoaneImbarcate = nrPersoaneImbarcate;
		}
		if (producator != nullptr) {
			this->producator = new char[strlen(producator) + 1];
			strcpy_s(this->producator, strlen(producator) + 1, producator);
		}

	}

	//constructor de copiere: creem o copie pe baza unui obiect existent
	Autobuz(const Autobuz& a) : idAutobuz(nrAutobuze++) {

		if (a.capacitate > 0 && a.capacitate >= a.nrPersoaneImbarcate) {
			this->capacitate = a.capacitate;
		}

		if (a.nrPersoaneImbarcate > 0 && a.nrPersoaneImbarcate <= a.capacitate) {
			this->nrPersoaneImbarcate = a.nrPersoaneImbarcate;
		}
		if (a.producator != nullptr) {
			this->producator = new char[strlen(a.producator) + 1];
			strcpy_s(this->producator, strlen(a.producator) + 1, a.producator);
		}
	}



	//destructor -> dezaloca memoria dinamica: char*, int*, float*, bool* etc...

	~Autobuz() {
		delete[] this->producator;
		cout << "Destructor apelat cu succes!" << endl;
	}


	//get si set -> getter: este o metoda prin care accesam valoarea unui camp privat al clasei
	//setter -> este o metoda prin care modificam valoarea unui camp privat al clasei


	//getteri
	int getNrPersoaneImbarcate() {
		return this->nrPersoaneImbarcate;
	}

	char* getProducator() {
		return this->producator;

	}

	int getCapacitate() {
		return this->capacitate;
	}

	//setteri

	void setNrPersoaneImbarcate(int nrNoiPersoaneImbarcate) {
		this->nrPersoaneImbarcate = nrNoiPersoaneImbarcate;
	}

	void setCapacitate(int capacitateNoua) {
		this->capacitate = capacitateNoua;
	}


	//supraincarcare operator << pentru afisarea campurilor obiectului la consola
	friend ostream& operator<<(ostream& out, Autobuz& a) {
		out << a.idAutobuz << "; ";
		out << a.capacitate << "; ";
		out << a.nrPersoaneImbarcate << "; ";
		if (a.producator != nullptr) {
			out << a.producator << "; ";
		}
		out << "\n";
		return out;
	}


	//supraincarcare operator =

	Autobuz& operator=(const Autobuz& a) {
		if (this != &a) { //nu permitem auto asignarea
			if (this->producator != nullptr) {
				delete[] this->producator;
			}
			if (a.capacitate > 0 && a.capacitate >= a.nrPersoaneImbarcate) {
				this->capacitate = a.capacitate;
			}
			if (a.nrPersoaneImbarcate > 0 && a.nrPersoaneImbarcate <= a.capacitate) {
				this->nrPersoaneImbarcate = a.nrPersoaneImbarcate;
			}
			if (a.producator != nullptr) {
				this->producator = new char[strlen(a.producator) + 1];
				strcpy_s(this->producator, strlen(a.producator) + 1, a.producator);
			}
		}

		return *this;

	}

	//calcul getLocuriLibere

	int getLocuriLibere() {
		return capacitate - nrPersoaneImbarcate;
	}

	operator int() {
		return nrPersoaneImbarcate;
	}

	bool operator >(const Autobuz& a) {
		return this->capacitate > a.capacitate;
	}

};


//initializare static
int Autobuz::nrAutobuze = 0;

//pt apel
int main() {

	//apel constructor fara param.
	Autobuz a;
	cout << a;
	cout << " ===================================== " << endl;

	//apel constructor cu param.
	Autobuz a1(100, 20, "OTOKAR");
	cout << a1;
	cout << " ===================================== " << endl;

	//apel getter
	cout << a1.getProducator() << endl;
	cout << a1.getNrPersoaneImbarcate() << endl;
	cout << a1.getCapacitate() << endl;
	//apel setter -> producator nou
	a1.setNrPersoaneImbarcate(70);
	a1.setCapacitate(120);
	cout << " ===================================== " << endl;

	cout << a1.getProducator() << endl;
	cout << a1.getNrPersoaneImbarcate() << endl;
	cout << a1.getCapacitate() << endl;
	cout << " ===================================== " << endl;
	cout << a1;
	cout << " ===================================== " << endl;

	//apel constructor de copiere
	Autobuz a2(a1);
	cout << a2;
	cout << " ===================================== " << endl;
	//apel operator =
	Autobuz a3 = a2;
	cout << a3;
	cout << " ===================================== " << endl;

	cout << "Locuri libere ramase in autobuz: " << a3.getLocuriLibere() << endl;

	cout << " ===================================== " << endl;

	//apel operator int
	cout << (int)a3 << endl;
	cout << " ===================================== " << endl;


	//apel operator >
	Autobuz a4(150, 40, "ROTOCAR");
	if (a1 < a4) {
		cout << "Autobuzul a1 are capacitatea mai mica decat a autobuzului a4" << endl;
	}
	else {
		cout << "Autobuzul a1 are capacitatea mai mare decat a autobuzului a4" << endl;
	}


}