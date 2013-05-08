#ifndef UDFSTRUCTS_H
#define	UDFSTRUCTS_H

#include <stddef.h>

#define     SECTOR 2048

typedef     unsigned char   Uint8;
typedef     unsigned short  Uint16;
typedef     unsigned int    Uint32;

typedef     short           Int16;

namespace   SN
{
    enum        SectorsNumber
    {
        VOLUME_RECOGNITION_STRUCTURES = 16,
        ANCHOR_VOLUME_DESCRIPTOR_POINTER = 256
    } ;
}

namespace   TI
{
    enum        TagIdentifier
    {
        PRIMARY_VOLUME_DESCRIPTOR = 1,
        ANCHOR_VOLUME_DESCRIPTOR_POINTER,
        VOLUME_DESCRIPTOR_POINTER,
        IMPLEMENTATION_USE_VOLUME_DESCRIPTOR,
        PARTITION_DESCRIPTOR,
        LOGICAL_VOLUME_DESCRIPTOR,
        UNALLOCATED_SPACE_DESCRIPTOR,
        TERMINATING_DESCRIPTOR,
        LOGICAL_VOLUME_INTEGRITY_DESCRIPTOR
    } ;
}

typedef struct      s_VolumeRecognitionStructures
{
    Uint8           structureType;
    char            standardIdentifier[5];
    Uint8           structureVersion;
    Uint8           reserved;
    char            structureData[2040];
}                   t_VolumeRecognitionStructures;

typedef struct      s_Tag
{
    Uint16          tagIdentifier;
    Uint16          descriptorVersion;
    Uint8           tagChecksum;
    Uint8           reserved;
    Uint16          tagSerialNumber;
    Uint16          descriptorCRC;
    Uint16          descriptorCRCLength;
    Uint32          tagLocation;
}                   t_Tag;

typedef struct      s_CharSpec
{
    Uint8           characterSetType;
    char            characterSetInformation[63];
}                   t_CharSpec;

typedef struct      s_ExtentAd
{
    Uint32          extentLength;
    Uint32          extentLocation;
}                   t_ExtentAd;

typedef struct      s_Regid
{
    Uint8           flags;
    char            identifier[23];
    char            identifierSuffix[8];
}                   t_Regid;

typedef struct      s_Timestamp
{
    Uint16          typeAndTimeZone;
    Int16           year;
    Uint8           month;
    Uint8           day;
    Uint8           hour;
    Uint8           minute;
    Uint8           second;
    Uint8           centiSeconds;
    Uint8           hundredOfMicroSeconds;
    Uint8           microSeconds;
}                   t_Timestamp;

typedef struct      s_PrimaryVolumeDescriptor
{
    Uint32          volumeDescriptorSequenceNumber;
    Uint32          primaryVolumeDescriptorNumber;
    char            volumeIdentifier[32];
    Uint16          volumeSequenceNumber;
    Uint16          maximumVolumeSequenceNumber;
    Uint16          interchangeLevel;
    Uint16          maximumInterchangeLevel;
    Uint32          characterSetList;
    Uint32          maximumCharacterList;
    char            volumeSetIdentifier[128];
    t_CharSpec      descriptorCharacterSet;
    t_CharSpec      explanatoryCharacterSet;
    t_ExtentAd      volumeAbstract;
    t_ExtentAd      volumeCopyrightNotice;
    t_Regid         applicationIdentifier;
    t_Timestamp     recordingDateAndTime;
    t_Regid         implementationIdentifier;
    char            implementationUse[64];
    Uint32          predecessorVolumeDescriptorSequenceLocation;
    Uint16          flags;
    char            reserved[22];
}                   t_PrimaryVolumeDescriptor;

typedef struct      s_AnchorVolumeDescriptorPointer
{
    t_ExtentAd      mainVolumeDescriptorSequenceExtent;
    t_ExtentAd      reserveVolumeDescriptorSequenceExtent;
    char            reserved[480];
}                   t_AnchorVolumeDescriptorPointer;

typedef struct      s_VolumeDescriptorPointer
{
    Uint32          volumeDescriptorSequenceNumber;
    t_ExtentAd      nextVolumeDescriptorSequenceExtent;
    char            reserved[484];
}                   t_VolumeDescriptorPointer;

typedef struct      s_ImplementationUseVolumeDescriptor
{
    Uint32          volumeDescriptorSequenceNumber;
    t_Regid         implementationIdentifier;
    char            implementationUse[460];
}                   t_ImplementationUseVolumeDescriptor;

typedef struct      s_PartitionDescriptor
{
    Uint32          volumeDescriptorSequenceNumber;
    Uint16          partitionFlags;
    Uint16          partitionNumber;
    t_Regid         partitionContents;
    char            partitionContentsUse[128];
    Uint32          accessType;
    Uint32          partitionStartingLocation;
    Uint32          partitionLength;
    t_Regid         implementationIdentifier;
    char            implementationUse[128];
    char            reserved[156];
}                   t_PartitionDescriptor;

typedef struct      s_LogicalVolumeDescriptor
{
    Uint32          volumeDescriptorSequenceNumber;
    t_CharSpec      descriptorCharacterSet;
    char            logicalVolumeIdentifier[128];
    Uint32          logicalBlockSize;
    t_Regid         domainIdentifier;
    char            logicalVolumeContentsUse[16];
    Uint32          mapTableLength;
    Uint32          numberOfPartitionMaps;
    t_Regid         implementationIdentifier;
    char            implementationUse[128];
    t_ExtentAd      integritySequenceExtent;
    char            partitionMaps[];
}                   t_LogicalVolumeDescriptor;

typedef struct      s_UnallocatedSpaceDescriptor
{
    Uint32          volumeDescriptorSequenceNumber;
    Uint32          numberOfAllocationDescriptors;
    t_ExtentAd      allocationDescriptors[];
}                   t_UnallocatedSpaceDescriptor;

typedef struct      s_TerminatingDescriptor
{
    char            reserved[496];
}                   t_TerminatingDescriptor;

typedef struct      s_LogicalVolumeIntegrity
{
    t_Timestamp     recordingDateAndTime;
    Uint32          integrityType;
    t_ExtentAd      nextIntegrityExtent;
    char            logicalVolumeContentsUse[32];
    Uint32          numberOfPartitions;
    Uint32          lengthOfImplementationUse;
    Uint32          freeSpaceTable[];
    Uint32          sizeTable[];
    char            implementationUse;
}                   t_LogicalVolumeIntegrity;

typedef union       u_Descriptors
{
    t_PrimaryVolumeDescriptor           pvd;
    t_AnchorVolumeDescriptorPointer     avdp;
    t_VolumeDescriptorPointer           vdp;
    t_ImplementationUseVolumeDescriptor iuvd;
    t_PartitionDescriptor               pd;
    t_LogicalVolumeDescriptor           lvd;
    t_UnallocatedSpaceDescriptor        usd;
    t_TerminatingDescriptor             td;
    t_LogicalVolumeIntegrity            lvi;
}                   t_Descriptors;

typedef struct      s_Content
{
    t_Tag           descriptorTag;
    t_Descriptors   descriptors;
}                   t_Content;

typedef union       u_UDFStruct
{
    char                            buffer[SECTOR];

    t_VolumeRecognitionStructures   vrs;
    t_Content                       content;

}                   t_UDFStruct;

#endif	/* UDFSTRUCTS_H */

