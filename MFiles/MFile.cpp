#include "MFile.h"

#include "VERSION.h"
#include "Util.h"

#include <fstream>


mfile::MFile::MFile() : _good_flag(false)
{
}

mfile::MFile::MFile(const std::string & path)
{
	_good_flag = open(path);
}

mfile::MFile::~MFile()
{
}


bool mfile::MFile::good() const
{
	return _good_flag;
}

bool mfile::MFile::createAndOpen(const char * path, short header_version, const char * header)
{
	std::ofstream stream(path, std::ofstream::trunc);

	stream.write((const char *)&header_version, sizeof(short));

	stream << header;
	stream.write("\0", 1);

	stream.close();

	return open(path);
}

bool mfile::MFile::open(const std::string & path)
{
	_path = path;

	std::string ext = getFilenameExtension(path);

	if (ext != "mob" && ext != "msh" && ext != "mcm" && ext != "mmt")
	{
		_good_flag = false;
		return false;
	}

	loadData(path);

	char * cur = _data;

	char * header = nullptr;

	short header_version;

	cur += pReadType(cur, header_version);

	if (header_version != MFILE_FMT_HEADER_CURRENT_VERSION)
	{
		_good_flag = false;
		return false;
	}

	cur += pReadCStr(cur, header);

	_header_data.importHeader(header);
	
	if (!compareCStr(_header_data.version, MFILE_FMT_MODEL3D_CURRENT_VERSION_STR))
	{
		_good_flag = false;
		return false;
	}

	_body = cur;

	goBeginning();

	determineContentType();

	_good_flag = true;
}

bool mfile::MFile::save()
{
	return save(_path);
}

bool mfile::MFile::save(const std::string & path)
{
	std::ofstream stream(path, std::ofstream::binary | std::ofstream::trunc);

	if (!stream.good())
		return false;

	stream.write(_data, _data_sz);

	stream.close();
}

void mfile::MFile::resizeAbsolute(unsigned int size)
{
	char * old_data = _data;
	_data = new char[size];

	unsigned int sz_min = min(_data_sz, size);

	std::copy(old_data, old_data + sz_min, _data);

	_body = _data + (_body - old_data);

	delete old_data;

	_data_sz = size;

	goBeginning();
}

void mfile::MFile::resize(unsigned int body_size)
{
	resizeAbsolute(_body - _data + body_size);
}

unsigned int mfile::MFile::getFileSize(std::istream & stream) const
{
	std::streampos cur_g = stream.tellg();

	stream.seekg(0, std::ios::end);

	unsigned int length = stream.tellg();

	stream.seekg(cur_g);

	return length;
}

unsigned int mfile::MFile::pReadCStr(char * pos, char * & target) const
{
	unsigned int str_length = 0;
	while (pos[str_length] != '\0' && pos + str_length < _data + _data_sz)
		str_length++;

	target = new char[str_length + 1];

	std::copy(pos, pos + str_length + 1, target);

	return str_length + 1;
}

unsigned int mfile::MFile::pReadRange(char * pos, unsigned int size, void * target)
{
	char * cptr = (char *)target;

	std::copy(pos, pos + size, (char *)target);

	return size;
}

unsigned int mfile::MFile::pWriteCStr(char * pos, const char * data)
{
	unsigned int str_length = 0;
	while (data[str_length] != '\0' && pos + str_length < _data + _data_sz)
		str_length++;

	std::copy(data, data + str_length + 1, pos);

	return str_length + 1;
}

unsigned int mfile::MFile::pWriteRange(char * pos, unsigned int size, const void * data)
{
	std::copy((char *)data, (char *)data + size, pos);

	return size;
}

void mfile::MFile::freeData()
{
	if (_data_sz == 0)
		return;

	delete[] _data;

	_data_sz = 0;
}

bool mfile::MFile::loadData(const std::string & path)
{
	std::ifstream stream(path, std::ios::binary);

	if (!stream.good())
		return false;

	freeData();

	_data_sz = getFileSize(stream);

	_data = new char[_data_sz];

	stream.read(_data, _data_sz);

	stream.close();

	return true;
}

mfile::FileContent mfile::MFile::contentType()
{
	return _content_type;
}

void mfile::MFile::goBeginning()
{
	_cpos = 0;
}

void mfile::MFile::goEnd()
{
	_cpos = _data_sz - 1;
}

void mfile::MFile::goPos(unsigned int pos)
{
	_cpos = pos;
}

void mfile::MFile::readRange(void * target, unsigned int size)
{
	_cpos += pReadRange(_body + _cpos, size, target);
}

void mfile::MFile::readCStr(char * & target)
{
	_cpos += pReadCStr(_body + _cpos, target);
}

void mfile::MFile::writeRange(const void * data, unsigned int size)
{
	_cpos += pWriteRange(_body + _cpos, size, data);
}

void mfile::MFile::writeCStr(const char * data)
{
	_cpos += pWriteCStr(_body + _cpos, data);
}

bool mfile::MFile::eof() const
{
	return _body + _cpos >= _data + _data_sz;
}

template<>
unsigned int mfile::MFile::pReadType<char>(char * pos, char & target) const
{
	target = *pos;

	return 1;
}

template<>
unsigned int mfile::MFile::pWriteType<char>(char * pos, const char & data)
{
	*pos = data;
}

const mfile::MFileHeaderData & mfile::MFile::getHeaderData() const
{
	return _header_data;
}

void mfile::MFile::determineContentType()
{
	if (compareCStr(_header_data.type, MFILE_FMT_MODEL3D_CURRENT_VERSION_FILETYPE_MODEL_3D_STR))
		_content_type = MODEL_3D;
	else if (compareCStr(_header_data.type, MFILE_FMT_MODEL3D_CURRENT_VERSION_FILETYPE_COLLISION_MESH_STR))
		_content_type = COLLISION_MESH;
	else if (compareCStr(_header_data.type, MFILE_FMT_MODEL3D_CURRENT_VERSION_FILETYPE_SKELETAL_MESH_STR))
		_content_type = SKELETAL_MESH;
		
}

const std::string & mfile::MFile::getFilePath() const
{
	return _path;
}


mfile::MFileHeaderData::MFileHeaderData()
{
	version = new char[4]{ 'N', '/', 'A', '\0' };
	type = new char[4]{ 'N', '/', 'A', '\0' };
}

mfile::MFileHeaderData::MFileHeaderData(char * header)
{
	getHeaderParam(header, "fmt_ver", version);
	getHeaderParam(header, "type", type);
}

void mfile::MFileHeaderData::importHeader(char * header)
{
	delete[] version;
	delete[] type;

	getHeaderParam(header, "fmt_ver", version);
	getHeaderParam(header, "type", type);
}

mfile::MFileHeaderData::~MFileHeaderData()
{
	delete[] version;
	delete[] type;
}

void mfile::MFileHeaderData::getHeaderParam(char * header, const char * name, char * & target) const
{
	int par_pos = findSubStr(header, ("[" + std::string(name) + "]=\"").c_str(), End);
	if (par_pos == -1)
		target = new char[4]{ 'N', '/', 'A', '\0' };
	else
		copyCStr(header, target, par_pos, '\"');
}

