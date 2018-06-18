#include "Util.h"

#include <iostream>

void fatalError(const std::string & message)
{
	std::cout << "\033[31;1m[FATAL ERROR] \033[37;1m" << message << std::endl << "The application will be terminated" << std::endl;

	system("pause");

	exit(-1);
}

void noteError(const std::string & message)
{
	std::cout << "\033[31;1m[ERROR]       \033[37;1m" << message << std::endl;
}