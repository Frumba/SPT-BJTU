#include <string.h>

#include "FPSShell.h"

FPSShell::FPSShell() : _rootDir("")
{
    //this->_Functions["cd"] = this->_cmd->cd);
    this->_Functions["dir"] = &ShellCommands::ls;
    //this->_Functions["fdisk"] = ;
    //this->_Functions["cp"] = &ShellCommands::cp;

}

FPSShell::~FPSShell()
{
}

bool            FPSShell::init()
{
    if ((this->_rootDir = Utilities::getExecResult("grep /dev/sr0 /etc/mtab | cut \"-d \" -f2")) != "")
    {
      this->_cmd = new ShellCommands(this->_rootDir.c_str());
      return (true);
    }
    return (false);
}

void            FPSShell::run()
{
    char*      argv[3];
    if (chdir(this->_rootDir.c_str()) == -1)
        throw Exception("Changing directory has failed");
    // Add loop
    while (1)
    {
        std::cout << "Root :" << this->_cmd->pwd(argv) << "> ";
        std::cin.getline(this->_line, 256);
        this->_token = strtok(this->_line, " ");
       // for (int i = 0; i < 3; ++i)
           // argv[i] = strtok(NULL, " ");
        
        //if (this->_Functions[this->_token])
          //    this->*_Functions[this->_token](argv);
        
        if (strcmp(this->_token, "exit") == 0)
        {  
            std::cout << "Bye :D" << std::endl;
            return;
        }
    }
}

