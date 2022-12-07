#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <fstream>

#define FILE_NAME "files/immovables.txt"
#define USERS_FILE "files/users.txt"
#define DESCRIPTION_FILE "files/descriptions.txt"
#define OBJECT_BORDER "====="

using namespace std;
template <class T> class immovable_window2;
template <class T> class more_info;

class immovables
{
	friend class immovable_list;
	friend void create_more_info(immovables* _ptr);
	template <class T> friend class more_info;
	template <class T> friend class immovable_window2;
protected:
	string *type;
	static int _id;
	unsigned int id;
	string *adress;
	unsigned int cost;
	unsigned int square;
	vector <string> *conveniences;
public:
	vector <string> virtual getPoles() = 0;
	int virtual calculate_meter_cost()
	{
		return cost / square;
	}
	immovables(string _adress = "Minsk", float _cost = 0, unsigned int _square = 0, vector <string> _conveniences = {})
	{
		adress = new string;
		*adress = _adress;
		cost = _cost;
		square = _square;
		conveniences = new vector <string>;
		*conveniences = _conveniences;
		id = _id++;
	}
	virtual ~immovables() {};
	void set_adress(string _adress)
	{
		*adress = _adress;
	}
	void set_cost(unsigned int _cost)
	{
		cost = _cost;
	}
	void set_square(unsigned int _square)
	{
		square = _square;
	}
	void set_conveniences(vector <string> _conveniences)
	{
		*conveniences = _conveniences;
	}
	void virtual save_to_file(ofstream& f) = 0;
	void virtual load_from_file(ifstream& f) = 0;
};

class home : public immovables
{
protected:
	unsigned int rooms;
public:
	home(string _adress = "Minsk", unsigned int _cost = 0, unsigned int _square = 0, unsigned int _rooms = 0, vector <string> _conveniences= {}) :
		immovables(_adress, _cost, _square, _conveniences)
	{
		rooms = _rooms;
	}
	virtual ~home() {};
	void set_rooms(unsigned int _rooms)
	{
		rooms = _rooms;
	}
};

class detached_house : public home
{
	template <class T> friend class immovable_window2;
protected:
	unsigned int floors;
	unsigned int yard_square;
public:
	vector <string> virtual getPoles()
	{
		vector <string> poles;
		string temp;

		poles.push_back(*type);

		temp = "Adress: ";
		temp.append(*adress);
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
	detached_house(string _adress = "Minsk", unsigned int _cost = 0, unsigned int _square = 0, unsigned int _rooms = 0,
		vector <string> _conveniences = {}, unsigned int _floors = 0, unsigned int _yard_square = 0) :
		home(_adress, _cost, _square, _rooms, _conveniences)
	{
		floors = _floors;
		yard_square = _yard_square;
		type = new string;
		*type = "Detached house";
	}
	detached_house(detached_house& _house)
	{
		adress = new string;
		conveniences = new vector<string>;
		type = new string;
		*adress = *_house.adress;
		cost = _house.cost;
		square = _house.square;
		rooms = _house.rooms;
		*conveniences = *_house.conveniences;
		floors = _house.floors;
		yard_square = _house.yard_square;
		*type = *_house.type;
	}
	detached_house(ifstream& f)
	{
		load_from_file(f);
	}
	~detached_house() {};
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
		f << id << '\n';
		f << *type << '\n';
		f << *adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(floors) << '\n';
		f << to_string(square) << '\n';
		f << to_string(yard_square) << '\n';
		for (int i = 0; i < conveniences->size(); i++)
			f << (*conveniences)[i] << '\n';
		f << OBJECT_BORDER << '\n';
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		getline(f, buffer);
		id = stoi(buffer);
		getline(f, *type);
		getline(f, *adress);
		getline(f, buffer);
		cost = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		floors = stoi(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		yard_square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences->push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences->pop_back();
	}
};

class villa : public detached_house
{
	template <class T> friend class immovable_window2;
protected:
	unsigned int pools;
	unsigned int pools_square;
public:
	vector <string> virtual getPoles()
	{
		vector <string> poles;
		string temp;

		poles.push_back(*type);

		temp = "Adress: ";
		temp.append(*adress);
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
	villa(string _adress = "Minsk", unsigned int _cost = 0, unsigned int _square = 0, unsigned int _rooms = 0,
		vector <string> _conveniences = {}, unsigned int _floors = 0, unsigned int _yard_square = 0,
		unsigned int _pools = 0, unsigned int _pools_square = 0) :
		detached_house(_adress, _cost, _square, _rooms, _conveniences, _floors, _yard_square)
	{
		pools = _pools;
		pools_square = _pools_square;
		*type = "Villa";
	}
	villa(ifstream& f)
	{
		load_from_file(f);
	}
	~villa() {};
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
		f << id << '\n';
		f << *type << '\n';
		f << *adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(floors) << '\n';
		f << to_string(pools) << '\n';
		f << to_string(square) << '\n';
		f << to_string(yard_square) << '\n';
		f << to_string(pools_square) << '\n';
		for (int i = 0; i < conveniences->size(); i++)
			f << (*conveniences)[i] << '\n';
		f << OBJECT_BORDER << '\n';
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		getline(f, buffer);
		id = stoi(buffer);
		getline(f, *type);
		getline(f, *adress);
		getline(f, buffer);
		cost = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		floors = stoi(buffer);
		getline(f, buffer);
		pools = stoi(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		yard_square = stoi(buffer);
		getline(f, buffer);
		pools_square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences->push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences->pop_back();
	}
};

class block_of_flats : public home
{
	template <class T> friend class immovable_window2;
protected:
public:
	block_of_flats(ifstream& f)
	{
		load_from_file(f);
	}
	~block_of_flats() {};
	void save_to_file(ofstream& f)
	{
		f << id << '\n';
		f << *type << '\n';
		f << *adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(square) << '\n';
		for (int i = 0; i < conveniences->size(); i++)
			f << (*conveniences)[i] << '\n';
		f << OBJECT_BORDER << '\n';
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		getline(f, buffer);
		id = stoi(buffer);
		getline(f, *type);
		getline(f, *adress);
		getline(f, buffer);
		cost = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences->push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences->pop_back();
	}
};

class bungalo : public detached_house
{
	template <class T> friend class immovable_window2;
protected:
public:
	vector <string> virtual getPoles()
	{
		vector <string> poles;
		string temp;

		poles.push_back(*type);

		temp = "Adress: ";
		temp.append(*adress);
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
	bungalo(string _adress = "Minsk", unsigned int _cost = 0, unsigned int _square = 0, unsigned int _rooms = 0,
		vector <string> _conveniences = {}, unsigned int _yard_square = 0) :
		detached_house(_adress, _cost, _square, _rooms, _conveniences, 1, _yard_square)
	{
		*type = "Bungalo";
	}
	bungalo(ifstream& f)
	{
		load_from_file(f);
	}
	~bungalo() {};
	void set_floors(unsigned int _floors) {};
	void save_to_file(ofstream& f)
	{
		f << id << '\n';
		f << *type << '\n';
		f << *adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(floors) << '\n';
		f << to_string(square) << '\n';
		f << to_string(yard_square) << '\n';
		for (int i = 0; i < conveniences->size(); i++)
			f << (*conveniences)[i] << '\n';
		f << OBJECT_BORDER << '\n';
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		getline(f, buffer);
		id = stoi(buffer);
		getline(f, *type);
		getline(f, *adress);
		getline(f, buffer);
		cost = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		floors = stoi(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		getline(f, buffer);
		yard_square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences->push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences->pop_back();
	}
};

class garage : protected immovables
{
	template <class T> friend class immovable_window2;
protected:
public:
	garage(string _adress, unsigned int _cost, unsigned int _square, unsigned int _rooms, vector <string> _conveniences) :
		immovables(_adress, _cost, _square, _conveniences)
	{
		*type = "Garage";
	};
	garage(ifstream& f)
	{
		load_from_file(f);
	}
	~garage() {};
	void save_to_file(ofstream& f)
	{
		f << id << '\n';
		f << *type << '\n';
		f << *adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(square) << '\n';
		for (int i = 0; i < conveniences->size(); i++)
			f << (*conveniences)[i] << '\n';
		f << OBJECT_BORDER << '\n';
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		getline(f, buffer);
		id = stoi(buffer);
		getline(f, *type);
		getline(f, *adress);
		getline(f, buffer);
		cost = stoi(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences->push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences->pop_back();
	}
};

class office : public immovables
{
	template <class T> friend class immovable_window2;
protected:
	unsigned int rooms;
public:
	office(string _adress = "Minsk", unsigned int _cost = 0, unsigned int _square = 0, unsigned int _rooms = 0, vector <string> _conveniences = {}) :
		immovables(_adress, _cost, _square, _conveniences)
	{
		rooms = _rooms;
		*type = "Office";
	}
	office(ifstream& f)
	{
		load_from_file(f);
	}
	~office() {};
	void set_rooms(unsigned int _rooms)
	{
		rooms = _rooms;
	}
	void save_to_file(ofstream &f)
	{
		f << id << '\n';
		f << *type << '\n';
		f << *adress << '\n';
		f << to_string(cost) << '\n';
		f << to_string(rooms) << '\n';
		f << to_string(square) << '\n';
		for (int i = 0; i < conveniences->size(); i++)
			f << (*conveniences)[i] << '\n';
		f << OBJECT_BORDER << '\n';
	}
	void load_from_file(ifstream& f)
	{
		string buffer;
		getline(f, buffer);
		id = stoi(buffer);
		getline(f, *type);
		getline(f, *adress);
		getline(f, buffer);
		cost = stoi(buffer);
		getline(f, buffer);
		rooms = stoi(buffer);
		getline(f, buffer);
		square = stoi(buffer);
		do
		{
			getline(f, buffer);
			conveniences->push_back(buffer);
		} while (buffer != OBJECT_BORDER);
		conveniences->pop_back();
	}
};