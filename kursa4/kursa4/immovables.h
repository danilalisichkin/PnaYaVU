#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <fstream>

#define FILE_NAME "Immovables.txt"
#define USERS_FILE "Users.txt"
#define DESCRIPTION_FILE "Description.txt"
#define OBJECT_BORDER "====="

using namespace std;

template <class T> class immovable_window2;

class immovables
{
protected:
	static int _id;
	unsigned int id;
	string adress;
	float cost;
	unsigned int square;
	vector <string> conveniences;
	vector <string> virtual getPoles() = 0;
public:
	float virtual calculate_meter_cost()
	{
		return cost / square;
	}
	immovables(string _adress = "Minsk", float _cost = 0.0, unsigned int _square = 0.0, vector <string> _conveniences = {})
	{
		adress = _adress;
		cost = _cost;
		square = _square;
		conveniences = _conveniences;
		id = _id++;
	}
	void set_adress(string _adress)
	{
		adress = _adress;
	}
	void set_cost(float _cost)
	{
		cost = _cost;
	}
	void set_square(unsigned int _square)
	{
		square = _square;
	}
	void set_conveniences(vector <string> _conveniences)
	{
		conveniences = _conveniences;
	}
	void virtual save_to_file(ofstream& f) = 0;
	void virtual load_from_file(ifstream& f) = 0;
};

class home : public immovables
{
protected:
	unsigned int rooms;
public:
	home(string _adress = "Minsk", float _cost = 0.0, unsigned int _square = 0.0, unsigned int _rooms = 0, vector <string> _conveniences= {}) :
		immovables(_adress, _cost, _square, _conveniences)
	{
		rooms = _rooms;
	}
	void set_rooms(unsigned int _rooms)
	{
		rooms = _rooms;
	}
};

class detached_house : public home
{
	template <class T> friend class immovable_window2;
protected:
	const string type = "Detached house";
	unsigned int floors;
	unsigned int yard_square;
	vector <string> virtual getPoles()
	{
		vector <string> poles;
		string temp;
		
		poles.push_back(type);

		temp = "Adress: ";
		temp.append(adress);
		poles.push_back(temp);
		temp.clear();

		temp = "Living square: ";
		temp.append(to_string(square));
		poles.push_back(temp);
		temp.clear();

		temp = "Rooms: ";
		temp.append(to_string(rooms));
		poles.push_back(temp);
		temp.clear();

		temp = "Cost: ";
		temp.append(to_string(cost));
		temp.append("$");
		poles.push_back(temp);
		temp.clear();

		temp = "$/m2: ";
		temp.append(to_string(calculate_meter_cost()));
		temp.append("$");
		poles.push_back(temp);
		temp.clear();
		return poles;
	}
public:
	detached_house(string _adress = "Minsk", float _cost = 0.0, unsigned int _square = 0, unsigned int _rooms = 0,
		vector <string> _conveniences = {}, unsigned int _floors = 0, unsigned int _yard_square = 0) :
		home(_adress, _cost, _square, _rooms, _conveniences)
	{
		floors = _floors;
		yard_square = _yard_square;
	}
	detached_house(detached_house& _house)
	{
		adress = _house.adress;
		cost = _house.cost;
		square = _house.square;
		rooms = _house.rooms;
		conveniences = _house.conveniences;
		floors = _house.floors;
		yard_square = _house.yard_square;
	}
	void virtual set_floors(unsigned int _floors)
	{
		floors = _floors;
	}
	void set_yard_square(unsigned int _yard_square)
	{
		yard_square = _yard_square;
	}
	void save_to_file(ofstream& f)
	{
		//ofstream f;
		//f.open(FILE_NAME, ios::app);
		f << id << ''
		f << type << '\n';
		f << adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		f << to_string(floors) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(yard_square) << '\n';
		for (int i = 0; i < conveniences.size(); i++)
			f << conveniences[i] << '\n';
		f << OBJECT_BORDER << '\n';
		//f.close();
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		//ifstream f;
		//f.open(FILE_NAME, ios::in);
		//getline(f, buffer);
		//if (buffer != type)
		//	return;
		getline(f, adress);
		getline(f, buffer);
		cost = stof(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		floors = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		yard_square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences.push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences.pop_back();
	}
};

class villa : protected detached_house
{
	template <class T> friend class immovable_window2;
protected:
	const string type = "Villa";
	unsigned int pools;
	unsigned int pools_square;
	vector <string> virtual getPoles()
	{
		vector <string> poles;
		string temp;

		poles.push_back(type);

		temp = "Adress: ";
		temp.append(adress);
		poles.push_back(temp);
		temp.clear();

		temp = "Living square: ";
		temp.append(to_string(square));
		poles.push_back(temp);
		temp.clear();

		temp = "Rooms: ";
		temp.append(to_string(rooms));
		poles.push_back(temp);
		temp.clear();

		temp = "Pools: ";
		temp.append(to_string(pools));
		poles.push_back(temp);
		temp.clear();

		temp = "Pools square: ";
		temp.append(to_string(pools_square));
		poles.push_back(temp);
		temp.clear();

		temp = "Cost: ";
		temp.append(to_string(cost));
		temp.append("$");
		poles.push_back(temp);
		temp.clear();

		temp = "$/m2: ";
		temp.append(to_string(calculate_meter_cost()));
		temp.append("$");
		poles.push_back(temp);
		temp.clear();
		return poles;
	}
public:
	villa(string _adress = "Minsk", float _cost = 0.0, unsigned int _square = 0, unsigned int _rooms = 0,
		vector <string> _conveniences = {}, unsigned int _floors = 0, unsigned int _yard_square = 0,
		unsigned int _pools = 0, unsigned int _pools_square = 0) :
		detached_house(_adress, _cost, _square, _rooms, _conveniences, _floors, _yard_square)
	{
		pools = _pools;
		pools_square = _pools_square;
	}
	void set_pools(unsigned int _pools)
	{
		pools = _pools;
	}
	void set_pools_square(unsigned int _pools_square)
	{
		pools_square = _pools_square;
	}
	void save_to_file(ofstream& f)
	{
		//ofstream f;
		//f.open(FILE_NAME, ios::app);
		f << type << '\n';
		f << adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		f << to_string(yard_square) << '\n';
		f << to_string(floors) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(pools) << '\n';
		f << to_string(pools_square) << '\n';
		for (int i = 0; i < conveniences.size(); i++)
			f << conveniences[i] << '\n';
		f << OBJECT_BORDER << '\n';
		//f.close();
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		//ifstream f;
		//f.open(FILE_NAME, ios::in);
		//getline(f, buffer);
		//if (buffer != type)
		//	return;
		getline(f, adress);
		getline(f, buffer);
		cost = stof(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		yard_square = stoi(buffer);
		getline(f, buffer);
		floors = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		pools = stoi(buffer);
		getline(f, buffer);
		pools_square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences.push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences.pop_back();
	}
};

class block_of_flats : protected home
{
	template <class T> friend class immovable_window2;
protected:
	const string type = "Block of flats";
public:
	void save_to_file(ofstream& f)
	{
		//ofstream f;
		//f.open(FILE_NAME, ios::app);
		f << type << '\n';
		f << adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		f << to_string(rooms) << '\n';
		for (int i = 0; i < conveniences.size(); i++)
			f << conveniences[i] << '\n';
		f << OBJECT_BORDER << '\n';
		//f.close();
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		//ifstream f;
		//f.open(FILE_NAME, ios::in);
		//getline(f, buffer);
		//if (buffer != type)
		//	return;
		getline(f, adress);
		getline(f, buffer);
		cost = stof(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences.push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences.pop_back();
	}
};

class bungalo : protected detached_house
{
	template <class T> friend class immovable_window2;
protected:
	const string type = "Bungalo";
	vector <string> virtual getPoles()
	{
		vector <string> poles;
		string temp;

		poles.push_back(type);

		temp = "Adress: ";
		temp.append(adress);
		poles.push_back(temp);
		temp.clear();

		temp = "Living square: ";
		temp.append(to_string(square));
		poles.push_back(temp);
		temp.clear();

		temp = "Rooms: ";
		temp.append(to_string(rooms));
		poles.push_back(temp);
		temp.clear();

		temp = "Cost: ";
		temp.append(to_string(cost));
		temp.append("$");
		poles.push_back(temp);
		temp.clear();

		temp = "$/m2: ";
		temp.append(to_string(calculate_meter_cost()));
		temp.append("$");
		poles.push_back(temp);
		temp.clear();
		return poles;
	}
public:
	bungalo(string _adress = "Minsk", float _cost = 0, unsigned int _square = 0, unsigned int _rooms = 0,
		vector <string> _conveniences = {}, unsigned int _yard_square = 0) :
		detached_house(_adress, _cost, _square, _rooms, _conveniences, 1, _yard_square)
	{

	}
	void set_floors(unsigned int _floors) {};
	void save_to_file(ofstream& f)
	{
		//ofstream f;
		//f.open(FILE_NAME, ios::app);
		f << type << '\n';
		f << adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		f << to_string(yard_square) << '\n';
		f << to_string(floors) << '\n';
		f << to_string(rooms) << '\n';
		for (int i = 0; i < conveniences.size(); i++)
			f << conveniences[i] << '\n';
		f << OBJECT_BORDER << '\n';
		//f.close();
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		//ifstream f;
		//f.open(FILE_NAME, ios::in);
		//getline(f, buffer);
		//if (buffer != type)
		//	return;
		getline(f, adress);
		getline(f, buffer);
		cost = stof(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		yard_square = stoi(buffer);
		getline(f, buffer);
		floors = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences.push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences.pop_back();
	}
};

class garage : protected immovables
{
	template <class T> friend class immovable_window2;
protected:
	const string type = "Garage";
public:
	garage(string _adress, float _cost, unsigned int _square, unsigned int _rooms, vector <string> _conveniences) :
		immovables(_adress, _cost, _square, _conveniences) {};
	void save_to_file(ofstream& f)
	{
		//ofstream f;
		//f.open(FILE_NAME, ios::app);
		f << type << '\n';
		f << adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		for (int i = 0; i < conveniences.size(); i++)
			f << conveniences[i] << '\n';
		f << OBJECT_BORDER << '\n';
		//f.close();
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		//ifstream f;
		//f.open(FILE_NAME, ios::in);
		//getline(f, buffer);
		//if (buffer != type)
		//	return;
		getline(f, adress);
		getline(f, buffer);
		cost = stof(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences.push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences.pop_back();
	}
};

class office : protected immovables
{
	template <class T> friend class immovable_window2;
protected:
	const string type = "Office";
	unsigned int rooms;
public:
	office(string _adress = "Minsk", float _cost = 0.0, unsigned int _square = 0, unsigned int _rooms = 0, vector <string> _conveniences = {}) :
		immovables(_adress, _cost, _square, _conveniences)
	{
		rooms = _rooms;
	}
	void set_rooms(unsigned int _rooms)
	{
		rooms = _rooms;
	}
	void save_to_file(ofstream &f)
	{
		//ofstream f;
		//f.open(FILE_NAME, ios::app);
		f << type << '\n';
		f << adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		f << to_string(rooms) << '\n';
		for (int i = 0; i < conveniences.size(); i++)
			f << conveniences[i] << '\n';
		f << OBJECT_BORDER << '\n';
		//f.close();
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		//ifstream f;
		//f.open(FILE_NAME, ios::in);
		//getline(f, buffer);
		//if (buffer != type)
		//	return;
		getline(f, adress);
		getline(f, buffer);
		cost = stof(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences.push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences.pop_back();
	}
};