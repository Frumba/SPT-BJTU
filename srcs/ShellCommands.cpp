#include <iostream>
#include <fstream>
#include <unistd.h>

#include "unused.h"
#include "ShellCommands.hpp"

// Magic methods

/*
**
*/
ShellCommands::ShellCommands(const char* a_root_path)
: root_path_(a_root_path)
{
	;
}
/*
**
*/
ShellCommands::~ShellCommands()
{
	;
}

// Methods call to perform a special action before an event

/*
**
*/
bool ShellCommands::validate_path(const char* path)
{
	if (path == NULL)
		return false;
	char resolved_path[1024];
	if (realpath(path, resolved_path) == NULL)
		return false;
	if (strstr(resolved_path, root_path_) == NULL)
		return false;
	std::cout << resolved_path << std::endl;
	return true;
}

// Shell methods

/*
**
*/
bool ShellCommands::cd(char* const * argv)
{
	if (validate_path(argv[0]) == false) {
		std::cerr << "The path is incorrect." << std::endl;
		return false;
	}
	if (argv[0] == NULL)
		return false;
	return (chdir(argv[0]) == 0 ? true : false);
}
/*
**
*/
bool ShellCommands::ls(char* const * argv)
{
	switch(fork())
	{
		case -1: // error
			return false;
			break;
		case 0: // children process
			execv("/bin/ls", argv);
			break;
		default: // parent process
			break;
	}
	return true;
}
/*
**
*/
bool ShellCommands::pwd(char* const * UNUSED(argv))
{
	char buf[256];
	std::cout << getcwd(buf, sizeof(buf)) << std::endl;
	return true;
}
/*
**
*/
bool ShellCommands::cp(char* const * argv)
{
	if (argv[0] == NULL || argv[1] == NULL || argv[2] != NULL)
		return false;
	if (validate_path(argv[0]) == false) {
		std::cerr << "Your file is not find on the disk." << std::endl;
		return false;
	}
	std::ofstream dest;
	dest.open(argv[1], std::ios::in | std::ios::out | std::ios::trunc);
	if (!dest.is_open())
		return false;
	std::ifstream source;
	source.open(argv[0]);
	if (!source.is_open())
		return false;
	source.seekg (0, source.end);
    int length = source.tellg();
    source.seekg (0, source.beg);
	char* buffer = new char [length];
	source.read(buffer, length);
	dest << buffer;
	delete[] buffer;
	source.close();
	dest.close();
	return true;
}