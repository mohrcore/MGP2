#pragma once

#include <string>

namespace mfile
{
	std::string getFilenameExtension(const std::string & filename);

	enum SubstrSearchResultMode
	{
		Beginning,
		End
	};

	int findSubStr(char * data, const char * target, SubstrSearchResultMode resultmode = Beginning);
	void copyCStr(const char * data, char * & target, unsigned int pos = 0, unsigned int length = 0);
	void copyCStr(const char * data, char * & target, unsigned int pos, char end_chr);

	bool compareCStr(const char * a, const char * b);

	unsigned int cStrLength(const char * cstr);
	unsigned int cStrSize(const char * cstr);

	template<typename T> const T & max(const T & a, const T & b);
	template<typename T> const T & min(const T & a, const T & b);
}



template<typename T> const T & mfile::max(const T & a, const T & b)
{
	if (a > b)
		return a;
	return b;
}

template<typename T> const T & mfile::min(const T & a, const T & b)
{
	if (a < b)
		return a;
	return b;
}