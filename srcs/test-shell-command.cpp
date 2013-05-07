#include <string>

#include "ShellCommands.hpp"

int main(char** argv, int argc, char** env)
{
	ShellCommands cmd;
	const char* path = "..";
	cmd.cd(path);
	// cmd.ls(path);
	// cmd.dir(path);
	return true;
}