#ifndef UDFSTRUCTS_H
#define	UDFSTRUCTS_H

#define     SECTOR 2048

typedef    unsigned char Uint8;

namespace   SecNumber
{

    enum        SectorsNumber
    {
        VOLUME_RECOGNITION_STRUCTURES = 16
    } ;
}

namespace   SecNames
{

    enum        SectorsName
    {
        VOLUME_RECOGNITION_STRUCTURES
    } ;
}

typedef struct      s_VolumeRecognitionStructures
{
    Uint8           structureType;
    char            standardIdentifier[5];
    Uint8           structureVersion;
    Uint8           reserved;
    char            structureData[2040];
}           t_VolumeRecognitionStructures;

typedef union       s_UDFStruct
{
    char                                buffer[SECTOR];
    struct s_VolumeRecognitionStructures       vrs;
}                   t_UDFStruct;

#endif	/* UDFSTRUCTS_H */

