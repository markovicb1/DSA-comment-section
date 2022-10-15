#include "lista_pitanja.h"
Lista_pitanja::~Lista_pitanja()
{
	Lista* temp;
	while (glava) {
		temp = glava;
		glava = glava->sledeci;
		delete temp;
	}
}

void Lista_pitanja::ispisiPitanja()
{
	Lista* temp = glava;
	if (!temp)
		cout << "Nema unetih pitanja\n";
	while (temp) {
		cout << temp->p->vratiOznaku() << " " << temp->p->vratiPitanje() << " ";
		temp = temp->sledeci;
	}
	cout << endl;
}

void Lista_pitanja::ispisOdgovoraZaPitanja(Pitanje* p)
{
	vector<Cvor*>vektor = p->preorder();
	Cvor* temp = nullptr;
	for (int i = 0; i < vektor.size(); i++) {
		string tabulator="";
		int ind = vektor[i]->oznaka.size() / 2 - 1 ;
		for (int j = 0; j < ind; j++)
			tabulator += "\t";
		cout << tabulator << vektor[i]->oznaka << " " << vektor[i]->tekst <<" | "<<p->oceneDece(vektor[i]) << endl;
	}
}

Pitanje* Lista_pitanja::pretraziPitanje(string oznaka)
{

		
		Lista* temp = glava;
		while (temp) {
			if (temp->p->vratiOznaku() == oznaka)
				return temp->p;
			temp = temp->sledeci;
		}
		return nullptr;
	
}

Cvor* Lista_pitanja::osnovnaPretraga(string pretraga)
{
	//prvo treba pronaci pitanje
	size_t tacka = pretraga.find(".");
	string ind = pretraga.substr(0, tacka) + ".";
	Pitanje* pocetni = nullptr;
	Lista* temp = glava;
	while (temp) {
		if (temp->p->vratiOznaku() == ind) {
			pocetni = temp->p;
			break;
		}	
		temp = temp->sledeci;
	}
	if (!pocetni)
		return nullptr;
	else {//ako smo pronasli pitanje, sada mozemo da trazimo odgovarajuci odgovor putem preordera
		vector<Cvor*>vektor = pocetni->preorder();
		for (int i = 0; i < vektor.size(); i++) {
			if (vektor[i]->oznaka == pretraga)
				return vektor[i];
		}
	}
	return nullptr;
}

Pitanje* Lista_pitanja::naprednaPretraga() //pitanje sa najvise dece
{
	int* brojDece = new int[size];
	if (size == 0)
		return nullptr;
	int br = 0;
	Lista* temp = glava;
	while (temp) {
		brojDece[br++] = temp->p->brojOdgovora();
		temp = temp->sledeci;
	}
	int max = 0;
	for (int i = 0; i < br; i++) {
		if (brojDece[i] > max)
			max = brojDece[i];
	}

	temp = glava;
	//PRONADJI MAKSIMUM BRE
	Pitanje* rez = nullptr;
	while (temp) {
		if (temp->p->brojOdgovora() == max)
			return temp->p;
		temp = temp->sledeci;
	}
}

bool poredi(Cvor* prvi, Cvor* drugi) {
	return(prvi->ocena[0] > drugi->ocena[0]);
}

void Lista_pitanja::azurirajRaspored()
{
	//potrebno je u svakom stablu, za svaki cvor (dakle na svakom nivou) urediti decu cvora po ocena[0]
	Lista* temp = glava;
	
	while (temp) {
		vector<Cvor*>vektor = temp->p->preorder();
		vector<Cvor*>::iterator i;
		//sada za trenutno stablo, idemo od deteta do deteta po preorderu i vrsimo sort
		for (i = vektor.begin(); i < vektor.end(); i++) { //pocinje od korena
			vector<Cvor*>vektor_deca = (*i)->deca;
			sort(vektor_deca.begin(), vektor_deca.end(), poredi);
			(*i)->deca = vektor_deca;
			vector<int>vektor_ocene = (*i)->ocena;
			sort(vektor_ocene.begin() + 1, vektor_ocene.end(), greater<int>());
			(*i)->ocena = vektor_ocene;
		}
		temp = temp->sledeci;
	}
}


void Lista_pitanja::obrisiPitanje(int ind) //poziva se destruktor za stablo
{
	if (!glava || ind > size)
		cout << "Nema postavljenih pitanja!" << endl;
	else if (glava->p->vratiRedniBroj() == ind) {
		Lista* temp = glava;
		glava = glava->sledeci;
		delete temp;
		size--;
		temp = glava;
		while (temp) {
			temp->p->izmeniRedniBroj(temp->p->vratiRedniBroj() - 1);
			vector<Cvor*>vektor = temp->p->preorder();
			vector<Cvor*>::iterator i;
			string noviId = to_string(temp->p->vratiRedniBroj());
			for (i = vektor.begin(); i < vektor.end(); i++) {
				/*string pom = noviId + (*i)->oznaka.substr(((*i)->oznaka.substr('.')));*/
				string stara = (*i)->oznaka;
				size_t poc = stara.find('.');
				string pom = noviId + stara.substr(poc);
				(*i)->oznaka = pom;
			}
				
			temp = temp->sledeci;
		}
	}
	else {
		Lista* temp = glava;
		while (temp->sledeci) {
			if (temp->sledeci->p->vratiRedniBroj() == ind)
				break;
			temp = temp->sledeci;
		}
		Lista* stari = temp->sledeci;
		temp->sledeci = stari->sledeci;
		delete stari;
		size--;
		temp = temp->sledeci;
		while (temp) {
			temp->p->izmeniRedniBroj(temp->p->vratiRedniBroj() - 1);
			vector<Cvor*>vektor = temp->p->preorder();
			vector<Cvor*>::iterator i;
			string noviId = to_string(temp->p->vratiRedniBroj());
			for (i = vektor.begin(); i < vektor.end(); i++) {
				/*string pom = noviId + (*i)->oznaka.substr(((*i)->oznaka.substr('.')));*/
				string stara = (*i)->oznaka;
				size_t poc = stara.find('.');
				string pom = noviId + stara.substr(poc);
				(*i)->oznaka = pom;
			}
			temp = temp->sledeci;
		}
	}

}
