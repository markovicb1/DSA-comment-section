#include "pitanje.h"

Pitanje::Pitanje(string p,int ind)
{
	koren = new Cvor(p,to_string(ind) + ".");
	koren->ocena[0] = -1000; //inicijalno za koren stabla, tj. za samo pitanje
}

vector<Cvor*> Pitanje::preorder() //fja generise vektor cvorova po preorder obilasku
{
	stack<Cvor*>stek;
	vector<Cvor*>vektor;
	stek.push(koren);
	while (!stek.empty()) {
		Cvor* temp = stek.top();
		stek.pop();
		vektor.push_back(temp);
		for (int i = temp->deca.size() - 1; i >= 0; i--)
			stek.push(temp->deca[i]);
	}
	return vektor;
}

void Pitanje::povecajOcenu(Cvor* cvor, int br)
{
	cvor->ocena[0] += br; //azurirali smo ocenu naseg cvora, ali je potrebno azurirati i ocenu u vektoru njegovog oca
	Cvor* otac = cvor->otac;
	vector<int>::iterator j;
	vector<Cvor*>::iterator i;
	int brojac = 1;
	i = otac->deca.begin();
	while (i < otac->deca.end()) {
		if (*i == cvor)
			break;
		i++;
		brojac++;
	}
	j = otac->ocena.begin();
	int brojac2 = 0;
	while (j < otac->ocena.end()) {
		if (brojac2 == brojac)
			break;
		j++;
		brojac2++;
	}
	(*j) += br;
}

void Pitanje::obrisiOdgovor(Cvor* cvor)
{
	Cvor* otac = cvor->otac;
	int stop = 1;
	vector<Cvor*>::iterator i;
	vector<int> ::iterator j;
	for (i = otac->deca.begin(); i < otac->deca.end(); i++) {
		if (*i == cvor)
			break;
		stop++;
	}
	j = otac->ocena.begin();
	int brojac = 0;
	while (j < otac->ocena.end()) {
		if (brojac == stop)
			break;
		brojac++;
		j++;
	} 
	otac->ocena.erase(j);
	otac->deca.erase(i);
	delete cvor;
}

int Pitanje::brojOdgovora()
{
	vector<Cvor*>vektor = preorder();
	return vektor.size();
}

string Pitanje::oceneDece(Cvor* cvor)
{
	string ocene = (!cvor->otac ? "" :to_string(cvor->ocena[0])) + " * ";
	vector<int>::iterator i;
	for (i = cvor->ocena.begin() + 1; i < cvor->ocena.end(); i++) {
		ocene += to_string(*i) + " ";
	}
	return ocene;
}

void Pitanje::dodajOdgovor(string t, string pozicija)
{
	vector<Cvor*>vektor = preorder();
	Cvor* temp = nullptr;
	for (int i = 0; i < vektor.size(); i++) {
		if (vektor[i]->oznaka == pozicija) {
			temp = vektor[i];
			break;
		}
	}
	if (!temp)
		cout << "Ne postoji trazena pozicija!" << endl;
	else if (temp->deca.size() == 10)
		cout << "Max broj odgovara unet!" << endl;
	else { //temp je cvor kojem dodajemo sina
		string pom = temp->oznaka;
		//string novaOznaka = pom + to_string(temp->deca.size()) + ".";
		string novaOznaka;
		if (temp->deca.size() == 0) {
			novaOznaka = pom + "0.";
		}
		else {
			string pom2 = temp->deca[temp->deca.size() - 1]->oznaka;
			vector<Cvor*>vektor_deca = temp->deca;
			vector<Cvor*>::iterator it;
			for (it = vektor_deca.begin(); it < vektor_deca.end(); it++) {
				if ((*it)->oznaka > pom2)
					pom2 = (*it)->oznaka;
			}
			//xxxx.xxxxx.xxxx.xxxx.
			int i;
			for (i = pom2.size() - 2; i >= 0; i--) {
				if (pom2[i] == '.')
					break;
			}
			i++;
			novaOznaka = pom + to_string(stoi(pom2.substr(i, pom2.size() - 2)) + 1) + ".";
		}
		Cvor* novi = new Cvor(t, novaOznaka, temp);
		temp->deca.push_back(novi);
		temp->ocena.push_back(0);
	}
}
