#ifndef FPSSHELL_H
#define	FPSSHELL_H

#include        <iostream>
#include        <unistd.h>
#include        <string.h>
#include        <map>

#include        "Exception.hpp"
#include        "Utilities.hpp"

#define         FILE_SYSTEM "/dev/sr0"

typedef void    (*FuncType)(char *const*);

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
    char        _line[256];
    char*       _token;
    std::map<std::string, FuncType> _Functions;
};

#endif	/* FPSSHELL_H */

