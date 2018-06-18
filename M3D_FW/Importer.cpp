#include "Importer.h"

#include <xutility>

m3dfw::Importer::Importer() : _data_sz(0)
{
}

m3dfw::Importer::~Importer()
{
}


bool m3dfw::Importer::loadFile(const std::string & path)
{
	std::ifstream stream(path, std::ios::binary);

	if (!stream.good())
		return false;

	freeData();

	_data_sz = getFileSize(stream);

	_data = new char[_data_sz];

	stream.read(_data, _data_sz);

	return true;
}

void m3dfw::Importer::freeData()
{
	if (_data_sz == 0)
		return;

	delete[] _data;

	_data_sz = 0;
}

unsigned int m3dfw::Importer::getFileSize(std::istream & stream)
{
	std::streampos cur_g = stream.tellg();

	stream.seekg(0, std::ios::end);

	unsigned int length = stream.tellg();

	stream.seekg(cur_g);

	return length;
}


unsigned int m3dfw::Importer::readCStr(unsigned int pos, char * target)
{
	unsigned int str_length = 0;
	while (_data[str_length + pos] != '\0')
		str_length++;

	target = new char[str_length + 1];

	std::copy(_data + pos, _data + pos + str_length + 1, target);

	return str_length + 1;
}

unsigned int m3dfw::Importer::readRange(unsigned int pos, unsigned int size, void * target)
{
	std::copy(_data + pos, _data + pos + size, (char *)target);

	return size;
}