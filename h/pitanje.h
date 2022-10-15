#ifndef _pitanje_h_
#define _pitanje_h_
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

typedef struct Cvor {
	string tekst, oznaka; //oznaka je u formatu deo_oca.redni_broj_sina
	vector<int>ocena;
	Cvor* otac;
	Cvor(string t, string oz, Cvor*o=nullptr) {
		tekst = t;
		oznaka = oz;
		ocena.push_back(0);
		otac = o;
	}
	vector<Cvor *>deca;
	~Cvor() {
		deca.clear();
	}
};

class Pitanje {
private:
	Cvor* koren;
public:
	Pitanje() { koren = nullptr; }
	Pitanje(string p, int ind);
	void dodajOdgovor(string t, string pozicija);
	string vratiOznaku() { return koren->oznaka; }
	Cvor* vratiKoren() { return koren; }
	int vratiOcenu() { return koren->ocena[0]; }
	int vratiRedniBroj() {
		if (!koren)
			return -1;
		else
			return stoi(koren->oznaka);
	}
	string vratiPitanje() {
		if (!koren)
			return "Nema pitanja!\n";
		else
			return koren->tekst;
	}
	void izmeniRedniBroj(int i) {
		if (!koren)
			cout << "Nema pitanja";
		else {
			koren->oznaka = to_string(i) + ".";
		}
	}
	~Pitanje() {
		koren->deca.clear();
		delete koren;
	}
	vector<Cvor*> preorder();
	void povecajOcenu(Cvor* cvor, int br);
	void obrisiOdgovor(Cvor* cvor);
	int brojOdgovora();
	string oceneDece(Cvor* cvor);
};
#endif // !_pitanje_h_
