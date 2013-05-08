#include <iostream>
#include <string>
#include <assert.h>

#include "ShellCommands.hpp"

void test_change_directory_should_failed(ShellCommands& cmd)
{
	std::cout << "Test: change directory should failed." << std::endl;
	std::cout << "before: " << *(cmd.pwd()) << std::endl;
	char* argv_cd[2];
	argv_cd[0] = strdup("../..");
	argv_cd[1] = NULL;
	assert(cmd.cd(argv_cd) == false);
	std::cout << "after: " << *(cmd.pwd()) << std::endl;
}

void test_change_directory_should_go_to_srcs_directory(ShellCommands& cmd)
{
	std::cout << "Test: change directory should go to parent directory." << std::endl;
	std::cout << "before: " << *(cmd.pwd()) << std::endl;
	char* argv_cd[2];
	argv_cd[0] = strdup("srcs");
	argv_cd[1] = NULL;
	assert(cmd.cd(argv_cd) == true);
	std::cout << "after: " << *(cmd.pwd()) << std::endl;
}

void test_change_directory_should_go_to_root_directory(ShellCommands& cmd)
{
	std::cout << "Test: change directory should go to root directory." << std::endl;
	std::cout << "before: " << *(cmd.pwd()) << std::endl;
	char* argv_cd[1];
	argv_cd[0] = NULL;
	assert(cmd.cd(argv_cd) == true);
	std::cout << "after: " << *(cmd.pwd()) << std::endl;
}

void test_list_directory_should_display_the_current_directory(ShellCommands& cmd)
{
	std::cout << "Test: list directory should display the current directory." << std::endl;
	char* argv_ls[3];
	argv_ls[0] = strdup("-l");
	argv_ls[1] = strdup("-a");
	argv_ls[2] = NULL;
	assert(cmd.ls(argv_ls) == true);
}

void test_copy_file_shoudl_not_be_copied(ShellCommands& cmd)
{
	std::cout << "Test: copy file shoudl not be copied." << std::endl;
	char* argv_cp[3];
	argv_cp[0] = strdup("../Software Project Training 2.zip");
	argv_cp[1] = strdup("./tests/test/Makefile");
	argv_cp[2] = NULL;
	assert(cmd.cp(argv_cp) == false);
}

void test_copy_file_shoudl_be_copied_and_replace_the_destination_file(ShellCommands& cmd)
{
	std::cout << "Test: copy file shoudl be copied and replace the destination file." << std::endl;
	char* argv_cp[3];
	argv_cp[0] = strdup("./main.cpp");
	argv_cp[1] = strdup("../tests/test/Makefile");
	argv_cp[2] = NULL;
	assert(cmd.cp(argv_cp) == true);
}

int main(/*char** argv, int argc, char** env*/)
{
	ShellCommands cmd("/Users/Romsi/Documents/Projects/BJTU/Software Project Training 3");
	test_change_directory_should_failed(cmd);
	test_list_directory_should_display_the_current_directory(cmd);
	test_change_directory_should_go_to_root_directory(cmd);
	test_change_directory_should_go_to_srcs_directory(cmd);
	test_list_directory_should_display_the_current_directory(cmd);
	test_copy_file_shoudl_not_be_copied(cmd);
	test_copy_file_shoudl_be_copied_and_replace_the_destination_file(cmd);
	return true;
}