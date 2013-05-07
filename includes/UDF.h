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
    void                fdisk();

private:
    bool                isUDF();
    bool                fillDiskInfos();
    
    void                goToSector(int);
    void                readNextSector(char *);
        
private:
    std::string         _fileDir;
    std::ifstream       _file;
    int                 _sectorOffset;
    
    // Disk infos
    std::string         _includingVolume;
    std::string         _recordingTime;
    std::string         _fileSystemVersion;
    std::string         _totalSize;
    std::string         _freeSize;
} ;

#endif	/* UDF_H */

