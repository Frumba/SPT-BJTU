#include "UDF.h"

UDF::UDF(const std::string & fileDir) :
_fileDir(fileDir), _file(fileDir.c_str(), std::ifstream::in),
_sectorOffset(0)
{
}

UDF::~UDF()
{
    if (this->_file)
        this->_file.close();
}

bool            UDF::init()
{
    bool            udf = false;
    char            ident[6];
    t_UDFStruct     info;

    this->goToSector(SecNumber::VOLUME_RECOGNITION_STRUCTURES);

    this->readNextSector(info.buffer);
    strncpy(ident, info.vrs.standardIdentifier, 5);
    ident[5] = '\0';
    if (!strcmp(ident, "BEA01"))
    {
        while (42)
        {
            this->readNextSector(info.buffer);
            strncpy(ident, info.vrs.standardIdentifier, 5);
            ident[5] = '\0';
            if (!strcmp(ident, "NSR02") || !strcmp(ident, "NSR03"))
                udf = true;
            else if (!strcmp(ident, "TEA01"))
                break;
        }
    }
    return (udf);
}

void            UDF::goToSector(int secNum)
{
    this->_file.seekg(secNum * SECTOR);
}

void            UDF::readNextSector(char * buff)
{
    this->_file.read(buff, SECTOR);
}