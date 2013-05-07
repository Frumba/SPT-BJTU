#ifndef FPSSHELL_H
#define	FPSSHELL_H

#include        <iostream>
#include        <unistd.h>

#include        "Exception.hpp"
#include        "Utilities.hpp"

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
};

#endif	/* FPSSHELL_H */
