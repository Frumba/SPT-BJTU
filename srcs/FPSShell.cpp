#include "FPSShell.h"

FPSShell::FPSShell() : _rootDir("")
{
}

FPSShell::~FPSShell()
{
}

bool            FPSShell::init()
{
    if ((this->_rootDir = Utilities::getExecResult("grep /dev/sr0 /etc/mtab | cut \"-d \" -f2")) != "")
        return (true);
    return (false);
}

void            FPSShell::run()
{
    if (chdir(this->_rootDir.c_str()) == -1)
        throw Exception("Changing directory has failed");
    // Add loop
}
