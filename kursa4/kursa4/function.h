#pragma once
#include "immovables.h"

template <typename T>
bool isBelongs(T data, T left, T right)
{
    return (data >= left && data <= right);
}

int load_base(vector<immovables*> *_vec, ifstream& _file, int _count);

ifstream& find_description(ifstream& f, int id);