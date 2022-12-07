#include "function.h"

int load_base(vector<immovables*> *_vec, ifstream & _file, int _count)
{
	int number = 0;
	string buffer;
	for (int i = 0; i < _count && !_file.eof(); i++)
	{
		int pos = _file.tellg();
		getline(_file, buffer);
		getline(_file, buffer);
		if (buffer == "Detached house") {
			_file.seekg(pos, ios_base::beg);
			detached_house* h = new detached_house;
			h->load_from_file(_file);
			_vec->push_back(h);
			number++;
		}
		else if (buffer == "Bungalo") {
			_file.seekg(pos, ios_base::beg);
			bungalo* h = new bungalo;
			h->load_from_file(_file);
			_vec->push_back(h);
			number++;
		}
		else if (buffer == "Villa") {
			_file.seekg(pos, ios_base::beg);
			villa* h = new villa;
			h->load_from_file(_file);
			_vec->push_back(h);
			number++;
		}
	}
	return number;
}

ifstream& find_description(ifstream& f, int id)
{
	string _id = to_string(id);
	string buffer;
	do
	{
		getline(f, buffer);
	} while (buffer != _id && !f.eof());
	return f;
}