#pragma once

#include <string>

namespace mfile
{
	enum FileContent
	{
		MODEL_3D,
		COLLISION_MESH,
		SKELETAL_MESH
	};

	class MFileHeaderData
	{
	public:

		MFileHeaderData();
		MFileHeaderData(char * header);
		~MFileHeaderData();

		void importHeader(char * header);

		char * type;
		char * version;

	private:

		void getHeaderParam(char * header, const char * name, char * & target) const;
	};

	class MFile
	{
	public:

		MFile();
		MFile(const std::string & path);
		~MFile();

		bool good() const;

		bool createAndOpen(const char * path, short header_version, const char * header);

		bool open(const std::string & path);
		bool save();
		bool save(const std::string & path);

		void resize(unsigned int body_size);
		void resizeAbsolute(unsigned int size);

		FileContent contentType();

		void goBeginning();
		void goEnd();
		void goPos(unsigned int pos);

		bool eof() const;

		template <typename T>
		void read(T & target);
		void readRange(void * target, unsigned int size);
		void readCStr(char * & target);

		template <typename T>
		void write(const T & data);
		void writeRange(const void * data, unsigned int size);
		void writeCStr(const char * data);

		const MFileHeaderData & getHeaderData() const;

		const std::string & getFilePath() const;

	private:

		bool loadData(const std::string & path);

		void freeData();

		void determineContentType();

		unsigned int getFileSize(std::istream & stream) const;

		template <typename T>
		unsigned int pReadType(char * pos, T & target) const;
		template<>
		unsigned int pReadType<char>(char * pos, char & target) const;
		//template <typename T>
		//unsigned int readWord(unsigned int pos, T & target);
		//template <typename T>
		//unsigned int readDWord(unsigned int pos, T & target);
		unsigned int pReadRange(char * pos, unsigned int size, void * target);
		unsigned int pReadCStr(char * pos, char * & target) const; //Returns cstring size

		template <typename T>
		unsigned int pWriteType(char * pos, const T & data);
		template<>
		unsigned int pWriteType<char>(char * pos, const char & data);
		unsigned int pWriteRange(char * pos, unsigned int size, const void * data);
		unsigned int pWriteCStr(char * pos, const char * data);

		char * _data;
		char * _body;

		unsigned int _cpos;

		unsigned int _data_sz;

		bool _good_flag;

		FileContent _content_type;

		MFileHeaderData _header_data;

		std::string _path;
	};
}


// TEMPLATE IMPLEMENTATIONS ----------------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
unsigned int mfile::MFile::pReadType(char * pos, T & target) const
{
	std::copy(pos, pos + sizeof(T), (char *)(&target));

	return sizeof(T);
}

template <typename T>
unsigned int mfile::MFile::pWriteType(char * pos, const T & data)
{
	std::copy((char *)&data, (char *)&data + sizeof(T), pos);

	return sizeof(T);
}

template <typename T>
void mfile::MFile::read(T & target)
{
	_cpos += pReadType<T>(_body + _cpos, target);
}

template <typename T>
void mfile::MFile::write(const T & data)
{
	_cpos += pWriteType<T>(_body + _cpos, data);
}

//template <typename T>
//unsigned int mfile::MFile::readWord(unsigned int pos, T & target)
//{
//	T * res_ptr = (T *)(_data + pos);
//
//	//res |= 0x0F & _data[pos];
//	//res |= 0xF0 & _data[pos + 1];
//
//	target = *res_ptr;
//
//	return 2;
//}
//
//template <typename T>
//unsigned int mfile::MFile::readDWord(unsigned int pos, T & target)
//{
//	T res_ptr = (T *)(_data + pos);
//
//	//res |= 0x000F & _data[pos];
//	//res |= 0x00F0 & _data[pos + 1];
//	//res |= 0x0F00 & _data[pos + 2];
//	//res |= 0xF000 & _data[pos + 3];
//
//	target = res;
//
//	return 4;
//}