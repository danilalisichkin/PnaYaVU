#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <fstream>
#include "consoleGraphic.h"
#include "GUI.h"
#include "immovables.h"
using namespace std;

int main()
{
	detached_house h2("Minsk", 60000, 78, 4, { "TV, WI-FI, Boiler, Dishwasher, Central heating, Toilet, Bathroom" }, 1, 300);
	detached_house h1("Brest", 35000, 50, 2, { "Tv", "Dish washer", "Wi-fi" }, 1, 250);
	villa v("Costa Rica", 180000, 150, 6, { "Tv", "Bar", "Garden", "Wi-fi" }, 1, 1, 40);
	bungalo b("Taiti", 120000, 60, 4, { "Wash", "WI-FI", "TV", "Outdoor kitchen" }, 200);
	detached_house h3("Lida", 30000, 60, 2, { "Central heating", "TV", "WI-FI", "Barbeq" }, 1, 350);

	ofstream f;
	f.open(FILE_NAME, ios::app);
	h2.save_to_file(f);
	h1.save_to_file(f);
	v.save_to_file(f);
	b.save_to_file(f);
	h3.save_to_file(f);
	f.close();

	ifstream f2;
	f2.open(FILE_NAME, ios::in);
	string buffer;
	while (!f2.eof())
	{
		getline(f2, buffer);
		if (buffer == "Detached house") {
			detached_house h;
			h.load_from_file(f2);
			immovable_window2<detached_house> w(h);
			w.logic();
		}
		else if (buffer == "Bungalo") {
			bungalo h;
			h.load_from_file(f2);
			immovable_window2<bungalo> w(h);
			w.logic();
		}
		else if (buffer == "Villa") {
			villa h;
			h.load_from_file(f2);
			immovable_window2<villa> w(h);
			w.logic();
		}
	}
	f2.close();
	getchar();
}

void funct()
{

}