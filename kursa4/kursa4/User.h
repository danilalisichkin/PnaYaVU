#pragma once
#include "immovables.h"
using namespace std;

class User
{
protected:
	string id;
	string password;
	string phone_number;
	int *ownerships;
public:
	vector<immovables*>* getOwnerships()
	{
		vector<immovables*>* _vec = new vector<immovables*>;
		ifstream _file;
		_file.open(FILE_NAME, ios::in);
		string buffer;
		while (!_file.eof())
		{
			getline(_file, buffer);
			if (buffer == id) {
				getline(_file, buffer);
				if (buffer == "Detached house") {
					detached_house* h = new detached_house;
					h->load_from_file(_file);
					_vec->push_back(h);
				}
				else if (buffer == "Bungalo") {
					bungalo* h = new bungalo;
					h->load_from_file(_file);
					_vec->push_back(h);
				}
				else if (buffer == "Villa") {
					villa* h = new villa;
					h->load_from_file(_file);
					_vec->push_back(h);
				}
			}
		}
		return _vec;
	}
};

