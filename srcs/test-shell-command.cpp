#include <iostream>
#include <string>
#include <assert.h>

#include "ShellCommands.hpp"

void test_change_dire_should_failed(ShellCommands& cmd)
{
	std::cout << *(cmd.pwd()) << std::endl;
	char* argv_cd[2];
	argv_cd[0] = strdup("../..");
	argv_cd[1] = NULL;
	assert(cmd.cd(argv_cd) == false);
	std::cout << *(cmd.pwd()) << std::endl;
}

void test_change_dire_should_go_to_parent_directory(ShellCommands& cmd)
{
	std::cout << *(cmd.pwd()) << std::endl;
	char* argv_cd[2];
	argv_cd[0] = strdup("..");
	argv_cd[1] = NULL;
	assert(cmd.cd(argv_cd) == true);
	std::cout << *(cmd.pwd()) << std::endl;
}

void test_list_directory_should_display_the_current_directory(ShellCommands& cmd)
{
	char* argv_ls[2];
	argv_ls[0] = strdup("-l");
	argv_ls[1] = NULL;
	assert(cmd.ls(argv_ls) == true);
}

void test_copy_file_shoudl_not_be_copied(ShellCommands& cmd)
{
	char* argv_cp[3];
	argv_cp[0] = strdup("../Software Project Training 2.zip");
	argv_cp[1] = strdup("./tests/test/Makefile");
	argv_cp[2] = NULL;
	assert(cmd.cp(argv_cp) == false);
}

void test_copy_file_shoudl_be_copied_and_replace_the_destination_file(ShellCommands& cmd)
{
	char* argv_cp[3];
	argv_cp[0] = strdup("./Makefile");
	argv_cp[1] = strdup("./tests/test/Makefile");
	argv_cp[2] = NULL;
	assert(cmd.cp(argv_cp) == true);
}

int main(/*char** argv, int argc, char** env*/)
{
	ShellCommands cmd("/Users/Romsi/Documents/Projects/BJTU/Software Project Training 3");
	test_change_dire_should_failed(cmd);
	test_list_directory_should_display_the_current_directory(cmd);
	test_change_dire_should_go_to_parent_directory(cmd);
	test_list_directory_should_display_the_current_directory(cmd);
	test_copy_file_shoudl_not_be_copied(cmd);
	test_copy_file_shoudl_be_copied_and_replace_the_destination_file(cmd);
	return true;
}