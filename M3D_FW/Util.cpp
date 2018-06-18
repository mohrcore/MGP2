#include "Util.h"

#include <SDL.h>


std::mutex _io_mutex; // cin/cout lock
//std::mutex _fstr_mutex; // fstream mutex


void m3dfw::outputCmd(const std::string & message)
{
	std::lock_guard<std::mutex> lock(_io_mutex);

	std::cout << message;

}

void m3dfw::fatalError(const std::string & message)
{
	outputCmd("[ FATAL ERROR ]: " + message);

	system("pause");

	SDL_Quit();

	exit(1);
}

bool m3dfw::fileToString(std::string & target, const std::string & path)
{
	std::string line;

	std::ifstream file(path);

	if (file.fail())
	{
		outputCmd("Error: Couldn't open file \"" + path + "\"");
		return false;
	}

	target.clear();

	while (std::getline(file, line))
		target += line + "\n";

	file.close();

	return true;
}

std::string m3dfw::getFilenameExtension(const std::string & filename)
{
	for (int i = filename.length() - 1; i >= 0; i--)
	{
		if (filename[i] == '.')
			return filename.substr(i + 1);
	}

	return "";
}

unsigned int m3dfw::getFileSize(std::istream & stream)
{
	stream.seekg(0, std::ios::beg);
	stream.ignore(std::numeric_limits<std::streamsize>::max());
	std::streamsize length = stream.gcount();
	stream.clear();
	stream.seekg(0, std::ios::beg);

	return length;
}

std::string m3dfw::getFileDir(const std::string & path)
{
	const char * last_slash = &path[0];

	for (const char * it = &path[0]; *it != '\0'; it++)
		if ((*it == '/') || (*it == '\\'))
			last_slash = it;

	return path.substr(0, last_slash - &path[0]);
}

void m3dfw::addSlashToDirIfMissing(std::string & dir)
{
	if (dir.empty())
		return;

	if ((dir[dir.length() - 1] != '/') || (dir[dir.length() - 1] != '/'))
		dir += '/';
}