// Test_XAVCWriter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char       BYTE;

typedef _Return_type_success_(return >= 0) long HRESULT;
#define S_OK    ((HRESULT)0L)
#define S_FALSE                                ((HRESULT)1L)

//
//keys.
//


const BYTE KEY_MXF_FILL_ITEM[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01, 0x02, 0x10, 0x01, 0x00, 0x00 , 0x00 };


const BYTE KEY_MXF_HAEDER_PARTITION_PACK[16] =
{ 0x06,0x0e,0x2b,0x34,0x02,0x05,0x01,0x01,0x0d,0x01,0x02,0x01,0x01,0x02,0x04,0x00 };
const BYTE KEY_MXF_FOOTER_PARTITION_PACK[16] =
{ 0x06,0x0e,0x2b,0x34,0x02,0x05,0x01,0x01,0x0d,0x01,0x02,0x01,0x01,0x04,0x04,0x00 };
const BYTE KEY_MXF_OPERATIONAL_PATTERN[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x02, 0x01, 0x01, 0x01, 0x09, 0x00 };


// for xavc
const BYTE KEY_MXF_Generic_Container_AVC[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0a, 0x0d, 0x01, 0x03, 0x01, 0x02, 0x10, 0x60, 0x01 };
const BYTE KEY_MXF_Frame_wrapped_AES3_audio_data[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x01, 0x0d, 0x01, 0x03,0x01, 0x02, 0x06, 0x03, 0x00 };
const BYTE KEY_MXF_Generic_Essence_Multiple_Mappings[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x03, 0x0d, 0x01, 0x03,0x01, 0x02, 0x7f, 0x01, 0x00 };
const BYTE KEY_MXF_ANC_Data_Mapping[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x09, 0x0d, 0x01, 0x03, 0x01, 0x02, 0x0e, 0x00, 0x00 };




const BYTE KEY_MXF_HEARDER_METADATA_PREFACE[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2f, 0x00 };

const BYTE KEY_MXF_METADATA_IDENTIFICATION[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x30, 0x00 };

const BYTE KEY_MXF_METADATA_CONTENTSTORAGE[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x18, 0x00 };

const BYTE KEY_MXF_METADATA_EssenceContainerData[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x23, 0x00 };

const BYTE KEY_MXF_METADATA_MaterialPackage[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x36, 0x00 };

const BYTE KEY_MXF_METADATA_SourcePackage[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x37, 0x00 };


const BYTE KEY_MXF_METADATA_TimelineTrack[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3b, 0x00 };


const BYTE KEY_MXF_METADATA_Seuence[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0f, 0x00 };


const BYTE KEY_MXF_METADATA_SourceClip[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x11, 0x00 };

const BYTE KEY_MXF_METADATA_TimecodeComponent[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x14, 0x00 };



const BYTE KEY_MXF_METADATA_CDCIEssenceDescriptor[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x28, 0x00 };



const BYTE KEY_MXF_METADATA_MultipleDescriptor[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x44, 0x00 };



const BYTE KEY_MXF_METADATA_AES3AudioEssenceDescriptor[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x47, 0x00 };


const BYTE KEY_MXF_METADATA_ANCPacketsDescriptor[16] =
{ 0x06, 0x0e, 0x2b, 0x34, 0x02, 0x53, 0x01, 0x01, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x5c, 0x00 };

const BYTE KEY_MXF_METADATA_Components[3][16] =
{
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x01,0x01,0x00,0x00,0x00 },//Timecode Component
};

enum EComponentDataDifinitionType
{
	keComponentDataDifinitionType_Timecode = 0,
	keComponentDataDifinitionType_Picture = 1,
	keComponentDataDifinitionType_Sound = 2,
	keComponentDataDifinitionType_Data = 10

};
const BYTE KEY_MXF_METADATA_Component_DataDifinitions[19][16] =
{
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x01,0x01,0x00,0x00,0x00 },//Timecode Track
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x01,0x00,0x00,0x00 },//Picture Essence Track
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },//Sound Essence Track
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x03,0x00,0x00,0x00 }, //Data Essence Track.

};



const BYTE KEY_MXF_METADATA_Component_DataDifinitions_16Audio_Track[19][16] =
{
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x01,0x01,0x00,0x00,0x00 },//Timecode Track
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x01,0x00,0x00,0x00 },//Picture Essence Track
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },//Sound Essence Track
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x02,0x00,0x00,0x00 },
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x01,0x03,0x02,0x02,0x03,0x00,0x00,0x00 } //Data Essence Track.
};



//Transfer Characteristic
const BYTE KEY_MXF_METADATA_CDCI_CaptureGamma[3][16] =
{
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x01,0x01,0x01,0x0b,0x00,0x00 },//ITU-R BT.2020 HLG
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x01,0x01,0x01,0x0a,0x00,0x00 },//ITU-R BT.2020 PQ


	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x04,0x01,0x01,0x01,0x01,0x02,0x00,0x00 }//ITU-R BT.709
};

//CodingEquation
const BYTE KEY_MXF_METADATA_CDCI_CodingEquation[2][16] =
{
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x01,0x01,0x02,0x06,0x00,0x00 },//ITU-R BT.2020 NCL
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x01,0x04,0x01,0x01,0x01,0x02,0x02,0x00,0x00 }//ITU-R BT.709
};


//ColorPrimaries
const BYTE KEY_MXF_METADATA_CDCI_ColorPrimaries[2][16] =
{
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x0d,0x04,0x01,0x01,0x01,0x03,0x04,0x00,0x00 },//ITU-R BT.2020
	{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x06,0x04,0x01,0x01,0x01,0x03,0x03,0x00,0x00 }//ITU-R BT.709
};


const BYTE KEY_MXF_METADATA_CDCI_PictureEssenceCoding[2][16] =
{
	{ 0x06, 0x0e, 0x2b, 0x34, 0x04, 0x01, 0x01, 0x0a, 0x04, 0x01, 0x02, 0x02, 0x01, 0x32, 0x30, 0x01 }
};


const BYTE KEY_MXF_METADATA_Sound_AES3EssenceCoding[2][16] =
{
	{ 0x06, 0x0E, 0x2B, 0x34, 0x04, 0x01, 0x01, 0x0A, 0x04, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00 }
};

const BYTE KEY_MXF_METADATA_Organizationally[16] =
{ 0x06,0x0e,0x2b,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x01,0x01,0x01,0x01,0x67,0x00 };


const BYTE KEY_MXF_METADATA_AVCSubDescriptor[16] =
{ 0x06,0x0e,0x2b,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x01,0x01,0x01,0x01,0x6e,0x00 };


const BYTE KEY_MXF_METADATA_IndexTableSegment[16] =
{ 0x06,0x0e,0x2b,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x02,0x01,0x01,0x10,0x01,0x00 };


const BYTE KEY_MXF_METADATA_SystemMetadataPack[16] =
{ 0x06,0x0E,0x2B,0x34,0x02,0x05,0x01,0x01,0x0D,0x01,0x03,0x01,0x04,0x01,0x01,0x00 };


const BYTE KEY_MXF_METADATA_PackageMetadataSet[16] =
{ 0x06,0x0E,0x2B,0x34,0x02,0x43,0x01,0x01,0x0D,0x01,0x03,0x01,0x04,0x01,0x02,0x01 };


const BYTE KEY_MXF_METADATA_GCEC_Label[16] =
{ 0x06,0x0e,0x2b,0x34,0x04,0x01,0x01,0x03,0x0d,0x01,0x03,0x01,0x02,0x7f,0x01,0x00 };


const BYTE KEY_MXF_METADATA_PackageMetadataSet_UMID[32] =
{ 0x06,0x0A,0x2B,0x34,0x01,0x01,0x01,0x05,0x01,0x01,0x0D,0x00,0x13,0x43,0xDB,0xB4,0xB4,0xDB,0x43,0xDE,0x50,0x0A,0x95,0x52,0xDB,0x43,0xDE,0x50,0x0A,0x95,0x52,0x01 };



const BYTE KEY_MXF_XAVC_VIDEO_FRAME[16] =
{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x15, 0x01, 0x05, 0x00 };

BYTE KEY_MXF_XAVC_16TRACK_AUDIO_SAMPLE[16][16] =
{
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x00 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x01 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x02 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x03 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x04 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x05 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x06 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x07 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x08 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x09 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x0a },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x0b },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x0c },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x0d },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x0e },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x10, 0x03, 0x0f }
};

const BYTE KEY_MXF_XAVC_8TRACK_AUDIO_SAMPLE[16][16] =
{
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x00 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x01 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x02 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x03 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x04 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x05 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x06 },
	{ 06, 0x0e, 0x2b, 0x34, 0x01, 0x02, 0x01, 0x01, 0x0d, 0x01, 0x03, 0x01, 0x16, 0x08, 0x03, 0x07 }
};


const BYTE KEY_MXF_VANC_container[16] =
{ 0x06,0x0e,0x2b,0x34,0x01,0x02,0x01,0x01,0x0d,0x01,0x03,0x01,0x17,0x01,0x02,0x01 };


const BYTE UUID_MXF_METADATA_AVCSubDescriptor[16] =
{ 0x06,0x0A,0x2B,0x34,0x2F,0x25,0x4D,0x10,0x92,0xFF,0x29,0xBD,0x00,0x10,0x00,0x00 };


const BYTE UUID_MXF_METADATA_IndexTableSegment[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0e,0x00,0x00 };


const BYTE UUID_MXF_METADATA_Organizationally[16] =
{ 0x43,0xFA,0x70,0x34,0xC0,0xD0,0x48,0x40,0xA6,0xDA,0x7A,0x5D,0xE7,0xA8,0xA2,0xD4 };


const BYTE UUID_MXF_METADATA_MultipleDescriptor_SubDescriptors[16] =
{ 0x43,0xfa,0x70,0x34,0xc0,0xd0,0x48,0x40,0xa6,0xda,0x7a,0x5d,0xe7,0xa8,0xa2,0xd4 };


const BYTE UUID_MXF_METADATA_CDCI_Maybe_SubDescriptors[16] =
{ 0x06,0x0A,0x2B,0x34,0x2F,0x25,0x4D,0x10,0x92,0xFF,0x29,0xBD,0x00,0x10,0x00,0x00 };


const BYTE IndexTableSegment_DeltaEntry[19][6] =
{
	{ 0x00,0x00,0x00,0x00,0x00,0x00 },//points the system item,be set to 0.
	{ 0x00,0x00,0x00,0x00,0x02,0x00 },//points picture item,implies the size of system item with fill item,should be set 0x0200.
	{ 0x00,0x00,0x00,0x13,0x3e,0x00 },//points lst sound item,imples the size of picture item with fill item,should be set 0x133e00
	{ 0x00,0x00,0x00,0x13,0x4a,0x00 },//0x133e00+0xC00
	{ 0x00,0x00,0x00,0x13,0x56,0x00 },//
	{ 0x00,0x00,0x00,0x13,0x62,0x00 },
	{ 0x00,0x00,0x00,0x13,0x6e,0x00 },
	{ 0x00,0x00,0x00,0x13,0x7a,0x00 },
	{ 0x00,0x00,0x00,0x13,0x86,0x00 },
	{ 0x00,0x00,0x00,0x13,0x92,0x00 },
	{ 0x00,0x00,0x00,0x13,0x9e,0x00 },//
	{ 0x00,0x00,0x00,0x13,0xaa,0x00 },
	{ 0x00,0x00,0x00,0x13,0xb6,0x00 },
	{ 0x00,0x00,0x00,0x13,0xc2,0x00 },
	{ 0x00,0x00,0x00,0x13,0xce,0x00 },
	{ 0x00,0x00,0x00,0x13,0xda,0x00 },
	{ 0x00,0x00,0x00,0x13,0xe6,0x00 },
	{ 0x00,0x00,0x00,0x13,0xf2,0x00 },
	{ 0x00,0x00,0x00,0x13,0xfe,0x00 }
};


const BYTE UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[18][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x00 },//CDCI Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x01 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x02 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x03 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x04 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x05 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x06 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x07 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x08 },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x09 }, //ANC Data Essence Descriptor/AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x0a },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x0b },//AES3 Audio Essence Descriptor
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x0c },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x0d },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x0e },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x0f },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x10 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0d,0x00,0x11 }//ANC Data Essence Descriptor/AES3 Audio Essence Descriptor
};


const BYTE UUID_MXF_METADATA_Source_Components[19][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x15,0xff,0xff },//Timecode Component
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x00 },//SourceClip picture
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x01 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x02 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x03 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x04 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x05 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x06 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x07 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x08 }, //SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x09 }, //SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x0a },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x0b },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x0c },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x0d },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x0e },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x0f },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x10 },//SourceClip audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x14,0x00,0x11 } //SourceClip audio

};



const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_INSTANCE[16] =
{ 0x06, 0x0a, 0x2b, 0x34, 0x2f, 0x25, 0x4d, 0x10, 0x92, 0xff, 0x29, 0xbd, 0x00, 0x0a, 0x00, 0x00 };//16


const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_Identification[16] =
{ 0x06, 0x0a, 0x2b, 0x34, 0x2f, 0x25, 0x4d, 0x10, 0x92, 0xff, 0x29, 0xbd, 0x00, 0x0b, 0x00, 0x00 };//16



const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_Identification_thisgeneration[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0b,0x00,0x01 };//16

const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_Identification_productuid[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0b,0x00,0x02 };//16

const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_contentstorage[16] =
{ 06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0c,0x00,0x00 };//16


const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_contentstorage_generationuid[16] =
{ 0x4c,0xbe,0xf5,0x55,0xc0,0x78,0x40,0x44,0xaa,0xaf,0x8f,0xd6,0x45,0xa7,0xa4,0xdb };//16


const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x01,0x00,0x00 };//16

BYTE UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_PackageUID[32] =
{ 0x06,0x0a,0x2b,0x34,0x01,0x01,0x01,0x05,0x01,0x01,0x0d,0x00,0x13,0x00,0x00,0x00,0xb4,0xdb,0x43,0xde,0x50,0x0a,0x95,0x52,0xdb,0x43,0xde,0x50,0x0a,0x95,0x52,0x21 };//32



const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x02,0x00,0x00 };//16

BYTE UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID[32] =
{ 0x06,0x0a,0x2b,0x34,0x01,0x01,0x01,0x05,0x01,0x01,0x0d,0x00,0x13,0x43,0xdb,0xb4,0xb4,0xdb,0x43,0xde,0x50,0x0a,0x95,0x52,0xdb,0x43,0xde,0x50,0x0a,0x95,0x52,0x21 };//32

const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_EssenceContainerData[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x0f,0x00,0x00 };//16

const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[19][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0xff,0xff },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x00 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x01 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x02 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x03 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x04 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x05 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x06 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x07 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x08 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x09 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x0a },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x0b },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x0c },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x0d },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x0e },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x0f },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x10 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x08,0x00,0x11 }
};
const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[19][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0xff,0xff },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x00 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x01 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x02 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x03 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x04 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x05 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x06 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x07 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x08 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x09 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x0a },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x0b },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x0c },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x0d },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x0e },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x0f },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x10 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x05,0x00,0x11 }
};


const BYTE UUID_MXF_METADATA_Material_Components[19][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x04,0xff,0xff },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x00 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x01 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x02 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x03 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x04 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x05 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x06 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x07 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x08 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x09 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x0a },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x0b },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x0c },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x0d },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x0e },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x0f },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x10 },
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x03,0x00,0x11 }

};

const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Tracks[19][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0xff,0xff },//timecode
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x00 },//picture
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x01 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x02 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x03 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x04 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x05 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x06 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x07 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x08 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x09 },//audio or anc(8audio track)
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x0a },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x0b },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x0c },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x0d },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x0e },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x0f },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x10 },//audio
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x19,0x00,0x11 }//audio or anc(16audio track)
};


const BYTE UUID_MXF_METADATA_SourcePackage_Descriptor[16] =
{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x06,0x00,0x00 };//16



const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[19][16] =
{
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0xff,0xff },//timecode sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x00 },//Picture sequence 
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x01 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x02 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x03 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x04 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x05 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x06 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x07 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x08 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x09 },//Sound sequence or anc sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x0a },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x0b },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x0c },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x0d },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x0e },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x0f },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x10 },//Sound sequence
	{ 0x06,0x0a,0x2b,0x34,0x2f,0x25,0x4d,0x10,0x92,0xff,0x29,0xbd,0x00,0x16,0x00,0x11 }//Sound sequence or anc sequence
};


const BYTE UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_SourcePackage_PackageUID[32] =
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };//32




const BYTE MXF_KEY_UMID_UNIVERAL_LABEL[16] =
{ 0x06, 0x0A, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };



//
// struct defines.
//
struct x_mxf_header_partition_pack_essencecontainers
{
	uint32_t count;
	uint32_t length;
	unsigned char **universallable;
};


struct x_mxf_header_partition_pack
{
	char key[16];
	int length;
	long long llposAtFile;
	uint16_t major_version;
	uint16_t minor_version;
	uint32_t kagsize;
	uint64_t thispartition;
	uint64_t previouspartition;
	uint64_t footerpartition;
	uint64_t headerbytecount;
	uint64_t indexbytecount;
	uint32_t indexsid;
	uint64_t bodyoffset;
	uint32_t bodysid;
	unsigned char operational_pattern[16];

	x_mxf_header_partition_pack_essencecontainers essencecontainers;
};


struct x_mxf_header_metadata
{
	int16_t tag;
	int16_t  length;
	unsigned char uid[16];
	unsigned char uid32[32];
	char *property;
	int32_t arraysize;
	int32_t arrayitemlength;
	unsigned char **arrayproperty;
	uint64_t _posAtFile;
	char description[100];
};


struct x_mxf_header_metadata_box
{
	unsigned char key[16];
	uint32_t length;
	long long llposAtFile;
	std::vector<x_mxf_header_metadata> propertys;
};


//
// fuctions.
//
void* memcpy_b2l(void*pDst, void*pSrc, size_t size)
{

	uint8_t *pD = (uint8_t *)pDst;
	uint8_t *pS = (uint8_t *)pSrc;

	for (size_t i = 0; i < size; i++)
	{
		pD[i] = pS[size - 1 - i];
	}

	return NULL;
}


void* memcpy_l2b(void*pDst, void*pSrc, size_t size)
{

	uint8_t *pD = (uint8_t *)pDst;
	uint8_t *pS = (uint8_t *)pSrc;

	for (int i = size - 1; i >= 0; i--)
	{
		pD[i] = pS[size - 1 - i];
	}

	return NULL;
}


//
// write file functions.
//


HRESULT _write_mxf_l2b(FILE *fp, void* data, int size)
{
	uint8_t big_end[8];
	uint8_t *pD = (uint8_t *)big_end;
	uint8_t *pS = (uint8_t *)data;

	for (int i = size - 1; i >= 0; i--)
	{
		pD[i] = pS[size - 1 - i];
	}

	int ret = fwrite(big_end, 1, size, fp);

	if (ret == size)
	{
		S_OK;
	}
	return S_FALSE;
}

HRESULT _write_mxf_key(FILE *fp, void* data)
{
	int ret = fwrite(data, 1, 16, fp);

	if (ret == 16)
	{
		S_OK;
	}
	return S_FALSE;
}

HRESULT _write_mxf_uuid(FILE *fp, void* data)
{
	int ret = fwrite(data, 1, 16, fp);

	if (ret == 16)
	{
		S_OK;
	}
	return S_FALSE;
}



HRESULT _write_mxf_tag(FILE *fp, void* data)
{

	int ret = fwrite(data, 1, 2, fp);

	if (ret == 2)
	{
		S_OK;
	}
	return S_FALSE;
}



HRESULT _write_mxf_direct(FILE *fp, void* data, int size)
{

	int ret = fwrite(data, 1, size, fp);

	if (ret == size)
	{
		S_OK;
	}
	return S_FALSE;
}





HRESULT _write_mxf_metadata_modify_length(FILE * fp, uint64_t  ui64LengthStartPosition, uint32_t length)
{
	x_mxf_header_metadata_box box;
	_fseeki64(fp, ui64LengthStartPosition, SEEK_SET);
	//cdciessencedescriptor->key
	//cdciessencedescriptor->length
	box.length = length;
	static int32_t length_4byte_big = 0;
	memcpy_l2b(&length_4byte_big, &box.length, 4);
	length_4byte_big = length_4byte_big | 0x83;
	fwrite(&length_4byte_big, 1, 4, fp);

	_fseeki64(fp, 0, SEEK_END);

	return S_OK;
}


HRESULT _write_mxf_metadata_modify_headerbytecount(FILE * fp, uint64_t Position, uint64_t headerbytecount)
{

	_fseeki64(fp, Position, SEEK_SET);
	_write_mxf_l2b(fp, &headerbytecount, 8);

	_fseeki64(fp, 0, SEEK_END);

	return S_OK;
}



HRESULT _write_mxf_metadata_date(FILE * fp, int16_t localtag, int16_t year, int8_t month, int8_t day, int8_t hour, int8_t minute, int8_t second, int8_t msecond, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata date;
	date.tag = localtag;

	date.length = 8;

	//year = year;
	//month = 8;
	//day = 7;
	//hour = 10;
	//minute = 43;
	//second = 3;
	//msecond = 0;
	_write_mxf_tag(fp, &date.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &date.length, 2);	ui64CurrentWritePosition += 2;

	_write_mxf_l2b(fp, &year, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &month, 1);	ui64CurrentWritePosition += 1;
	_write_mxf_l2b(fp, &day, 1);	ui64CurrentWritePosition += 1;
	_write_mxf_l2b(fp, &hour, 1);	ui64CurrentWritePosition += 1;
	_write_mxf_l2b(fp, &minute, 1);	ui64CurrentWritePosition += 1;
	_write_mxf_l2b(fp, &second, 1);	ui64CurrentWritePosition += 1;
	_write_mxf_l2b(fp, &msecond, 1); ui64CurrentWritePosition += 1;

	return S_OK;
}



HRESULT _write_mxf_property_array(FILE *fp, x_mxf_header_metadata &property, uint64_t &ui64CurrentWritePosition)
{
	_write_mxf_tag(fp, &property.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &property.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &property.arraysize, 4);	ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &property.arrayitemlength, 4);	ui64CurrentWritePosition += 4;
	for (int i = 0; i < property.arraysize; i++)
	{
		//if (property.arrayitemlength == 16)
		//{
		//	_write_mxf_uuid(fp, property.arrayproperty[i]); ui64CurrentWritePosition + property.arrayitemlength;
		//}
		//else
		{
			_write_mxf_direct(fp, property.arrayproperty[i], property.arrayitemlength); ui64CurrentWritePosition += property.arrayitemlength;
		}


	}

	return S_OK;

}



HRESULT _write_mxf_property_uuid(FILE *fp, x_mxf_header_metadata &property, uint64_t &ui64CurrentWritePosition)
{
	_write_mxf_tag(fp, &property.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &property.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_uuid(fp, property.property); ui64CurrentWritePosition += 16;

	return S_OK;

}


HRESULT _write_mxf_utf16string(FILE *fp, int tag, wchar_t * pwszString, uint64_t &ui64CurrentWritePosition)
{
	x_mxf_header_metadata stringdata;
	stringdata.tag = tag;//2

	stringdata.length = wcslen(pwszString) * 2;//2

	stringdata.property = new char[stringdata.length];

	char*pszString = (char*)pwszString;
	static char *tempUTF16String = new char[1024];
	for (int i = 0; i < stringdata.length; i++)
	{
		if (i % 2)
		{
			tempUTF16String[i] = pszString[i - 1];
		}
		else
		{
			tempUTF16String[i] = pszString[i + 1];
		}
	}

	_write_mxf_tag(fp, &stringdata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &stringdata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_direct(fp, tempUTF16String, stringdata.length);	ui64CurrentWritePosition += stringdata.length;


	return S_OK;
}



HRESULT _write_mxf_metadata_property_uint32_uint32(FILE * fp, int16_t localtag, uint32_t Value1, uint32_t Value2, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 8;//2
	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &Value1, 4); ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &Value2, 4); ui64CurrentWritePosition += 4;

	return S_OK;
}

HRESULT _write_mxf_metadata_property_uint32(FILE * fp, int16_t localtag, uint32_t Value, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 4;//2
	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &Value, 4); ui64CurrentWritePosition += 4;

	return S_OK;
}

HRESULT _write_mxf_metadata_property_int8(FILE * fp, int16_t localtag, uint32_t Value, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 1;//2
	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &Value, 1); ui64CurrentWritePosition += 1;

	return S_OK;
}

HRESULT _write_mxf_metadata_property_int16(FILE * fp, int16_t localtag, uint32_t Value, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 2;//2
	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &Value, 2); ui64CurrentWritePosition += 2;

	return S_OK;
}


HRESULT _write_mxf_metadata_property_int32(FILE * fp, int16_t localtag, int32_t Value, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 4;//2
	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &Value, 4); ui64CurrentWritePosition += 4;

	return S_OK;
}
HRESULT _write_mxf_metadata_property_uint64(FILE * fp, int16_t localtag, uint64_t Value, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 8;//2
	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &Value, 8); ui64CurrentWritePosition += 8;
	return S_OK;
}
HRESULT _write_mxf_metadata_property_uuid(FILE * fp, int16_t localtag, void* pUUID, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata metadata;
	metadata.tag = localtag;//2
	metadata.length = 16;//2
	memcpy(metadata.uid, pUUID, 16);


	_write_mxf_tag(fp, &metadata.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &metadata.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_uuid(fp, metadata.uid); ui64CurrentWritePosition += 16;

	return S_OK;
}


HRESULT _write_mxf_metadata_box(FILE * fp, void* pKey, uint32_t length, uint64_t & ui64CurrentWritePosition)
{

	x_mxf_header_metadata_box box;

	//cdciessencedescriptor->key
	memcpy(box.key, pKey, 16);
	fwrite(box.key, 1, 16, fp);	ui64CurrentWritePosition += 16;
	//cdciessencedescriptor->length
	box.length = length;
	static int32_t length_4byte_big = 0;
	memcpy_l2b(&length_4byte_big, &box.length, 4);
	length_4byte_big = length_4byte_big | 0x83;
	fwrite(&length_4byte_big, 1, 4, fp); ui64CurrentWritePosition += 4;

	return S_OK;
}

HRESULT _write_mxf_metadata_fill_box_and_fill_value(FILE * fp, void* pKey, uint32_t length, uint64_t & ui64CurrentWritePosition)
{


	_write_mxf_metadata_box(fp, pKey, length, ui64CurrentWritePosition);


	int8_t fill_value = 0;
	for (int i = 0; i < length; i++)
	{
		fwrite(&fill_value, 1, 1, fp);
	}
	ui64CurrentWritePosition += length;

	return S_OK;
}


void _write_mxf_header_partition_pack(FILE *fp, uint64_t & ui64CurrentWritePosition, uint64_t &ui64HeaderPartitionPack_footerpartition_pos, uint32_t &ui32headerbytecountPos)
{
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_HAEDER_PARTITION_PACK, 152, ui64CurrentWritePosition);
	x_mxf_header_partition_pack spartition_pack;
	// set value.
	spartition_pack.major_version = 1;
	spartition_pack.minor_version = 3;
	spartition_pack.kagsize = 512;
	spartition_pack.thispartition = 0;
	spartition_pack.previouspartition = 0;
	spartition_pack.footerpartition = 321550336;// this value,will be soon modify by turely.
	spartition_pack.headerbytecount = 13312;// this value,will be soon modify by turely.
	spartition_pack.indexbytecount = 512;
	spartition_pack.indexsid = 1;
	spartition_pack.bodyoffset = 0;
	spartition_pack.bodysid = 2;
	memcpy(spartition_pack.operational_pattern, KEY_MXF_OPERATIONAL_PATTERN, 16);
	spartition_pack.essencecontainers.count = 4;
	spartition_pack.essencecontainers.length = 16;
	spartition_pack.essencecontainers.universallable = new unsigned char *[spartition_pack.essencecontainers.count];
	spartition_pack.essencecontainers.universallable = new unsigned char *[spartition_pack.essencecontainers.count];

	for (int i = 0; i < spartition_pack.essencecontainers.count; i++)
	{
		spartition_pack.essencecontainers.universallable[i] = new unsigned char[spartition_pack.essencecontainers.length];
	}

	memcpy(spartition_pack.essencecontainers.universallable[0], KEY_MXF_Generic_Container_AVC, 16);
	memcpy(spartition_pack.essencecontainers.universallable[1], KEY_MXF_Frame_wrapped_AES3_audio_data, 16);
	memcpy(spartition_pack.essencecontainers.universallable[2], KEY_MXF_Generic_Essence_Multiple_Mappings, 16);
	memcpy(spartition_pack.essencecontainers.universallable[2], KEY_MXF_ANC_Data_Mapping, 16);



	//write to file.

	_write_mxf_l2b(fp, &spartition_pack.major_version, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &spartition_pack.minor_version, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &spartition_pack.kagsize, 4);	ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &spartition_pack.thispartition, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.previouspartition, 8);	ui64CurrentWritePosition += 8;

	ui64HeaderPartitionPack_footerpartition_pos = ui64CurrentWritePosition;

	_write_mxf_l2b(fp, &spartition_pack.footerpartition, 8);	ui64CurrentWritePosition += 8;

	ui32headerbytecountPos = ui64CurrentWritePosition;

	_write_mxf_l2b(fp, &spartition_pack.headerbytecount, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.indexbytecount, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.indexsid, 4);	ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &spartition_pack.bodyoffset, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.bodysid, 4);	ui64CurrentWritePosition += 4;

	fwrite(spartition_pack.operational_pattern, 1, 16, fp);	ui64CurrentWritePosition += 16;

	_write_mxf_l2b(fp, &spartition_pack.essencecontainers.count, 4);	ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &spartition_pack.essencecontainers.length, 4);	ui64CurrentWritePosition += 4;

	fwrite(KEY_MXF_Generic_Essence_Multiple_Mappings, 1, 16, fp);	ui64CurrentWritePosition += 16;
	fwrite(KEY_MXF_Generic_Container_AVC, 1, 16, fp);	ui64CurrentWritePosition += 16;
	fwrite(KEY_MXF_Frame_wrapped_AES3_audio_data, 1, 16, fp);	ui64CurrentWritePosition += 16;
	fwrite(KEY_MXF_ANC_Data_Mapping, 1, 16, fp);	ui64CurrentWritePosition += 16;


	uint64_t hearder_partition_fill_lengh = (512 - ui64CurrentWritePosition % 512 - 16 - 4);
	if (hearder_partition_fill_lengh < 0)
		hearder_partition_fill_lengh += 512;

	_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, hearder_partition_fill_lengh, ui64CurrentWritePosition);
};


void _write_mxf_header_metadate_primer_pack(FILE *fp, uint64_t & ui64CurrentWritePosition)
{

	//primer pack
	{

		FILE *fpPrimer = NULL;
		errno_t error = fopen_s(&fpPrimer, "XAVC_PRIMER.dat", "rb");
		if (error)
		{
			printf("Open Failed!");
		}

		_fseeki64(fpPrimer, 0, SEEK_SET);
		unsigned char *pszBufferRead = new unsigned char[2560];
		size_t readsize = fread_s(pszBufferRead, 2560, 1, 2560, fpPrimer);

		fclose(fpPrimer);

		fwrite(pszBufferRead, 1, 2560, fp); ui64CurrentWritePosition += 2560;
	}


};



void _write_mxf_header_metadate_preface(FILE *fp, uint64_t & ui64CurrentWritePosition)
{

	//preface

	_write_mxf_metadata_box(fp, (void*)KEY_MXF_HEARDER_METADATA_PREFACE, 194, ui64CurrentWritePosition);
	//preface->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_INSTANCE, ui64CurrentWritePosition);
	//preface->lastmodifydate
	_write_mxf_metadata_date(fp, 0x023b, 2018, 7, 31, 3, 18, 35, 0, ui64CurrentWritePosition);
	//preface->version
	x_mxf_header_metadata sversion;
	sversion.tag = 0x053b;
	sversion.length = 2;
	int16_t sversion_value = 0x0301;
	_write_mxf_tag(fp, &sversion.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &sversion.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_direct(fp, &sversion_value, 2); ui64CurrentWritePosition += 2;

	//preface->identifications
	x_mxf_header_metadata sidentifications;
	sidentifications.tag = 0x063b;
	sidentifications.length = 24;//0x18  //2
	sidentifications.arraysize = 1;//4 
	sidentifications.arrayitemlength = 16;//4 
	sidentifications.arrayproperty = new unsigned char *[sidentifications.arraysize];
	sidentifications.arrayproperty[0] = new unsigned char[sidentifications.arrayitemlength];
	memcpy(sidentifications.arrayproperty[0], UUID_MXF_HAEDER_METADATA_PREFACE_Identification, 16);
	_write_mxf_property_array(fp, sidentifications, ui64CurrentWritePosition);
	//preface->contentstorage
	_write_mxf_metadata_property_uuid(fp, 0x033b, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_contentstorage, ui64CurrentWritePosition);
	//preface->operationalpattern;
	_write_mxf_metadata_property_uuid(fp, 0x093b, (void*)KEY_MXF_OPERATIONAL_PATTERN, ui64CurrentWritePosition);
	//preface->essencecontainers;
	x_mxf_header_metadata essencecontainers;
	essencecontainers.tag = 0x0a3b;
	essencecontainers.length = 72;//2
	essencecontainers.arraysize = 4;
	essencecontainers.arrayitemlength = 16;
	essencecontainers.arrayproperty = new unsigned char*[essencecontainers.arraysize];

	for (int i = 0; i < essencecontainers.arraysize; i++)
	{
		essencecontainers.arrayproperty[i] = new unsigned char[essencecontainers.arrayitemlength];
	}
	memcpy(essencecontainers.arrayproperty[0], KEY_MXF_Generic_Essence_Multiple_Mappings, essencecontainers.arrayitemlength);
	memcpy(essencecontainers.arrayproperty[1], KEY_MXF_Generic_Container_AVC, essencecontainers.arrayitemlength);
	memcpy(essencecontainers.arrayproperty[2], KEY_MXF_Frame_wrapped_AES3_audio_data, essencecontainers.arrayitemlength);
	memcpy(essencecontainers.arrayproperty[3], KEY_MXF_ANC_Data_Mapping, essencecontainers.arrayitemlength);

	_write_mxf_property_array(fp, essencecontainers, ui64CurrentWritePosition);

	x_mxf_header_metadata dm_schemes;
	dm_schemes.tag = 0x0b3b;
	dm_schemes.length = 8;
	dm_schemes.arraysize = 0;
	dm_schemes.arrayitemlength = 0;
	_write_mxf_property_array(fp, dm_schemes, ui64CurrentWritePosition);


};

void _write_mxf_header_metadate_identification(FILE *fp, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata_box  identification;

	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_IDENTIFICATION, 194, ui64CurrentWritePosition);

	int32_t ui32Identification_length_pos = ui64CurrentWritePosition - 4;
	//identification->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_Identification, ui64CurrentWritePosition);

	//identification->thisgenerationuid
	_write_mxf_metadata_property_uuid(fp, 0x093c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_Identification_thisgeneration, ui64CurrentWritePosition);

	//identification->companyname
	x_mxf_header_metadata scompanyname;
	scompanyname.tag = 0x013c;//2

							  //_write_mxf_utf16string(fp, scompanyname.tag, L"Jetsen", ui64CurrentWritePosition);
	_write_mxf_utf16string(fp, scompanyname.tag, L"CDV", ui64CurrentWritePosition);

	x_mxf_header_metadata sproductname;
	sproductname.tag = 0x023c;//2
							  //_write_mxf_utf16string(fp, sproductname.tag, L"MXF OP1a Muxer", ui64CurrentWritePosition);
	_write_mxf_utf16string(fp, sproductname.tag, L"CreaStudio", ui64CurrentWritePosition);

	//identification->versionstring
	x_mxf_header_metadata sversionstring;

	sversionstring.tag = 0x043c;//2
								//_write_mxf_utf16string(fp, sversionstring.tag, L"write by bay,complie at Jul 27 2018", ui64CurrentWritePosition);
	_write_mxf_utf16string(fp, sversionstring.tag, L"3.0", ui64CurrentWritePosition);

	//identification->productuid
	_write_mxf_metadata_property_uuid(fp, 0x053c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_Identification_productuid, ui64CurrentWritePosition);

	//identification->modificationdate
	_write_mxf_metadata_date(fp, 0x063c, 2018, 7, 31, 3, 18, 35, 0, ui64CurrentWritePosition);


	_write_mxf_metadata_modify_length(fp, ui32Identification_length_pos, ui64CurrentWritePosition - ui32Identification_length_pos - 4);
};
void _write_mxf_header_metadate_contentstorage(FILE *fp, uint64_t & ui64CurrentWritePosition)
{

	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_CONTENTSTORAGE, 92, ui64CurrentWritePosition);

	uint32_t ui32contentstoragestart_length_pos = ui64CurrentWritePosition - 4;


	//contentstorage->instanceuid;
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_contentstorage, ui64CurrentWritePosition);

	//contentstorage->packages;
	x_mxf_header_metadata contentstorage_packages;
	contentstorage_packages.tag = 0x0119;
	contentstorage_packages.length = 40;
	contentstorage_packages.arraysize = 2;
	contentstorage_packages.arrayitemlength = 16;

	contentstorage_packages.arrayproperty = new unsigned char*[contentstorage_packages.arraysize];

	for (int i = 0; i < contentstorage_packages.arraysize; i++)
	{
		contentstorage_packages.arrayproperty[i] = new unsigned char[contentstorage_packages.arrayitemlength];
	}
	memcpy(contentstorage_packages.arrayproperty[0], UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage, contentstorage_packages.arrayitemlength);
	memcpy(contentstorage_packages.arrayproperty[1], UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage, contentstorage_packages.arrayitemlength);

	_write_mxf_property_array(fp, contentstorage_packages, ui64CurrentWritePosition);


	//contentstorage->essencecontainerdata
	x_mxf_header_metadata contentstorage_essencecontainerdata;
	contentstorage_essencecontainerdata.tag = 0x0219;
	contentstorage_essencecontainerdata.length = 24;
	contentstorage_essencecontainerdata.arraysize = 1;
	contentstorage_essencecontainerdata.arrayitemlength = 16;
	contentstorage_essencecontainerdata.arrayproperty = new unsigned char*[contentstorage_essencecontainerdata.arraysize];

	for (int i = 0; i < contentstorage_essencecontainerdata.arraysize; i++)
	{
		contentstorage_essencecontainerdata.arrayproperty[i] = new unsigned char[contentstorage_essencecontainerdata.arrayitemlength];
	}
	memcpy(contentstorage_essencecontainerdata.arrayproperty[0], UUID_MXF_HAEDER_METADATA_PREFACE_EssenceContainerData, contentstorage_essencecontainerdata.arrayitemlength);


	_write_mxf_property_array(fp, contentstorage_essencecontainerdata, ui64CurrentWritePosition);


	_write_mxf_metadata_modify_length(fp, ui32contentstoragestart_length_pos, ui64CurrentWritePosition - ui32contentstoragestart_length_pos - 4);


};


HRESULT _write_mxf_metadata_property_umid(FILE * fp, int16_t localtag, void* pUMID, uint64_t & ui64CurrentWritePosition)
{
	x_mxf_header_metadata umid;
	umid.tag = localtag;//2
	umid.length = 32;//2


	memcpy(umid.uid32, pUMID, 32);

	_write_mxf_tag(fp, &umid.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &umid.length, 2);	ui64CurrentWritePosition += 2;

	_write_mxf_direct(fp, umid.uid32, 32); ui64CurrentWritePosition += 32;

	return S_OK;
}




HRESULT _write_mxf_timelinetrack(FILE *fp, void*InstanceUID, uint32_t trackID, uint32_t trackNumber, uint32_t EditRateX, uint32_t EditRateY, uint64_t Origin, void *sequenceUID, uint64_t & ui64CurrentWritePosition)
{
	//header metadate 
	//TimelineTrack
	//
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_TimelineTrack, 80, ui64CurrentWritePosition);

	//TimelineTrack->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, InstanceUID, ui64CurrentWritePosition);

	//TimelineTrack->trackid
	uint32_t ui32TrackID = trackID;
	_write_mxf_metadata_property_uint32(fp, 0x0148, ui32TrackID, ui64CurrentWritePosition);

	//TimelineTrack->tracknumber
	uint32_t ui32TrackNumber = trackNumber;
	_write_mxf_metadata_property_uint32(fp, 0x0448, trackNumber, ui64CurrentWritePosition);

	//TimelineTrack->editrate
	uint32_t ui32EditRateX = EditRateX;
	uint32_t ui32EditRateY = EditRateY;
	_write_mxf_metadata_property_uint32_uint32(fp, 0x014b, EditRateX, EditRateY, ui64CurrentWritePosition);

	//TimelineTrack->origin
	uint64_t ui32Origin = Origin;
	_write_mxf_metadata_property_uint64(fp, 0x024b, ui32Origin, ui64CurrentWritePosition);

	//TimelineTrack->sequence
	_write_mxf_metadata_property_uuid(fp, 0x0348, sequenceUID, ui64CurrentWritePosition);

	return S_OK;
}



HRESULT _write_mxf_sequence(FILE *fp, void*InstanceUID, void*DataDefinition, uint64_t Duration, void *Component, uint64_t & ui64CurrentWritePosition)
{
	//header metadate 
	//Sequence
	//
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_Seuence, 80, ui64CurrentWritePosition);

	//Sequence->instanceuid

	_write_mxf_metadata_property_uuid(fp, 0x0a3c, InstanceUID, ui64CurrentWritePosition);

	////Sequence->DataDefinition
	_write_mxf_metadata_property_uuid(fp, 0x0102, DataDefinition, ui64CurrentWritePosition);


	//Sequence->Duration
	_write_mxf_metadata_property_uint64(fp, 0x0202, Duration, ui64CurrentWritePosition);

	//Sequence->Structural Components
	x_mxf_header_metadata sequence_components;
	sequence_components.tag = 0x0110;
	sequence_components.length = 24;
	sequence_components.arraysize = 1;
	sequence_components.arrayitemlength = 16;

	sequence_components.arrayproperty = new unsigned char*[sequence_components.arraysize];

	for (int i = 0; i < sequence_components.arraysize; i++)//for seuence arraysize always equal 1.
	{
		sequence_components.arrayproperty[i] = new unsigned char[sequence_components.arrayitemlength];
		memcpy(sequence_components.arrayproperty[i], Component, sequence_components.arrayitemlength);

	}

	_write_mxf_property_array(fp, sequence_components, ui64CurrentWritePosition);


	return S_OK;
}


HRESULT _write_mxf_TimecodeComponent(FILE *fp, void*InstanceUID, void*DataDefinition, uint64_t Duration, uint64_t StartTimecode, uint16_t RoundedTimecodeBase, uint8_t DropFrame, uint64_t &ui64CurrentWritePosition)
{
	//header metadate 
	//TimecodeComponent
	//
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_TimecodeComponent, 75, ui64CurrentWritePosition);

	//TimecodeComponent->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, InstanceUID, ui64CurrentWritePosition);

	//TimecodeComponent>DataDefinition
	_write_mxf_metadata_property_uuid(fp, 0x0102, DataDefinition, ui64CurrentWritePosition);

	//TimecodeComponent->Duration
	_write_mxf_metadata_property_uint64(fp, 0x0202, Duration, ui64CurrentWritePosition);

	//TimecodeComponent->StartTimecode
	_write_mxf_metadata_property_uint64(fp, 0x0115, StartTimecode, ui64CurrentWritePosition);

	//TimecodeComponent->RoundedTimecodeBase
	_write_mxf_metadata_property_int16(fp, 0x0215, RoundedTimecodeBase, ui64CurrentWritePosition);


	//TimecodeComponent->DropFrame
	_write_mxf_metadata_property_int8(fp, 0x0315, DropFrame, ui64CurrentWritePosition);


	return S_OK;
}


HRESULT _write_mxf_SourceClip(FILE *fp, void*InstanceUID, void*DataDefinition, uint64_t Duration, void* SourcePackageID, uint32_t SourceTrackID, uint64_t StartPosition, uint64_t &ui64CurrentWritePosition)
{
	//header metadate 
	//sourceclip
	//
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_SourceClip, 108, ui64CurrentWritePosition);

	//sourceclip->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, InstanceUID, ui64CurrentWritePosition);

	//sourceclip->DataDefinition
	_write_mxf_metadata_property_uuid(fp, 0x0102, DataDefinition, ui64CurrentWritePosition);

	//sourceclip->Duration
	_write_mxf_metadata_property_uint64(fp, 0x0202, Duration, ui64CurrentWritePosition);


	//sourceclip->StartPosition
	_write_mxf_metadata_property_uint64(fp, 0x0112, StartPosition, ui64CurrentWritePosition);


	//sourceclip->SourcePackageID
	_write_mxf_metadata_property_umid(fp, 0x0111, SourcePackageID, ui64CurrentWritePosition);

	//sourceclip->SourceTrackID
	//_write_mxf_metadata_property_uint32(fp, 0x0211, SourceTrackID<<8, ui64CurrentWritePosition);
	_write_mxf_metadata_property_uint32(fp, 0x0211, SourceTrackID, ui64CurrentWritePosition);

	return S_OK;
}




void _write_mxf_header_metadate_materialpackage(FILE *fp, uint64_t & ui64CurrentWritePosition, int nAudioChannelCount, uint64_t ui64Duration, uint64_t ui64StartTimecode)
{
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_MaterialPackage, 268, ui64CurrentWritePosition);

	uint32_t ui32MaterialPackage_lenght_pos = ui64CurrentWritePosition - 4;

	//materialpackage->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage, ui64CurrentWritePosition);


	//materialpackage->package
	_write_mxf_metadata_property_umid(fp, 0x0144, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_PackageUID, ui64CurrentWritePosition);


	//materialpackage->creation date
	_write_mxf_metadata_date(fp, 0x0544, 2018, 7, 31, 3, 18, 35, 0, ui64CurrentWritePosition);

	//materialpackage->modified date
	_write_mxf_metadata_date(fp, 0x0444, 2018, 7, 31, 3, 18, 35, 0, ui64CurrentWritePosition);


	//materialpackage->tracks
	x_mxf_header_metadata materialpackage_tracks;
	materialpackage_tracks.tag = 0x0344;
	materialpackage_tracks.arraysize = nAudioChannelCount + 3;
	materialpackage_tracks.arrayitemlength = 16;

	materialpackage_tracks.length = materialpackage_tracks.arraysize*materialpackage_tracks.arrayitemlength + 8;

	materialpackage_tracks.arrayproperty = new unsigned char*[materialpackage_tracks.arraysize];

	for (int i = 0; i < materialpackage_tracks.arraysize; i++)
	{
		materialpackage_tracks.arrayproperty[i] = new unsigned char[materialpackage_tracks.arrayitemlength];
		memcpy(materialpackage_tracks.arrayproperty[i], UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[i], materialpackage_tracks.arrayitemlength);
	}

	_write_mxf_property_array(fp, materialpackage_tracks, ui64CurrentWritePosition);


	_write_mxf_metadata_modify_length(fp, ui32MaterialPackage_lenght_pos, ui64CurrentWritePosition - ui32MaterialPackage_lenght_pos - 4);




	//enum EComponentDataDifinitionType
	//{
	//	keComponentDataDifinitionType_Timecode = 0,
	//	keComponentDataDifinitionType_Picture = 1,
	//	keComponentDataDifinitionType_Sound = 2,
	//	keComponentDataDifinitionType_Data = 10

	//};


	//timecode 
	int nTrackID = 0;
	int nTrackIndex = 0;
	nTrackID = nTrackIndex + 1;

	//track.
	_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[nTrackIndex], nTrackID, 0, 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

	//Squence
	_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Timecode], ui64Duration, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], ui64CurrentWritePosition);

	//Timecode Component
	_write_mxf_TimecodeComponent(fp, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Timecode], ui64Duration, 0, 50, 0, ui64CurrentWritePosition);

	//picture
	nTrackIndex++;
	nTrackID++;
	_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[nTrackIndex], nTrackID, 0, 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

	//Squence
	_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Picture], ui64Duration, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], ui64CurrentWritePosition);

	//SourceClip Component
	_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Picture], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, nTrackID, 0, ui64CurrentWritePosition);

	//aes3
	for (int i = 0; i < nAudioChannelCount; i++)
	{
		nTrackIndex++;
		nTrackID++;
		_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[nTrackIndex], nTrackID, 0, 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

		//Squence
		_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Sound], ui64Duration, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], ui64CurrentWritePosition);

		//SourceClip Component
		_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Sound], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, nTrackID, 0, ui64CurrentWritePosition);
	}

	//anc
	nTrackIndex++;
	nTrackID++;
	_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[nTrackIndex], nTrackID, 0, 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

	//Squence
	_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Data], ui64Duration, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], ui64CurrentWritePosition);

	//SourceClip Component
	_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Material_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Data], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, nTrackID, 0, ui64CurrentWritePosition);


	//if (nAudioChannelCount == 16)
	//{
	//	for (int i = 0; i < nAudioChannelCount + 3; i++)
	//	{
	//		_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Tracks[i], i + 1, 0, 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[i], ui64CurrentWritePosition);



	//		//header metadate 
	//		//Squence
	//		_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_Track_Sequence[i], (void*)KEY_MXF_METADATA_Component_DataDifinitions_16Audio_Track[i], ui64Duration, (void*)UUID_MXF_METADATA_Material_Components[i], ui64CurrentWritePosition);

	//		if (i == 0)
	//		{
	//			//header metadate 
	//			//Timecode Component
	//			_write_mxf_TimecodeComponent(fp, (void*)UUID_MXF_METADATA_Material_Components[i], (void*)KEY_MXF_METADATA_Component_DataDifinitions_16Audio_Track[i], ui64Duration, ui64StartTimecode, 50, 0, ui64CurrentWritePosition);
	//		}
	//		else
	//		{
	//			//header metadate 
	//			//SourceClip Component
	//			//_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Material_Components[i], (void*)KEY_MXF_METADATA_Component_DataDifinitions[i], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, 512 + (i-1)*256, 0, ui64CurrentWritePosition);
	//			_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Material_Components[i], (void*)KEY_MXF_METADATA_Component_DataDifinitions_16Audio_Track[i], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, i + 1, 0, ui64CurrentWritePosition);
	//		}

	//	}
	//}
};

void _write_mxf_header_metadate_sourcepackage(FILE *fp, uint64_t & ui64CurrentWritePosition, int nAudioChannelCount)
{
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_SourcePackage, 288, ui64CurrentWritePosition);


	uint32_t ui32SourcePackage_length_pos = ui64CurrentWritePosition - 4;
	//sourcepackage->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage, ui64CurrentWritePosition);


	//sourcepackage->package
	_write_mxf_metadata_property_umid(fp, 0x0144, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, ui64CurrentWritePosition);

	//sourcepackage->creation date
	_write_mxf_metadata_date(fp, 0x0544, 2018, 7, 31, 3, 18, 35, 0, ui64CurrentWritePosition);

	//sourcepackage->modified date
	_write_mxf_metadata_date(fp, 0x0444, 2018, 7, 31, 3, 18, 35, 0, ui64CurrentWritePosition);

	//sourcepackage->tracks
	x_mxf_header_metadata sourcepackage_tracks;
	sourcepackage_tracks.tag = 0x0344;

	//sourcepackage_tracks.arraysize = 11;
	sourcepackage_tracks.arraysize = nAudioChannelCount + 3;
	sourcepackage_tracks.arrayitemlength = 16;

	sourcepackage_tracks.length = sourcepackage_tracks.arraysize*sourcepackage_tracks.arrayitemlength + 8;


	sourcepackage_tracks.arrayproperty = new unsigned char*[sourcepackage_tracks.arraysize];

	for (int i = 0; i < sourcepackage_tracks.arraysize; i++)
	{
		sourcepackage_tracks.arrayproperty[i] = new unsigned char[sourcepackage_tracks.arrayitemlength];
		memcpy(sourcepackage_tracks.arrayproperty[i], UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Tracks[i], sourcepackage_tracks.arrayitemlength);
	}

	_write_mxf_property_array(fp, sourcepackage_tracks, ui64CurrentWritePosition);


	//sourcepackage->descriptor
	x_mxf_header_metadata materialpackage_descriptor;
	materialpackage_descriptor.tag = 0x0147;//2
	materialpackage_descriptor.length = 16;//2

	memcpy(materialpackage_descriptor.uid, UUID_MXF_METADATA_SourcePackage_Descriptor, 16);

	_write_mxf_tag(fp, &materialpackage_descriptor.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &materialpackage_descriptor.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_uuid(fp, materialpackage_descriptor.uid); ui64CurrentWritePosition += 16;



	_write_mxf_metadata_modify_length(fp, ui32SourcePackage_length_pos, ui64CurrentWritePosition - ui32SourcePackage_length_pos - 4);

};
void _write_mxf_header_metadate_multipledescriptor(FILE *fp, uint64_t & ui64CurrentWritePosition, int nAudioChannelCount)
{
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_MultipleDescriptor, 224, ui64CurrentWritePosition);

	uint32_t ui32MultipleDescriptor_length_pos = ui64CurrentWritePosition - 4;



	//multipledescriptor->instanceuid
	x_mxf_header_metadata multipledescriptor_instanceuid;
	multipledescriptor_instanceuid.tag = 0x0a3c;//2
	multipledescriptor_instanceuid.length = 16;//2

	memcpy(multipledescriptor_instanceuid.uid, UUID_MXF_METADATA_SourcePackage_Descriptor, 16);

	_write_mxf_tag(fp, &multipledescriptor_instanceuid.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &multipledescriptor_instanceuid.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_uuid(fp, multipledescriptor_instanceuid.uid); ui64CurrentWritePosition += 16;


	//multipledescriptor->samplerate
	x_mxf_header_metadata multipledescriptor_samplerate;
	multipledescriptor_samplerate.tag = 0x0130;//2
	multipledescriptor_samplerate.length = 8;//2

	uint32_t ui32SampleRateX = 50;
	uint32_t ui32SampleRateY = 1;
	_write_mxf_tag(fp, &multipledescriptor_samplerate.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &multipledescriptor_samplerate.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &ui32SampleRateX, 4); ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &ui32SampleRateY, 4); ui64CurrentWritePosition += 4;


	//multipledescriptor->essencecontainer
	x_mxf_header_metadata multipledescriptor_essencecontainer;
	multipledescriptor_essencecontainer.tag = 0x0430;//2
	multipledescriptor_essencecontainer.length = 16;//2

	memcpy(multipledescriptor_essencecontainer.uid, KEY_MXF_Generic_Essence_Multiple_Mappings, 16);

	_write_mxf_tag(fp, &multipledescriptor_essencecontainer.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &multipledescriptor_essencecontainer.length, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_uuid(fp, multipledescriptor_essencecontainer.uid); ui64CurrentWritePosition += 16;


	//multipledescriptor->SubDescriptorUIDs
	x_mxf_header_metadata multipledescriptor_SubDescriptorUIDs;
	multipledescriptor_SubDescriptorUIDs.tag = 0x013f;

	multipledescriptor_SubDescriptorUIDs.arraysize = nAudioChannelCount + 2;//2= pic and anc
	multipledescriptor_SubDescriptorUIDs.arrayitemlength = 16;
	multipledescriptor_SubDescriptorUIDs.length = multipledescriptor_SubDescriptorUIDs.arraysize*multipledescriptor_SubDescriptorUIDs.arrayitemlength + 8;
	multipledescriptor_SubDescriptorUIDs.arrayproperty = new unsigned char*[multipledescriptor_SubDescriptorUIDs.arraysize];

	for (int i = 0; i < multipledescriptor_SubDescriptorUIDs.arraysize; i++)
	{
		multipledescriptor_SubDescriptorUIDs.arrayproperty[i] = new unsigned char[multipledescriptor_SubDescriptorUIDs.arrayitemlength];
		memcpy(multipledescriptor_SubDescriptorUIDs.arrayproperty[i], UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[i], multipledescriptor_SubDescriptorUIDs.arrayitemlength);
	}

	_write_mxf_property_array(fp, multipledescriptor_SubDescriptorUIDs, ui64CurrentWritePosition);


	_write_mxf_metadata_modify_length(fp, ui32MultipleDescriptor_length_pos, ui64CurrentWritePosition - ui32MultipleDescriptor_length_pos - 4);

};
void _write_mxf_header_metadate_sourcepackage_cdci_descriptor(FILE *fp, uint64_t & ui64CurrentWritePosition, uint32_t ui32LinkedTrackID, void*SubDescriptorUID)
{
	//CDCI Essence Descriptor
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_CDCIEssenceDescriptor, 379, ui64CurrentWritePosition);

	uint32_t ui32CDCIEssenceDescriptor_length_pos = ui64CurrentWritePosition - 4;



	//cdciessencedescriptor->instanceuid
	//_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[0], ui64CurrentWritePosition);
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, SubDescriptorUID, ui64CurrentWritePosition);


	//cdciessencedescriptor->linkedtrackid
	//uint32_t ui32LinkedTrackID = 512;
	//uint32_t ui32LinkedTrackID = i + 1;
	_write_mxf_metadata_property_uint32(fp, 0x0630, ui32LinkedTrackID, ui64CurrentWritePosition);

	//cdciessencedescriptor->samplerate
	_write_mxf_metadata_property_uint32_uint32(fp, 0x0130, 50, 1, ui64CurrentWritePosition);

	//cdciessencedescriptor->EssenceContainer
	_write_mxf_metadata_property_uuid(fp, 0x0430, (void*)KEY_MXF_Generic_Container_AVC, ui64CurrentWritePosition);


	//cdciessencedescriptor->StoredWidth
	uint32_t ui32StoredWidth = 3840;
	_write_mxf_metadata_property_uint32(fp, 0x0332, ui32StoredWidth, ui64CurrentWritePosition);

	//cdciessencedescriptor->Stored Height
	uint32_t ui32StoredHeight = 2160;
	_write_mxf_metadata_property_uint32(fp, 0x0232, ui32StoredHeight, ui64CurrentWritePosition);




	//cdciessencedescriptor->DisplayWidth
	uint32_t ui32DisplayWidth = 3840;
	_write_mxf_metadata_property_uint32(fp, 0x0932, ui32DisplayWidth, ui64CurrentWritePosition);

	//cdciessencedescriptor->DisplayHeight
	uint32_t ui32DisplayHeight = 2160;
	_write_mxf_metadata_property_uint32(fp, 0x0832, ui32DisplayHeight, ui64CurrentWritePosition);




	//cdciessencedescriptor->Component Depth
	uint32_t ui32ComponentDepth = 10;
	_write_mxf_metadata_property_uint32(fp, 0x0133, ui32ComponentDepth, ui64CurrentWritePosition);




	//Horizontal Subsampling
	uint32_t ui32HorizontalSubsampling = 2;
	_write_mxf_metadata_property_uint32(fp, 0x0233, ui32HorizontalSubsampling, ui64CurrentWritePosition);


	//Vertical Subsampling
	uint32_t ui32VerticalSubsampling = 1;
	_write_mxf_metadata_property_uint32(fp, 0x0833, ui32VerticalSubsampling, ui64CurrentWritePosition);


	//cdciessencedescriptor->FrameLayout
	uint8_t ui8FrameLayout = 0;

	_write_mxf_metadata_property_int8(fp, 0x0c32, ui8FrameLayout, ui64CurrentWritePosition);



	//cdciessencedescriptor->VideoLineMap
	x_mxf_header_metadata cdciessencedescriptor_VideoLineMap;
	cdciessencedescriptor_VideoLineMap.tag = 0x0d32;//2
	cdciessencedescriptor_VideoLineMap.length = 16;//2

	uint32_t VideoLineMap[4] = { 2,4,0x2A,0 };

	_write_mxf_tag(fp, &cdciessencedescriptor_VideoLineMap.tag);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &cdciessencedescriptor_VideoLineMap.length, 2);	ui64CurrentWritePosition += 2;
	for (int i = 0; i < 4; i++)
	{
		_write_mxf_l2b(fp, &VideoLineMap[i], 4); ui64CurrentWritePosition += 4;
	}


	//x_mxf_header_metadata cdciessencedescriptor_VideoLineMap;
	//cdciessencedescriptor_VideoLineMap.tag = 0x0d32;//2
	//cdciessencedescriptor_VideoLineMap.length = 12;//2

	//uint32_t VideoLineMap[4] = { 1,4,0 };

	//_write_mxf_tag(fp, &cdciessencedescriptor_VideoLineMap.tag);	ui64CurrentWritePosition += 2;
	//_write_mxf_l2b(fp, &cdciessencedescriptor_VideoLineMap.length, 2);	ui64CurrentWritePosition += 2;
	//for (int i = 0; i < 3; i++)
	//{
	//	_write_mxf_l2b(fp, &VideoLineMap[i], 4); ui64CurrentWritePosition += 4;
	//}



	//cdciessencedescriptor->Aspect Ratio
	uint32_t ui32AspectRatioX = 16;
	uint32_t ui32AspectRatioY = 9;

	_write_mxf_metadata_property_uint32_uint32(fp, 0x0e32, ui32AspectRatioX, ui32AspectRatioY, ui64CurrentWritePosition);

	//cdciessencedescriptor->Active Format Descriptor
	int8_t i8ActiveFormatDescriptor = 68;
	_write_mxf_metadata_property_int8(fp, 0x1832, i8ActiveFormatDescriptor, ui64CurrentWritePosition);



	//cdciessencedescriptor->Picture Essence Coding
	_write_mxf_metadata_property_uuid(fp, 0x0132, (void*)KEY_MXF_METADATA_CDCI_PictureEssenceCoding[0], ui64CurrentWritePosition);


	//cdciessencedescriptor->Signal Standard
	uint8_t ui8SignalStandard = 0;
	_write_mxf_metadata_property_int8(fp, 0x1532, ui8SignalStandard, ui64CurrentWritePosition);


	//cdciessencedescriptor->SampledWidth
	uint32_t ui32SampledWidth = 3840;
	_write_mxf_metadata_property_uint32(fp, 0x0532, ui32SampledWidth, ui64CurrentWritePosition);

	//cdciessencedescriptor->Sampled Height
	uint32_t ui32SampledHeight = 2160;
	_write_mxf_metadata_property_uint32(fp, 0x0432, ui32SampledHeight, ui64CurrentWritePosition);


	//
	//cdciessencedescriptor->SampledXOffset
	int32_t i32SampledXOffset = 0;
	_write_mxf_metadata_property_int32(fp, 0x0632, i32SampledXOffset, ui64CurrentWritePosition);

	//cdciessencedescriptor->SampledYOffset
	int32_t i32SampledYOffset = 0;
	_write_mxf_metadata_property_int32(fp, 0x0732, i32SampledYOffset, ui64CurrentWritePosition);


	//
	//cdciessencedescriptor->DisplayXOffset
	int32_t i32DisplayXOffset = 0;
	_write_mxf_metadata_property_int32(fp, 0x0A32, i32DisplayXOffset, ui64CurrentWritePosition);



	//cdciessencedescriptor->DisplayYOffset
	int32_t i32DisplayYOffset = 0;
	_write_mxf_metadata_property_int32(fp, 0x0B32, i32DisplayYOffset, ui64CurrentWritePosition);


	//cdciessencedescriptor->CaptureGamma
	_write_mxf_metadata_property_uuid(fp, 0x1032, (void*)KEY_MXF_METADATA_CDCI_CaptureGamma[0], ui64CurrentWritePosition);

	//cdciessencedescriptor->CodingEquation
	_write_mxf_metadata_property_uuid(fp, 0x1a32, (void*)KEY_MXF_METADATA_CDCI_CodingEquation[0], ui64CurrentWritePosition);

	//cdciessencedescriptor->ColorPrimaries
	_write_mxf_metadata_property_uuid(fp, 0x1932, (void*)KEY_MXF_METADATA_CDCI_ColorPrimaries[0], ui64CurrentWritePosition);



	//cdciessencedescriptor->Image Alignment Offset
	uint32_t ui32ImageAlignmentOffset = 0;
	_write_mxf_metadata_property_uint32(fp, 0x1132, ui32ImageAlignmentOffset, ui64CurrentWritePosition);



	//cdciessencedescriptor->Image Start Offset
	uint32_t ui32ImageStartOffset = 0;
	_write_mxf_metadata_property_uint32(fp, 0x1332, ui32ImageStartOffset, ui64CurrentWritePosition);



	//cdciessencedescriptor->Image End Offset
	uint32_t ui32ImageEndOffset = 0;
	_write_mxf_metadata_property_uint32(fp, 0x1432, ui32ImageEndOffset, ui64CurrentWritePosition);




	//Color Siting
	uint8_t ui8ColorSiting = 0;
	_write_mxf_metadata_property_int8(fp, 0x0333, ui8ColorSiting, ui64CurrentWritePosition);



	//Black Ref Level
	uint32_t ui32BlackRefLevel = 64;
	_write_mxf_metadata_property_uint32(fp, 0x0433, ui32BlackRefLevel, ui64CurrentWritePosition);


	//White Ref level
	uint32_t ui32WhiteRefLevel = 940;
	_write_mxf_metadata_property_uint32(fp, 0x0533, ui32WhiteRefLevel, ui64CurrentWritePosition);
	//Color Range
	uint32_t ui32ColorRange = 897;
	_write_mxf_metadata_property_uint32(fp, 0x0633, ui32ColorRange, ui64CurrentWritePosition);


	//ReversedByteOrder
	uint8_t ui8ReversedByteOrder = 0;
	_write_mxf_metadata_property_int8(fp, 0x0b33, ui8ReversedByteOrder, ui64CurrentWritePosition);


	//PaddingBits
	int16_t i16PaddingBits = 0;
	_write_mxf_metadata_property_int16(fp, 0x0733, i16PaddingBits, ui64CurrentWritePosition);




	//multipledescriptor->Sub Descriptors
	x_mxf_header_metadata multipledescriptor_maybe_subdescriptors;//it's property analyser dont get know.
	multipledescriptor_maybe_subdescriptors.tag = 0x1080;
	multipledescriptor_maybe_subdescriptors.length = 24;
	multipledescriptor_maybe_subdescriptors.arraysize = 1;
	multipledescriptor_maybe_subdescriptors.arrayitemlength = 16;

	multipledescriptor_maybe_subdescriptors.arrayproperty = new unsigned char*[multipledescriptor_maybe_subdescriptors.arraysize];

	for (int i = 0; i < multipledescriptor_maybe_subdescriptors.arraysize; i++)
	{
		multipledescriptor_maybe_subdescriptors.arrayproperty[i] = new unsigned char[multipledescriptor_maybe_subdescriptors.arrayitemlength];
		//memcpy(multipledescriptor_maybe_subdescriptors.arrayproperty[i], UUID_MXF_METADATA_CDCI_Maybe_SubDescriptors, multipledescriptor_maybe_subdescriptors.arrayitemlength);
		memcpy(multipledescriptor_maybe_subdescriptors.arrayproperty[i], UUID_MXF_METADATA_AVCSubDescriptor, multipledescriptor_maybe_subdescriptors.arrayitemlength);
	}

	_write_mxf_property_array(fp, multipledescriptor_maybe_subdescriptors, ui64CurrentWritePosition);


	_write_mxf_metadata_modify_length(fp, ui32CDCIEssenceDescriptor_length_pos, ui64CurrentWritePosition - ui32CDCIEssenceDescriptor_length_pos - 4);



};

void _write_mxf_header_metadate_sourcepackage_avc_descriptor(FILE *fp, uint64_t & ui64CurrentWritePosition)
{
	//header metadate
	//AVCSubDescriptor
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_AVCSubDescriptor, 95, ui64CurrentWritePosition);

	//AVCSubDescriptor->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_METADATA_AVCSubDescriptor, ui64CurrentWritePosition);

	_write_mxf_metadata_property_int8(fp, 0x1180, 1, ui64CurrentWritePosition);//0x8001
	_write_mxf_metadata_property_int8(fp, 0x1280, 1, ui64CurrentWritePosition);//0x8002
	_write_mxf_metadata_property_int8(fp, 0x1380, 1, ui64CurrentWritePosition);//0x8004
	_write_mxf_metadata_property_int8(fp, 0x1480, 1, ui64CurrentWritePosition);//0x8005
	_write_mxf_metadata_property_int16(fp, 0x1580, 1, ui64CurrentWritePosition);//0x8006
	_write_mxf_metadata_property_int16(fp, 0x1680, 0, ui64CurrentWritePosition); //0x8007
	_write_mxf_metadata_property_int32(fp, 0x1780, 0x1dcf4000, ui64CurrentWritePosition);//0x8008
	_write_mxf_metadata_property_int8(fp, 0x1980, 0x7a, ui64CurrentWritePosition);//0x8009
	_write_mxf_metadata_property_int8(fp, 0x1a80, 0x10, ui64CurrentWritePosition);//0x800a
	_write_mxf_metadata_property_int8(fp, 0x1b80, 0x34, ui64CurrentWritePosition);//0x800b
	_write_mxf_metadata_property_int8(fp, 0x1c80, 0, ui64CurrentWritePosition);//0x800c
	_write_mxf_metadata_property_int8(fp, 0x1d80, 0, ui64CurrentWritePosition);//0x800d
	_write_mxf_metadata_property_int8(fp, 0x1e80, 0x20, ui64CurrentWritePosition);//0x800e
	_write_mxf_metadata_property_int8(fp, 0x1f80, 0x20, ui64CurrentWritePosition);//0x800f
};

void _write_mxf_header_metadate_sourcepackage_anc_descriptor(FILE *fp, uint64_t & ui64CurrentWritePosition, uint32_t ui32LinkedTrackID, void*SubDescriptorUID)
{

	//
	//header metadate
	//ANC Packets Descriptor
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_ANCPacketsDescriptor, 60, ui64CurrentWritePosition);

	uint32_t ui32ANCPacketsDescriptor_length_pos = ui64CurrentWritePosition - 4;

	//instanceuid
	//_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[i - 1], ui64CurrentWritePosition);
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, SubDescriptorUID, ui64CurrentWritePosition);

	//linkedtrackid
	_write_mxf_metadata_property_uint32(fp, 0x0630, ui32LinkedTrackID, ui64CurrentWritePosition);

	//samplerate
	_write_mxf_metadata_property_uint32_uint32(fp, 0x0130, 50, 1, ui64CurrentWritePosition);


	//EssenceContainer
	_write_mxf_metadata_property_uuid(fp, 0x0430, (void*)KEY_MXF_ANC_Data_Mapping, ui64CurrentWritePosition);

	_write_mxf_metadata_modify_length(fp, ui32ANCPacketsDescriptor_length_pos, ui64CurrentWritePosition - ui32ANCPacketsDescriptor_length_pos - 4);


};

void _write_mxf_header_metadate_sourcepackage_aes3_descriptor(FILE *fp, uint64_t & ui64CurrentWritePosition, uint32_t ui32LinkedTrackID, void*SubDescriptorUID)
{
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_AES3AudioEssenceDescriptor, 107, ui64CurrentWritePosition);

	uint32_t ui32AES3AudioEssenceDescriptor_length_pos = ui64CurrentWritePosition - 4;


	//instanceuid
	//_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[i - 1], ui64CurrentWritePosition);
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, SubDescriptorUID, ui64CurrentWritePosition);

	//linkedtrackid
	//uint32_t ui32LinkedTrackID = 512 + (i - 1) * 256;
	//uint32_t ui32LinkedTrackID = i + 1;
	_write_mxf_metadata_property_uint32(fp, 0x0630, ui32LinkedTrackID, ui64CurrentWritePosition);

	//samplerate

	_write_mxf_metadata_property_uint32_uint32(fp, 0x0130, 50, 1, ui64CurrentWritePosition);
	//_write_mxf_metadata_property_uint32_uint32(fp, 0x0130, 48000, 1, ui64CurrentWritePosition);

	//EssenceContainer
	_write_mxf_metadata_property_uuid(fp, 0x0430, (void*)KEY_MXF_Frame_wrapped_AES3_audio_data, ui64CurrentWritePosition);

	//Locked
	_write_mxf_metadata_property_int8(fp, 0x023d, 1, ui64CurrentWritePosition);


	//Audio sampling rate
	_write_mxf_metadata_property_uint32_uint32(fp, 0x033d, 48000, 1, ui64CurrentWritePosition);


	////Audio Ref Level
	//_write_mxf_metadata_property_int8(fp, 0x043d, 0, ui64CurrentWritePosition);

	//ChannelCount
	_write_mxf_metadata_property_uint32(fp, 0x073d, 1, ui64CurrentWritePosition);

	//Qantization bits
	_write_mxf_metadata_property_uint32(fp, 0x013d, 24, ui64CurrentWritePosition);

	//_write_mxf_metadata_property_uuid(fp, 0x063d, (void*)KEY_MXF_METADATA_Sound_AES3EssenceCoding[0], ui64CurrentWritePosition);

	//BlockAlign
	_write_mxf_metadata_property_int16(fp, 0x0a3d, 3, ui64CurrentWritePosition);

	//AvgBps
	_write_mxf_metadata_property_uint32(fp, 0x093d, 144000, ui64CurrentWritePosition);

	_write_mxf_metadata_modify_length(fp, ui32AES3AudioEssenceDescriptor_length_pos, ui64CurrentWritePosition - ui32AES3AudioEssenceDescriptor_length_pos - 4);

};

void _write_mxf_header_metadate_sourcetracks_and_descriptors(FILE *fp, uint64_t & ui64CurrentWritePosition, uint64_t ui64Duration, int nAudioChannelCount)
{
	uint32_t *ui32TrackNumber;
	uint32_t ui32TrackNumber8Audio[11] = { 0,0x15010500 ,0x16080300,0x16080300 + 1,0x16080300 + 2,0x16080300 + 3,0x16080300 + 4,0x16080300 + 5,0x16080300 + 6,0x16080300 + 7 ,0x17010201 };



	uint32_t ui32TrackNumber16Audio[19] = { 0,0x15010500 ,0x16100300,0x16100300 + 1,0x16100300 + 2,0x16100300 + 3,0x16100300 + 4,0x16100300 + 5,0x16100300 + 6,0x16100300 + 7 ,0x16100300 + 8 ,0x16100300 + 9 ,0x16100300 + 10 ,0x16100300 + 11 ,0x16100300 + 12 ,0x16100300 + 13 ,0x16100300 + 14 ,0x16100300 + 15 ,0x17010201 };


	if (nAudioChannelCount == 8)
		ui32TrackNumber = ui32TrackNumber8Audio;
	else if (nAudioChannelCount == 16)
		ui32TrackNumber = ui32TrackNumber16Audio;


	/*
	*timecode track.
	*/
	int nTrackID = 0;
	int nTrackIndex = 0;
	nTrackID = nTrackIndex + 1;

	//track.
	_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Tracks[nTrackIndex], nTrackID, ui32TrackNumber[nTrackIndex], 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

	//Squence
	_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Timecode], ui64Duration, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], ui64CurrentWritePosition);

	//Timecode Component
	_write_mxf_TimecodeComponent(fp, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Timecode], ui64Duration, 0, 50, 0, ui64CurrentWritePosition);

	/*
	*picture track.
	*/
	nTrackIndex++;
	nTrackID++;
	_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Tracks[nTrackIndex], nTrackID, ui32TrackNumber[nTrackIndex], 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

	//Squence
	_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Picture], ui64Duration, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], ui64CurrentWritePosition);

	//SourceClip Component
	_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Picture], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_SourcePackage_PackageUID, 0, 0, ui64CurrentWritePosition);

	//cdci descriptor and avc descriptor.
	uint32_t ui32LinkedTrackID = nTrackID;
	_write_mxf_header_metadate_sourcepackage_cdci_descriptor(fp, ui64CurrentWritePosition, ui32LinkedTrackID, (void*)UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[nTrackIndex - 1]);
	_write_mxf_header_metadate_sourcepackage_avc_descriptor(fp, ui64CurrentWritePosition);

	/*
	*sounds track.
	*/

	for (int i = 0; i < nAudioChannelCount; i++)
	{
		nTrackIndex++;
		nTrackID++;
		_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Tracks[nTrackIndex], nTrackID, ui32TrackNumber[nTrackIndex], 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

		//Squence
		_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Sound], ui64Duration, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], ui64CurrentWritePosition);

		//SourceClip Component
		_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Sound], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_SourcePackage_PackageUID, 0, 0, ui64CurrentWritePosition);

		//aes3 descriptor 
		uint32_t ui32LinkedTrackID = nTrackID;
		_write_mxf_header_metadate_sourcepackage_aes3_descriptor(fp, ui64CurrentWritePosition, ui32LinkedTrackID, (void*)UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[nTrackIndex - 1]);

	}

	/*
	*anc of data track.
	*/
	nTrackIndex++;
	nTrackID++;
	_write_mxf_timelinetrack(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Tracks[nTrackIndex], nTrackID, ui32TrackNumber[nTrackIndex], 50, 1, 0, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], ui64CurrentWritePosition);

	//Squence
	_write_mxf_sequence(fp, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_Track_Sequence[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Data], ui64Duration, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], ui64CurrentWritePosition);

	//SourceClip Component
	_write_mxf_SourceClip(fp, (void*)UUID_MXF_METADATA_Source_Components[nTrackIndex], (void*)KEY_MXF_METADATA_Component_DataDifinitions[keComponentDataDifinitionType_Data], ui64Duration, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_SourcePackage_PackageUID, 0, 0, ui64CurrentWritePosition);


	//ANC Packets Descriptor
	ui32LinkedTrackID = nTrackID;
	_write_mxf_header_metadate_sourcepackage_anc_descriptor(fp, ui64CurrentWritePosition, ui32LinkedTrackID, (void*)UUID_MXF_METADATA_MultipleDescriptor_SubDescriptorUIDs[nTrackIndex - 1]);


};

void _write_mxf_header_metadate_essencecontainerdata(FILE *fp, uint64_t & ui64CurrentWritePosition)
{
	//header metadate 
	//essencecontainerdata
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_EssenceContainerData, 72, ui64CurrentWritePosition);

	uint32_t ui32EssenceContainerData_length_pos = ui64CurrentWritePosition - 4;

	//essencecontainerdata->instanceuid
	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_EssenceContainerData, ui64CurrentWritePosition);

	//essencecontainerdata->linkedpackageui
	//_write_mxf_metadata_property_umid(fp, 0x0127, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_EssenceContainerData_PackageUID, ui64CurrentWritePosition);
	_write_mxf_metadata_property_umid(fp, 0x0127, (void*)UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, ui64CurrentWritePosition);


	//essencecontainerdata->BodySID
	_write_mxf_metadata_property_int32(fp, 0x073f, 2, ui64CurrentWritePosition);


	//essencecontainerdata->IndexSID
	_write_mxf_metadata_property_int32(fp, 0x063f, 1, ui64CurrentWritePosition);



	_write_mxf_metadata_modify_length(fp, ui32EssenceContainerData_length_pos, ui64CurrentWritePosition - ui32EssenceContainerData_length_pos - 4);

};
void _write_mxf_header_metadate_indextablesegment(FILE *fp, uint64_t & ui64CurrentWritePosition, int nAudioChannelCount)
{
	uint32_t ui32EditUnitByteCount = 1286144;

	if (nAudioChannelCount == 16)
	{
		ui32EditUnitByteCount += 24576;
	}


	uint32_t ui32PositionSaveIndextablesegmentStart = ui64CurrentWritePosition;

	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_IndexTableSegment, 163, ui64CurrentWritePosition);

	uint32_t ui32IndexTableSegment_length_pos = ui64CurrentWritePosition - 4;



	_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_METADATA_IndexTableSegment, ui64CurrentWritePosition);

	//Index Edit Rate
	_write_mxf_metadata_property_uint32_uint32(fp, 0x0b3f, 50, 1, ui64CurrentWritePosition);

	//Index Start Position
	_write_mxf_metadata_property_uint64(fp, 0x0c3f, 0, ui64CurrentWritePosition);

	//Index Duration
	_write_mxf_metadata_property_uint64(fp, 0x0d3f, 0, ui64CurrentWritePosition);

	//EditUnitByteCount
	_write_mxf_metadata_property_uint32(fp, 0x053f, ui32EditUnitByteCount, ui64CurrentWritePosition);

	//IndexSID
	_write_mxf_metadata_property_uint32(fp, 0x063f, 1, ui64CurrentWritePosition);

	//BodySID
	_write_mxf_metadata_property_uint32(fp, 0x073f, 2, ui64CurrentWritePosition);

	//Slice Count
	_write_mxf_metadata_property_int8(fp, 0x083f, 0, ui64CurrentWritePosition);



	//Delta Entry Array
	x_mxf_header_metadata indextablesegment_deltaentryarray;

	indextablesegment_deltaentryarray.tag = 0x093f;

	//indextablesegment_deltaentryarray.arraysize = 11;
	indextablesegment_deltaentryarray.arraysize = nAudioChannelCount + 3;

	indextablesegment_deltaentryarray.arrayitemlength = 6;

	indextablesegment_deltaentryarray.length = indextablesegment_deltaentryarray.arraysize*indextablesegment_deltaentryarray.arrayitemlength + 8;

	indextablesegment_deltaentryarray.arrayproperty = new unsigned char*[indextablesegment_deltaentryarray.arraysize];

	for (int i = 0; i < indextablesegment_deltaentryarray.arraysize; i++)
	{
		indextablesegment_deltaentryarray.arrayproperty[i] = new unsigned char[indextablesegment_deltaentryarray.arrayitemlength];
		memcpy(indextablesegment_deltaentryarray.arrayproperty[i], IndexTableSegment_DeltaEntry[i], indextablesegment_deltaentryarray.arrayitemlength);
	}


	_write_mxf_property_array(fp, indextablesegment_deltaentryarray, ui64CurrentWritePosition);


	//modify IndexTableSegment's truely length.
	_write_mxf_metadata_modify_length(fp, ui32IndexTableSegment_length_pos, ui64CurrentWritePosition - ui32IndexTableSegment_length_pos - 4);



	////IndexEntryArray
	//x_mxf_header_metadata indextablesegment_indexentryarray;
	//indextablesegment_indexentryarray.tag = 0x0a3f;
	//indextablesegment_indexentryarray.length = 8;
	//indextablesegment_indexentryarray.arraysize = 0;
	//indextablesegment_indexentryarray.arrayitemlength = 0;

	//indextablesegment_indexentryarray.arrayproperty = new unsigned char*[indextablesegment_indexentryarray.arraysize];

	//for (int i = 0; i < indextablesegment_indexentryarray.arraysize; i++)
	//{
	//	indextablesegment_indexentryarray.arrayproperty[i] = new unsigned char[indextablesegment_indexentryarray.arrayitemlength];
	//	memcpy(indextablesegment_indexentryarray.arrayproperty[i], IndexTableSegment_DeltaEntry[i], indextablesegment_indexentryarray.arrayitemlength);
	//}

	//_write_mxf_property_array(fp, indextablesegment_indexentryarray, ui64CurrentWritePosition);

	//fill

	uint64_t indextable_fill_lengh = (512 - (ui64CurrentWritePosition - ui32PositionSaveIndextablesegmentStart) % 512) - 16 - 4;//309

	if (indextable_fill_lengh < 0)
		indextable_fill_lengh += 512;


	_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, indextable_fill_lengh, ui64CurrentWritePosition);
};

void _write_mxf_system_and_package_metadata(FILE *fp, uint64_t & ui64CurrentWritePosition)
{
	uint32_t ui32PositionSaveStart = ui64CurrentWritePosition;
	// write system metadata pack
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_SystemMetadataPack, 57, ui64CurrentWritePosition);

	uint64_t system_metadata_lengh = 57;
	int8_t system_metadata_value = 0;
	for (int i = 0; i < system_metadata_lengh; i++)
	{
		fwrite(&system_metadata_value, 1, 1, fp);
	}
	ui64CurrentWritePosition += system_metadata_lengh;


	//write package metadata pack
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_PackageMetadataSet, 35, ui64CurrentWritePosition);


	uint64_t package_metadata_lengh = 35;
	int8_t package_metadata_value = 0;
	for (int i = 0; i < package_metadata_lengh; i++)
	{
		fwrite(&package_metadata_value, 1, 1, fp);
	}
	ui64CurrentWritePosition += package_metadata_lengh;

	//type
	//type = 0x83;//UMDI
	//_write_mxf_l2b(fp, &type, 1); ui64CurrentWritePosition += 1;
	////length
	//uint16_t length = 0x20;//64;
	//_write_mxf_l2b(fp, &length, 2); ui64CurrentWritePosition += 2;

	////KEY_MXF_METADATA_PackageMetadataSet_UMID
	//_write_mxf_direct(fp, (void*)KEY_MXF_METADATA_PackageMetadataSet_UMID, 32); ui64CurrentWritePosition += 32;

	uint64_t system_and_package_fill_lengh = (512 - (ui64CurrentWritePosition - ui32PositionSaveStart) % 512) - 16 - 4;//360

	if (system_and_package_fill_lengh < 0)
		system_and_package_fill_lengh += 512;

	//fill

	_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, system_and_package_fill_lengh, ui64CurrentWritePosition);
};

void _write_mxf_anc(FILE *fp, uint64_t & ui64CurrentWritePosition)
{
	_write_mxf_metadata_box(fp, (void*)KEY_MXF_VANC_container, 28, ui64CurrentWritePosition);

	int8_t anc_value = 0;
	for (int i = 0; i < 28; i++)
	{
		fwrite(&anc_value, 1, 1, fp);
	}
	ui64CurrentWritePosition += 28;


	//ANC's fill item.
	uint64_t anc_item_fill_lengh = 444;

	_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, anc_item_fill_lengh, ui64CurrentWritePosition);
};

void _write_mxf_footer_partition_pack(FILE *fp, uint64_t & ui64CurrentWritePosition)
{
	//footer partition pack.
	x_mxf_header_partition_pack spartition_pack;

	uint64_t ui64FooterPartitionPos = ui64CurrentWritePosition;

	_write_mxf_metadata_box(fp, (void*)KEY_MXF_FOOTER_PARTITION_PACK, 152, ui64CurrentWritePosition);


	// set value.
	spartition_pack.major_version = 1;
	spartition_pack.minor_version = 3;
	spartition_pack.kagsize = 512;
	spartition_pack.thispartition = ui64FooterPartitionPos;
	spartition_pack.previouspartition = 0;
	spartition_pack.footerpartition = ui64FooterPartitionPos;
	spartition_pack.headerbytecount = 0;

	spartition_pack.indexbytecount = 0;
	spartition_pack.indexsid = 0;
	spartition_pack.bodyoffset = 0;
	spartition_pack.bodysid = 0;
	memcpy(spartition_pack.operational_pattern, KEY_MXF_OPERATIONAL_PATTERN, 16);
	spartition_pack.essencecontainers.count = 4;
	spartition_pack.essencecontainers.length = 16;
	spartition_pack.essencecontainers.universallable = new unsigned char *[spartition_pack.essencecontainers.count];
	spartition_pack.essencecontainers.universallable = new unsigned char *[spartition_pack.essencecontainers.count];

	for (int i = 0; i < spartition_pack.essencecontainers.count; i++)
	{
		spartition_pack.essencecontainers.universallable[i] = new unsigned char[spartition_pack.essencecontainers.length];
	}

	memcpy(spartition_pack.essencecontainers.universallable[0], KEY_MXF_Generic_Container_AVC, 16);
	memcpy(spartition_pack.essencecontainers.universallable[1], KEY_MXF_Frame_wrapped_AES3_audio_data, 16);
	memcpy(spartition_pack.essencecontainers.universallable[2], KEY_MXF_Generic_Essence_Multiple_Mappings, 16);
	memcpy(spartition_pack.essencecontainers.universallable[2], KEY_MXF_ANC_Data_Mapping, 16);



	//write to file.

	_write_mxf_l2b(fp, &spartition_pack.major_version, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &spartition_pack.minor_version, 2);	ui64CurrentWritePosition += 2;
	_write_mxf_l2b(fp, &spartition_pack.kagsize, 4);	ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &spartition_pack.thispartition, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.previouspartition, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.footerpartition, 8);	ui64CurrentWritePosition += 8;





	_write_mxf_l2b(fp, &spartition_pack.headerbytecount, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.indexbytecount, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.indexsid, 4);	ui64CurrentWritePosition += 4;
	_write_mxf_l2b(fp, &spartition_pack.bodyoffset, 8);	ui64CurrentWritePosition += 8;
	_write_mxf_l2b(fp, &spartition_pack.bodysid, 4);	ui64CurrentWritePosition += 4;
	fwrite(spartition_pack.operational_pattern, 1, 16, fp);	ui64CurrentWritePosition += 16;




	_write_mxf_l2b(fp, &spartition_pack.essencecontainers.count, 4);	ui64CurrentWritePosition += 4;

	_write_mxf_l2b(fp, &spartition_pack.essencecontainers.length, 4);	ui64CurrentWritePosition += 4;

	fwrite(KEY_MXF_Generic_Essence_Multiple_Mappings, 1, 16, fp);	ui64CurrentWritePosition += 16;
	fwrite(KEY_MXF_Generic_Container_AVC, 1, 16, fp);	ui64CurrentWritePosition += 16;
	fwrite(KEY_MXF_Frame_wrapped_AES3_audio_data, 1, 16, fp);	ui64CurrentWritePosition += 16;
	fwrite(KEY_MXF_ANC_Data_Mapping, 1, 16, fp);	ui64CurrentWritePosition += 16;


	uint64_t footer_partition_fill_lengh = (512 - (ui64CurrentWritePosition - ui64FooterPartitionPos) % 512) - 16 - 4;


	if (footer_partition_fill_lengh < 0)
		footer_partition_fill_lengh += 512;


	_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, footer_partition_fill_lengh, ui64CurrentWritePosition);

}


void template_8audio_and_16audio_24bit_hlg()
{
	// TODO: 
	//_MakeUMID32InUUIDMethod(UUID_MXF_HAEDER_METADATA_PREFACE_MaterialPackage_PackageUID, 0x05, 0x0d, 0x01);

	//_MakeUMID32InUUIDMethod(UUID_MXF_HAEDER_METADATA_PREFACE_SourcePackage_PackageUID, 0x05, 0x0d, 0x01);


	FILE *fp = NULL;


	//settings of writer.
	uint64_t ui64Duration = 5;
	uint32_t nAudioChannelCount = 8;
	uint64_t ui64StartTimecode = 0;
	int64_t i64VideoFrameBufferSize = 1260032;
	int64_t i64AudioSampleBufferSize = 2880;

	errno_t error = _wfopen_s(&fp, L"G:\\XAVC_TEST_WRITE_new.MXF", L"wb");
	_fseeki64(fp, 0, SEEK_SET);


	uint64_t ui64CurrentWritePosition = 0;
	uint64_t ui64HeaderPartitionPack_footerpartition_pos = 0;
	uint32_t ui32headerbytecountPos = 0;

	//write header partiton pack.
	_write_mxf_header_partition_pack(fp, ui64CurrentWritePosition, ui64HeaderPartitionPack_footerpartition_pos, ui32headerbytecountPos);


	//writer primer pack.
	_write_mxf_header_metadate_primer_pack(fp, ui64CurrentWritePosition);

	uint32_t ui32PositionSavePrefaceStart = ui64CurrentWritePosition;
	////preface
	_write_mxf_header_metadate_preface(fp, ui64CurrentWritePosition);

	//identification
	_write_mxf_header_metadate_identification(fp, ui64CurrentWritePosition);

	//contentstorage
	_write_mxf_header_metadate_contentstorage(fp, ui64CurrentWritePosition);

	//materialpackage
	_write_mxf_header_metadate_materialpackage(fp, ui64CurrentWritePosition, nAudioChannelCount, ui64Duration, ui64StartTimecode);

	//sourcepackage
	_write_mxf_header_metadate_sourcepackage(fp, ui64CurrentWritePosition, nAudioChannelCount);

	//Multiple Descriptor
	_write_mxf_header_metadate_multipledescriptor(fp, ui64CurrentWritePosition, nAudioChannelCount);


	//
	////header metadate
	////Organizationally Organizationally registered local set for public use
	//_write_mxf_metadata_box(fp, (void*)KEY_MXF_METADATA_Organizationally, 20, ui64CurrentWritePosition);

	////multipledescriptor->instanceuid
	//_write_mxf_metadata_property_uuid(fp, 0x0a3c, (void*)UUID_MXF_METADATA_Organizationally, ui64CurrentWritePosition);

	//source tracks and descriptors
	_write_mxf_header_metadate_sourcetracks_and_descriptors(fp, ui64CurrentWritePosition, ui64Duration, nAudioChannelCount);


	//essencecontainerdata
	_write_mxf_header_metadate_essencecontainerdata(fp, ui64CurrentWritePosition);

	//fill of preface.
	uint64_t hearder_metadata_fill_lengh = (512 - (ui64CurrentWritePosition - ui32PositionSavePrefaceStart) % 512) - 16 - 4;//500
	if (hearder_metadata_fill_lengh < 0)
		hearder_metadata_fill_lengh += 512;
	_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, hearder_metadata_fill_lengh, ui64CurrentWritePosition);


	//modify headerpartition headerbeytecout.
	_write_mxf_metadata_modify_headerbytecount(fp, ui32headerbytecountPos, ui64CurrentWritePosition - 512);


	//IndexTableSegment
	_write_mxf_header_metadate_indextablesegment(fp, ui64CurrentWritePosition, nAudioChannelCount);



	// continer data.(kind of all,the video,sound,data).
	FILE *fpReadDummyAV;
	error = fopen_s(&fpReadDummyAV, "template_8audio_24bit_hlg.MXF", "rb");
	if (error)
	{
		printf("Open Failed!");
	}
	int8_t *pVideoFrame = new int8_t[20 + 1260032 + 20 + 472];
	int8_t *pAudioFrame24 = new int8_t[20 + 2880];

	//_fseeki64(fpReadDummyAV, 524800, SEEK_SET);
	//_fseeki64(fpReadDummyAV, 6096241152, SEEK_SET);
	_fseeki64(fpReadDummyAV, 13824, SEEK_SET);
	

	for (int i = 0; i <ui64Duration; i++)
	{

		_fseeki64(fpReadDummyAV, 512, SEEK_CUR);

		/*
		*write system and package metadata.
		*/

		_write_mxf_system_and_package_metadata(fp, ui64CurrentWritePosition);

		/*
		* Video DATA
		*/
		//skip key and length.
		_fseeki64(fpReadDummyAV, 20, SEEK_CUR);

		_write_mxf_metadata_box(fp, (void*)KEY_MXF_XAVC_VIDEO_FRAME, i64VideoFrameBufferSize, ui64CurrentWritePosition);

		//picture data and fill item.
		fread(pVideoFrame, 1, 1260032, fpReadDummyAV);
		fwrite(pVideoFrame, 1, 1260032, fp);
		ui64CurrentWritePosition += 1260032;

		int video_item_fill_lengh = 472;
		_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, video_item_fill_lengh, ui64CurrentWritePosition);

		//skip video fill.
		_fseeki64(fpReadDummyAV, 20 + 472, SEEK_CUR);


		/*
		* Audio DATA
		*/

		if (nAudioChannelCount >= 8)
		{

			int64_t i64CurrentPos = _ftelli64(fpReadDummyAV);


			for (int a = 0; a < nAudioChannelCount; a++)
			{

				if (a == 8)
				{
					_fseeki64(fpReadDummyAV, i64CurrentPos, SEEK_SET);//for 重复利用8轨音频，生成16轨音频
				}
				KEY_MXF_XAVC_16TRACK_AUDIO_SAMPLE[a][13] = nAudioChannelCount;
				_write_mxf_metadata_box(fp, (void*)KEY_MXF_XAVC_16TRACK_AUDIO_SAMPLE[a], i64AudioSampleBufferSize, ui64CurrentWritePosition);


				fread(pAudioFrame24, 1, 2880 + 20, fpReadDummyAV);

				
				fwrite(pAudioFrame24 +20, 1, 2880, fp);

				ui64CurrentWritePosition += 2880;

				uint64_t audio_item_fill_lengh = 152;
				_write_mxf_metadata_fill_box_and_fill_value(fp, (void*)KEY_MXF_FILL_ITEM, audio_item_fill_lengh, ui64CurrentWritePosition);


				_fseeki64(fpReadDummyAV, 20 + 152, SEEK_CUR);

			}

		}


		/*
		* ANC DATA.
		*/
		_write_mxf_anc(fp, ui64CurrentWritePosition);

	}

	/*
	*write footer partition pack.
	*/

	uint64_t ui64FooterPartitionPos = ui64CurrentWritePosition;
	_write_mxf_footer_partition_pack(fp, ui64CurrentWritePosition);

	//modify header partition pack info.
	_write_mxf_metadata_modify_headerbytecount(fp, ui64HeaderPartitionPack_footerpartition_pos, ui64FooterPartitionPos);

	fclose(fp);
	return;
}

int main()
{
	template_8audio_and_16audio_24bit_hlg();
    return 0;
}

