#ifndef _SHELL_COMMANDS_HPP_
# define _SHELL_COMMANDS_HPP_

class ShellCommands
{
	/*
	** Magic methods
	*/
public:
	ShellCommands();
	~ShellCommands();
	/*
	** Methods call to perform a special action
	** before an event
	*/
private:
	//
	bool before_exec();
	/*
	** Shell methods
	*/
public:
	// Change directory
	bool cd(const char* path);
	// List directory contents
	bool ls(const char* path);

	/*
	** Attributs
	*/
private:

};

#endif // !_SHELL_COMMANDS_HPP_