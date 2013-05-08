#ifndef UTILITIES_HPP
#define	UTILITIES_HPP

#include        <fstream>
#include        <algorithm>
#include        <sstream>

#include        <stdio.h>

class Utilities
{
public:

    static bool checkExistingFile(const char * devPath)
    {
        std::ifstream   stream;

        stream.open(devPath, std::ifstream::in);
        if (stream.fail())
            return (false);
        stream.close();
        return (true);
    }

    static std::string removeCharactersFromString(std::string str,
        const std::string & chars)
    {
        for (unsigned int i = 0; i < chars.size(); ++i)
            str.erase (std::remove(str.begin(), str.end(), chars[i]), str.end());
        return (str);
    }

    static std::string getExecResult(const char * command)
    {
        FILE* pipe = popen(command, "r");
        if (!pipe)
            return "";
        char buffer[256];
        std::string result = "";
        while (!feof(pipe))
        {
            if (fgets(buffer, 256, pipe) != NULL)
                result += buffer;
        }
        pclose(pipe);
        result = Utilities::removeCharactersFromString(result, "\n");
        return result;
    }

    static std::string  shortToString(short val)
    {
        std::stringstream ss;
        ss << val;

        std::string s = ss.str();
        return (s);
    }

    static std::string      fromDec(int n, int base)
    {
        char        DIGITS[17] = {"0123456789ABCDEF"};
        std::string result;
        bool is_negative = n < 0;

        if (is_negative)
        {
            n = - n;
        }

        while (n != 0)
        {
            result = DIGITS[n % base] + result;
            n /= base;
        }

        if (is_negative)
        {
            result = '-' + result;
        }

        return result;
    }
} ;

#endif	/* UTILITIES_HPP */

