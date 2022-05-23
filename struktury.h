#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

struct dane {
	int dystans;
	bool odwiedzony;
}; 

struct Element {
	Element * nastepny;
	int wezel;
	int waga;
};