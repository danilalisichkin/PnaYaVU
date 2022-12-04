#pragma once
#include "immovables.h"

template <typename T>
bool isBelongs(T data, T left, T right)
{
	return (data >= left && data <= right);
}