#ifndef FPSSHELL_H
#define	FPSSHELL_H

#include        <iostream>
#include        <unistd.h>
#include        <string.h>
#include        <map>

#include        "Exception.hpp"
#include        "Utilities.hpp"
#include        "UDF.h"
#include        "ShellCommands.hpp"

#define         FILE_SYSTEM "/dev/sr0"


class           FPSShell
{
public: // Functions
    FPSShell();
    virtual ~FPSShell();

    bool        init();
    void        run();
private: // Functions
    FPSShell(const FPSShell& orig);

private: // Members
    std::string _rootDir;
    UDF *       _udf;
    char        _line[256];
    char*       _token;
};

#endif	/* FPSSHELL_H */

