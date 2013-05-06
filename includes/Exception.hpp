#ifndef EXCEPTION_HPP
#define	EXCEPTION_HPP

#include		<exception>

class Exception : public std::exception
{
public:

    Exception(const std::string& sentence = "fail") throw () :
        _sentence(sentence)
    {
    }

    virtual ~Exception() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return (_sentence.c_str());
    }

private:
    std::string         _sentence;
};

#endif	/* EXCEPTION_HPP */

