#include <string.h>

#include "FPSShell.h"

FPSShell::FPSShell() : _rootDir(""), _udf(NULL)
{

}

FPSShell::~FPSShell()
{
    if (this->_udf != NULL)
        delete this->_udf;
}

bool            FPSShell::init()
{
    if ((this->_rootDir = Utilities::getExecResult("grep /dev/sr0 /etc/mtab | cut \"-d \" -f2")) != "")
    {
        this->_udf = new UDF(FILE_SYSTEM);
        if (!this->_udf->init())
        {
            std::cerr << "The file your trying to read is not UDF type" << std::endl;
            return (false);
        }
        return (true);
    }
    return (false);
}

void            FPSShell::run()
{
    char*           argv[3];
    ShellCommands*   cmd;
    if (chdir(this->_rootDir.c_str()) == -1)
        throw Exception("Changing directory has failed");
    cmd = new ShellCommands(this->_rootDir.c_str());
    while (1)
    {
        std::cout << "Root :" << *(cmd->pwd()) << "> ";
        std::cin.getline(this->_line, 256);
        this->_token = strtok(this->_line, " ");
        for (int i = 0; i < 3; ++i)
             argv[i] = strtok(NULL, " ");

        if (strcmp(this->_token, "exit") == 0)
        {
            std::cout << "Bye :D" << std::endl;
            return;
        }
        else if (strcmp(this->_token, "cd") == 0)
          cmd->cd(argv);
        else if (strcmp(this->_token, "dir") == 0)
          cmd->ls(argv);
        else if (strcmp(this->_token, "cp") == 0)
          cmd->cp(argv);
        else
          std::cout << "Command not found" << std::endl;
    }
}

