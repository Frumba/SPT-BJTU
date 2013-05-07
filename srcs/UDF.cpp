#include "UDF.h"

UDF::UDF(const std::string & fileDir) :
_fileDir(fileDir), _file(fileDir.c_str(), std::ifstream::in),
_sectorOffset(0), _includingVolume(""), _recordingTime(""),
_fileSystemVersion(""), _totalSize(""), _freeSize("")
{
}

UDF::~UDF()
{
    if (this->_file)
        this->_file.close();
}

char *Unicodedecode(char *data, int len, char *target)
{
    int p = 1, i = 0;
    if ((data[0] == 8) || (data[0] == 16)) do
        {
            if (data[0] == 16) p++;  // ignore MSB of unicode16
            if (p < len)
            {
                target[i++] = data[p++];
            }
        } while (p < len);
    target[i] = '\0';
    return target;
}

bool            UDF::init()
{
    if (this->isUDF())
        return (this->fillDiskInfos());
    return (false);
}

void            UDF::fdisk()
{
    std::cout << this->_includingVolume << std::endl;
    std::cout << this->_recordingTime << std::endl;
    std::cout << this->_fileSystemVersion << std::endl;
    std::cout << this->_totalSize << std::endl;
    std::cout << this->_freeSize << std::endl;
}

bool            UDF::isUDF()
{
    bool            udf = false;
    char            ident[6];
    t_UDFStruct     info;

    this->goToSector(SN::VOLUME_RECOGNITION_STRUCTURES);

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
            else if (this->_sectorOffset == 256)
                break;
        }
    }
    return (udf);
}

bool            UDF::fillDiskInfos()
{
    t_UDFStruct     info;

    this->goToSector(SN::ANCHOR_VOLUME_DESCRIPTOR_POINTER);
    this->readNextSector(info.buffer);
    if (info.content.descriptorTag.tagIdentifier == 2)
    {
        bool    terDesc = false;
        //std::ofstream    outfile("plop.txt");

        this->goToSector(info.content.descriptors.avdp.mainVolumeDescriptorSequenceExtent.extentLocation);
        while (!terDesc)
        {
            t_Timestamp   *     t;
            char                buff[512];
            char *              b;

            this->readNextSector(info.buffer);
            t = &info.content.descriptors.pvd.recordingDateAndTime;
            switch (info.content.descriptorTag.tagIdentifier)
            {
                case TI::PRIMARY_VOLUME_DESCRIPTOR:
                    std::cout << "PRIMARY_VOLUME_DESCRIPTOR" << std::endl;
                    b = Unicodedecode(info.content.descriptors.pvd.volumeIdentifier, 32, buff);
                    this->_includingVolume = b;
                    std::cout << this->_includingVolume << std::endl;
                    sprintf(buff, "Recording Time: %d-%d-%d  %d:%d:%d",
                        (int) t->year, (int) t->day, (int) t->month, (int) t->hour,
                        (int) t->minute, (int) t->second);
                    this->_recordingTime = buff;
                    std::cout << this->_recordingTime << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::VOLUME_DESCRIPTOR_POINTER:
                    std::cout << "VOLUME_DESCRIPTOR_POINTER" << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::IMPLEMENTATION_USE_VOLUME_DESCRIPTOR:
                    std::cout << "IMPLEMENTATION_USE_VOLUME_DESCRIPTOR" << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::PARTITION_DESCRIPTOR:
                    std::cout << "PARTITION_DESCRIPTOR" << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::LOGICAL_VOLUME_DESCRIPTOR:
                    std::cout << "LOGICAL_VOLUME_DESCRIPTOR" << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::UNALLOCATED_SPACE_DESCRIPTOR:
                    std::cout << "UNALLOCATED_SPACE_DESCRIPTOR" << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::TERMINATING_DESCRIPTOR:
                    std::cout << "TERMINATING_DESCRIPTOR" << std::endl;
                    terDesc = true;
                    //outfile.write(info.buffer, SECTOR);
                    break;
                case TI::LOGICAL_VOLUME_INTEGRITY_DESCRIPTOR:
                    std::cout << "LOGICAL_VOLUME_INTEGRITY_DESCRIPTOR" << std::endl;
                    //outfile.write(info.buffer, SECTOR);
                    break;
            }
            if (this->_sectorOffset == 256)
                return (false);
        }
        //outfile.close();
        return (true);
    }
    return (false);
}

void            UDF::goToSector(int secNum)
{
    this->_file.seekg(secNum * SECTOR);
    this->_sectorOffset = secNum;
}

void            UDF::readNextSector(char * buff)
{
    this->_file.read(buff, SECTOR);
    this->_sectorOffset++;
}