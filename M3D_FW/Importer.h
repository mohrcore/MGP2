#pragma once

#include <string>
#include <fstream>

namespace m3dfw
{
	class Importer
	{
	public:

		Importer();
		~Importer();

		bool loadFile(const std::string & path);
		//virtual unsigned int getRequiredSpace() = 0;
		virtual void importData(void * target) = 0;

	protected:

		void freeData();

		unsigned int getFileSize(std::istream & stream);

		unsigned int readCStr(unsigned int pos, char * target); //Return cstring size
		template <typename T>
		unsigned int readByte(unsigned int pos, T & target);
		template <typename T>
		unsigned int readWord(unsigned int pos, T & target);
		template <typename T>
		unsigned int readDWord(unsigned int pos, T & target);
		unsigned int readRange(unsigned int pos, unsigned int size, void * target);


		char * _data;
		unsigned int _data_sz;
	};
}


// TEMPLATE IMPLEMENTATIONS ----------------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
unsigned int m3dfw::Importer::readByte(unsigned int pos, T & target)
{
	target = _data[pos];

	return 1;
}

template <typename T>
unsigned int m3dfw::Importer::readWord(unsigned int pos, T & target)
{
	T res = 0x00;

	res |= 0x0F & _data[pos];
	res |= 0xF0 & _data[pos + 1];

	target = res;

	return 2;
}

template <typename T>
unsigned int m3dfw::Importer::readDWord(unsigned int pos, T & target)
{
	T res = 0x0000;

	res |= 0x000F & _data[pos];
	res |= 0x00F0 & _data[pos + 1];
	res |= 0x0F00 & _data[pos + 2];
	res |= 0xF000 & _data[pos + 3];

	target = res;

	return 4;
}