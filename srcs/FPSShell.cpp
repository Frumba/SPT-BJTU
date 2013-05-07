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
    if (chdir(this->_rootDir.c_str()) == -1)
        throw Exception("Changing directory has failed");
    // Add loop
}
