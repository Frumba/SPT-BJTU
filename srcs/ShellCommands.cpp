#include "ShellCommands.hpp"

// Magic methods

/*
**
*/
ShellCommands::ShellCommands()
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
bool ShellCommands::before_exec()
{
	return true;
}

// Shell methods

/*
**
*/
bool ShellCommands::cd(char* path)
{
	if (before_exec() == false)
		return false;

}
/*
**
*/
bool ShellCommands::ls(char* path)
{
	if (before_exec() == false)
		return false;
}