#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>


#define M3DFW_CopyStructArrayMembersToMemberArr(S, M, C, T) for(unsigned int i = 0; i < (C); i++) (T)[i] = (S)[i].M;

namespace m3dfw
{
	void outputCmd(const std::string & message); //Use this instead of std::cout for thread safety

	void fatalError(const std::string & message);

	bool fileToString(std::string & target, const std::string & path);

	std::string getFilenameExtension(const std::string & filename);
	std::string getFileDir(const std::string & path);
	unsigned int getFileSize(std::istream & stream);
	void addSlashToDirIfMissing(std::string & dir);

	//template <typename T, typename M>
	//void copyStructArrayMembersToMemberArray(T * source, const M(memberget)(const T & src), unsigned int count, M * target);

	template <typename T>
	T intPow(T base, int exponent);

	template <typename T>
	T max(T a, T b);

	template <typename T>
	void removeDuplicatesInVector(std::vector<T> & vector);
}


// TEMPLATE IMPLEMENTATIONS! -----------------------------------------------------------------------------------------------------------------------------------------


template <typename T> T m3dfw::intPow(T base, int exponent)
{
	if (exponent < 0)
	{
		base = 1 / base;
		exponent = -exponent;
	}

	T result = 1;

	for (int i = 0; i < exponent; i++)
		result *= base;

	return result;
}

template <typename T> T m3dfw::max(T a, T b)
{
	if (a > b)
		return a;
	return b;
}

template <typename T>
void m3dfw::removeDuplicatesInVector(std::vector<T> & vector)
{
	//Remove all duplicates
	for (std::vector<T>::iterator it = vector.begin(); it != vector.end(); it++)
	{
		std::vector<T>::iterator it_cpy = it;

		it_cpy++;
		if (it_cpy == vector.end())
			break;

		while (it_cpy != vector.end())
		{
			if (*it == *it_cpy)
				it_cpy = vector.erase(it_cpy);
			else
				it_cpy++;
		}
	}
}