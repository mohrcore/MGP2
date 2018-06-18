#include "Util.h"

std::string mfile::getFilenameExtension(const std::string & filename)
{
	for (int i = filename.length() - 1; i >= 0; i--)
	{
		if (filename[i] == '.')
			return filename.substr(i + 1);
	}

	return "";
}

int mfile::findSubStr(char * data, const char * target, mfile::SubstrSearchResultMode resultmode)
{
	for (char * a = data; *a != '\0'; a++)
		for (const char * b = target; *b == *(a + (b - target)) || *b == '\0'; b++)
			if (*b == '\0')
				if (resultmode == Beginning)
					return a - data;
				else if (resultmode = End)
					return a - data + (b - target);

	return -1;
}

void mfile::copyCStr(const char * data, char * & target, unsigned int pos, unsigned int length)
{
	if (data == nullptr)
	{
		target = nullptr;
		return;
	}

	unsigned int str_length = 0;
	if (length > 0)
		str_length = length;
	else
		for (const char * chr = data + pos; *chr != '\0'; chr++)
			str_length++;

	target = new char[str_length + 1];

	std::copy(data + pos, data + pos + str_length + 1, target);

	target[str_length] = '\0';
}

void mfile::copyCStr(const char * data, char * & target, unsigned int pos, char end_chr)
{
	unsigned int str_length = 0;
	for (const char * chr = data + pos; *chr != '\0' && *chr != end_chr; chr++)
		str_length++;

	target = new char[str_length + 1];

	std::copy(data + pos, data + pos + str_length + 1, target);

	target[str_length] = '\0';
}

bool mfile::compareCStr(const char * a, const char * b)
{
	while (*a == *b)
	{
		if (*a == '\0')
			return true;
		a++;
		b++;
	}

	return false;
}

unsigned int mfile::cStrLength(const char * cstr)
{
	for (const char * it = cstr; true; it++)
		if (*it == '\0')
			return it - cstr;
}

unsigned int mfile::cStrSize(const char * cstr)
{
	return cStrLength(cstr) + 1;
}