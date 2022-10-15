#include"lista_pitanja.h"
//Dodatni zahtevi:preorder, Pitanje za koje postoji najvise odgovora i komentara (stablo sa najvise cvorova)
int main() {
	Lista_pitanja l1;
	//inicijalno, pitanja imaju ocenu -1000 poena, ovo se nigde ne vidi doduse
	while (true) {
		int indeks;
		cout << "\nKOMENT SEKCIJA\n\nIzaberi stavku iz menija:\n1-Dodaj pitanje\n2-Dodaj odgovor/komentar na pitanje\n3-Pretrazi pitanje i ispisi ga\n4-Pretrazi pitanje i ispisi njegovu sekciju\n5-Povecaj ocenu odgovoru/komentaru\n6-Uredi po oceni\n7-Ispisi sva pitanja\n8-Obrisi odgovor\n9-Obrisi pitanje\n10-Pronadji pitanje sa najvise ocenjenom sekcijom i  ispisi ga\n0-Prekini rad programa\n\n";
		cin >> indeks;
		getchar();
		switch (indeks)
		{
		case 1:
			l1.dodajPitanje();
			break;
		case 2:
		{cout << "Uneti za koje pitanje/odgovor/komentar se unosi odgovor. Format upisa je x.x.x.\n";
		string oznaka;
		getline(cin, oznaka);
		string pom = oznaka.substr(0,2);
		Pitanje* p = l1.pretraziPitanje(pom);
		if (!p)
			cout << "Ne moguce izvrsiti upis\n";
		else {
			string tekst;
			getline(cin, tekst);
			p->dodajOdgovor(tekst, oznaka);
		}
		}
		break;
		case 3:
		{
			cout << "Uneti oznaku pitanja" << endl;
			string oznaka;
			getline(cin, oznaka);
			Pitanje* p = l1.pretraziPitanje(oznaka);
			if (!p)
				cout << "Ne postoji pitanje sa datom oznakom!\n";
			else
				cout << p->vratiOznaku() << " " << p->vratiPitanje() << endl;
		}
		break;
		case 4:
		{
			cout << "Uneti oznaku pitanja" << endl;
			string oznaka;
			getline(cin, oznaka);
			Pitanje* p = l1.pretraziPitanje(oznaka);
			if (!p)
				cout << "Ne postoji pitanje sa datom oznakom!\n";
			else
				l1.ispisOdgovoraZaPitanja(p);
			cout << endl;
		}
		break;
		case 5:
		{
			cout << "Uneti oznaku odgovora/komentara kojem se povecava ocena\n";
			string oznaka;
			getline(cin, oznaka);
			string pom = oznaka.substr(0,2);
			Pitanje* p = l1.pretraziPitanje(pom);
			if (!p)
				cout << "Ne moguce izvrsiti upis\n";
			else {
				Cvor* zaPovecati = l1.osnovnaPretraga(oznaka);
				if (!zaPovecati)
					cout << "Ne moguce izvrsiti povecanje ocene\n";
				else if (!zaPovecati->otac) {
					cout << "Nije dozvoljeno povecanje ocene pitanju!";
				}
				else {
					int b;
					cout << "Uneti za koliko se povecava ocena:\n";
					cin >> b;
					if (b >= -100000 && b <= 100000)
						p->povecajOcenu(zaPovecati, b);
					else
						cout << "Ocena nije u podrzanom opsegu!\n";
				}
			}
		}
		break;
		case 6:
			{
			l1.azurirajRaspored();
			}
			break;
		case 7:
			{
			l1.ispisiPitanja();
			}
			break;
		case 8:
			{
			cout << "Uneti oznaku odgovora/komentara koji se brise\n";
			string oznaka;
			getline(cin, oznaka);
			string pom = oznaka.substr(0,2);
			Pitanje* p = l1.pretraziPitanje(pom);
			if (!p)
				cout << "Ne uspesan pronalazak odgovora\n";
			else {
				Cvor* pretraga = l1.osnovnaPretraga(oznaka);
				if (!pretraga)
					cout << "Ne postojeci odgovor\n";
				else if (!pretraga->otac)
					cout << "Pozvati sekciju za brisanje pitanja!\n";
				else
					p->obrisiOdgovor(pretraga);
			}
			}
			break;
		case 9:
			{
			cout << "Uneti redni broj pitanja koje se brise. Format je x  (dakle bez tacke!)\n";
			int r;
			cin >> r;
			l1.obrisiPitanje(r);
			}
			break;
		case 10:
			{
			Pitanje* p = l1.naprednaPretraga();
			if (!p)
				cout << "Nema unetih pitanja\n";
			else {
				cout << p->vratiOznaku() << " " << p->vratiPitanje() <<" | "<< p->oceneDece(p->vratiKoren()) << endl;
			}
			}
			break;
		case 0:
			{
			return 0;
			
			}
			break;
		default:
			cout << "Unet nepostojeci indeks!\n";
			break;
		}
	}
}
