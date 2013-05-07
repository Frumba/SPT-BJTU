#include <string>

#include "ShellCommands.hpp"

int main(/*char** argv, int argc, char** env*/)
{
	ShellCommands cmd("/Users/Romsi/Documents/Projects/BJTU/Software Project Training 3");
	
	cmd.pwd(NULL);
	char* argv_cd[2];
	argv_cd[0] = strdup("../..");
	argv_cd[1] = NULL;
	cmd.cd(argv_cd);
	cmd.pwd(NULL);
	
	char* argv_ls[2];
	argv_ls[0] = strdup("-l");
	argv_ls[1] = NULL;
	cmd.ls(argv_ls);

	char* argv_cp[3];
	argv_cp[0] = strdup("../../Software Project Training 2.zip");
	argv_cp[1] = strdup("./test/Makefile");
	argv_cp[2] = NULL;
	cmd.cp(argv_cp);
	return true;
}