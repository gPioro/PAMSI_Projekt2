#include <memory>
#include <ctime>
#include <iostream>
#include "Graf.h"

#define INT_MAX 2147483647;

using namespace std;

Graf::Graf(int Wierzcholki, int Krawedzie, int Start)
{
	this->Wierzcholki = Wierzcholki;
	this->Krawedzie = Krawedzie;
	this->Start = Start;
	MacierzGrafu = new int*[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++)
		MacierzGrafu[i] = new int[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++)
		for (int j = 0; j < Wierzcholki; j++) 
			MacierzGrafu[i][j] = 0;
		
	Lista = new Element*[Wierzcholki];

	for (int i = 0; i < Wierzcholki; i++)
		Lista[i] = NULL;


	
}

void Graf::WypelnijGraf(double gestosc, Graf *_Graf) const {
	srand(time(NULL));
	if(gestosc == 1)
	{
		for(int iRzad = 0; iRzad < Wierzcholki; ++iRzad)
		{
			for(int jKolumna = 0; jKolumna < Wierzcholki; ++jKolumna)
			{
				if(iRzad != jKolumna)
				{
					int waga = rand() % 50;
					while(waga == 0)
					{
					waga = rand() % 50;
					}
					MacierzGrafu[iRzad][jKolumna] = waga;
					MacierzGrafu[jKolumna][iRzad] = waga;
					_Graf->dodaj_krawedz(iRzad, jKolumna, waga);
				}
			}
		}
	}
	else
	{
	int kr = Krawedzie;
	srand(time(NULL));
	
	while(kr)
	{
		int rzadWezla = rand() & Wierzcholki;
		int kolumnaWezla = rand() & Wierzcholki;

		if(rzadWezla != kolumnaWezla){
			if (MacierzGrafu[rzadWezla][kolumnaWezla] == 0)
			{
				int waga = rand() % 50;
				while(waga == 0)
				{
					waga = rand() % 50;
				}
				MacierzGrafu[rzadWezla][kolumnaWezla] = waga;
				MacierzGrafu[kolumnaWezla][rzadWezla] = waga;
				_Graf->dodaj_krawedz(rzadWezla, kolumnaWezla, waga);
				--kr;
			}
		}
		}
	}
}


int Graf::Minimum(dane* tab) {
	int min = -1;
	int mindist = INT_MAX;
	for (int i = 0; i < Wierzcholki; i++) {
		if (!tab[i].odwiedzony && tab[i].dystans < mindist) {
			min = i;
			mindist = tab[i].dystans;
		}
	}
	return min;
}

dane* Graf::Dijkstra_Lista() {

	dane* tab = new dane[Wierzcholki];
	droga = new int[Wierzcholki];
	Element *pomocniczy;
	for (int i = 0; i < Wierzcholki; i++) {
		if (i == Start)
		{
			tab[i].dystans = 0;
		}
		else
		{
			tab[i].dystans = INT_MAX;
		}
		tab[i].odwiedzony = false;
		droga[i] = -1;
	}

	int min = Minimum(tab);

	while (min != -1) {
		tab[min].odwiedzony = true;
		pomocniczy = Lista[min];
		
		for (pomocniczy = Lista[min]; pomocniczy; pomocniczy = pomocniczy->nastepny)
		{
			if (tab[min].dystans + pomocniczy->waga < tab[pomocniczy->wezel].dystans) {
				tab[pomocniczy->wezel].dystans = tab[min].dystans + pomocniczy->waga;
				droga[pomocniczy->wezel] = min;
			}
			
		}
		
		min = Minimum(tab);

	}
	return tab;
}




dane* Graf::Dijkstra_Macierz() {

	dane* tab = new dane[Wierzcholki];
	droga = new int[Wierzcholki];
	for (int i = 0; i < Wierzcholki; i++) {
		if (i == Start)
		{
			tab[i].dystans = 0;
		}
		else
		{
			tab[i].dystans = INT_MAX;
		}
		tab[i].odwiedzony = false;
		droga[i] = -1;
	}

	int min = Minimum(tab);
	while (min != -1) {
		tab[min].odwiedzony = true;
		for (int i = 0; i < Wierzcholki; i++) {
			if (MacierzGrafu[min][i] > 0 && tab[min].dystans + MacierzGrafu[min][i] < tab[i].dystans) {
				tab[i].dystans = tab[min].dystans + MacierzGrafu[min][i];
				droga[i] = min;
			}
		}
		
		min = Minimum(tab);
	}

	return tab;
}

int Graf::dodaj_krawedz(int i, int j, int waga)
{
	
	element = new Element;
	element->wezel = j;
	element->waga = waga;
	element->nastepny = Lista[i];
	Lista[i] = element;

	return MacierzGrafu[i][j] = waga;

	

}


void Graf::wyswietl()
{
	std::cout << "Macierz: \n";
	for (int i = 0; i < Wierzcholki; i++)
	{
		for (int j = 0; j < Wierzcholki; j++)
		{
			std::cout << MacierzGrafu[i][j] << "\t";
		}
		std::cout << endl;
	}
}

void Graf::wyswietl_liste()
{
	Element *tmp;
	std::cout << "Lista: \n";
	for (int i = 0; i < Wierzcholki; i++)
	{
		tmp = Lista[i];
		cout << i << ": ";
		while (tmp)
		{
			cout << "Wierzcholek: " << tmp->wezel << " waga = " << tmp->waga<<"; ";
			tmp = tmp->nastepny;
		}
		cout << endl;
	}
}

void Graf::zapisz( dane *tab) {
	int licznik = 0;
	int *Tab_drogi = new int[Wierzcholki];       
	std::ofstream plik("PlikWynikowy.txt");
	
	for (int i = 0; i < Wierzcholki; i++)
	{
		plik << "Droga do wierzcholka " << i << ": " ;
		for (int j = i; j > -1; j = droga[j])
			Tab_drogi[licznik++] = j;
		while (licznik)
		plik << Tab_drogi[--licznik] << "->";
		plik << "Suma wag (koszt drogi) = "<< tab[i].dystans << endl;
	}
	plik.close();
	delete [] Tab_drogi;
}


Graf::~Graf()
{
}
