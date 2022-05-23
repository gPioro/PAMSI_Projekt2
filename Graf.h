#pragma once
#include "struktury.h"
#include <memory>

using namespace std; 

class Graf
{

private:

	int *droga;
	int **MacierzGrafu;
	Element *element;
	Element **Lista;
	int Wierzcholki;
	int Krawedzie; 
	int Start;
public:
	Graf() {};
	Graf(int Wierzcholki , int Krawedzie, int Start);
	~Graf();
	void WypelnijGraf(double gestosc, Graf *_Graf) const;
	void ustawWierzcholki(int wierzcholki);
	int dodaj_krawedz(int i, int j, int waga);
	void wyswietl();
	void wyswietl_liste();
	int Minimum(dane* tab);
	dane* Dijkstra_Macierz();
	dane* Dijkstra_Lista();
	void zapisz( dane *tab);


};




