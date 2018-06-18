#pragma once

#include <string>
#include <vector>

void fatalError(const std::string & message);
void noteError(const std::string & message);

template <typename T>
unsigned int findIdInVector(const std::vector<T> & vec, const T & value);



template <typename T>
unsigned int findIdInVector(const std::vector<T> & vec, const T & value)
{
	for (unsigned int i = 0; i < vec.size(); i++)
		if (vec[i] == value)
			return i;
}