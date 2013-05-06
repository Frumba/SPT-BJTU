#include        <exception>
#include        <iostream>

#include        "Exception.hpp"
#include        "Utilities.hpp"
#include        "FPSShell.h"

int main()
{
    if (!Utilities::checkExistingFile(FILE_SYSTEM))
        std::cerr << "There is no mounted disc" << std::endl;
    else
    {
        try
        {
            FPSShell    shell;

            if (shell.init())
                shell.run();
            else
                std::cerr << "The main root could not be determined" << std::endl;
        }
        catch (const Exception & e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::exception & e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
