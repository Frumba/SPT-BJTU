#ifndef UDF_H
#define	UDF_H

#include    <fstream>
#include    <iostream>
#include    <string.h>

#include    "UDFStructs.h"

class UDF
{
public:
    UDF(const std::string &);
    virtual ~UDF();

    bool                init();
    
private:
    bool                isUDF();
    
    void                goToSector(int);
    void                readNextSector(char *);
        
private:
    std::string         _fileDir;
    std::ifstream       _file;
    int                 _sectorOffset;
} ;

#endif	/* UDF_H */

