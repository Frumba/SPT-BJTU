#ifndef _SHELL_COMMANDS_HPP_
# define _SHELL_COMMANDS_HPP_

# include <string>

class ShellCommands
{
	/*
	** Magic methods
	*/
public:
	ShellCommands(const char* a_root_path);
	~ShellCommands();
	/*
	** Methods call to perform a special action
	** before an event
	*/
private:
	//
	bool validate_path(const char* path);
	/*
	** Shell methods
	*/
public:
	// Change directory
	bool cd(char* const * argv);
	// List directory contents
	bool ls(char* const * argv);
	//
	std::string* pwd();
	//
	bool cp(char* const * argv);

	/*
	** Attributs
	*/
private: 
	const char* root_path_;

};

#endif // !_SHELL_COMMANDS_HPP_
