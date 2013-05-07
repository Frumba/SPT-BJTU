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
    if (this->isUDF())
    {
        t_UDFStruct     info;
        this->goToSector(SN::ANCHOR_VOLUME_DESCRIPTOR_POINTER);

        this->readNextSector(info.buffer);
        std::cout << "Identifier: " << info.content.descriptorTag.tagIdentifier << std::endl;
        if (info.content.descriptorTag.tagIdentifier == 2)
        {
            bool    terDesc = false;
            std::cout << "Extent location: " << info.content.descriptors.avdp.mainVolumeDescriptorSequenceExtent.extentLocation << std::endl;
            std::cout << "Extent length: " << info.content.descriptors.avdp.mainVolumeDescriptorSequenceExtent.extentLength << std::endl;
            this->goToSector(info.content.descriptors.avdp.mainVolumeDescriptorSequenceExtent.extentLocation);
            while (!terDesc)
            {
                this->readNextSector(info.buffer);
                switch (info.content.descriptorTag.tagIdentifier)
                {
                    case TI::PRIMARY_VOLUME_DESCRIPTOR:
                        std::cout << "PRIMARY_VOLUME_DESCRIPTOR" << std::endl;
                        break;
                    case TI::ANCHOR_VOLUME_DESCRIPTOR_POINTER:
                        std::cout << "ANCHOR_VOLUME_DESCRIPTOR_POINTER" << std::endl;
                        break;
                    case TI::VOLUME_DESCRIPTOR_POINTER:
                        std::cout << "VOLUME_DESCRIPTOR_POINTER" << std::endl;
                        break;
                    case TI::IMPLEMENTATION_USE_VOLUME_DESCRIPTOR:
                        std::cout << "IMPLEMENTATION_USE_VOLUME_DESCRIPTOR" << std::endl;
                        break;
                    case TI::PARTITION_DESCRIPTOR:
                        std::cout << "PARTITION_DESCRIPTOR" << std::endl;
                        break;
                    case TI::LOGICAL_VOLUME_DESCRIPTOR:
                        std::cout << "LOGICAL_VOLUME_DESCRIPTOR" << std::endl;
                        break;
                    case TI::UNALLOCATED_SPACE_DESCRIPTOR:
                        std::cout << "UNALLOCATED_SPACE_DESCRIPTOR" << std::endl;
                        break;
                    case TI::TERMINATING_DESCRIPTOR:
                        std::cout << "TERMINATING_DESCRIPTOR" << std::endl;
                        terDesc = true;
                        break;
                    case TI::LOGICAL_VOLUME_INTEGRITY_DESCRIPTOR:
                        std::cout << "LOGICAL_VOLUME_INTEGRITY_DESCRIPTOR" << std::endl;
                        break;
                }
                if (this->_sectorOffset == 256)
                    return (false);
            }
            return (true);
        }
    }
    return (false);
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