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
	//villa v("Marocco", 400000, 230, 10, { "Garage", "Bowling", "Cinema", "Garden", "Wi-fi", "TVs", "Near sea" }, 2, 400, 2, 50);
	//villa vil("Marocco", 200000, 350, 8, { "Garage", "Cinema", "Barbeq", "Wi-fi", "TVs", "On hills" }, 2, 500, 2, 50);
	//bungalo b("Maldives", 100000, 50, 3, { "Bathroom", "Toilet", "WI-FI", "TV", "Outdoor kitchen" }, 150);
	//detached_house h3("Homel", 20000, 85, 4, { "TV", "WI-FI", "Barbeq", "Close to river" }, 2, 200);
	//villa v2("Barcelona", 300000, 250, 10, { "Garage", "Cinema", "Garden", "Wi-fi", "TVs", "PS5", "Near sea" }, 2, 500, 1, 40);
	//detached_house h2("Minsk", 40000, 60, 3, { "TV", "CCTV", "Wi-fi", "Dish washer" }, 1, 200);

	//ofstream f;
	//f.open(FILE_NAME, ios::app);
	//v.save_to_file(f);
	//b.save_to_file(f);
	//h3.save_to_file(f);
	//v2.save_to_file(f);
	//h2.save_to_file(f);
	//vil.save_to_file(f);
	//f.close();

	immovable_list l;
	l.logic();

	//main_menu m;
	//m.logic();
}