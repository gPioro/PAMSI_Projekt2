#include "UI.h"
#include <chrono>
#define MAKSIMUM 1000
#define PRZYROST 200
#define PETLE 100
using namespace std;


void Wczytaj(Graf *&_Graf)
{
	int Krawedzie;
	int Wierzcholki;
	int Start, start;
	int wierz_pocz;
	int wierz_kon;
	int waga;
	string nazwa_pliku;
	ifstream plik;
	printf("Podaj nazwe pliku \n");
	cin >> nazwa_pliku;
	plik.open(nazwa_pliku.c_str());
	
	if (plik.good())
	{
		printf("Podaj wierzcholek poczatkowy \n");
		cin >> start;
		plik >> Krawedzie;
		plik >> Wierzcholki;
		plik >> Start;
		_Graf = new Graf(Wierzcholki, Krawedzie, start);
		while (!plik.eof())
		{
			plik >> wierz_pocz;
			plik >> wierz_kon;
			plik >> waga;

			_Graf->dodaj_krawedz(wierz_pocz, wierz_kon, waga);
		}

	}
	else
	{
		printf("Niepoprawna nazwa pliku! \n");
	}
	plik.close();


}
void stworz_i_Wyswietl(){
	Graf *_Graf = NULL;
	double gestosc;
	int Wierzcholki;
	int Start;
	printf("Podaj liczbę wierzcholkow: \n");
	cin>>Wierzcholki;
	printf("Podaj gęstość w przedziale 0.1 - 1: \n");
	cin>>gestosc;
	printf("Podaj wierzcholek poczatkowy: \n");
	cin>>Start;
	int Krawedzie = ((Wierzcholki * (Wierzcholki - 1)) / 2) * gestosc;
	_Graf = new Graf(Wierzcholki, Krawedzie, Start);
	_Graf->WypelnijGraf(gestosc, _Graf);
	_Graf->wyswietl();
	_Graf->wyswietl_liste();
}

void generujPlikiDoTestow()
{
	int Krawedzie;
	int Wierzcholki;
	int Start;
	double gestosc;
	string nazwa_pliku;
	ofstream plik;
	int waga;
	srand(time(NULL));
	for (int j = PRZYROST; j <= MAKSIMUM; j = j + PRZYROST)
	{
		
		for (double i = 0.25; i <= 1; i = i + 0.25)
		{
			plik.open(to_string(i) + "_" + to_string(j) + ".txt");
			Wierzcholki = j;
			gestosc = i;
			Start = 0;
			int licznik=0;
			Krawedzie = ((Wierzcholki * (Wierzcholki - 1)) / 2) * gestosc;

			plik << Krawedzie << " " << Wierzcholki << " " << Start << endl;

			for (int i = 0; i < Wierzcholki; i++)
				for (int j = i; j < Wierzcholki; j++)
				{

					if (i != j && licznik < Krawedzie)
					{
						waga = rand() % 50 + 1;
						plik << i << " " << j << " " << waga << endl;
						plik << j << " " << i << " " << waga << endl;
						licznik++;
					}
				}

			plik.close();
		}
	}
}



void algorytmMacierz(Graf *_Graf){
	fstream dane_wyniku;
	dane_wyniku.open("WynikiTestow.txt", ios::app);
	int Krawedzie;
	int Wierzcholki;
	int Start;
	int wierz_poccz;
	int wierz_kon;
	int waga;
	string nazwa_pliku;
	ifstream plik;

	dane_wyniku << "Algorytm wykorzystujący macierz" << endl;
	for (int j = PRZYROST; j <= MAKSIMUM; j = j + PRZYROST)
	{
		for (double i = 0.25; i <= 1; i = i + 0.25)
		{
			plik.open(to_string(i) + "_" + to_string(j)+".txt");
			if (plik.good())
			{
				plik >> Krawedzie;
				plik >> Wierzcholki;
				plik >> Start;
				_Graf = new Graf(Wierzcholki, Krawedzie, Start);
				while (!plik.eof())
				{
					plik >> wierz_poccz;
					plik >> wierz_kon;
					plik >> waga;
					_Graf->dodaj_krawedz(wierz_poccz, wierz_kon, waga);
				}
			}
			else
			{
				printf("zla nazwa pliku \n");
			}
			plik.close();

					
			double suma = 0;
			for (int i = 0; i < PETLE; i++)
			{
				auto czasStart = std::chrono::high_resolution_clock::now();
				dane* tab = _Graf->Dijkstra_Macierz();
				auto czasStop = std::chrono::high_resolution_clock::now();
				suma += std::chrono::duration<double, std::milli>(czasStop - czasStart).count();
				_Graf->zapisz(tab);
			}
		dane_wyniku << to_string(i) + "_" + to_string(j)<< ";" << suma << ";" << suma / 100 << endl;
		}
	}
	dane_wyniku << endl;
	dane_wyniku.close();
}


void algorytmLista(Graf *_Graf){
	fstream dane_wyniku;
	dane_wyniku.open("WynikiTestow.txt", ios::app);
	int Krawedzie;
	int Wierzcholki;
	int Start;
	int wierz_poccz;
	int wierz_kon;
	int waga;
	string nazwa_pliku;
	ifstream plik;
	dane_wyniku << "Algorytm wykorzystujący listę" << endl;
	for (int j = PRZYROST; j <= MAKSIMUM; j = j + PRZYROST)
	{
		for (double i = 0.25; i <= 1; i = i + 0.25)
		{
			plik.open(to_string(i) + "_" + to_string(j) + ".txt");
			if (plik.good())
			{
			plik >> Krawedzie;
			plik >> Wierzcholki;
			plik >> Start;
			_Graf = new Graf(Wierzcholki, Krawedzie, Start);
			while (!plik.eof())
			{
				plik >> wierz_poccz;
				plik >> wierz_kon;
				plik >> waga;
				_Graf->dodaj_krawedz(wierz_poccz, wierz_kon, waga);
			}
		}
		else
		{
			printf("zla nazwa pliku \n");
		}
		plik.close();
		double suma = 0;
		for (int i = 0; i < PETLE; i++)
		{
			auto czasStart = std::chrono::high_resolution_clock::now();
			dane* tab = _Graf->Dijkstra_Lista();
			auto czasStop = std::chrono::high_resolution_clock::now();
			suma += std::chrono::duration<double, std::milli>(czasStop - czasStart).count();
			_Graf->zapisz(tab);
		}
		dane_wyniku << to_string(i) + "_" + to_string(j) << ";" << suma << ";" << suma / 100 << endl;
		}
	}
	dane_wyniku << endl;
	dane_wyniku.close();
}


void menu()
{
	char opcja;
	Graf *_Graf = NULL;
	while (1)
	{
		cout << endl << "S - Stworz graf i wyswietl go w konsoli" << endl;
		cout << "W - Wczytaj graf z pliku tekstowego, wyświetl go i zapisz wyniki" << endl;
		cout << "G - Generuj pliki do testow" << endl;
		cout << "M - Algorytm wykorzystujący macierz" << endl;
		cout << "L - Algorytm wykorzystujący listę" << endl;
		cout << "K - Koniec działania programu" << endl;
		cout << "podaj opcje" << endl;
		cin >> opcja;

		switch (opcja)
		{
		case 'S':
			stworz_i_Wyswietl();
			break;
		case 'K':
			cout << "Kończę działanie programu \n";
			return;
		case 'G':
			generujPlikiDoTestow();
			break;
		case 'W':
		{
			Wczytaj(_Graf);
			dane* tab = _Graf->Dijkstra_Macierz();			
			_Graf->zapisz(tab);
			_Graf->wyswietl();
			_Graf->wyswietl_liste();
		}
			break;
		case 'M':
			{
			algorytmMacierz(_Graf);
			break;
			}	
		case 'L':
			algorytmLista(_Graf);
			break;	
		}
	}
}
