#ifndef _lista_pitanja_h_
#define _lista_pitanja_h_
#include "pitanje.h"

typedef struct Lista {
	Pitanje* p;
	struct Lista* sledeci = nullptr;
	Lista(Pitanje* pitanje, Lista* sl=nullptr) {
		p = pitanje;
	}
};

class Lista_pitanja {
private:
	Lista* glava;
	int size;
public:
	Lista_pitanja() { glava = nullptr; size = 0; }
	void dodajPitanje() {
		string pitanje;

		getline(cin, pitanje);
		Pitanje* p = new Pitanje(pitanje,size);
		Lista* novi = new Lista(p);
		if (!glava)
			glava = novi;
		else {
			Lista* temp = glava;
			while (temp->sledeci)
				temp = temp->sledeci;
			temp->sledeci = novi;
		}
		size++;
	}
	~Lista_pitanja();
	void obrisiPitanje(int ind);
	void ispisiPitanja();
	void ispisOdgovoraZaPitanja(Pitanje* p);
	Pitanje* pretraziPitanje(string oznaka);
	Cvor* osnovnaPretraga(string pretraga);
	Pitanje* naprednaPretraga();
	void azurirajRaspored();
};

#endif // !_lista_pitanja_h_
