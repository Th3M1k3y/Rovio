//******************************************************************************************************
//																										//	
//	FUNCTION																							//		
// 		caplib.h																						//
//																										//
//	DESCRIPTION																							//
//		The header file for caplib.a																	//
//																										//																							//	
//																										//
//	HISTORY																								//
//		Name				Date				Remark													//	
//		swchou				09-13-04					1th release										//
//																										//
//	REMARK																								//
//		None																							//
//																										//		
//******************************************************************************************************//
#ifndef _CAPLIB_H_
#define _CAPLIB_H_

#ifndef _WBERRCODE_H
#include  "WBERRCODE.H"
#endif

#ifdef ECOS
#include "cyg/hal/hal_arch.h"           // CYGNUM_HAL_STACK_SIZE_TYPICAL
#include "cyg/kernel/kapi.h"
#include "cyg/infra/testcase.h"
typedef struct
{
	 cyg_interrupt cap_int;
	 cyg_handle_t cap_int_handle;
	 cyg_sem_t cap_data_ready; 
}ECOS_CAP_T;
#endif

//CAP error code 
#define 	ERR_CAP_WIDTH_HEIGHT	(CAP_ERR_ID | 0x01)
#define	ERR_CAP_LINE_OFFSET		(CAP_ERR_ID | 0x02)
#define 	ERR_CAP_ENGINE			(CAP_ERR_ID | 0x03)
#define    ERR_CAP_INT				(CAP_ERR_ID | 0x04)
#define 	ERR_CAP_DDA				(CAP_ERR_ID | 0x05)	
#define 	ERR_CAP_TIMEOUT			(CAP_ERR_ID | 0x06)
#define 	ERR_CAP_COLOR_MODE		(CAP_ERR_ID | 0x07)
#define 	ERR_CAP_FORMAT			(CAP_ERR_ID | 0x08)
#define 	ERR_CAP_FIELD			(CAP_ERR_ID | 0x09)


typedef enum tag_CAP_PLANAR_FMT{
	CAP_PLANAR_YUV444=0, 
	CAP_PLANAR_YUV422,
	CAP_PLANAR_YUV420,
	RESERVED
}E_CAP_PLANAR_FMT;
typedef enum tag_CAP_PACKET_FMT
{
	CAP_PACKET_RGB565=0, 
	CAP_PACKET_RGB555,
	CAP_PACKET_RGB444,
	CAP_PACKET_RGB332,
	CAP_PACKET_RGB565_SWAP,
	CAP_PACKET_RGB555_SWAP,
	CAP_PACKET_RGB444_SWAP,
	CAP_PACKET_RGB888,
	CAP_PACKET_YUV422
}E_CAP_PACKET_FMT;
typedef enum tag_PPF
{
	CAP_PACKET_PPF=0,
    CAP_PLANAR_PPF
}E_PPF_FLAG;
typedef enum tag_CAP_ROTATION
{
	CAP_NORMAL,
    CAP_LEFT_90,
    CAP_RIGHT_90,
    CAP_H_FLIP,
    CAP_V_FLIP,
    CAP_R_180
}E_CAP_ROTATION;
typedef enum tag_CAP_OTF
{
    CAP_LINT16=0,
    CAP_LINT32,
    CAP_LINT64,
    CAP_LINT128,
    CAP_LINT256,
    CAP_LINT512,
    CAP_LINT1024
}E_CAP_OTF;
typedef enum tag_CAP_EFF
{
    EFF_NORMAL=0,
    EFF_BLACK_WHITE,
    EFF_NEGATIVE,
    EFF_OIL_PAINTING,
    EFF_THRESHOLD
}E_CAP_EFFECT;
typedef enum tag_CAP_FIELD
{
    E_FIELD_BOTH=0,
    E_FIELD_1,
    E_FIELD_2
}E_CAP_FIELD;
typedef struct tag_CAP_DUAL_BUF_CON
{
	BOOL bIsDualBufCon;			//planar/packet dual buffer on/off
	UINT uPacBufAddr0;			//packet buffer 0
	UINT uPacBufAddr1;			//packet buffer 1
	UINT uPlaYBufAddr0;			//planar buffer 0	
	UINT uPlaUBufAddr0;
	UINT uPlaVBufAddr0;
	UINT uPlaYBufAddr1;			//planar buffer 1 address
	UINT uPlaUBufAddr1;
	UINT uPlaVBufAddr1;			
	UINT uPacMaskAddr;			//sticker maker mask pattern address
 	UINT uPlaMaskAddr;		
}T_CAP_DUAL_BUF_CON;

typedef struct tag_CAP_FLY
{
	BOOL bIsOnTheFly;		//On the fly on/off
	E_CAP_OTF eLine;	//Lines for on the fly 	
}T_CAP_FLY;

typedef struct tag_CAP_EFFECT
{
	E_CAP_EFFECT eEffect;	
	UCHAR ucPatY;	
	UCHAR ucPatU;
	UCHAR ucPatV;
	UCHAR ucYTH;				
}T_CAP_EFFECT;

typedef struct tag_CAP
{
	E_PPF_FLAG eFilterSelect;
	E_CAP_PLANAR_FMT ePlaFormat;
	E_CAP_PACKET_FMT ePacFormat;
	E_CAP_ROTATION ePlaRor;
	E_CAP_ROTATION ePacRor;
	BOOL bIsPlaSticker;	
	BOOL bIsPacSticker;
	BOOL bIsPlaEnable;
	BOOL bIsPacEnable;
	BOOL bIsInterlaceFields;
	UCHAR ucFRNumerator;
	UCHAR ucFRDenominator;	
	SHORT usPlaLineOffset;
	SHORT usPlaLineOffset_UV;
	SHORT usPacLineOffset;
	SHORT usPacLineOffset_UV;
	UINT uPlaImgWH;
	UINT uPacImgWH;
	T_CAP_DUAL_BUF_CON *pAddr;
	T_CAP_FLY *pOTF;
	T_CAP_EFFECT *pEffect;
}T_CAP_SET;

typedef struct tag_Flash_Light
{
	BOOL bIsFlasher;				//Define Flasher exist?
	BOOL bIsNonChargeLevel;		//non charge level
	USHORT usChargeLowWidth;		//
	USHORT usChargeHeightWidth;	//
	BOOL bIsNonTriggerLevel;		//non trigger level	
}T_WBCAP_FL;


#ifndef Successful  
#define	   Successful  0
#endif
#ifndef Fail
#define	   Fail        1
#endif

void capClkRatio(BOOL);
#ifdef ECOS
cyg_uint32 capIntHandler(cyg_vector_t vector, cyg_addrword_t data);
#else
void capIntHandler(void);
#endif
void capSetIRQHandler(PVOID isr);
INT capImageTransform(T_CAP_SET* ptCapSet );
#ifdef ECOS
void capInit(BOOL,BOOL, ECOS_CAP_T *);
#else
void capInit(BOOL,BOOL);
#endif

void capPlanarOut(T_CAP_SET* ptCapSet);
void capPacketOut(T_CAP_SET* ptCapSet);
INT capSetPlanarFormat(T_CAP_SET* ptCapSet);
INT capSetPacketFormat(T_CAP_SET* ptCapSet);
void capPlanarSticker(T_CAP_SET* ptCapSet);
void capPacketSticker(T_CAP_SET* ptCapSet);
INT capColorEffect(T_CAP_SET* ptCapSet);
INT capSetDdaFactor(T_CAP_SET* ptCapSet);
void capOnTheFly(T_CAP_SET* ptCapSet);
void capSetFiledCount(UINT uFiled);
void capSetBufferAddr(T_CAP_SET* ptCapSet);
UINT capFieldSelection(E_CAP_FIELD uFiledEnable);


typedef void (*PFN_CAP)(UCHAR ucPacketBufID, UCHAR ucPlanarBufID, UCHAR ucFrameRate, BOOL bFlasherOn);

//Internal
void capSkipFrame(UCHAR ucFrame);
UCHAR fin_min(UCHAR a, UCHAR b, UCHAR c, UCHAR d );
USHORT lcd(USHORT m1, USHORT m2);

void capSinglePipePolyPhaseFilter(USHORT an, USHORT bm, USHORT cn, USHORT dm, E_PPF_FLAG flag);
void factor(UINT n, UCHAR *arr);
void PlanarReSetBufferAddr(void);
void PacketReSetBufferAddr(void);
void	capSetFIFOThreshold(T_CAP_SET* ptCapSet, UINT32 uPacImgWH);

#endif //#ifdef _CAPLIB_H_